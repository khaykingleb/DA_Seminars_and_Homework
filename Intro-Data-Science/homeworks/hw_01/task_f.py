n = int(input())
current_seq = [n]
cnt = 1
cnt_max = 1

if n == 0:
    print(cnt_max)
else:
    n = int(input())
    while n != 0:
        if not any([n == i for i in current_seq]):
            if n > current_seq[-1] and all([current_seq[i+1] > current_seq[i] for i in range(len(current_seq)-1)]):
                cnt += 1
                current_seq.append(n)

            elif n < current_seq[-1] and all([current_seq[i+1] < current_seq[i] for i in range(len(current_seq) - 1)]):
                cnt += 1
                current_seq.append(n)
            else:
                if cnt > cnt_max:
                    cnt_max = cnt
                cnt = 2
                current_seq = [current_seq[-1], n]
        else:
            if cnt > cnt_max:
                cnt_max = cnt
            current_seq = [current_seq[-1], n]

            if current_seq[0] == current_seq[1]:
                cnt = 1
            else:
                cnt = 2

        n = int(input())

    if cnt > cnt_max:
        cnt_max = cnt
    print(cnt_max)
