#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	cin >> s;
	int C[]{ 4, 3, 2, 7, 6, 5, 0, 4, 3, 2, 1 };
	int tot = 0;
	for (int i = 0; i < 11; i++)
	{
		tot += (s[i] - '0') * C[i];
	}
	cout << (tot % 11 == 0);
}