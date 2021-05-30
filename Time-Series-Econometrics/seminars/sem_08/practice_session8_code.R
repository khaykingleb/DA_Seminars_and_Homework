library(tidyverse)
library(forecast)


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

## PACF for a series in levels and differences

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

# ARIMA representation

y <- arima.sim(model = list(ar = c(1.3,  -0.4),
                            order = c(2,1,0)), n = 1000)
plot(y)
ggAcf(y)
ggPacf(y)

 ##ADF-test

 library(tseries)
 adf.test(y3, k = 10)


##urca:: ur.df function: output

library(urca)
urtest1 <- ur.df(y3, lags = 10, type = 'trend')
summary(urtest1)
