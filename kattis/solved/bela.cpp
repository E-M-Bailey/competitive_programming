#include <bits/stdc++.h>

using namespace std;

int main()
{
	pair<int, int> V[200]{};
	V[(int)'A'] = {11, 11};
	V[(int)'K'] = {4, 4};
	V[(int)'Q'] = {3, 3};
	V[(int)'J'] = {20, 2};
	V[(int)'T'] = {10, 10};
	V[(int)'9'] = {14, 0};

	int	 n, ans = 0;
	char d;
	cin >> n >> d;
	string s;
	while (cin >> s)
		ans += s[1] == d ? V[(int)s[0]].first : V[(int)s[0]].second;
	cout << ans;
}
