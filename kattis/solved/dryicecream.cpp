#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n, t;
	cin >> n;
	vector<int> A(n);
	vector<int> IDX(101);

	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
		if (IDX[A[i]] == 0)
			IDX[A[i]] = i;
	}
	cin >> t;

	sort(begin(A), end(A));
	A.erase(unique(begin(A), end(A)), end(A));
	n = (int)A.size();
	int g = accumulate(begin(A), end(A), 0, gcd<int, int>);
	if (t % g)
	{
		cout << "impossible";
		return 0;
	}

	while (t >= A.front())
	{
		cout << "fill " << IDX[A.front()] + 1 << '\n';
		cout << "transfer " << IDX[A.front()] + 1 << " 0\n";
		t -= A.front();
	}
	if (t == 0)
		return 0;
	// for (int a : A)
	// 	cerr << a << ' ';
	// cerr << endl << t << endl;

	int lim = 2 * A.back() + 1;
	vector<vector<int>> D(1, vector<int>(lim));
	D.back()[0] = INT_MIN;
	while (!D.back()[t])
	{
		vector<int> NW = D.back();
		for (int i = 0; i < n; i++)
		{
			int a = A[i];
			for (int j = a; j < lim; j++)
				if (!NW[j] && D.back()[j - a])
					NW[j] = i + 1;
			for (int j = lim - 1; j >= a; j--)
				if (!NW[j - a] && D.back()[j])
					NW[j - a] = -(i + 1);
		}
		// for (int d : NW)
		// 	cerr << d << ' ';
		// cerr << endl;
		D.push_back(move(NW));
	}

	unordered_map<int, int> F;
	for (int i = t; i;)
	{
		int d = D.back()[i];
		D.pop_back();
		if (d > 0)
		{
			d = -1 + d;
			F[d]++;
			i -= A[d];
		}
		else
		{
			d = -1 - d;
			F[d]--;
			i += A[d];
		}
	}

	vector<int> P{ -1 }, N{ -1 };
	for (auto [d, f] : F)
	{
		while (f > 0)
		{
			P.push_back(d);
			f--;
		}
		while (f < 0)
		{
			N.push_back(d);
			f++;
		}
	}


	vector<int> B(n, 0);
	int tot = 0, ip = P.back(), in = N.back();
	while (ip >= 0 || in >= 0)
	{
		if (in >= 0 && tot >= A[in])
		{
			for (int i = 0; B[in] < A[in]; i++)
			{
				if (i >= n)
					exit(-1);
				if (i != in && B[i] > 0)
				{
					int amt = min(B[i], A[in] - B[in]);
					B[i] -= amt;
					B[in] += amt;
					cout << "transfer " << IDX[A[i]] + 1 << ' ' << IDX[A[in]] + 1 << '\n';
				}
			}
			B[in] = 0;
			tot -= A[in];
			cout << "discard " << IDX[A[in]] + 1 << '\n';
			N.pop_back();
			in = N.back();
		}
		else
		{
			if (ip < 0)
				exit(-1);
			for (int i = 0; B[ip] > 0; i++)
			{
				if (i >= n)
					exit(-1);
				if (i != ip && B[i] < A[i])
				{
					int amt = min(A[i] - B[i], B[ip]);
					B[i] += amt;
					B[ip] -= amt;
					cout << "transfer " << IDX[A[ip]] + 1 << ' ' << IDX[A[i]] + 1 << '\n';
				}
			}
			B[ip] = A[ip];
			tot += A[ip];
			cout << "fill " << IDX[A[ip]] + 1 << '\n';
			P.pop_back();
			ip = P.back();
		}
	}
	for (int i = 0; tot > 0; i++)
	{
		if (i >= n)
			exit(-1);
		if (B[i] > 0)
		{
			tot -= B[i];
			B[i] = 0;
			cout << "transfer " << IDX[A[i]] + 1 << " 0\n";
		}
	}
}
