// 0000
// 1101
// 0011
// 1110
// 0101
// 1000
// 0110
// 1011
// 1100
// ...
// 
// 00000
// 11101
// 00011
// 11110
// 00101
// 11000
// 00110
// 11011
// ...
// 01111
// ...
// 01010

#include <bits/stdc++.h>

using namespace std;

string bin(int x, int n)
{
	string ans;
	for (int bit = 1; bit < 1 << n; bit <<= 1)
		ans += x & bit ? '1' : '0';
	return ans;
}

vector<int> gray(int n, int st)
{
	if (n == 0)
		return { 0 };
	vector<int> ans(1 << n);
	for (int i = 0; i < 1 << n; i++)
	{
		ans[i] = i;
		for (int bit = 1 << (n - 1); bit; bit >>= 1)
		{
			if (ans[i] & bit)
				ans[i] ^= bit - 1;
		}
		ans[i] ^= st;
	}
	return ans;
}

vector<int> gray(int n, int st, int a)
{
	vector<int> ans;
	int sx = a - 1, sy = n - a + 1;
	vector<int> X = gray(sx, 0), Y = gray(sy, 0);
	for (int x : X)
	{
		for (int y : Y)
		{
			//cerr << i << ' ' << (i % 2 << sx) - 1 << endl;
			ans.push_back((y << sx) | x);
			x ^= (1 << sx) - 1;
		}
		rotate(begin(Y), begin(Y) + 1, end(Y));
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> A(m);
	for (int &a : A)
		cin >> a;
	sort(begin(A), end(A));
	for (int a : A)
		if (a % 2 == 1 && a != n)
		{

			return 0;
		}

	if (A.back() == n && A.size() >= 2)
	{
		int a = A[0];
		vector<int> X = gray(n, 0);
		for (int x : X)
			cout << bin(x, )
	}

}
