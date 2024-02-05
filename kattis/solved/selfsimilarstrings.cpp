#include <bits/stdc++.h>

using namespace std;

int main()
{
	string					   s;
	unordered_map<string, int> F;
	while (cin >> s)
	{
		int ans = 1;
		for (; ans < (int)s.size(); ans++)
		{
			F.clear();
			for (int i = ans; i <= (int)s.size(); i++)
				F[s.substr(i - ans, ans)]++;
			bool works = true;
			for (auto const &[_, f] : F)
				works &= f > 1;
			if (!works)
				break;
		}
		cout << --ans << '\n';
	}
}
