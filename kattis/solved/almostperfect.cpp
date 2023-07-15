#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		cout << n << ' ';
		int64_t sum = 1;
		int n2 = n;
		for (int i = 2; i * i <= n2; i++)
		{
			int mul = 1;
			while (n2 % i == 0)
			{
				n2 /= i;
				mul = mul * i + 1;
			}
			sum *= mul;
		}
		if (n2 != 1)
			sum *= n2 + 1;
		
		if (sum == 2 * n)
			cout << "perfect";
		else if (abs(sum - 2 * n) <= 2)
			cout << "almost perfect";
		else
			cout << "not perfect";
		cout << '\n';
	}
}