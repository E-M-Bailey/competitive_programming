#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<pair<int, string>> A{{0, "Monnei"}, {0, "Fjee"}, {0, "Dolladollabilljoll"}};
	for (auto &[x, s] : A)
		cin >> x;
	cout << min_element(begin(A), end(A))->second;
}
