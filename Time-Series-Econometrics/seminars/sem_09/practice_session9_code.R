library(tidyverse)
library(forecast)
library(gridExtra)
library(urca)
library(tseries)
## Simulated series

y3 <- arima.sim(model = list(ar = c(1.3,  -0.4),
                             order = c(2,1,0)), n = 1000)
autoplot(y3) + ylab("") + ggtitle("Simulated series")


 ##ADF-test
library(tseries)
adf.test(y3, k = 10)


##urca:: ur.df function: output
library(urca)
urtest1 <- ur.df(y3, lags = 10, type = 'trend')
summary(urtest1)

## AR order choice
ur.df(y3, type = 'trend', lags = 12, selectlags = "BIC")

## Unit root testing:example
empl_manuf <- read_csv("empl_manuf.csv")
empl <- ts(empl_manuf, start = c(1992, 1), freq = 12)
plot1 <- autoplot(empl) + ggtitle("Employment in manufacturing") +
  ylab("")
plot2 <- autoplot(diff(empl)) +
  ggtitle("Change in employment in manufacturing") + ylab("")
grid.arrange(plot1, plot2, nrow = 1)

##  Unit root testing:example(2)

model1 <- ur.df(diff(empl,differences = 2), type = "none",
                lags = 6, selectlags = "BIC")
summary(model1)

##  Unit root testing:example(3)
model2 <- ur.df(diff(empl,1), type = "drift",
                lags = 6, selectlags = "BIC")
summary(model2)

## tseries:: kpss.test

kpss.test(y3, null = "Trend", lshort =TRUE)

## urca:: ur.kpss
kpss_y3 <- ur.kpss(y3, type = "tau", lags = "short")
summary(kpss_y3)

## KPSS test for a real series (1)

kpss_empl0 <- ur.kpss(empl, type = "tau", lags = "long")
summary(kpss_empl0)


## KPSS test for a real series (2)
kpss_empl1 <- ur.kpss(diff(empl), type = "mu", 
                      lags = "long")
summary(kpss_empl1)


## KPSS test for a real series (3)
kpss_empl2 <- ur.kpss(diff(diff(empl)), type = "mu", 
                      lags = "long")
summary(kpss_empl2)


## Example with Seasonal ARIMA
autoplot(empl)
autoplot(diff(empl))
ggAcf(diff(empl))
autoplot(diff(diff(empl)))
ggAcf(diff(diff(empl)))
ggPacf(diff(diff(empl)))  
fit1 <- Arima(empl, order = c(3,2,4), seasonal = c(0,0,1))          
summary(fit1)
autoplot(residuals(fit1))
ggAcf(residuals(fit1))
ggPacf(residuals(fit1))
ur_test1 <- ur.df(diff(diff(empl)), type = "none",
                  lags = 12, selectlags = "BIC")
summary(ur_test1)
kpss_test1 <- ur.kpss(diff(diff(empl)))
summary(kpss_test1)
Box.test(residuals(fit1), lag = 24, fitdf = 8, type = 'Ljung')
jarque.bera.test(residuals(fit1))
autoplot(forecast(fit1, h = 24)) + ylab("")

autoplot(empl)         
fit2 <- auto.arima(empl)         
summary(fit2)
autoplot(residuals(fit2))
ggAcf(residuals(fit2))
ggPacf(residuals(fit2))
ur_test1 <- ur.df(diff(diff(empl)), type = "none",
                  lags = 12, selectlags = "BIC")
summary(ur_test1)
kpss_test1 <- ur.kpss(diff(diff(empl)))
summary(kpss_test1)
Box.test(residuals(fit2), lag = 24, fitdf = 6, type = 'Ljung')
jarque.bera.test(residuals(fit2))
autoplot(forecast(fit2, h = 24)) + ylab("")

## Example: code
set.seed(500)
y4 <- arima.sim(model = list(order = c(4,1,4), ar = c(0.3, -0.4,0,-0.2), ma = c(0.8,0,0,0.5), mean = 2),
                n = 300)
for1 <- meanf(y4, h = 50)
for2 <- naive(y4, h = 50)
for3 <- rwf(y4, drift = TRUE, h = 50)
plot(y4, xlim = c(1,350))
lines(for1$mean,col = 4)
lines(for2$mean, col = 2)
lines(for3$mean, col = 3)
legend("bottomleft",lty=1,col=c(4,2,3),
       legend=c("Mean method","Naive method","Drift method"))


## Simple forecasts: an alternative code
fit1 <- Arima(y4, order = c(0,0,0), include.constant = TRUE)
fit2 <- Arima(y4, order = c(0,1,0))
fit3 <- Arima(y4, order = c(0,1,0), include.drift = TRUE)
fore1 <- forecast(fit1, h = 24)
fore2 <- forecast(fit2, h = 24)
fore3 <- forecast(fit3, h = 24)
plot(y4, xlim = c(1,350))
lines(fore1$mean, col = 4)
lines(fore2$mean, col = 2)
lines(fore3$mean, col = 3)
legend("bottomleft",lty = 1,col=c(4,2,3),
       legend = c("WN+const","RW","RW with drift"))



## Application: a nominal exchange rate

ner <- read_csv("nominal_ER1.csv")
ner <- ts(ner, start = c(1994, 10), freq = 12)
train <- subset(ner, end = length(ner) - 24)
autoplot(train)
autoplot(diff(train))
adf_ner <- ur.df(diff(ner), lags = 12, selectlags = 'BIC', type = 'drift')
summary(adf_ner)
kpss_ner <-ur.kpss(diff(ner),type = "mu", lags = 'long')
summary(kpss_ner)
ggAcf(diff(train))
ggPacf(diff(train))
a <- rep(0, times = 16)
A <- matrix(a, nrow = 4)
for (i in 1:4) {
  for (j in 1:4) {
    model <-  Arima(train, order = c(i-1,1,j-1), include.drift = TRUE)
    A[i,j] <- model$aicc
  }
}
A
fit_ner <- Arima(train, order = c(3,1,3), include.drift = TRUE)
autoplot(residuals(fit_ner))
ggAcf(residuals(fit_ner))
ggPacf(residuals(fit_ner))

Box.test(residuals(fit_ner), lag = 24, fitdf = 4, type = 'Ljung')
jarque.bera.test(residuals(fit_ner))
fore_arima <- forecast(fit_ner, h = 24)
autoplot(fore_arima) + ylab("")
fore_rw <- rwf(train, h = 24)
fore_rwd <- rwf(train, drift = TRUE, h = 24)
accuracy(fore_arima, ner)
accuracy(fore_rw, ner)
accuracy(fore_rwd, ner)
f_arima_ts <- fore_arima$mean
f_rw_ts <- fore_rw$mean
f_rwd_ts <- fore_rwd$mean
all_ts <- ts.union(ner, f_arima_ts, f_rw_ts, f_rwd_ts )
autoplot(all_ts)

## Cross-validation example 
fore_arima_212 <- function(y, h) {
  model <- Arima(y, order = c(2, 1, 2), 
                 include.drift = TRUE)
  forecast <- forecast(model, h)
  return(forecast)
}
errors_cv <- tsCV(ner, fore_arima_212, h = 1)
errors_cv


