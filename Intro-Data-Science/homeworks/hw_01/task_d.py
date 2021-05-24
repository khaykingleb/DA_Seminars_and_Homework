n = int(input())
stations = list(map(int, input().split()))
for i in range(n):
    stations[i] = [stations[i], i + 1, 0]
stations.sort()

m = int(input())
lesopilki = list(map(int, input().split()))
for i in range(m):
    lesopilki[i] = [lesopilki[i], i + 1]
lesopilki.sort()

cnt = 0
for station in stations:
    distance = 1e9
    for i in range(cnt, m):
        cur_distance = abs(station[0] - lesopilki[i][0])
        if cur_distance < distance:
            distance = cur_distance
            cnt = i
            station[2] = lesopilki[i][1]
        else:
            break

stations.sort(key=lambda x: x[1])

for station in stations:
    print(station[2])