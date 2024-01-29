#include <bits/stdc++.h>

using namespace std;

long long constexpr MOD = 1000000007;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	long long n;
	long long t;
	cin >> n >> t;
	long long a, b, c;
	vector<long long> T(1);
	cin >> a >> b >> c >> T[0];
	vector<long long> F(c + 1);
	F[T[0]]++;

	{
		long long r = 1;
		for (; r < n; r++)
		{
			T.push_back((T[r - 1] * a + b) % c + 1);
			if (F[T[r]])
				break;
			F[T[r]]++;
		}
		if (r < n)
		{
			long long l = 0;
			while (T[l] != T[r])
				l++;
			long long prd = r - l;
			long long q = (n - r) / prd;
			for (long long i = l; i < r; i++)
				F[T[i]] += q;
			for (auto i = r; i < n - q * prd; i++)
			{
				if (i > r)
					T.push_back((T[i - 1] * a + b) % c + 1);
				F[T[i]]++;
			}
		}
	}

	long long cnt = 0, cur = 0, pen = 0;

	for (int i = 1; i <= c; i++)
	{
		long long amt = min((long long)F[i], t / i);
		cnt += amt;
		t -= i * amt;
		pen = (pen + cur * amt % MOD + amt * (amt + 1) / 2 % MOD * i % MOD) % MOD;
		cur = (cur + i * amt % MOD) % MOD;
	}
	cout << cnt << ' ' << pen;
}