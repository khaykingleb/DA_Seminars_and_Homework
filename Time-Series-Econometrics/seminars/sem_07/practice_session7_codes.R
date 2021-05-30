library(forecast)
library(tidyverse)
library(tseries)
library(gridExtra)

## Preliminary transformation
invest_index <- read_csv("invest_index.csv")
invest <- ts(invest_index, start = c(1994, 1), freq = 12)
autoplot(invest) + ggtitle("Investment index")

## Transformed series
plot1 <- autoplot(sqrt(invest)) + ylab("")+
ggtitle("Square root of monthly investment index")
plot2 <- autoplot(invest^(1/3)) + ylab("")+
  ggtitle("Cube root of monthly investment index")
plot3 <- autoplot(log(invest)) + ylab("")+
  ggtitle("Log of monthly investment index")
plot4 <- autoplot(invest^(-1)) + ylab("")+
  ggtitle("Inverse of monthly investment index")
grid.arrange(plot1, plot2, plot3, plot4, nrow = 2)


 ## Box-Cox transformation: code
plot1 <- autoplot(log(invest))+ylab("")
plot2 <- autoplot(BoxCox(invest, lambda = 0))+ylab("")
grid.arrange(plot1, plot2, ncol = 2)

## Portmanteau test: code
y <- arima.sim(model = list(ar = c(0.5,  0.4), ma = 0.4, 
                            order = c(2,0,1), mean = 3), n = 200)
fit <- Arima(y,order = c(2,0,1), include.constant = TRUE)
ggAcf(residuals(fit))
Box.test(residuals(fit), lag = 24, fitdf = 3, type = 'Ljung')

## Forecasts:example
y <- arima.sim(model = list(ar = c(0.4,  0.5), ma = 0.4, 
                            order = c(2,0,1), mean = 3), 
               n = 200)
fit <- Arima(y,order = c(2,0,1), include.constant = TRUE)

##Forecasts: code(1) 
forecast(fit, h = 12, level = 95)
autoplot(forecast(fit, h=24)) + ylab("")

 ## Test for nonnormality: code 
jarque.bera.test(residuals(fit))

## Accuracy measures:code
US_inv <- read_csv("US_investment.dat")
US_inv_ts <- ts(US_inv, start = c(1947, 2), freq = 4)
train = window(US_inv_ts, end = c(1969,4))
fit1 <- Arima(train, order = c(4,0,4))
fore1 <- forecast(fit1, h = 12)
fit2 <- auto.arima(train, d = 0, seasonal = FALSE)
fore2 <- forecast(fit2, h = 12)
options(digits = 3)
accuracy(fore1, US_inv_ts)
accuracy(fore2, US_inv_ts)


## Trends in economic time series
empl_manuf <- read_csv("empl_manuf.csv")
empl <- ts(empl_manuf, start = c(1992, 1), freq = 12)
autoplot(empl)+ylab("") + ggtitle("Employment in Manufacturing")


## Simulations: code
bet0 = 0.1
bet1 = 0.2
mu = 0.3
y1 = rep(0,times = 200)
y2 = rep(0,times = 200)
eps = rnorm(200)
nu = rnorm(200)
for (i in 2:200) {
  y2[i] = mu +  y2[i - 1] + nu[i]
}
t = 1:200
y1 = bet0 + bet1*t + eps
par(mfrow = c(1,2))
plot(t,y1, type = "l", main = "Trend stationary")
plot(t,y2, type = "l", main = "Difference stationary")

##Alternative simulation: code
library(gridExtra)
bet0 <- 0.1
bet1 <- 0.2
mu <- 0.3
y1 <- arima.sim(model = list(order = c(0,0,0)), n = 200, mean = bet0)
y1 <- y1 + bet1*(1:200)
y2 <- arima.sim(model = list(order = c(0,1,0)), n = 200, mean = mu)
plot1 <- autoplot(y1) + ggtitle("Trend stationary")
plot2 <- autoplot(y2) + ggtitle("Difference stationary")
grid.arrange(plot1, plot2, ncol = 2)

## ACF and PACF for a TS process
grid.arrange(ggAcf(y1), ggPacf(y1), nrow = 2)

## ACF and PACF for a DS process
grid.arrange(ggAcf(y2), ggPacf(y2), nrow=2)

## ACF for a series in levels and differences

plot1 <- autoplot(empl) + ggtitle("Employment in manufacturing") + ylab("")
plot2 <- ggAcf(empl) + ggtitle("")
plot3 <- autoplot(diff(empl)) + ggtitle("Change in employment in manufacturing") + ylab("")
plot4 <- ggAcf(diff(empl)) + ggtitle("")
grid.arrange(plot1, plot2, plot3, plot4, nrow = 2)

### PACF for a series in levels and differences

plot1 <- autoplot(empl) + ggtitle("Employment in manufacturing") + ylab("")
plot2 <- ggPacf(empl) + ggtitle("")
plot3 <- autoplot(diff(empl)) + ggtitle("Change in employment in manufacturing") + ylab("")
plot4 <- ggPacf(diff(empl)) + ggtitle("")
grid.arrange(plot1, plot2, plot3, plot4, nrow = 2)


## Seasonal differencing
invest_index <- read_csv("invest_index.csv")
invest <- ts(invest_index, start = c(1994, 1), freq = 12)
plot1 <- autoplot(invest) + ggtitle("Investment index")
plot2 <- autoplot(diff(invest,12)) +
  ggtitle("Annual change in monthly investment index")
grid.arrange(plot1, plot2, nrow = 2)


##Simulated series
phi1 <- 2.3
phi2 <- -1.7
phi3 <- 0.4
y3 <- rep(0,times = 1003)
nu <- rnorm(1003)
for (i in 4:1003) {
  y3[i] <- phi1*y3[i - 1] + phi2*y3[i - 2] + phi3*y3[i - 3] + nu[i]
}
y3 <- y3[-(1:3)]
t <- 1:1000
y3 <- ts(y3)
autoplot(y3) + ylab("") + ggtitle("Simulated series")

## ACF and PACF for the simulated series
plot1 <- ggAcf(y3) + ggtitle("")
plot2 <- ggPacf(y3) + ggtitle("")
grid.arrange(plot1, plot2, nrow = 2)

## ARIMA representation

y <- arima.sim(model = list(ar = c(1.3,  -0.4),
                            order = c(2,1,0)), n = 1000)
plot(y)
ggAcf(y)
ggPacf(y)

# ##ADF-test

library(tseries)
adf.test(y3, k = 10)


# ##urca:: ur.df function: output
#
# library(urca)
# urtest1 <- ur.df(y3, lags = 10, type = 'trend')
# summary(urtest1)

# ## AR order choice
# ur.df(y3, type = 'trend', lags = 12, selectlags = "BIC")

# ## Unit root testing:example
#
# plot1 <- autoplot(empl) + ggtitle("Employment in manufacturing") +
#   ylab("")
# plot3 <- autoplot(diff(empl)) +
#   ggtitle("Change in employment in manufacturing") + ylab("")
# grid.arrange(plot1, plot3, nrow = 1)

# ##  Unit root testing:example(2)
#
# model1 <- ur.df(diff(empl,2), type = "none",
#                 lags = 6, selectlags = "BIC")
# summary(model1)

# ##  Unit root testing:example(3)
#
# model2 <- ur.df(diff(empl,1), type = "drift",
#                 lags = 6, selectlags = "BIC")

