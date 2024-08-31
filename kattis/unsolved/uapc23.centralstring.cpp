#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, l, d;
	cin >> n >> l >> d;
	string ans(l, '\0');
	vector<string> A(n);
	unordered_set<int> IS;
	for (int i = 0; i < l; i++)
		IS.insert(i);
	for (string& a : A)
		cin >> a;
	for (int i = 0; i < l; i++)
	{
		int c = A[0][i];
		bool all = true;
		for (int j = 1; j < n; j++)
			if (A[j][i] != c)
				all = false;
		if (all)
		{
			ans[i] = c;
			IS.erase(i);
		}
	}
	vector<int> I(begin(IS), end(IS));
	sort(begin(I), end(I));


}