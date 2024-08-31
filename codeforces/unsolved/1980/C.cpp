#include <bits/stdc++.h>

using namespace std;

#define sz(C) (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n), B(n);
	for (int &a : A)
		cin >> a;
	for (int &b : B)
		cin >> b;
	
	map<int, vector<int>> I1, I2;
	vector<int> J;

	int m;
	cin >> m;
	vector<int> D(m);
	for (int &d : D)
		cin >> d;

	vector<int> C(m);
	
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		(A[i] == B[i] ? I2 : I1)[B[i]].push_back(i);
		cnt += A[i] != B[i];
	}
	for (int i = m; i--;)
	{
		int d = D[i];
		auto &II1 = I1[d];
		auto &II2 = I2[d];
		if (!II1.empty())
		{
			C[i] = II1.back();
			J.push_back(II1.back());
			II1.pop_back();
			cnt--;
		}
		else if (!II2.empty())
		{
			C[i] = II2.back();
			J.push_back(II2.back());
			II2.pop_back();
		}
		else if (!J.empty())
		{
			C[i] = J[0];
		}
		else
			cnt = INT_MAX;
	}

	cout << (cnt == 0 ? "YES\n" : "NO\n");
}
