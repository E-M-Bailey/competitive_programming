#include <bits/stdc++.h>

using namespace std;

int main()
{
	int h, b;
	cin >> h >> b;
	h *= b;
	cout << h / 2;
	if (h % 2)
		cout << ".5";
}
