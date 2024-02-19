#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int ans = 1;
	while ((4 * ans * ans - 1) * ans <= 3 * n)
		ans++;
	cout << ans - 1;
}
