#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<vector<int>> A;

bool same(vector<int> const &X, vector<int> const &Y)
{
	if (X.size() != Y.size())
		return false;
	if (X.empty())
		return true;
	vector<int> XL, XR, YL, YR;
	for (int i = 1; i < (int)X.size(); i++)
	{
		(X[i] < X[0] ? XL : XR).push_back(X[i]);
		(Y[i] < Y[0] ? YL : YR).push_back(Y[i]);
	}
	return same(XL, YL) && same(XR, YR);
}

int main()
{
	cin >> n >> k;
	A.resize(n, vector<int>(k, 0));
	for (auto &AA : A)
		for (auto &a : AA)
			cin >> a;
	vector<int> I;
	for (int i = 0; i < n; i++)
	{
		bool found = false;
		for (int j : I)
			found |= same(A[j], A[i]);
		if (!found)
			I.push_back(i);
	}
	cout << I.size();
}