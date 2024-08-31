#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int n = (int)size(s);

	vector<int> P(n, -1);
	vector<int> st;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '(')
			st.push_back(i);
		else if (s[i] == ')')
		{
			int j = st.back();
			st.pop_back();
			P[i] = j;
			P[j] = i;
		}
	}

	bool r = false;
	for (int i = 0; i < n; i = r ? i - 1 : i + 1)
	{
		if (s[i] == '(' || s[i] == ')')
		{
			i = P[i];
			r ^= 1;
		}
		else
			cout << char(r ? s[i] ^ 32 : s[i]);
	}
}
