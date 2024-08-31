#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	cout << fixed << setprecision(8) << accumulate(istream_iterator<int>(cin), istream_iterator<int>(), 0.) / (n * m);
}
