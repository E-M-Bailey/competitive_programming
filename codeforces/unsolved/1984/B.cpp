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
	string s;
	cin >> s;
	int n = (int)size(s);
	reverse(begin(s), end(s));
	while (s.back() == '0')
		s.pop_back();
	vector<int> A(n);
	for (int i = 0; i < n; i++)
		A[i] = s[i] - '0';
	for (int i = 1; i < n; i++)
	{
		A[i]--;
		A[i - 1] += 10;
	}
	if (A.back() == 0)
		A.pop_back();
	cout << (*min_element(begin(A), end(A)) >= 10 && *max_element(begin(A), end(A)) <= 18 ? "YES\n" : "NO\n");
}
