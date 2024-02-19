#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int ct[3]{};
	int n;
	cin >> n;
	while (n--)
		for (int i = 0; i < 3; i++)
		{
			char c;
			cin >> c;
			ct[i] += c == 'J';
		}
	cout << *min_element(begin(ct), end(ct));
}