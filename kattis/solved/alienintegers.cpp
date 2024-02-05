#include <bits/stdc++.h>

using namespace std;

string	   s, def;
bitset<10> S;

void norm(string &a)
{
	auto it = begin(a);
	while (it + 1 != end(a) && *it == '0')
		++it;
	a.erase(begin(a), it);
	if (a.empty() || (a.front() == '0' && a.size() > 1))
		exit(-1);
}

char succ(char c)
{
	int d = c - '0';
	while (d < 10 && S[d])
		d++;
	return char(d >= 10 ? -1 : d + '0');
}
char pred(char c)
{
	int d = c - '0';
	while (d >= 0 && S[d])
		d--;
	return char(d < 0 ? -1 : d + '0');
}
// 5555555 -> 4999999
string t1()
{
	char a = pred(s[0]), b = pred('9');
	if (a < 0)
	{
		if (s.size() == 1)
			return def;
		else
			a = '0';
	}
	return a + string(size(s) - 1, b);
}
// 6000000
string t2()
{
	char a = succ(s[0]), b = succ('0');
	if (a < 0)
		return def;
	else
		return a + string(size(s) - 1, b);
}
// 10000000
string t3()
{
	char a = succ('1'), b = succ('0');
	if (a < 0)
		return def;
	else
		return a + string(size(s), b);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> s;
	for (char c : s)
		S[c - '0'] = true;

	if (S.count() == 10)
	{
		cout << "Impossible";
		return 0;
	}

	def = succ('0');
	vector<string>			   T{t1(), t2(), t3(), def};
	map<int64_t, set<int64_t>> M;

	int64_t ns = atoll(s.c_str());
	for (auto &t : T)
	{
		norm(t);
		int64_t nt = atoll(t.c_str());
		M[abs(nt - ns)].insert(nt);
	}
	for (auto t : begin(M)->second)
		cout << t << ' ';
}
