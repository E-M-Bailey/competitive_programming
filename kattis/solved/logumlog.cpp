#include <bits/stdc++.h>

using namespace std;

int const A_MINOR[12]{9, 11, 0, 2, 4, 5, 7};

int in()
{
	string s;
	cin >> s;
	if (s == "-")
		return -1;
	int ans = A_MINOR[s[0] - 'A'], st = 2;
	if (s[1] == 'b')
		ans--;
	else if (s[1] == '#')
		ans++;
	else
		st = 1;
	ans += 12 * stoi(s.substr(st));
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;

	vector<int> A(n), B(n);
	for (int &a : A)
		a = in();
	for (int &b : B)
		b = in();
	int	 offset = INT_MIN;
	bool match	= true;
	for (int i = 0; i < n; i++)
	{
		int a = A[i], b = B[i];
		if (a < 0 || b < 0)
		{
			match &= a < 0 && b < 0;
			continue;
		}
		int cur = b - a;
		if (offset == INT_MIN)
			offset = cur;
		match &= offset == cur;
	}
	cout << (match ? "Jebb" : "Neibb");
}
