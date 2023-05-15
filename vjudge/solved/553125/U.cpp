#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int T;
	cin >> T;
	while (T--)
	{
		string s;
		int a, b;
		cin >> s;
		a = stoi(s);
		b = stoi(s.substr(s.find('/') + 1));
		s.clear();
		while (a != b)
		{
			cerr << a << ' ' << b << ' ';
			if (b > a)
			{
				b -= a;
				s += 'L';
			}
			else
			{
				a -= b;
				s += 'R';
			}
			swap(a, b);
		}
		cout << s << '\n';
	}
}