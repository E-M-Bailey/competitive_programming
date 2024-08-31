#include <bits/stdc++.h>

using namespace std;

double huff(vector<double> const &F)
{
	double ans = 0;
	priority_queue<double> Q;
	for (auto f : F)
		Q.push(-f);
	while (Q.size() > 1)
	{
		auto x = Q.top();
		Q.pop();
		auto y = Q.top();
		Q.pop();
		ans += x + y;
		Q.push(x + y);
	}
	return -ans;
}

int main()
{
	int n;
	cin >> n;
	vector<double> X(n), Y(n), Z(n * n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			double p;
			cin >> p;
			X[i] += p;
			Y[j] += p;
			Z[i * n + j] += p;
		}
	double x = huff(X), y = huff(Y), z = huff(Z);
	cout << fixed << setprecision(8) << x + y - z;
}
