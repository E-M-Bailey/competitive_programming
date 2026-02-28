#include <bits/extc++.h>

using namespace std;

template<typename C, integral T = int>
[[nodiscard]] static constexpr int sz(const C& c) noexcept
{
	return static_cast<T>(size(c));
}

int main()
{
	string s;
	cin >> s;
	int n = 0;
	for (int i = -1, j = 0, k = 1;; ++n)
	{
		do
			++i;
		while (i < sz(s) && s[i] != 'A');
		do
			++j;
		while (j < sz(s) && (j <= i || s[j] != 'B'));
		do
			++k;
		while (k < sz(s) && (k <= j || s[k] != 'C'));
		if (k >= sz(s))
			break;
	}
	cout << n;
}
