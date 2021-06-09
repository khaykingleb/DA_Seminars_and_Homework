library("readxl") # чтение excel-файла
library("tidyverse") # коллекция пакетов: ggplot2, dplyr, etc.
library("knitr") # создание отчётов

library("forecast") # прогнозирование временных рядов: ARMA и ETS модели
library("xts") # операции с временными рядами

library("tseries")

library("repr") # отрегулируем размер картинок
options(repr.plot.width=10, repr.plot.height=8)

df <- read_excel("data.xlsx")
head(df)

df$log_taxes = log(df$taxes)
df$log_gdp = log(df$gdp)

log_gdp_ts <- ts(df$log_gdp, start = c(2011, 1), freq = 4)
log_gdp_ts

log_taxes_ts <- ts(df$log_taxes, start = c(2011, 1), freq = 4)
log_taxes_ts

ggplot(data=df, aes(x = date, y = log_gdp))+
  geom_line(color = "#00AFBB", size = 1) + 
    labs(x = "Data",
         y = "GDP in logarithmic scale", 
         color = "") +
    theme_minimal() + 
    ggtitle("GDP by Quarter") + 
    theme(text = element_text(size=18))

decomp <- decompose(log_gdp_ts)
plot(decomp)

ggplot(data = df, aes(x = date, y = log_taxes))+
  geom_line(color = "#00AFBB", size = 1) + 
    labs(x = "Data",
         y = "Taxes in logarithmic scale", 
         color = "") +
    theme_minimal() + 
    ggtitle("Taxes by Quarter") + 
    theme(text = element_text(size=18))

decomp <- decompose(log_taxes_ts)
plot(decomp)

par(mfrow = c(3, 1), mar = c(3, 3, 2, 1), mgp = c(2, 0.6, 0), oma = c(0, 0, 0, 0))
plot(log_gdp_ts, ylab="GDP, log scale"); 
acf(log_gdp_ts, lag.max = 40, main=""); 
pacf(log_gdp_ts, lag.max = 40, main="")

par(mfrow = c(3, 1), mar = c(3, 3, 2, 1), mgp = c(2, 0.6, 0), oma = c(0, 0, 0, 0))
plot(log_taxes_ts, ylab="Taxes, log scale"); 
acf(log_taxes_ts, lag.max = 40, main=""); 
pacf(log_taxes_ts, lag.max = 40, main="")

adf.test(log_gdp_ts)

adf.test(log_taxes_ts)

kpss.test(log_gdp_ts)

kpss.test(log_taxes_ts)

nsdiffs(log_gdp_ts)

log_gdp_ts_seasdiff <- diff(log_gdp_ts, lag=4, differences=1)
plot(log_gdp_ts_seasdiff, type="l", main="Seasonally Differenced", ylab="GDP, log scale")

ndiffs(log_gdp_ts_seasdiff)

nsdiffs(log_taxes_ts)

log_taxes_ts_seasdiff <- diff(log_taxes_ts, lag=4, differences=1)
plot(log_taxes_ts_seasdiff, type="l", main="Seasonally Differenced", ylab="Taxes, log scale")

nsdiffs(log_taxes_ts_seasdiff)

par(mfrow = c(3, 1), mar = c(3, 3, 2, 1), mgp = c(2, 0.6, 0), oma = c(0, 0, 0, 0))
plot(log_gdp_ts_seasdiff, ylab="Seasonally Differenced GDP, log scale"); 
acf(log_gdp_ts_seasdiff, lag.max = 40, main=""); 
pacf(log_gdp_ts_seasdiff, lag.max = 40, main="")

arima100_gdp <- Arima(log_gdp_ts_seasdiff, order = c(1, 0, 0), include.constant = TRUE)
summary(arima100_gdp)

arima102_gdp <- Arima(log_gdp_ts_seasdiff, order = c(1, 0, 2), include.constant = TRUE)
summary(arima102_gdp)

arima002_gdp <- Arima(log_gdp_ts_seasdiff, order = c(0, 0, 2), include.constant = TRUE)
summary(arima002_gdp)

par(mfrow = c(3, 1), mar = c(3, 3, 2, 1), mgp = c(2, 0.6, 0), oma = c(0, 0, 0, 0))
plot(log_taxes_ts_seasdiff, ylab="Seasonally Differenced Taxes, log scale"); 
acf(log_taxes_ts_seasdiff, lag.max = 40, main=""); 
pacf(log_taxes_ts_seasdiff, lag.max = 40, main="")

arima100_taxes <- Arima(log_taxes_ts_seasdiff, order = c(1, 0, 0), include.constant = TRUE)
summary(arima100_taxes)

arima102_taxes <- Arima(log_taxes_ts_seasdiff, order = c(1, 0, 2), include.constant = TRUE)
summary(arima102_taxes)

arima002_taxes <- Arima(log_taxes_ts_seasdiff, order = c(0, 0, 2), include.constant = TRUE)
summary(arima002_taxes)

c(arima100_gdp$aic, arima102_gdp$aic, arima002_gdp$aic)

c(arima100_gdp$bic, arima102_gdp$bic, arima002_gdp$bic)

# Используем ARIMA(1,0,0)(0,1,0)[4] для исходного нестационарного ряда, чтобы именно для него получить прогнозы
sarima110_gdp <- Arima(log_gdp_ts, order = c(1, 1, 0), seasonal=c(0, 1, 0), include.constant = TRUE)
future <- forecast(sarima110_gdp, h = 4)
autoplot(future, main="ARIMA(1, 1, 0)", ylab="Seasonally Differenced GDP, log scale")

sarima110_gdp$coef

c(arima100_taxes$aic, arima102_taxes$aic, arima002_taxes$aic)

c(arima100_taxes$bic, arima102_taxes$bic, arima002_taxes$bic)

# Используем ARIMA(1,0,0)(0,1,0)[4] для исходного нестационарного ряда, чтобы именно для него получить прогнозы
sarima110_taxes <- Arima(log_taxes_ts, order = c(1, 1, 0), seasonal=c(0, 1, 0), include.constant = TRUE)
future <- forecast(sarima110_taxes, h = 4)
autoplot(future, main="ARMA(1,0)", ylab="Seasonally Differenced Taxes, log scale")

sarima110_taxes$coef

resid_sarima110_gdp <- resid(sarima110_gdp)
Box.test(resid_sarima110_gdp, lag = 8, type = "Ljung-Box", fitdf=1)

resid_sarima110_taxes <- resid(sarima110_taxes)
Box.test(resid_sarima110_taxes, lag = 8, type = "Ljung-Box", fitdf=1)

lr <- lm(diff(log_gdp) ~ diff(log_taxes), data = df)
lr_res_ts <- ts(residuals(lr), freq = 4)

par(mfrow = c(3, 1), mar = c(3, 3, 2, 1), mgp = c(2, 0.6, 0), oma = c(0, 0, 0, 0))
plot(lr_res_ts, ylab="Residuals"); 
acf(lr_res_ts, lag.max = 40, main=""); 
pacf(lr_res_ts, lag.max = 40, main="")

adf.test(lr_res_ts)
