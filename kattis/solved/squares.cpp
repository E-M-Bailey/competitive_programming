#include <bits/stdc++.h>

using namespace std;

using T = int64_t;

struct vec2
{
	T x, y;
	inline vec2(T x, T y) : x(x), y(y) {}

	vec2 operator-() const
	{
		return vec2{-x, -y};
	}

	vec2 operator-(vec2 v) const
	{
		return vec2{x - v.x, y - v.y};
	}

	vec2 operator*(T s) const
	{
		return vec2{x * s, y * s};
	}

	vec2 operator/(T s) const
	{
		return vec2{x / s, y / s};
	}

	vec2 reduce() const
	{
		if (x == 0 && y == 0)
			return *this;
		T	 g	 = gcd(abs(x), abs(y));
		vec2 ans = *this / g;
		if (ans.x < 0 || (ans.x == 0 && ans.y < 0))
			return -ans;
		else
			return ans;
	}

	T operator^(vec2 v) const
	{
		return x * v.y - y * v.x;
	}

	bool operator==(vec2 v) const
	{
		return x == v.x && y == v.y;
	}

	friend istream &operator>>(istream &strm, vec2 &v)
	{
		int x, y;
		strm >> x >> y;
		v.x = x;
		v.y = y;
		return strm;
	}
};

template<>
struct std::hash<vec2>
{
	inline size_t operator()(const vec2 &v) const
	{
		std::hash<T> tHash;
		return tHash((v.x << 32) + v.y);
	}
};

struct line
{
	vec2 pt{0, 0}, dir{0, 0};

	friend istream &operator>>(istream &strm, line &l)
	{
		vec2 b(0, 0);
		strm >> l.pt >> b;
		l.dir = (b - l.pt).reduce();
		return strm;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<line> lines(n);
	for (int i = 0; i < n; i++)
		cin >> lines[i];

	unordered_map<vec2, vector<vec2>> DR;
	for (line l : lines)
		DR[l.dir].push_back(l.pt);

	unordered_map<vec2, unordered_map<T, T>> DI;
	for (auto &[d, L] : DR)
	{
		int m = L.size();
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
			{
				T dist = abs(d ^ (L[j] - L[i]));
				DI[d][dist]++;
			}
	}

	T ans = 0;
	for (auto &[d1, D1] : DI)
	{
		vec2 d2 = vec2{d1.y, -d1.x}.reduce();
		if (DI.find(d2) == DI.end())
			continue;
		unordered_map<T, T> &D2 = DI[d2];
		for (auto [dist, c1] : D1)
		{
			if (dist == 0)
				continue;
			int c2 = D2[dist];
			ans += (T)c1 * c2;
		}
	}
	ans /= 8;
	string s;
	while (ans)
	{
		s.push_back(char(ans % 10 + '0'));
		ans /= 10;
	}
	if (s.empty())
		s.push_back('0');
	reverse(begin(s), end(s));
	cout << s;
}
