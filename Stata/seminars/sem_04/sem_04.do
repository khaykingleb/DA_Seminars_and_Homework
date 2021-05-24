version 13 // version control
clear all // cleans memory from data
set more off // cancel pauses 
capture log close // closes open log file. На самом деле 2 команды: capture + log close

cd /Users/khaykingleb/Desktop/Personal/Work/HSE/Current_Semester/Stata-Course/seminars/sem_04 // sets working directory
log using log_2.log, replace
use card-2.dta, clear

// Создаем дополнительные переменные
gen lwage = ln(wage)
gen exper = age - educ - 6 //опыт работы
gen expersq = exper * exper

// Саммари
sum age educ exper wage black smsa south

// Переменная motheduc содержат значительное количество пропущенных значений. Создайте дамми-переменную для пропущенных значений по этой переменной (meduc_miss), затем пропущенные значения в переменной motheduc замените среднем значением в переменной motheduc.
sum motheduc

gen meduc_miss = .
replace meduc_miss = 1 if motheduc == .
replace meduc_miss = 0 if motheduc != .
 
mean motheduc

replace motheduc = 10.34814 if motheduc == .

// Определить количество и долю замененных (пропущенных) значений
sum meduc_miss // 0.1172757 — доля
tab meduc_miss // 353 — количество

// Создайте дамми-переменную (low_motheduc), равную 1, если motheduc<=8.

gen low_motheduc = . // или просто gen low_motheduc = (motheduc <= 8)
replace low_motheduc = 1 if motheduc <= 8
replace low_motheduc = 0 if motheduc > 8

// Какова доля респондентов, у которых мать имеет образование не выше 8 классов?
tab low_motheduc // 24.85 %

// Уравнение заработной платы
reg lwage educ exper expersq black smsa south smsa66
// => При увеличении образования на один год заработная плата растет на 7.4% 
//    Adj R-squared = 0.2893
// Q: Почему коэффициент β_1 может быть смещенным? Что может являться источником эндогенности в данном уравнении?
// A: Коэффициент может быть смешенным, если регрессор коррелирует с ошибками. Возможные источники эндогенности: пропуск переменных, ошибки измерения, самоотбор 
// Скорее всего, оценка β_1 смещена, поскольку мы пропустили переменную skills, потому наш регрессор коррелирует с ошибками (чем способнее человек, тем выше у него уровень образования)

// Следующее уравнение
gen educ_exper = educ * exper
reg lwage educ exper expersq educ_exper


// Рассчитайте среднее число лет обучения для респондентов, проживавших рядом и не рядом с колледжем с 4-летней программой обучения (переменная nearc4)
ttest educ, by(nearc4)
// Q: Являются различия между этими средними статистически значимыми?
// A: Да, являются при любом разумном уровне значимости.

// Постройте матрицу корреляции между educ motheduc iq lwage (звездочками обозначьте значимость коэффициентов: * - на 10% уровне, ** - на 5% уровне, *** - на 1% уровне)
pwcorr educ motheduc iq lwage, sig 
 
// Уравнение заработной платы с добавлением iq
reg lwage educ exper expersq black smsa south smsa66 iq

// Оцените уравнение методом инструментальных переменных, используя в качестве инструментов для продолжительности обучения переменные nearc4 и low_motheduc 
ivregress 2sls lwage exper expersq black smsa south smsa66 (educ = nearc4 low_motheduc)
