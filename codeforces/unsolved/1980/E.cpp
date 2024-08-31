#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
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
	int n, m;
	cin >> n >> m;
	vector<vector<int>> A(n, vector<int>(m)), B = A;
	for (auto &AA : A)
	{
		for (int &a : AA)
			cin >> a;
		AA.push_back(*min_element(begin(AA), end(AA)));
	}
	for (auto &AA : B)
	{
		for (int &a : AA)
			cin >> a;
		AA.push_back(*min_element(begin(AA), end(AA)));
	}

	auto const c1 = [&](auto const &AA, auto const &BB)
	{
		return AA.back() < BB.back();
	};

	sort(begin(A), end(A), c1);
	sort(begin(B), end(B), c1);
	for (auto &AA : A)
		AA.pop_back();
	for (auto &AA : B)
		AA.pop_back();

	vector<pair<int, int>> X(m), Y(m);
	for (int i = 0; i < m; i++)
	{
		X[i] = {A[0][i], i};
		Y[i] = {B[0][i], i};
	}
	sort(begin(X), end(X));
	sort(begin(Y), end(Y));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (A[i][X[j].second] != B[i][Y[j].second])
			{
				cout << "NO\n";
				return;
			}
	cout << "YES\n";
}
