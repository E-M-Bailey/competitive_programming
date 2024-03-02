#include <bits/stdc++.h>

using namespace std;

int main()
{
	int64_t n, k;
	cin >> n >> k;
	vector<int64_t> A(n);
	copy(istream_iterator<int>(cin), istream_iterator<int>(), begin(A));
	int64_t s = accumulate(begin(A), end(A), k - 1);
	cout << max(*max_element(begin(A), end(A)), s / k) * k - s;
}
