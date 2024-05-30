#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<pair<int, string>> A(n);
	for (auto &[v, s] : A)
		cin >> s >> v;
	cout << max_element(begin(A), end(A))->second;
}
