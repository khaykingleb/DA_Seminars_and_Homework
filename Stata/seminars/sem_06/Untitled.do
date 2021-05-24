version 13 // version control
clear all // cleans memory from data
set more off // cancel pauses 
capture log close // closes open log file. На самом деле 2 команды: capture + log close

cd /Users/khaykingleb/Desktop/Personal/Work/HSE/Current_Semester/Stata-Course/seminars/sem_07 // sets working directory
log using log_2.log, replace
use auction_data.dta, clear

clear all
//set scheme s1mono
set obs 1000 // generate N=1000
set seed 101010 // set the simulation seed to get same results
gen s = 10 + 5 * rnormal(0,1)
global s_star = 10
global sigma = 100
gen x= s - $s_star // define x as (s–s*)
gen w=1 if s > $s_star // define treatment
replace w=0 if s <= $s_star
gen y1 = 600 + 6.5*x - 2*x^2 + 0.001*x^3 + rnormal(0, $sigma) // generate y1
gen y0 = 200 + 6.5*x - 0.20*x^2 + 0.01*x^3 + rnormal(0, $sigma) // generate y0
// since x(s*)=0, ATE=400
gen y = y0 + w*(y1 - y0) // generate the observable outcome by POM

// Histogramms: see the difference in distribution of outcomes below and above the threshold
twoway ///
hist y if s>$s_star, barw(60) bcolor(gray) ///
|| ///
hist y if s<$s_star , barw(60) bcolor(black) ///
legend(order(1 "Right side" 2 "Left side") pos(11) col(1) ring(0)) ///
xtitle() ytitle(Frequency) ylabel()

// Non-manipulation test for running variable
// basic version
hist s , xline(10) 
// McCray test
drop Xj Yj r0 fhat se_fhat
DCdensity s, breakpoint($s_star) generate(Xj Yj r0 fhat se_fhat) // ядерная оценка плотности 
rddensity s , c($s_star) p(1) bwselect(diff) all vce(plugin) // формальная проверка того, что функция плотности непрерывна (нулевая гипотеза), то есть манипуляций нет (ибо нет разрывов)


// Effect of treatment inside regression (Генерируем полиномы слева и справа от границы)
gen x2 = x^2
gen x3 = x^3
gen wx = w*x
gen wx2 = w*(x^2)
gen wx3 = w*(x^3)

reg y w x wx // linear regression

// Plotting the graph
predict y_hat_l , xb // global linear fit

graph twoway ///
(scatter y s if s>=$s_star , clstyle(p1)) ///
(scatter y s if s<=$s_star , clstyle(p1)) ///
(scatter y_hat_l s if s>=$s_star , msymbol(o)) ///
(scatter y_hat_l s if s<=$s_star , msymbol(o)) ///
, xline($s_star, lpattern(dash)) ///
title("Sharp–RDD – Parametric linear regression") ///
legend( label(1 "Right Actual Data") label(2 "Left Actual Data") ///
label(3 "Right Prediction") label(4 "Left Prediction"))

reg y w x x2 x3 wx wx2 wx3 // polinomil regression regression
rdrobust y s, c($s_star) p(1) // local polinomial regression
rdrobust y x, c(0) p(1) // similar to previous

// Quasi-test for continuity of potential outcomes: 
// check the continuity of outcome at points other than s* 
rdrobust y s, c(7) p(1) // local polinomial regression
rdrobust y s, c(13) p(1) // local polinomial regression
// коэф незначимы — значит тут непрерывны


// For fuzzy rdd it is better to use rdrobust rather than ivreg2



*** Новый ду файл
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
clear all
set more off
global basedir "D:\Job\Преподавание ВШЭ\НИС, ИПС\Практикум 3 курс\Практикум 20-21\RDD seminars"
cd "$basedir\"
use auction_data

encode plcr_org_type, gen(placer)
gen centr_auth=(placer<=2) if !missing(placer)
gen eauction=(proced==1 | proced==2) & !missing(proced)

gen init_prc_rdd=init_price
replace  init_prc_rdd=init_price-1 if init_price==500000 // make it in order not to have problems around threshold
drop if sample==0

global bounds init_price>100000 & init_price<1000000
global cutoff 500000
global subsample centr_auth==1 & subordinationtype==2
// 


* McCray non-manipulation test: 
//density of the running variable is continuous at the threshold

// visualization of McCray non-manipulation test
DCdensity init_prc_rdd if $bounds , breakpoint($cutoff) generate(Xj Yj r0 fhat se_fhat) // Видно, что резервной ценой манипулируют
drop Xj Yj r0 fhat se_fhat
// robust non-manipulation test
rddensity init_prc_rdd if $bounds, c($cutoff) p(1) bwselect(diff) all vce(plugin) // делаем формальный тест
count if $bounds

// Replicate the non-manipulation test for subsample
DCdensity init_prc_rdd if $subsample & $bounds, breakpoint($cutoff) generate(Xj Yj r0 fhat se_fhat)  // subsample —  centr_auth==1 & subordinationtype==2. Сокрее, непрерывность есть 
drop Xj Yj r0 fhat se_fhat
rddensity init_prc_rdd if $subsample & $bounds, c($cutoff) p(1) bwselect(diff) all vce(plugin) // Да, непрерывность есть
count if $subsample & $bounds


// Test for balancing: 
//below and above the threshold exogenous characteristics are continuous, i.e
// no effect of procedure on exogenous characteristics
rdplot duration init_prc_rdd if $subsample & $bounds, c($cutoff) p(4)
rdrobust duration init_price if $subsample & $bounds, c($cutoff) p(1) fuzzy(eauction)

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
