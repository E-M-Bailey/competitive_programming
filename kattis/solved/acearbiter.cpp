#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	int pa = 0, pb = 0;
	string str;
	bool good = true;
	for (int i = 1; i <= n; i++)
	{
		cin >> str;
		auto pos = str.find('-');
		int a = stoi(str.substr(0, pos)), b = stoi(str.substr(pos + 1));
		if ((a + b + 1) % 4 >= 2)
			swap(a, b);
		good &= a >= pa && b >= pb && (a < 11 || b < 11);
		if (pa == 11 || pb == 11)
			good &= a == pa && b == pb;
		if (!good)
		{
			cout << "error " << i;
			break;
		}
		pa = a;
		pb = b;
	}
	if (good)
		cout << "ok";
}