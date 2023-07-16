#include <bits/stdc++.h>

using namespace std;

bitset<100001> S{};
int main()
{
	int n;
	cin >> n;
	S[0] = 1;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		S |= S << a;
		sum += a;
	}
	
	if (sum % 2 == 0 && S[sum / 2])
		cout << "YES";
	else
		cout << "NO";
}