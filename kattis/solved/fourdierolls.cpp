#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int A[4];
	for (int i = 0; i < n; i++)
		cin >> A[i];

	int a = 0, b = 0;
	if (n == 3)
		for (A[3] = 1; A[3] <= 6; A[3]++)
		{
			bool go_a = true;
			for (int i = 0; i < 4; i++)
				for (int j = i + 1; j < 4; j++)
					go_a &= A[i] != A[j];
			a += go_a;
			b += !go_a;
		}
	else if (n == 2)
		for (A[2] = 1; A[2] <= 6; A[2]++)
			for (A[3] = 1; A[3] <= 6; A[3]++)
			{
				bool go_a = true;
				for (int i = 0; i < 4; i++)
					for (int j = i + 1; j < 4; j++)
						go_a &= A[i] != A[j];
				a += go_a;
				b += !go_a;
			}
	else
		for (A[1] = 1; A[1] <= 6; A[1]++)
			for (A[2] = 1; A[2] <= 6; A[2]++)
				for (A[3] = 1; A[3] <= 6; A[3]++)
				{
					bool go_a = true;
					for (int i = 0; i < 4; i++)
						for (int j = i + 1; j < 4; j++)
							go_a &= A[i] != A[j];
					a += go_a;
					b += !go_a;
				}
	cout << a << ' ' << b;
}
