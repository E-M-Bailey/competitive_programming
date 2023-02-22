#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> O(n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
	{
		char c;
		cin >> c;
		if (c == '(') O[j]++;
	}
	vector<int> V(n);
	for (int i = 0; i < n; i++)
	{
		sort(begin(V), end(V));
		for (int j = 0; j < O[i]; j++)
			++V[j];
		for (int j = O[i]; j < n; j++)
			if (--V[j] < 0)
			{
				cout << "No\n";
				return 0;
			}
	}
	cout << (accumulate(begin(V), end(V), 0) == 0 ? "Yes\n" : "No\n");
}