library(plm)
library(dplyr)
library(ggplot2)

#1
df = data('Cigar', package = "plm")
df = Cigar

#2
cigar80 = filter(df, year == 80, sales < 200, sales > 100)

ggplot(data = cigar80, aes(x=ndi, y = sales)) + geom_point()

3#
youth_data = select(cigar80, starts_with("pop"), "sales")
youth_data = mutate(youth_data, ratio = pop16 / pop)
ggplot(data = youth_data, aes(x = ratio, y = sales)) + geom_point()

#4
real_pr = select(df, "price", "cpi", "sales")
real_pr = mutate(real_pr, real_pr = price * cpi)
ggplot(data = real_pr, aes(x = real_pr, y = sales)) + geom_point()


# 5
largest = arrange(Cigar, -sales)
head(largest, 10)
largest = filter(largest, state != 30, state != 9, state != 18)
largest = mutate(largest, real_pr = price*cpi)
ggplot(data = largest, aes(x = real_pr, y = sales)) + geom_point()


#6
some = select(df, price, cpi, sales, year)
some = filter(some, 60 <= year, year <= 90)
some = filter(some, year %% 5 == FALSE)
some = mutate(some, real_pr = price/cpi)

ggplot(data = some, aes(x = real_pr, y = sales)) + geom_point() + facet_wrap("year")
