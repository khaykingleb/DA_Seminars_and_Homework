a = int(input())
b = int(input())
c = int(input())

vertex_1 = None
vertex_2 = None
cnt = 0
cur_dist = 1e9
min_dist = 1e9

while c != 0:
    if (a < b) & (b > c):
        cnt += 1
        if cnt == 1:
            vertex_1 = b
        elif cnt == 2:
            vertex_2 = b
        else:
            vertex_1, vertex_2 = vertex_2, b

        if cur_dist < min_dist:
            min_dist = cur_dist

        cur_dist = 1

    else:
        cur_dist += 1

    a, b, c = b, c, int(input())

if cnt < 2:
    print(0)
else:
    print(min_dist)