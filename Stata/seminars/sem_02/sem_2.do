version 13 // version control
clear all // cleans memory from data
set more off // cancel pauses 
capture log close // closes open log file. На самом деле 2 команды: capture + log close

cd /Users/khaykingleb/Desktop/Personal/Work/HSE/Current_Semester/Stata-Course/seminars/sem_02 // sets working directory
log using log_1.log, replace
use StataIntroData.dta, clear


* describe data
describe

* descriptive analysis: continuous variables 
summarize age
sum age, det // detailed description of a continuous variable
sum // produces means, etc for all vars in the data

drop year // removes variables from the data file

rename wagelm wage //renames variable

drop if age<16 // drops observations

sum // summarize /Users/khaykingleb/Desktop/Personal/Work/HSE/2nd year/Term paper/Stochastic_Optimization_Methods/Genetic_Algorithm
sort educyears
drop if educyears == . // "." means missing value 


* descriptive analysis: discrete variables 
tabulate male
tab urban
tab male urban
tab male urban, row
tab male urban, ro nofre
tab male urban, co nofre


* Analysis by groups
bysort male: sum age

sum age if male==0
sum age if male==1


* Correlations 
pwcorr educyears wage
pwcorr educyears wage, sig // проверить статистическую значимость sig — significance 

* New variables
generate lwage=ln(wage)
gen age2=age * age
gen age2_new = age^2

* New dummy variables
gen high_sc = 0 // Method 1
replace high_sc = 1 if educyears > 11

gen high_sc_new = (educyears > 11) // Method 2

tab high_sc high_sc_new
drop high_sc_new

* Graphs
histogram age
hist wage
hist lwage
kdensity lwage

scatter educyears wage

save data_work.dta, replace // Сохраняем обработанный датасет
log close

