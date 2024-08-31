#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

typedef long long ll;
#define sz(C) int(size(C))

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
		go();
}

uint64_t constexpr A1 = 31, A2 = 37, M1 = 1e9 + 7, M2 = 1e9 + 9;

struct Tree
{
	struct T
	{
		uint64_t h1, h2;
		uint64_t p1, p2;
	};
	static constexpr T unit{0, 0, 1, 1};

	T f(T a, T b)
	{
		return {(a.h1 * b.p1 + b.h1) % M1, (a.h2 * b.p2 + b.h2) % M2, a.p1 * b.p1 % M1, a.p2 * b.p2 % M2};
	} // (any associative fn)
	vector<T> s;
	int		  n;
	Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e)
	{ // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2)
		{
			if (b % 2)
				ra = f(ra, s[b++]);
			if (e % 2)
				rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
struct FT
{
	vector<ll> s;
	FT(int n = 0) : s(n) {}
	void update(int pos, ll dif)
	{ // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1)
			s[pos] += dif;
	}
	ll query(int pos)
	{ // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1)
			res += s[pos - 1];
		return res;
	}
};

void go()
{
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;

	vector<int64_t> SO(n + 1), SE(n + 1);
	for (int i = 2; i < n; i++)
	{
		SO[i + 1] = SO[i];
		SE[i + 1] = SE[i];
		(i % 2 ? SO : SE)[i + 1] += i;
	}

	Tree H1(n), H2(n);
	FT	 E[26], O[26];
	for (int i = 0; i < 26; i++)
		E[i] = O[i] = FT(n);

	for (int i = 0; i < n; i++)
	{
		Tree::T cur{s[i] - 'a', s[i] - 'a', A1, A2};
		H1.update(i, cur);
		H2.update(n - 1 - i, cur);
		(i % 2 ? O : E)[s[i] - 'a'].update(i, 1);
	}

	while (q--)
	{
		int l, r;
		cin >> l >> r;
		l--;

		auto h1 = H1.query(l, r), h2 = H2.query(n - r, n - l);

		ll cur = 0;
		if (h1.h1 != h2.h1 || h1.h2 != h2.h2)
			cur += r - l;

		int e = 0, o = 0;
		for (int i = 0; i < 26; i++)
		{
			if (E[i].query(r) - E[i].query(l))
				e |= 1 << i;
			if (O[i].query(r) - O[i].query(l))
				o |= 1 << i;
		}
		int ce = __builtin_popcount(e), co = __builtin_popcount(o);
		if (ce > 1 || co > 1)
			cur += SO[r - l] + SE[r - l];
		else if (ce && co && e != o)
			cur += SE[r - l];
		cout << cur << '\n';
	}
}

// tuple<int, int, int> proj(pair<int, int> a, int b)
// {
// 	return {a.first / b, a.second, a.first % b};
// }
//
// uint64_t constexpr A1 = 13, /*A2 = 13,*/ M1 = 1e9 + 9, /*M2 = 1e9 + 9,*/ I1 = 615384621 /*I2 = 615384621*/;
//
// struct hash_deque
// {
// 	deque<char> S;
// 	uint64_t	h1 = 0, /*h2 = 0,*/ p1 = 1 /*p2 = 1*/;
//
// 	size_t size() const
// 	{
// 		return S.size();
// 	}
// 	bool empty() const
// 	{
// 		return S.empty();
// 	}
// 	uint64_t hash() const
// 	{
// 		return h1;
// 	}
//
// 	char front() const
// 	{
// 		return S.front();
// 	}
// 	char back() const
// 	{
// 		return S.back();
// 	}
// 	char operator[](size_t n) const
// 	{
// 		return S[n];
// 	}
//
// 	void push_front(char c)
// 	{
// 		S.push_front(c);
// 		h1 = (h1 + (c - '0') * p1) % M1, p1 = p1 * A1 % M1;
// 		//h2 = (h2 + (c - '0') * p2) % M2, p2 = p2 * A2 % M2;
// 	}
// 	void push_back(char c)
// 	{
// 		S.push_back(c);
// 		h1 = (h1 * A1 + c - '0') % M1, p1 = p1 * A1 % M1;
// 		//h2 = (h2 * A2 + c - '0') % M2, p2 = p2 * A2 % M2;
// 	}
// 	void pop_front()
// 	{
// 		char c = front();
// 		S.pop_front();
// 		p1 = p1 * I1 % M1, h1 = (h1 + M1 - (c - '0') * p1 % M1) % M1;
// 		//p2 = p2 * I2 % M2, h2 = (h2 + M2 - (c - '0') * p2 % M2) % M2;
// 	}
// 	void pop_back()
// 	{
// 		char c = back();
// 		S.pop_back();
// 		p1 = p1 * I1 % M1, h1 = (h1 + M1 - (c - '0')) * I1 % M1;
// 		//p2 = p2 * I2 % M2, h2 = (h2 + M2 - (c - '0')) * I2 % M2;
// 	}
//
// 	void clear()
// 	{
// 		S.clear();
// 		h1 = /*h2 =*/ 0;
// 		//p1 = p2 = 1;
// 	}
// };
//
// struct palindrome_deque
// {
// 	int		   l = 0;
// 	int		   E[26]{}, O[26]{};
// 	hash_deque pre{}, suf{};
//
// 	void push_front(int i, char c)
// 	{
// 		pre.push_front(c);
// 	}
// };
//
// void go()
// {
// 	int n, q;
// 	cin >> n >> q;
// 	string s;
// 	cin >> s;
// 	vector<tuple<int, int, int>> Q(q);
//
// 	int b = 1;
// 	while (b * b < n)
// 		b++;
//
// 	int q_ctr = 0;
// 	for (auto &[l, r, i] : Q)
// 	{
// 		cin >> l >> r;
// 		l--;
// 		i = q_ctr++;
// 	}
// 	sort(begin(Q),
// 		 end(Q),
// 		 [b](tuple<int, int, int> x, tuple<int, int, int> y)
// 		 {
// 			 return proj({get<0>(x), get<1>(x)}, b) < proj({get<0>(y), get<1>(y)}, b);
// 		 });
//
// 	int				ll = 0, rr = 0;
// 	int				E[26]{}, O[26]{};
// 	vector<int64_t> ans(q);
//
// 	vector<int64_t> SO(n + 1), SE(n + 1);
// 	for (int i = 2; i < n; i++)
// 	{
// 		SO[i + 1] = SO[i];
// 		SE[i + 1] = SE[i];
// 		(i % 2 ? SO : SE)[i + 1] += i;
// 	}
//
// 	hash_deque forw, back;
//
// 	for (auto [l, r, i] : Q)
// 	{
// 		while (ll > l)
// 		{
// 			ll--;
// 			forw.push_front(s[ll]);
// 			back.push_back(s[ll]);
// 			(ll % 2 ? O : E)[s[ll] - 'a']++;
// 		}
// 		while (rr < r)
// 		{
// 			forw.push_back(s[rr]);
// 			back.push_front(s[rr]);
// 			(rr % 2 ? O : E)[s[rr] - 'a']++;
// 			rr++;
// 		}
// 		while (ll < l)
// 		{
// 			forw.pop_front();
// 			back.pop_back();
// 			(ll % 2 ? O : E)[s[ll] - 'a']--;
// 			ll++;
// 		}
// 		while (rr > r)
// 		{
// 			rr--;
// 			forw.pop_back();
// 			back.pop_front();
// 			(rr % 2 ? O : E)[s[rr] - 'a']--;
// 		}
//
// 		int64_t cur = 0;
// 		if (forw.hash() != back.hash())
// 			cur += r - l;
// 		int ce = count_if(E,
// 						  E + 26,
// 						  [](int x)
// 						  {
// 							  return x != 0;
// 						  });
// 		int co = count_if(O,
// 						  O + 26,
// 						  [](int x)
// 						  {
// 							  return x != 0;
// 						  });
// 		if (ce > 1 || co > 1)
// 			cur += SO[r - l] + SE[r - l];
// 		else if (ce && co && max_element(E, E + 26) - E != max_element(O, O + 26) - O)
// 			cur += SE[r - l];
// 		ans[i] = cur;
// 	}
//
// 	for (auto a : ans)
// 		cout << a << '\n';
// }
