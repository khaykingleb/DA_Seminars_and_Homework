library(tidyverse)
library(forecast)
library(lattice)
library(gridExtra)
library(urca)
library(readxl)
library(vars)
library(matrixcalc)

## Data graphs 
money_demand_germany <- read_excel("money_demand_germany.xlsx")
gd_ts <- ts(money_demand_germany, start = c(1975, 1), frequency = 4)
plotR <- autoplot(gd_ts[,"r"]) + ggtitle("Nominal LT interest rate")
plotY <- autoplot(gd_ts[,"y"]) + ggtitle("Real GNP (in logs)")
grid.arrange(plotR, plotY, ncol = 2)   
plotM <- autoplot(gd_ts[,"m"]) + ggtitle("Real M3(in logs)")
plotM

## Autocorrelation functions
plotR_acf <- ggAcf(gd_ts[,"r"]) + ggtitle("ACF for interest rate")
plotY_acf <- ggAcf(gd_ts[,"y"]) + ggtitle("ACF for GNP")
grid.arrange(plotR_acf, plotY_acf, ncol = 2)  
plotM_acf <- ggAcf(gd_ts[,"m"]) + ggtitle("ACF for M3")
plotM_acf

## Partial autocorrelation functions
plotR_pacf <- ggPacf(gd_ts[,"r"]) + ggtitle("PACF for interest rate")
plotY_pacf <- ggPacf(gd_ts[,"y"]) + ggtitle("PACF for GNP")
grid.arrange(plotR_pacf, plotY_pacf, ncol = 2) 
plotM_pacf <- ggPacf(gd_ts[,"m"]) + ggtitle("PACF for M3")
plotM_pacf

## ADF tests 
adf_r <- ur.df(gd_ts[,"r"], type = "drift",lags = 8, selectlags = "BIC")
summary(adf_r)
adf_dr <- ur.df(diff(gd_ts[,"r"]), type = "none",lags = 8, selectlags = "BIC")
summary(adf_dr)


## Determining the cointegration rank
unif_dum = rep(0, 96)

unif_dum[63] = 1
VARselect(gd_ts, lag.max = 10, type =  "both",
          season = 4, exogen = unif_dum)$select
coint_h1 <- ca.jo(gd_ts, type = "trace", K = 2, 
                  spec = "transitory", season = 4, 
                  dumvar = unif_dum)
coint_h2 <- ca.jo(gd_ts, type = "eigen", K = 2, 
                  spec = "transitory", season = 4, 
                  dumvar = unif_dum)
summary(coint_h1)
summary(coint_h2)

## Eigenvectors and cointegration relations
coint_h2@V

## Error correction term
ec = gd_ts[,"m"] + coint_h2@V[2,1]*gd_ts[,"y"] +
  coint_h2@V[3,1]*gd_ts[,"r"]
plot_ec <- autoplot(ec) + ggtitle("Error correction term")
acf_ec <- ggAcf(ec)
grid.arrange(plot_ec, acf_ec, ncol = 2 )

## Unit root and stationarity tests for $EC_t$
adf_ec <- ur.df(ec, type = "drift",lags = 8, selectlags = "BIC")
summary(adf_ec)

kpss_ec <- ur.kpss(ec, type = "mu",lags = "short")
summary(kpss_ec)

## Matrix decomposition
alpha_m <- coint_h2@W[,1] # Loading matrix 
alpha_m 
beta_m <- coint_h2@V[,1] # Cointegration matrix 
beta_m
pi_m <- alpha_m %*% t(beta_m)
pi_m
matrix.rank(pi_m)

## VECM estimation
gd_vecm <- cajorls(coint_h2, r = 1) 
gd_var <- vec2var(coint_h2, r = 1) 
gd_var2 <- VAR(gd_ts, p = 2, type = "const", 
               season = 4, exogen = unif_dum)

## Graph of residuals:  m - equation
res1_m <- ts(residuals(gd_var)[,1], start = c(1975, 3), frequency = 4)
res2_m <- ts(residuals(gd_var2)[,1], start = c(1975, 3), frequency = 4)
autoplot(cbind(res1_m,res2_m))

## Graph of residuals:  y - equation
res1_y <- ts(residuals(gd_var)[,2], start = c(1975, 3), frequency = 4)
res2_y <- ts(residuals(gd_var2)[,2], start = c(1975, 3), frequency = 4)
autoplot(cbind(res1_y,res2_y))

## Graph of residuals:  r - equation
res1_r <- ts(residuals(gd_var)[,3], start = c(1975, 3), frequency = 4)
res2_r <- ts(residuals(gd_var2)[,3], start = c(1975, 3), frequency = 4)
autoplot(cbind(res1_r,res2_r))
