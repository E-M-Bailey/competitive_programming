#include <bits/stdc++.h>

using namespace std;

struct ent
{
	int ab, ac, ba, bc, ca, cb;
	ent() = default;
	ent(char a, char b) :
		ab(a == 'A' && b == 'T'),
		ac(a == 'A' && b == 'C'),
		ba(a == 'T' && b == 'A'),
		bc(a == 'T' && b == 'C'),
		ca(a == 'C' && b == 'A'),
		cb(a == 'C' && b == 'T')
	{}
	int cost() const
	{
		int a = ab + ac, A = ba + ca, b = ba + bc, B = ab + cb, c = ca + cb, C = ac + bc;
		//cerr << a << ' ' << A << ' ' << b << ' ' << B << ' ' << c << ' ' << C << endl;
		//cerr << ab << ' ' << ac << ' ' << ba << ' ' << bc << ' ' << ca << ' ' << cb << endl;
		if (a != A || b != B || c != C)
			return -1;
		int AB = min(ab, ba), AC = min(ac, ca), BC = min(bc, cb);
		//cerr << ' ' << AB << ' ' << AC << ' ' << BC << endl;
		return (ab + ac + ba + bc + ca + cb - 2 * (AB + AC + BC)) * 2 / 3 + AB + AC + BC;
	}
	friend ent operator+(ent const &a, ent const &b)
	{
		ent d;
		d.ab = a.ab + b.ab;
		d.ac = a.ac + b.ac;
		d.ba = a.ba + b.ba;
		d.bc = a.bc + b.bc;
		d.ca = a.ca + b.ca;
		d.cb = a.cb + b.cb;
		return d;
	}
};

int n;
vector<ent> S;

void init(string a, string b)
{
	n = (int)a.size();
	S.resize(2 * n);
	for (int i = 0; i < n; i++)
		S[i + n] = ent(a[i], b[i]);
	for (int i = n - 1; i > 0; i--)
		S[i] = S[2 * i] + S[2 * i + 1];
}

int get_distance(int x, int y)
{
	ent X{}, Y{};
	for (x += n, y += n + 1; x < y; x /= 2, y /= 2)
	{
		if (x % 2) X = X + S[x++];
		if (y % 2) Y = S[--y] + Y;
	}
	return (X + Y).cost();
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int N, q;
	cin >> N >> q;
	string a, b;
	cin >> a >> b;
	init(a, b);
	while (q--)
	{
		int x, y;
		cin >> x >> y;
		cout << get_distance(x, y) << '\n';
	}
}