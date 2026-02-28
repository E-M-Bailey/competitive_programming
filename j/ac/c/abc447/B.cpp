#include <bits/extc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int F[26]{};
	int mf = 0;
	for (char c : s)
		mf = max(mf, ++F[c - 'a']);
	erase_if(s, [F, mf](char c) { return F[c - 'a'] == mf; });
	cout << s;
}
