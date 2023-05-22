#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	else
	{
		ignore = freopen("tallbarn.in", "r", stdin);
		ignore = freopen("tallbarn.out", "w", stdout);
	}

	int N;
	int64_t K;
	cin >> N >> K;
	vector<long double> A(N), S(N);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
		S[i] = sqrtl(A[i]);
	}

	long double lo = 1e-25l, hi = 1e13l, lam;
	long double val;
	long double ans = numeric_limits<long double>::infinity();
	while (true)
	{
		lam = lo + (hi - lo) / 2;
		long double ls = 1 / sqrtl(lam);
		int64_t ksum = 0;
		val = 0;
		for (int i = 0; i < N; i++)
		{
			long double k = S[i] * ls;
			int64_t kf = (int64_t)k, kc = kf + 1;
			long double vf = A[i] / kf, vc = A[i] / kc;
			if (vf <= vc + lam)
			{
				ksum += kf;
				val += vf;
			}
			else
			{
				ksum += kc;
				val += vc;
			}
		}
		if (ksum > K)
		{
			if (lo == lam)
				break;
			lo = lam;
		}
		else
		{
			ans = min(ans, val);
			if (hi == lam)
				break;
			hi = lam;
		}
		//cerr << lam << ' ' << ksum << ' ' << val << ' ' << lo << ' ' << hi << endl;
	}

	//cerr << fixed << setprecision(0) << roundl(1e+13);

	cout << fixed << setprecision(0) << roundl(ans);
}