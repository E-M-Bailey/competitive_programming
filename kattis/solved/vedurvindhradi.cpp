#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	auto i = s.find('.');
	s.erase(i, 1);
	int n = stoi(s);

	if (n <= 2)
		cout << "Logn";
	else if (n <= 15)
		cout << "Andvari";
	else if (n <= 33)
		cout << "Kul";
	else if (n <= 54)
		cout << "Gola";
	else if (n <= 79)
		cout << "Stinningsgola";
	else if (n <= 107)
		cout << "Kaldi";
	else if (n <= 138)
		cout << "Stinningskaldi";
	else if (n <= 171)
		cout << "Allhvass vindur";
	else if (n <= 207)
		cout << "Hvassvidri";
	else if (n <= 244)
		cout << "Stormur";
	else if (n <= 284)
		cout << "Rok";
	else if (n <= 326)
		cout << "Ofsavedur";
	else
		cout << "Farvidri";
}
