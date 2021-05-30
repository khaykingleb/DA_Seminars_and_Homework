library(tidyverse)
library(forecast)
library(lattice)
library(gridExtra)
library(urca)
library(readxl)
library(vars)
library(matrixcalc)



## Example:Uhlig(2005)
library(VARsignR)
data(uhligdata)

## Constraints and estimation
constr <- c(+4,-3,-2,-5)
model1 <- uhlig.reject(Y = uhligdata, nlags = 12, 
                       nkeep = 1000, KMIN = 1, 
                       KMAX = 6, constrained = constr,
                       constant = FALSE, steps = 60)

## Impulse response functions 
irfs1 <- model1$IRFS
vl <- c("GDP","GDP Deflator","Comm.Pr.Index",
        "Fed Funds Rate", "NB Reserves", "Total Reserves")
irfplot(irfdraws = irfs1, type = "median", labels = vl, 
        save = FALSE, bands = c(0.16, 0.84), grid = TRUE,
        bw = FALSE)

## Forward error variance decomposition 

fevd1 <- model1$FEVDS
fevd.table <- fevdplot(fevd1, table = TRUE, label = vl, 
                       periods = c(1,10,20,30,40,50,60))
print(fevd.table)


## Cointegration: idea(2)

T <- 200
u2 <- rnorm(T, mean = 0, sd = 2)
u3 <- rnorm(T, mean = 0, sd = 3)
r1 <- arima.sim(n = T - 1, model = list(order = c(1,1,0), ar = 0.6))
r2 <- 3 + 0.8*r1 + u2
r3 <- -4 + 1.2*r1 + u3
all_r <- tibble(r1 = r1, r2 = r2, r3 = r3, time = 1:T)

## Cointegration: idea(3)
plot2d <- autoplot(cbind(r1,r2,r3))
plot3d <- cloud(data = all_r, r3 ~ r1 * r2)
grid.arrange(plot2d, plot3d, ncol = 2, top = "Cointegrated I(1) series")

