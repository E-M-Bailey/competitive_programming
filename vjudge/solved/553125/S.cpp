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
		int K;
		string s;
		cin >> K >> s;
		auto pos = s.find('/');
		int p = stoi(s), q = stoi(s.substr(pos + 1));
		int d = p / q;
		p -= d * q;
		q -= p;
		p += q;
		q += d * p;
		cout << K << ' ' << p << '/' << q << '\n';
	}
}