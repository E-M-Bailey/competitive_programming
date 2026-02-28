#include <bits/extc++.h>

using namespace std;
namespace rng = ranges;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		string s;
		cin >> n >> s;
		vector<char> S;
		for (char c : s)
		{
			if (S.empty() || S.back() != c)
				S.push_back(c);
			else
				S.pop_back();
		}
		cout << (S.empty() ? "YES\n" : "NO\n");
	}
}
