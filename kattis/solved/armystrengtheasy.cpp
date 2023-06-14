#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int m, n;
		cin >> m >> n;
		priority_queue<int, vector<int>, greater<>> A, B;
		while (m--)
		{
			int a;
			cin >> a;
			A.push(a);
		}
		while (n--)
		{
			int b;
			cin >> b;
			B.push(b);
		}
		for (;;)
		{
			if (A.empty())
				cout << "Mecha";
			else if (!B.empty())
			{
				if (A.top() < B.top())
					A.pop();
				else
					B.pop();
				continue;
			}
			break;
		}
		cout << "Godzilla\n";
	}
}