#include <bits/stdc++.h>

using namespace std;

int main()
{
	int64_t n;
	while (cin >> n)
	{
		for (int64_t x = 1;; x *= 18)
		{
			if (n <= x)
			{
				cout << "Ollie wins.\n";
				break;
			}
			else if (n <= x * 9)
			{
				cout << "Stan wins.\n";
				break;
			}
		}
	}
}