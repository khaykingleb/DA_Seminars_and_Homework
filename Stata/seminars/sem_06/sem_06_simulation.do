*** Пример Sharp RDD
clear all

* Просто рандомно генерируем данные

//set scheme s1mono
set obs 1000 // generate N=1000
set seed 101010 // set the simulation seed to get same results

gen s = 10 + 5 * rnormal(0, 1) // генерируем переменне
global s_star = 10 // threshold (наша forcing variable)
global sigma = 100

gen x = s - $s_star // define x as (s–s*) — делаем это, чтобы в threshold наша переменная равнялась нулю

// переменая, что человек получил treatment или не получил
gen d = 1 if s > $s_star 
replace d = 0 if s <= $s_star

// Potential outcome, где индивид получил treatment
gen y1 = 600 + 6.5 * x - 2 * x^2 + 0.001 * x^3 + rnormal(0, $sigma) // generate y1

// Potential outcome, где индивид не получил treatment
gen y0 = 200 + 6.5 * x - 0.20 * x^2 + 0.01 * x^3 + rnormal(0, $sigma) // generate y0

gen y = y0 + d * (y1 - y0) // generate the observable outcome by POM

// Histogramms: see the difference in distribution of outcomes below and above the threshold
twoway ///
hist y if s>$s_star, barw(60) bcolor(gray) ///
|| ///
hist y if s<$s_star , barw(60) bcolor(black) ///
legend(order(1 "Right side" 2 "Left side") pos(11) col(1) ring(0)) ///
xtitle() ytitle(Frequency) ylabel()

* Non-manipulation test for running variable
// basic version
hist s , xline(10) 
// McCray test
DCdensity s, breakpoint($s_star) generate(Xj Yj r0 fhat se_fhat) 
// Видим, что сильного скачка после threshold нет. 
rddensity s , c($s_star) p(1) bwselect(diff) all vce(plugin)
// Коэффициет при Conventional равен -0.8502 и не значим. Не можем отвергнуть гипотезу о том, что плотность непрерывна
drop Xj Yj r0 fhat se_fhat

* Effect of treatment inside regression
gen x2 = x^2
gen x3 = x^3
gen dx = d * x
gen dx2 = d * x^2
gen dx3 = d * x^3

// linear regression
reg y d x dx
// Получили оценку treatment эффекта (при коэф d), равную 412.86: завысили на 12.86
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

// Оцениваем полиномом второй степени для control группы, а третей степени — для treatment группы
reg y d x x2 x3 dx dx2 dx3 // polinomil regression 
rdrobust y s, c($s_star) p(1) // local polinomial regression
rdrobust y x, c(0) p(1) // similar to previous

* Quasi-test for continuity of potential outcomes: 
// check the continuity of outcome at points other than s*: например при quasi-threshold
// в районе 7, то есть c(7), или в районе 13, то есть c(13)
rdrobust y s, c(7) p(1) // local polinomial regression
// Взял окно 1.921 => получилось 113 наблюдений слево и 149 справо
// Гипотеза о непрервыности не отвергается

rdrobust y s, c(13) p(1) // local polinomial regression
// Гипотеза о непрервыности не отвергается

rdrobust y s, c(9) p(1) // local polinomial regression
// Гипотеза о непрервыности отвергается, так как очень близко к threshold => Окно получили такое, что залазием за него (1.711) => Резко идет скачек вверх, так как мы так генерировали данные

// For fuzzy rdd it is better to use rdrobust rather than ivreg2
