#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, x;
	cin >> n >> x;
	cout << (x >= accumulate(istream_iterator<int>(cin), istream_iterator<int>(), 0) ? "Jebb" : "Neibb");
}
