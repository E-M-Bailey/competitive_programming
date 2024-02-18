#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> A(n);
	copy(istream_iterator<int>(cin), istream_iterator<int>(), begin(A));
	reverse_copy(begin(A), end(A), ostream_iterator<int>(cout, "\n"));
}
