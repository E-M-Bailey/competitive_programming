#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 924844033;
constexpr int PHI = MOD - 1; // 3*3*7*7*2^21
// can use powers of 2 up to 2M
constexpr int LIMN = (1 << 18) + 1;

const struct sieve
{
	vector<int> pr;
	vector<int> lp;
	sieve(int n): lp(n)
	{
		for (int i = 2; i < n; i++)
		{
			if (lp[i])
				continue;
			pr.push_back(i);
			for (int j = i; j < LIMN; j += i)
				if (!lp[j])
					lp[j] = i;
		}
	}
} SV(LIMN);

const struct divs
{
	int n;
	vector<int> pf;
	vector<int> dv;
	bool incr(int& d)
	{
		for (int p : pf)
		{
			int dp = d * p;
			if (n % dp == 0)
			{
				d = dp;
				return true;
			}
			do
				d /= p;
			while (d % p == 0);
		}
		return false;
	}
	divs(int N): n(N)
	{
		for (int p : SV.pr)
			if (N % p == 0)
			{
				pf.push_back(p);
				do
					N /= p;
				while (N % p == 0);
			}
		if (N > 1)
			pf.push_back(N);

		int d = 1;
		do
			dv.push_back(d);
		while (incr(d));
		sort(begin(dv), end(dv));
	}
	int rudiv(int x)
	{
		return *lower_bound(begin(dv), end(dv), x);
	}
} DV(PHI);

struct ntt
{
	
};

int main()
{

}