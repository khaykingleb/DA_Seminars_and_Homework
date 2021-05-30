
# You should complete the lines to make the code work. 
# Some tasks are interdependent 
# To comment or uncomment lines use Ctrl + Shift + C or 
# Code -> Comment/Uncomment Lines


# # Task 1
# 1994, 1996, 1998, 2000, 2001
# "Mexico", "Thailand", "Russia", "Turkey", "Argentina"
# "Mexico" and "Russia"

years = c(1994, 1996, 1998, 2000, 2001)
names(years) = c("Mexico", "Thailand", "Russia", "Turkey", "Argentina")

years[c("Mexico", "Russia")]
## Task 2
a <- seq(from = 40, to = 2, by = -2)
A_mat <- matrix(a, nrow = 4, ncol = 5)

## Task 3
cn = c("col1", "col2", "col3", "col4", "col5")
rn = c("row1", "row2", "row3", "row4")
colnames(A_mat) <- cn
rownames(A_mat) <- rn

## Task 4
rs <- rowSums(A_mat)
cs <- colSums(A_mat)

rs
cs

##Task 5
A_mat[3,3]
A_mat[2,4]
## Task 6
cbind(A_mat, A_mat)
rbind(A_mat, A_mat)


# Task 7
v1 <- c(1:3)
v2 <- c(4:6)
v1+v2
v1*v2
v1%*%v2




# Task 8
B_arr <-    array(seq(40, 2, -2), c(2,2,5))
B_arr[,,3]


# Task 9
head(swiss)
tail(swiss)
str(swiss)

## Task 10
## Define the variables
id <- c("Courtelary", "Delemont", "Franches-Mnt", "Moutier")
fertility <- c(80.2, 83.1, 92.5, 85.8)
agriculture<- c(17.0, 45.1, 39.7, 36.5)
examination<- c(15, 6, 5,12)
education<- c(12, 9, 5, 7)
 catholic <- c(9.96, 84.84, 93.40, 33.77)
inf_mortality<- c(22.2, 22.2, 20.2, 20.3)
# # Create a data frame from the variables
swiss4 <- data.frame(fertility, agriculture, examination, education, catholic, inf_mortality,row.names = id)
## Print the data frame
#   
  
##Task 11
#swiss4[]
#mean(swiss4)

## Task12
# swiss_draftees <-"Examination", "Education"
# (swiss_draftees)

## Task 13
#lower_mortality <-swiss$Infant.Mortality<20
#lower_mortality

## Task 14
#subset(swiss, )
