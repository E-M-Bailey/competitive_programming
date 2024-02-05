#include <bits/stdc++.h>

using namespace std;

int main()
{
	string str;
	cin >> str;
	for (char ch : str)
		if (ch >= 'A' && ch <= 'Z')
			cout << ch;
}
