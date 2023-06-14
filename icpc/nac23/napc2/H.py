def main():
	D, H = map(int, input().split())
	F = [1]
	while len(F) <= H:
		F.append(F[-1] * len(F))
	DP = [[set() for i in range(H + 1)] for j in range(D + 1)]
	def rec(i, h):
		dp = DP[i][h]
		if 
	

if __name__ == '__main__':
	main()
