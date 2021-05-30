library(tidyverse)
## TS class
rus_data <- read_csv("rus_data.csv")
class(rus_data)
rus_data <- select(rus_data, -time)
rus_data_ts <- ts(rus_data, start = c(1995, 1), freq = 12)
class(rus_data_ts)

## ARMA models: simulation
#Simulating AR(1) model
ar1 <- arima.sim(model = list(ar = 0.8, order = c(1,0,0)), n = 200)
#Simulating ARMA(1,1) model
arma11 <- arima.sim(model = list(ar = 0.4, ma = 0.5,order = c(1,0,1)), n = 200)
#Simulating MA(2) model
ma2 <- arima.sim(model = list(ma = c(0.5, -0.3), order = c(0,0,2)), n = 200)

## ARMA models: packages
install.packages("forecast")
library(forecast)

## Time series visualisation
autoplot(cbind(ar1, arma11,ma2), facets = TRUE) + ylab('')

## ACF and PACF for AR(1) model
ggAcf(ar1)
ggPacf(ar1)

## ACF and PACF for MA(2)
ggAcf(ma2)
ggPacf(ma2)

## ACF and PACF for ARMA(1,1)
ggAcf(arma11)
ggPacf(arma11)

## White noise
wn <- arima.sim(model = list(order = c(0,0,0)), n = 200)
ggAcf(wn)
ggPacf(wn)

## US investment growth: importing and plotting data 
US_inv <- read_csv("US_investment.dat")
US_inv_ts <- ts(US_inv, start = c(1947, 2), freq = 4)
autoplot(US_inv_ts) + ylab("") + ggtitle("US investment growth")

## ACF and PACF for US investment growth 
ggAcf(US_inv_ts) + ggtitle("US investment growth")
ggPacf(US_inv_ts) + ggtitle("US investment growth")

## Ljung - Box test for US investment growth series 
Box.test(US_inv_ts, lag = 24, fitdf = 0, type = "Lj")

 ## Estimaton(1) 
Arima(US_inv_ts, order = c(2,0,3), include.constant = TRUE)

## Estimaton(3) 
Arima(US_inv_ts, order = c(4,0,4), include.constant = TRUE)
Arima(US_inv_ts, order = c(5,0,5), include.constant = TRUE)

## Lag order choice
model1 <- Arima(US_inv_ts, order = c(5,0,5), 
                include.constant = TRUE)
model1$aic
model1$aicc
model1$bic

## Automatic ARIMA
auto.arima(US_inv_ts, d = 0, seasonal = FALSE)

