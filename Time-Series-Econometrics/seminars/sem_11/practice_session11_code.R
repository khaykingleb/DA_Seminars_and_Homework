
## VAR estimation: example
library(fpp)
library(vars)
data(usconsumption, package = "fpp")
head(usconsumption)
VARselect(usconsumption, lag.max=7, type = "const")

## VAR estimation: example(3)
VARselect(usconsumption, lag.max = 7, type = "const")$selection

## VAR estimation: example(4)
var1 <- VAR(usconsumption, p = 1, type = "const")
summary(var1)

## Autocorrelation tests: code 
serial.test(var1, lags.pt = 10, type = "PT.asymptotic")
serial.test(var1, lags.pt = 10, type = "PT.adjusted")
serial.test(var1, lags.pt = 10, type = "BG")

## Autocorrelation tests: example
var2 <- VAR(usconsumption, p = 2, type = "const")
serial.test(var2, lags.pt = 10, type = "PT.asymptotic")
serial.test(var2, lags.pt = 10, type = "BG")
var3 <- VAR(usconsumption, p = 3, type = "const")
serial.test(var3, lags.pt = 10, type = "PT.asymptotic")
serial.test(var3, lags.pt = 10, type = "BG")
var4 <- VAR(usconsumption, p = 4, type = "const")
serial.test(var4, lags.pt = 10, type = "PT.asymptotic")
serial.test(var4, lags.pt = 10, type = "BG")

## Test for non-normality: code
normality.test(var3, multivariate.only = FALSE)

## Forecasting: code and values
var_fcst <- forecast(var3, h = 8)
var_fcst$forecast$consumption$mean
var_fcst$forecast$income$mean

## Granger Causality: testing
autoplot(var_fcst)
causality(var3, 'consumption')
causality(var3, 'income')

    
