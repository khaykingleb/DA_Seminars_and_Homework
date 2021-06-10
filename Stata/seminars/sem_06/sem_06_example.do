// We study the effect of procurement procedure on auction outcomes
// Below the cutoff=500K RUB there are two possible procesures: sealed-bid auction and electronic open auction
// Above the cutoff=500K RUB electronic open auction is only eligible
// Data - procurement of granulated sugar.
// Outcomes: number of bidder, auction rebate, relative sugar price per kilo (contract price per kilo over regional retail price per kilo)

/* For RDD you need to install the following packages MANUALLY by downloading them and put into the folder 
C:\ado\plus 
inside the folder that corresponds the first letter of package name 
For package DCdensity use
https://eml.berkeley.edu/~jmccrary/DCdensity/
For other packages use 
https://sites.google.com/site/rdpackages/home
You need the following packages
rddensity rdplot rdrobust
*/

// Data preparation
clear all // cleans memory from data
set more off // cancel pauses 
capture log close // closes open log file. На самом деле 2 команды: capture + log close

* Define your working directory 
cd /Users/khaykingleb/Desktop/Personal/Work/HSE/Current_Semester/Stata-Course/seminars/sem_06 // create YOUR OWN working folder at YOUR computer, and put here the path to this folder
	
* Start a log-file that will save all results automatically to your computer
log using sem_06.log, replace

* Open data file - this is original datafile from Card & Krueger (1994)
use data.dta, clear


*** Пример Fuzzy RDD
// Свыше 500k используется открытый аукцион с вероятностью, равной единице. Ниже 500k используется открытый аукцион с вероятностью, не равной единице.
encode plcr_org_type, gen(placer)
gen centr_auth = (placer <= 2) if !missing(placer)
gen eauction = (proced ==1 | proced == 2) & !missing(proced)

gen init_prc_rdd = init_price
replace init_prc_rdd = init_price - 1 if init_price == 500000 // make it in order not to have problems around threshold
drop if sample == 0

global bounds init_price > 100000 & init_price < 1000000
global cutoff 500000
global subsample centr_auth == 1 & subordinationtype == 2 

* McCray non-manipulation test: 
// Предположение RDD — отсутствие манипуляций. Если оно не выполнено, то RDD не может быть применен
// Density of the running variable is continuous at the threshold
// Visualization of McCray non-manipulation test
DCdensity init_prc_rdd if $bounds , breakpoint($cutoff) generate(Xj Yj r0 fhat se_fhat)
drop Xj Yj r0 fhat se_fhat
// Видим, что есть весомый скачок => Люди манипулируют резервной ценой так, чтобы было меньше 500K (e.g. 499K)
// robust non-manipulation test
rddensity init_prc_rdd if $bounds, c($cutoff) p(1) bwselect(diff) all vce(plugin)
count if $bounds
// Гипотеза об отсутствии манипуляций (непрерывности) отвергается

// Q: Что делать?
// A: Делаем на подвыборке, где заказчики регионального, а не муниципального, уровня подчинения, которых контролируют больше => Они гораздо меньше манипулируют. Проверим снова
// Replicate the non-manipulation test for subsample
DCdensity init_prc_rdd if $subsample & $bounds, breakpoint($cutoff) generate(Xj Yj r0 fhat se_fhat)
drop Xj Yj r0 fhat se_fhat
rddensity init_prc_rdd if $subsample & $bounds, c($cutoff) p(1) bwselect(diff) all vce(plugin)
// Гипотеза об отсутствии манипуляций (непрерывности) не отвергается

count if $subsample & $bounds

// Для этой подвыборки пробуем оценить эффект на различные показатели
// Test for balancing: 
//below and above the threshold exogenous characteristics are continuous, i.e
// no effect of procedure on exogenous characteristics
rdplot duration init_prc_rdd if $subsample & $bounds, c($cutoff) p(4)
rdrobust duration init_price if $subsample & $bounds, c($cutoff) p(1) fuzzy(eauction)
// Вероятность электронного аукциона увеличивается на 39.273% после границы 500K
// Оценка эффекта значима: если бы выбирали электронный аукцион, то срок процедуры увеличился бы на Оценка дней

rdplot quantity init_prc_rdd if $subsample & $bounds, c($cutoff) p(4)
rdrobust quantity init_price if $subsample & $bounds, c($cutoff) p(1) fuzzy(eauction)

// Effect of e-auctions on number of applicants
rdplot appl_amnt init_prc_rdd if $subsample & $bounds, c($cutoff) p(4)
// Smoothing: GLOBAL polinome of order 4 (p(4) is by default)
rdrobust appl_amnt init_price if $subsample & $bounds, c($cutoff) p(1) fuzzy(eauction) covs(quantity duration)
// Smoothing: LOCAL polinome of order 1 (p(1) is by default)

// Effect of e-auctions on number of bidders
rdplot bidder_amnt init_prc_rdd if $subsample & $bounds, c($cutoff)
rdrobust bidder_amnt init_price if $subsample & $bounds, c($cutoff) fuzzy(eauction) covs(quantity duration)

// Effect of e-auctions on auction rebate
rdplot rebate init_prc_rdd if $subsample & $bounds, c($cutoff)
rdrobust rebate init_price if $subsample & $bounds, c($cutoff) fuzzy(eauction) covs(quantity duration)

// Effect of e-auctions on relative price
rdplot price_rel init_prc_rdd if $subsample & $bounds, c($cutoff)
rdrobust price_rel init_price if $subsample & $bounds, c($cutoff) fuzzy(eauction) covs(quantity duration)

// Implementation RDD inside regression see rdd_simulation.do


