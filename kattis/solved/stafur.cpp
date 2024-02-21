#include <bits/stdc++.h>

using namespace std;

int main()
{
	char c;
	cin >> c;
	switch (c)
	{
	case 'Y':
		cout << "Kannski";
		break;
	case 'A':
	case 'E':
	case 'I':
	case 'O':
	case 'U':
		cout << "Jebb";
		break;
	default:
		cout << "Neibb";
		break;
	}
}
