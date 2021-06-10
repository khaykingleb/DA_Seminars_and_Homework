 * Seminar on Difference-in-Difference, 2020
 * Replicating some results of Card & Krueger (1994)

clear all // cleans memory from data
set more off // cancel pauses 
capture log close // closes open log file. На самом деле 2 команды: capture + log close

* Define your working directory 
cd /Users/khaykingleb/Desktop/Personal/Work/HSE/Current_Semester/Stata-Course/seminars/sem_09 // create YOUR OWN working folder at YOUR computer, and put here the path to this folder
	
* Start a log-file that will save all results automatically to your computer
log using sem_09.log, replace

* Open data file - this is original datafile from Card & Krueger (1994)
use data.dta, clear

* Сreate label for variable "state"
label define state 0 "PA" 1 " NJ"
label values state state
tab state


* Task1
* Impact on Employment
// create employment varaible (FTE) for both periods
gen FTE = empft + 0.5 * emppt + nmgrs //  сумма занятостей разных типов работы
gen FTE2 = empft2 + 0.5 * emppt2 + nmgrs2

// Видим повышение занятости в Нью-Джерси от повышения МЗП
tabstat FTE FTE2 if wage_st != . & wage_st2 != ., statistics(mean) by(state) columns(variables) // using the balanced sample

// Хотим провести t-тест на равенство средних
by state, sort: ttest FTE == FTE2 if wage_st != . & wage_st2 != ., unpaired
// Видим, что изменения в средних незначимо

// Хотя изменения в средних незначимо, нам больше важно, значим ли DiD эффект
gen FTE_change = FTE2 - FTE
ttest FTE_change if wage_st != . & wage_st2 != ., by(state)
// Получили, что DiD эффект значим при уровне значимости 10%
	
* Impact on wages
tabstat wage_st wage_st2 if wage_st != . & wage_st2 != ., statistics(mean) by(state) columns(variables) // using the balanced sample

by state, sort: ttest wage_st == wage_st2 if wage_st!=. & wage_st2 !=., unpaired

gen WAGE_change = wage_st2 - wage_st
ttest WAGE_change if wage_st != . & wage_st2 != ., by(state)

* Impact on price
// create the price of full meal for both periods
gen price_full_meal = psoda + pfry + pentree
gen price_full_meal2 = psoda2 + pfry2 + pentree2
  
tabstat price_full_meal price_full_meal2 if wage_st != . & wage_st2 != ., statistics(mean) by(state) columns(variables) // using the balanced sample

by state, sort: ttest price_full_meal == price_full_meal2 if wage_st != . & wage_st2 != ., unpaired

gen PRICE_change = price_full_meal2 - price_full_meal
ttest PRICE_change if wage_st != . & wage_st2 != ., by(state)

	
	
* Task 2
// Model 1
regress FTE_change state if wage_st != . & wage_st2 != .

// Model 2
// Добавим к модели 1 контрольные переменные
xi: regress FTE_change state i.chain co_owned if wage_st != . & wage_st2 != . //xi используется в связке i.chain и разбивает на _Ichain_1 _Ichain_2 _Ichain_3 _Ichain_4 (первая делается ommited, чтобы не было проблемы мультиколлинеарности)
// Получили почти такую же оценку при регрессоре state => Модель прошла проверку на введение контрольных переменных: результат устойчив к небольшим изменениям спецификации модели
// Тест на совместную значимость контрольных переменных в последней регрессии
test _Ichain_2 _Ichain_3 _Ichain_4 co_owned
	
// Model 3
gen GAP = 0
replace GAP = (5.05 - wage_st)/wage_st if wage_st < 5.05 & state == 1
regress FTE_change GAP if wage_st != . & wage_st2 != .
// Чем фирмам больше надо подтягиваться к новому МЗП = 5.05, тем больше эффект от повшения МЗП
// Однако, величина коэффициента при регрессоре GAP достаточно большая, но масштаб влияния небольшой, так как GAP маленький
sum GAP

// Model 4
// Введем контрольные переменные
xi: regress FTE_change GAP i.chain co_owned if wage_st != . & wage_st2 != .
test _Ichain_2 _Ichain_3 _Ichain_4 co_owned

// Model 5
// Введем контрольные переменные
xi: regress FTE_change GAP i.chain co_owned  centralj northj pa1 pa2  if wage_st != . & wage_st2 != .
test _Ichain_2 _Ichain_3 _Ichain_4 co_owned centralj northj pa1 pa2

* Save final file and close log
save data.dta, replace
log close
