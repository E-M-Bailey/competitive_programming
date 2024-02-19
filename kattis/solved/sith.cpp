#include <bits/stdc++.h>

using namespace std;

int main()
{
	string name;
	int	   a, b, diff;
	getline(cin, name) >> a >> b >> diff;
	if (diff < 0)
		cout << "JEDI";
	else if (a - b < 0)
		cout << "SITH";
	else
		cout << "VEIT EKKI";
}
