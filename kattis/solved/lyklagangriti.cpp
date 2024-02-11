#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string str;
	cin >> str;
	list<char>			 ans;
	list<char>::iterator it = begin(ans);
	for (char c : str)
	{
		if (c == 'L')
			--it;
		else if (c == 'R')
			++it;
		else if (c == 'B')
			ans.erase(prev(it));
		else
			ans.insert(it, c);
	}
	cout << string(begin(ans), end(ans));
}
