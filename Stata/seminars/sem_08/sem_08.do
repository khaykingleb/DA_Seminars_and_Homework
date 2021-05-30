version 13 // version control
clear all // cleans memory from data
set more off // cancel pauses 
capture log close // closes open log file. На самом деле 2 команды: capture + log close

cd /Users/khaykingleb/Desktop/Personal/Work/HSE/Current_Semester/Stata-Course/seminars/sem_08 // sets working directory
log using log_2.log, replace
use data.dta, clear

describe

tab year // базовый год цен в несбалансированных панельных данных (e.g. по некоторым фирмам есть данные только в 2008 и 2010 годах) — 2008.

sort id year

// Говорим, что мы работаем с панельными данными
xtset id year, yearly // в опциях указываем, что работаем с годовыми данными

* Оценка производственной функции Кобба-Дугласа на панельных данных
gen log_rva = ln(rva)
gen log_K = ln(rk)
gen log_L = ln(emp)

// Оцениваем регрессию на панельных данных
xtreg log_rva log_L log_K, fe // будем оценивать методом fixed effects

// Number of groups — сколько уникальных предприятий в данных есть 
// Obs per group: min — самое малое кол-во лет презентации фирмы в данных (какая-то фирма была представлена в выборке только единожды)
// Obs per group: max — самое максимально кол-во лет презентации фирмы в данных (какая-то фирма была представлена в выборке все 8 лет)

* Оценка транслогарифмической производственной функции
gen log_K_sq = log_K^2 
gen log_L_sq = log_L^2
gen log_K_product_log_L = log_K * log_L

xtreg log_rva log_L log_K log_L_sq log_K_sq log_K_product_log_L, fe

// Рассчитаем эластичности
matrix list e(b)

gen elasticity_yk = _b[log_K] + 2 * _b[log_K_sq] * log_K + _b[log_K_product_log_L] * log_L
gen elasticity_yl = _b[log_L] + 2 * _b[log_L_sq] * log_L + _b[log_K_product_log_L] * log_K 

sum elasticity_yk elasticity_yl

tab year, sum(elasticity_yk)
tab year, sum(elasticity_yl)

by year, sort: sum elasticity_yk
by year, sort: sum elasticity_yl

// Рассчитаем отдачу от масштаба 
gen rts = elasticity_yk + elasticity_yl

// Проверим гипотезу о постоянной отдаче от масштаба
ttest rts == 1 if year == 2009

* Посчитаем TPF (Total Factor Productivity)
sort id year
// Сначала посчитаем прирост труда и капитала
// Будем аппроксимировать прирост разницей логарифмов
// Для этого вводим оператор лага
gen drva = log_rva - l.log_rva
gen dk = log_K - l.log_K
gen dl = log_L - l.log_L 
gen avg_elasticity_yk = (elasticity_yk + l.elasticity_yk) / 2
gen avg_elasticity_yl = (elasticity_yl + l.elasticity_yl) / 2

// Считаем TFP
gen tfp = drva - avg_elasticity_yk * dk - avg_elasticity_yl * dl

// Строим таблицы со средними и средневзвешенными показателями роста TFP
tabstat tfp, by(year) statistics(n mean) 
tabstat tfp [w=rva], by(year) statistics(n mean) // значит, крупные фирмы намного лучше пережили кризисы 2008 и 2014 годов, нежели средние по выборке фирмы. Много фирм с отрицательным ростом, но они мелкие

// Графики
graph bar tfp if year >= 2009, over(year) name(gr1, replace) ///
ytitle("%")	blabel (bar, position(outside) format(%9.2f)) ///
title("Average TFP growth rates", size(medium))

graph bar tfp[w=rva] if year >= 2009, over(year) name(gr1, replace) ///
ytitle("%")	blabel (bar, position(outside) format(%9.2f)) ///
title("Average TFP growth rates", size(medium))

* Labor productivity
gen labor_productivity = rva / emp
egen max_labor_productivity = max(labor_productivity), by(year)
gen labor_productivity_gap = labor_productivity / max_labor_productivity

tabstat labor_productivity_gap, by(year) statistics(n mean sd median min max p90)

hist labor_productivity_gap if year == 2008, bin(100)
hist labor_productivity_gap if year == 2015, bin(100)

// Делаем ядерную оценку плотности
twoway (kdensity labor_productivity_gap if year == 2008, lpattern(dash)) (kdensity labor_productivity_gap if year == 2015), ///
legend(order(1 "2008" 2 "2015")) scheme(s1mono) ytitle("") xtitle("") ///
title("Labor productivity gap", size(medium))
// Видим, что большая доля предприятий оказывается неэффективной (но они мелкие)
// Они не растут, но не уходят с рынка

// Графики
egen lpg90 = pctile(labor_productivity_gap), p(90) by(year)
gen dummy_lpg90 = (labor_productivity_gap >= lpg90) if labor_productivity_gap != .

tabstat tfp if dummy_lpg90 == 1, by(year) statistics(n mean)
tabstat tfp if dummy_lpg90 == 0, by(year) statistics(n mean)

graph bar tfp if year >= 2009 &	dummy_lpg90 == 1, over(year) ///
ytitle("%") blabel (bar, position(outside) format(%9.2f)) ylabel(-0.3(0.1)0.3) ///
title("Average TFP growth rates	(top 10%)",	size(medium))	

graph bar tfp if year >= 2009	& dummy_lpg90 == 0, over(year) ///
ytitle("%")	blabel (bar, position(outside) format(%9.2f)) ylabel(-0.3(0.1)0.3) ///
title("Average TFP growth rates	(other)", size(medium))

// Накопленные темпы роста
preserve
collapse tfp, by(year)
rename tfp tfp_avg
save tfp_avg, replace
restore

preserve
collapse tfp[w=rva], by(year)
rename tfp tfp_wavg
save tfp_wavg, replace
restore

preserve
collapse tfp if dummy_lpg90 == 1, by(year)
rename tfp tfp_top
save tfp_top, replace
restore

preserve
collapse tfp if dummy_lpg90 == 0, by(year)
rename tfp tfp_other
save tfp_other, replace
restore

clear 

use tfp_avg
merge 1:1 year using tfp_wavg
drop _merge
merge 1:1 year using tfp_top
drop _merge
merge 1:1 year using tfp_other
drop _merge

sort year 
gen tfp_top_ac = 1 if year == 2008
replace tfp_top_ac = tfp_top_ac[_n - 1] * (tfp_top[_n] + 1) if year >= 2009
replace tfp_top_ac = tfp_top_ac * 100
label var tfp_top_ac "Top 10%"

sort year 
gen tfp_other_ac = 1 if year == 2008
replace tfp_other_ac = tfp_other_ac[_n - 1] * (tfp_other[_n] + 1) if year >= 2009
replace tfp_other_ac = tfp_other_ac * 100
label var tfp_other_ac "Other"

sort year
gen tfp_avg_ac = 1 if year == 2008
replace tfp_avg_ac = tfp_avg_ac[_n - 1] * (tfp_avg[_n] + 1) if year >= 2009
replace tfp_avg_ac = tfp_avg_ac * 100
label var tfp_avg_ac "All firms (average)"

sort year
gen tfp_wavg_ac = 1 if year == 2008
replace tfp_wavg_ac = tfp_wavg_ac[_n - 1] * (tfp_wavg[_n] + 1) if year >= 2009
replace tfp_wavg_ac = tfp_wavg_ac * 100
label var tfp_wavg_ac "All firms (weighted average)"

list year tfp_avg_ac tfp_wavg_ac tfp_top_ac tfp_other_ac

twoway connected tfp_top_ac tfp_avg_ac tfp_wavg_ac tfp_other_ac year, ///
xtitle("") xlabel(2008(1)2015, angle(45) labsize(small)) ///
yline(100) ///
ytitle("%") ylabel(0(50)200, labsize(small)) ///
legend(row(4) order(1 2 3 4) size(small)) ///
title("Cumulative growth rates", size(medium))

erase tfp_avg.dta
erase tfp_wavg.dta
erase tfp_top.dta
erase tfp_other.dta

