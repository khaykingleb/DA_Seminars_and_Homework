
# You should complete the lines to make the code work. 
# Some tasks are interdependent 
# To comment or uncomment lines use Ctrl + Shift + C or 
# Code -> Comment/Uncomment Lines
library(dplyr)

## Task 1
# ggplot(data = ) +
#   geom_point(mapping = aes(x = , y = ))

## Task 2

# pop <- population[c(784:802,1681:1699),]
# ggplot(data = pop) +
#   geom_point(mapping = aes(x = year, y = population)) +
#   facet_wrap()

##Task 3
# herbi_arti_sleep <- filter(msleep, "herbi", "Artiodactyla")

## Task 4
#select(msleep, name, contains())

## Task 5
# arrange(select(msleep,name, order, bodywt))

## Task 6
# msleep_new <- select(msleep, name, starts_with())
# sleep_phases <- mutate(msleep_new, nonrem_sleep = )

## Task 7
#summarise(airquality, sol_rad = mean(TRUE))


## Task 8 
# air2 <- group_by()
# summarise()

## Task 9
# iris2 <- select(iris, -Sepal.Width)
# iris3 <- group_by(iris2, Species)
# iris4 <- mutate(iris3, ratio = Petal.Length/Sepal.Length, dev = Petal.Width - mean(Petal.Width))
# iris4
