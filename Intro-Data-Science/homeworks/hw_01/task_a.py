import sys
coord = dict()
nums = list(map(int, ''.join(sys.stdin.readlines()).strip().split()))


def euclid_dist(x1, x2):
    return ((x1[0] - x2[0]) ** 2 + (x1[1] - x2[1]) ** 2) ** 0.5


i = 0
while i < len(nums):
    coord['x{}'.format(i)] = nums[i:i+2]
    i += 2

keys = tuple(coord.keys())
a = coord[keys[-1]]
b = coord[keys[0]]
P = euclid_dist(a, b)

for i in range(len(keys) - 1):
    a, b = b, coord[keys[i + 1]]
    P += euclid_dist(a, b)

print(round(P, 6))