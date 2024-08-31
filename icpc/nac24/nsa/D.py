import sys
from collections import defaultdict

n, q = map(int, sys.stdin.readline().rstrip('\r\n').split())
obs = []
start = defaultdict(int)
pos = defaultdict(int)
l = defaultdict(int)

for i in range(n):
	data = sys.stdin.readline().rstrip('\r\n').split()
	if data[1] == "Start":
		start[int(data[0])] = int(data[2])
		pos[int(data[0])] = int(data[3], 16)
		l[int(data[0])] = int(data[4])
	elif data[1] == "End":
		obs.append((start[int(data[0])], int(data[2]), pos[int(data[0])], pos[int(data[0])] + l[int(data[0])] - 1, int(data[0])))

obs.sort(key = lambda x : x[4])

for i in range(q):
	data = sys.stdin.readline().rstrip('\r\n').split()
	x1, x2 = int(data[1]), int(data[2])
	y1, y2 = int(data[3], 16), int(data[4], 16)
	ret = []
	cnt = 0
	for j in range(len(obs)):
		if obs[j][0] > x2 or obs[j][1] < x1:
			continue
		if obs[j][2] > y2 or obs[j][3] < y1:
			continue
		if len(ret) < 20:
			ret.append(obs[j][4])
		cnt += 1
	print(f"{cnt} {' '.join([str(c) for c in ret])}")