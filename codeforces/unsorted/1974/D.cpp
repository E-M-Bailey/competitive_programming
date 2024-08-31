#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void solve(int N, int S, int &Na, int &Nb, int &Sa, int &Sb)
{
	while (N > S)
	{
		Na++;
		Nb++;
		N -= 2;
	}
	while (S > N)
	{
		Sa++;
		Sb++;
		S -= 2;
	}
	Na += N / 2;
	Nb += (N + 1) / 2;
	Sa += S / 2;
	Sb += (S + 1) / 2;
}

void go()
{
	int n;
	string s;
	cin >> n >> s;
	int N = 0, E = 0, S = 0, W = 0;
	for (char c : s)
	{
		N += c == 'N';
		E += c == 'E';
		S += c == 'S';
		W += c == 'W';
	}
	if ((N + S) % 2 || (E + W) % 2 || ((int)size(s) == 2 && s[0] != s[1]))
	{
		cout << "NO\n";
		return;
	}
	int Na = 0, Ea = 0, Sa = 0, Wa = 0;
	int Nb = 0, Eb = 0, Sb = 0, Wb = 0;
	solve(N, S, Na, Nb, Sa, Sb);
	solve(E, W, Eb, Ea, Wb, Wa);
	for (char c : s)
	{
		int &a = c == 'N' ? Na : c == 'E' ? Ea : c == 'S' ? Sa : Wa;
		int &b = c == 'N' ? Nb : c == 'E' ? Eb : c == 'S' ? Sb : Wb;
		if (a)
		{
			cout << 'R';
			a--;
		}
		else
		{
			cout << 'H';
			b--;
		}
	}
	cout << '\n';
}
