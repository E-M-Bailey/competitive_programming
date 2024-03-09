#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string ln;
	while (getline(cin, ln))
	{
		istringstream is(ln);
		vector<int> A;
		copy(istream_iterator<int>(is), istream_iterator<int>{}, back_inserter(A));
		int n = (int)size(A), k = *max_element(begin(A), end(A));
		vector<bool> V(k + 1, true);
		V[0] = false;
		int ct = k;
		bool good = true;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
			{
				int p = abs(A[i] - A[j]);
				if (V[p])
					ct--;
				else
					good = false;
				V[p] = false;
			}
		
		if (!good)
			cout << "not a ruler\n";
		else if (ct == 0)
			cout << "perfect\n";
		else
		{
			cout << "missing";
			for (int i = 1; i <= k; i++)
				if (V[i])
					cout << ' ' << i;
			cout << '\n';
		}
	}
}
