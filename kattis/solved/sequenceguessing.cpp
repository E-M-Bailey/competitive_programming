#include <bits/stdc++.h>

using namespace std;

bitset<66668> S;
int			  rem = 66668;
vector<int>	  M(33334, 0);

int qry(int x)
{
	int i = x / 3, m = x % 3;
	if (m == 0)
		return i * 2 + 1;
	if (M[i] == 0)
		M[i] = 3 - m;
	return M[i] == m ? i * 2 + 2 : -1;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	M[33333] = 1;
	cout << "66668\n" << flush;

	while (rem)
	{
		int x;
		cin >> x;
		if (x == -1)
		{
			for (int i = 0; i <= 100000; i++)
				if (qry(i) >= 0)
					cout << i << '\n';
			break;
		}
		int q = qry(x);
		if (q > 0 && !S[q - 1])
		{
			S[q - 1] = true;
			rem--;
		}
		cout << q << '\n' << flush;
	}
}
