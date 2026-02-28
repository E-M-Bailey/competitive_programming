#include <bits/extc++.h>

using namespace std;

template<typename C, integral T = int>
static constexpr int sz(const C& c)
{
	return static_cast<T>(size(c));
}

int main()
{
	string s, t, ss, tt;
	cin >> s >> t;
	vector<int> S{ 0 }, T{ 0 };
	for (char c : s)
		if (c == 'A')
			++S.back();
		else
		{
			S.push_back(0);
			ss.push_back(c);
		}
	for (char c : t)
		if (c == 'A')
			++T.back();
		else
		{
			T.push_back(0);
			tt.push_back(c);
		}
	if (ss != tt)
	{
		cout << "-1";
		return 0;
	}
	int k = 0;
	for (int i = 0; i < sz(S); ++i)
		k += abs(S[i] - T[i]);
	cout << k;
}
