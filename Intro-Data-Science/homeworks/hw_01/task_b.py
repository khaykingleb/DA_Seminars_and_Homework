a = int(input())
b = int(input())

for i in range(a, b + 1):
    if str(i) == str(i)[::-1]:
        print(i)