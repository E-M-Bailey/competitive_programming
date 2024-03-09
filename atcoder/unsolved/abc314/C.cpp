#include <bits/stdc++.h>

using namespace std;

int main()
{
	int m, n;
	cin >> n >> m;

	string s;
	cin >> s;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	string t(m, '\0');
	for (int i = 0; i < n; i++)
		t[--A[i]] = s[i];
	for (int i = 0; i < n; i++)
		swap(s[i], t[A[i]]);
	cout << s;
}