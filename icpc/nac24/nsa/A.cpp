// UT Dallas whooosh
#include <bits/stdc++.h>

using namespace std;

string const HEX = "0123456789ABCDEF";

void p8(int n)
{
	cout << HEX[n / 16] << HEX[n % 16];
}

void p32(int n)
{
	p8(n >> 24);
	p8((n >> 16) % 256);
	p8((n >> 8) % 256);
	p8(n % 256);
}

int r4(string::iterator &it)
{
	char c = *it++;
	return int(find(begin(HEX), end(HEX), c) - begin(HEX));
}

int r8(string::iterator &it)
{
	int a = r4(it);
	int b = r4(it);
	return a * 16 + b;
}
int r32(string::iterator &it)
{
	int a = r8(it);
	int b = r8(it);
	int c = r8(it);
	int d = r8(it);
	return (((a * 256 + b) * 256 + c) * 256 + d);
}

int bcnt(int x)
{
	for (int i = 1; i < 32; i *= 2)
		x |= x >> i;
	return __builtin_popcount(x);
}

void enc(string s)
{
	map<char, int> F;
	for (char c : s)
		F[c]++;
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> PQ;
	for (auto [c, f] : F)
		PQ.emplace(f, string(1, c));
	map<char, vector<bool>> H;
	while ((int)size(PQ) > 1)
	{
		auto [f1, s1] = PQ.top();
		PQ.pop();
		auto [f2, s2] = PQ.top();
		PQ.pop();
		for (char c : s1)
			H[c].push_back(0);
		for (char c : s2)
			H[c].push_back(1);
		string s3 = s1 + s2;
		sort(begin(s3), end(s3));
		PQ.emplace(f1 + f2, s3);
	}
	// for (auto &[c, hc] : H)
	// {
	// 	reverse(begin(hc), end(hc));
	// }
	int n = (int)size(F);
	p8(n);

	vector<char> C;
	for (auto [c, f] : F)
	{
		C.push_back(c);
	}
	sort(begin(C),
		 end(C),
		 [&](char c, char d)
		 {
			 return pair{size(H[c]), c} < pair{size(H[d]), d};
		 });
	int ctr = -1;
	int lp = -1, bp = -1;
	for (char c : C)
	{
		ctr++;
		int lc = (int)size(H[c]), bc = bcnt(ctr);
		if (lp >= 0 && lc > lp)
		{
			ctr <<= lc - lp;
		}
		// if (lp >= 0 && lc > lp && bc == bp)
		// {
		// 	ctr *= 2;
		// }
		// cerr << c << ' ' << lc << ' ' << bc << ' ' << lp << ' ' << bp << ' ' << ctr << endl;
		lp				 = lc;
		bp				 = bcnt(ctr);
		int			 cur = ctr;
		vector<bool> H2;
		for (int i = 0; i < (int)size(H[c]); i++)
		{
			H2.push_back(cur % 2);
			cur /= 2;
		}
		reverse(begin(H2), end(H2));
		H[c] = move(H2);
		p8((int)c);
		p8((int)size(H[c]));
	}
	vector<bool> S;
	for (char c : s)
	{
		for (bool b : H[c])
			S.push_back(b);
	}
	int k1 = (int)size(S);
	while (size(S) % 8)
		S.push_back(0);
	int k = (int)size(S);
	p32(k1);
	// cout << flush;
	for (int i = 0; i < k / 8; i++)
	{
		int x = 0;
		for (int j = 0; j < 8; j++)
		{
			x = 2 * x + S[i * 8 + j];
		}
		p8(x);
		// cout << flush;
	}
	// for (int i = 0; i < k / 8; i++)
	// {
	// 	int x = 0;
	// 	for (int j = 0; j < 8; j++)
	// 	{
	// 		x = 2 * x + S[i * 8 + j];
	// 	}
	// 	cout << bitset<8>(x);
	// }
}

void dec(string s)
{
	auto it = begin(s);
	int	 n	= r8(it);

	string ans;

	int						ctr = -1;
	int						lp = -1, bp = -1;
	map<vector<bool>, char> H;
	for (int i = 0; i < n; i++)
	{
		ctr++;
		char c	= char(r8(it));
		int	 lc = r8(it);
		int	 bc = bcnt(ctr);
		if (lp >= 0 && lc > lp)
		{
			ctr <<= lc - lp;
		}
		// cerr << c << ' ' << lc << ' ' << bc << ' ' << lp << ' ' << bp << ' ' << ctr << endl;
		lp				 = lc;
		bp				 = bcnt(ctr);
		int			 cur = ctr;
		vector<bool> hc;
		for (int j = 0; j < lc; j++)
		{
			hc.push_back(cur % 2);
			cur /= 2;
		}
		reverse(begin(hc), end(hc));
		H[hc] = c;
	}
	int			 k = r32(it);
	vector<bool> S;
	vector<bool> t;
	for (int i = 0; i < (k + 7) / 8; i++)
	{
		int x = r8(it);
		for (int j = 0; j < 8; j++)
		{
			S.push_back(x % 2);
			x /= 2;
		}
		reverse(begin(S) + i * 8, begin(S) + (i + 1) * 8);
	}
	while (size(S) > k)
		S.pop_back();
	for (bool b : S)
	{
		t.push_back(b);
		auto jt = H.find(t);
		if (jt != end(H))
		{
			t.clear();
			ans += jt->second;
		}
	}
	cout << ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string cmd, s;
	getline(cin, cmd);
	getline(cin, s);
	if (cmd[0] == 'C')
		enc(s);
	else
		dec(s);
	cout << '\n';
}
