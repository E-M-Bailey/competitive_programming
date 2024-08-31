#include <bits/stdc++.h>

using namespace std;

int n, k, t, K;

int dec(string const &s)
{
	int ans = 0;
	for (int i = 0, p = 1; i < k; i++, p *= 3)
		ans += p * (s[i] == 'A' ? 0 : s[i] == 'E' ? 1 : 2);
	return ans;
}

string enc(int x)
{
	string ans(k, '\0');
	for (char &c : ans)
	{
		c = "0+-"[x % 3];
		x /= 3;
	}
	return ans;
}

int add(int a, int b)
{
	int ans = 0;
	for (int p = 1; p < K; p *= 3)
	{
		ans += (a + b) % 3 * p;
		a /= 3;
		b /= 3;
	}
	return ans;
}

bool solve(vector<int> &A, vector<int> &st)
{
	
}

int main()
{
	cin >> n >> k >> t;

	K = 1;
	for (int i = 0; i < k; i++)
		K *= 3;

	vector<long long> A(K), B(K);
	for (int i = 0; i < t; i++)
	{
		string s;
		long long f;
		cin >> s >> f;
		A[dec(s)] += f;
	}
	
	for (int x = 0; x < K; x++)
	{
		bool good = true;
		while (good)
		{
			for (int a = 0; a < K; a++)
			{
				int b = add(a, x), c = add(b, x);
				B[a] = A[a] + A[b] - A[c];
				good &= B[a] % 2 == 0 && B[a] >= 0;
				B[a] /= 2;
			}
			good &= B[0] > 0;
			if (good)
			{
				cout << enc(x) << '\n';
				n--;
				copy(begin(B), end(B), begin(A));
			}
		}
	}
}
