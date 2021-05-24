version 13 // version control
clear all // cleans memory from data
set more off // cancel pauses 
capture log close // closes open log file. На самом деле 2 команды: capture + log close

cd /Users/khaykingleb/Desktop/Personal/Work/HSE/Current_Semester/Stata-Course/seminars/sem_03 // sets working directory
log using log_2.log, replace
use data_work.dta, clear

* hypothesis testing
bysort male: sum wage
ttest wage, by(male) // tests that group means (wages of males and females) are equal to each other

* OLS-regression
regress lwage educyears age age2 i.male i.urban // or use reg
test age age2 // tests equality of coefficients 
predict fit_lw // creates new variable that contains fitted values
sum lwage fit_lw
predict fit_lw2 if e(sample) // просим предсказать только по переменным, где нет пропусков
sum lwage fit_lw fit_lw2

* Tables of several estimates
reg lwage educyears age age2 i.urban if male==0
estimates store female // store estimates for future use
reg lwage educyears age age2 i.urban if male ==1
estimates store male
estimates table male female, star

* Interaction terms - think about interpretation of these results
regress lwage  educyears c.age##c.age i.male i.urban // age##age = age age*age; c — говороим, что переменная непрерывная 
regress lwage  educyears c.age#c.age i.male i.urban
regress lwage c.educyears##i.male age age2 i.urban  // c.educyears##i.male = c.educyears i.male c.educyears*i.male

* Categorial variables
recode age (min/25 = 1 "16-25") (26/45 = 2 "26-45") (46/max = 3 "46+"), gen(age_gr)
tab age_gr
reg lwage educyears male urban age_gr
reg lwage educyears male urban i.age_gr // говорим стате, что она работает с категориальной переменной, иначе будут неправильные результаты
reg lwage educyears male urban ib2.age_gr // хотим, чтобы вторая группа была базовой, а не первой

 
* Probit-regression
gen employ = (wage != .) // assume that all who did not report wages have no jobs; 1 = not NA, 0 = NA
regress employ i.male i.urban age age2 educyears // linear probability model
predict emp_lpm

probit employ i.male i.urban age age2 educyears // coefficients of probit-model have no direct interpretation. 
predict emp_probit

sum employ emp_lpm emp_probit

* Margins — conditional marginal effects (at certain points)
margins, dydx(*) atmeans // * — средний предельный эффект по всем переменным
margins, dydx(*) at (age=30 educyears=17 urban=1 male=1)


* Margins — average marginal effects 
margins, dxdy(*)

* Margins — predicted probabilities
margins, at(educyears=(0(5)27))
marginsplot

* Probit with interaction and non linearities
probit employ i.urban c.age##c.age i.male educyears i.male#c.educyears // стоит делать тут так, а не так
probit employ i.urban age age2 i.male educyears i.male#c.educyears // так делать здесь не надо

// pay attention to the difference between # and ##. read help for factor variables
margins, dxdy(*)

save data_work.dta, replace
log close
