string = input()
substring = input()
ans = []
a = string.find(substring)

while a != -1:
    ans.append(a + 1)
    string = string.replace(string[:a+1], '∂' * len(string[:a+1]), 1)
    a = string.find(substring)

if len(ans) == 0:
    print(0)
else:
    print(*ans)