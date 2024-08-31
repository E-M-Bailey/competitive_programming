#include <bits/stdc++.h>

using namespace std;

vector<tuple<int, int, bitset<4>, bool>> E;
bool									 def;

bitset<4> parse_x(string const &s, int &i);
bitset<4> parse_p(string const &s, int &i)
{
	bitset<4> ans;
	if (s[i] == '(')
		ans = parse_x(s, ++i);
	else if (s[i] == 'x')
		ans = 12;
	else if (s[i] == 'y')
		ans = 10;
	else if (s[i] == '0')
		ans = 0;
	else
		ans = 15;
	i++;
	return ans;
}
bitset<4> parse_n(string const &s, int &i)
{
	bool p = 0;
	while (s[i] == '!')
		p = !p, i++;
	bitset<4> ans = parse_p(s, i);
	return p ? ~ans : ans;
}
bitset<4> parse_e(string const &s, int &i)
{
	bitset<4> ans = parse_n(s, i);
	while (s[i] == '=')
		ans ^= ~parse_n(s, ++i);
	return ans;
}
bitset<4> parse_a(string const &s, int &i)
{
	bitset<4> ans = parse_e(s, i);
	while (s[i] == '&')
		ans &= parse_e(s, ++i);
	return ans;
}
bitset<4> parse_o(string const &s, int &i)
{
	bitset<4> ans = parse_a(s, i);
	while (s[i] == '|')
		ans |= parse_a(s, ++i);
	return ans;
}
bitset<4> parse_x(string const &s, int &i)
{
	bitset<4> ans = parse_o(s, i);
	while (s[i] == '^')
		ans ^= parse_o(s, ++i);
	return ans;
}
bitset<4> parse(string const &s)
{
	int i = 0;
	return parse_x(s, i);
}

template<int K>
void solve(int n)
{
	array<array<bitset<4>, K>, K>			 seen{};
	vector<tuple<int, int, bitset<4>, bool>> F;
	for (auto [a, b, e, d] : E)
	{
		for (int i = 0; i < 4; i++)
			if (e[i] && !seen[a][b][i])
			{
				seen[a][b][i] = true;
				F.emplace_back(a, b, e, d);
			}
	}

	array<bitset<1 << K>, 1 << K> A{};
	for (int x = 0; x < (1 << K); x++)
	{
		if (def)
			A[x].set();
		bitset<K> X(x);
		for (int y = 0; y < (1 << K); y++)
		{
			bitset<K> Y(y);
			for (auto [a, b, e, d] : F)
			{
				if (e[int(X[a]) * 2 + int(Y[b])])
				{
					A[x][y] = d;
					break;
				}
			}
		}
	}

	long long p = 0, q = 0, r = 0;
	for (int x = 0; x < (1 << K); x++)
	{
		// cerr << A[x] << endl;
		if (A[x][x])
			p++;
		for (int y = 0; y < (1 << K); y++)
		{
			if (A[x][y] && A[y][x])
				q++;
			if (A[x][y])
				r += (~A[x] & A[y]).count();
		}
	}
	cout << p << ' ' << q << ' ' << r;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		int	   a, b, d;
		string s;
		cin >> a >> b >> s >> d;
		a--;
		b--;
		s.push_back(' ');
		E.emplace_back(a, b, parse(s), d);
	}
	cin >> def;
	switch (k)
	{
	case 1:
		solve<1>(n);
		break;
	case 2:
		solve<2>(n);
		break;
	case 3:
		solve<3>(n);
		break;
	case 4:
		solve<4>(n);
		break;
	case 5:
		solve<5>(n);
		break;
	case 6:
		solve<6>(n);
		break;
	case 7:
		solve<7>(n);
		break;
	case 8:
		solve<8>(n);
		break;
	case 9:
		solve<9>(n);
		break;
	case 10:
		solve<10>(n);
		break;
	}
}
