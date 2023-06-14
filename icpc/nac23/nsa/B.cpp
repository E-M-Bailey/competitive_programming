#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

//string s;

/*
bool valid(char c)
{
	return ((c >= '0' & c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool good(char c)
{
	for (char l : s)
	{
		if (!valid(c ^ l)) return false;
	}
	return true;
}*/

uint8_t val(char c)
{
	return c <= '9' ? c - '0' : c - 'a' + 10;
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	string str;
	cin >> str;
	int n = sz(str) / 2;
	vector<uint8_t> s(n);
	for (int i = 0; i < n; i++)
	{
		s[i] = val(str[i * 2]) * 16 + val(str[i * 2 + 1]);
	}
	vector<vector<uint8_t>> DP;

	vector<uint8_t> A;
	for (uint8_t a = '0'; a <= '9'; a++) A.push_back(a);
	for (uint8_t a = 'a'; a <= 'z'; a++) A.push_back(a);
	for (uint8_t a = 'A'; a <= 'Z'; a++) A.push_back(a);

	bitset<256> AS{};
	for (uint8_t a : A)
		AS[a] = true;

	rep(l, 1, n + 1)
	{
		DP.resize(l);
		for (auto &row : DP)
			row.clear();
		bool good = true;
		rep(st, 0, l)
		{
			for (char a : A)
				DP[st].push_back(a ^ s[st]);
			good &= !DP[st].empty();
			for (int i = st + l; good && i < n; i += l)
			{
				for (int j = 0; j < sz(DP[st]);)
				{
					if (!AS[DP[st][j] ^ s[i]])
					{
						swap(DP[st][j], DP[st].back());
						DP[st].pop_back();
					}
					else
						j++;
				}
				//cerr << "Checked " << i << ' ' << st << ' ' << good << endl;
				good &= !DP[st].empty();
			}
			if (!good) break;
		}
		if (good)
		{
			//cerr << "DP:" << endl;
			//rep(st, 0, l)
			//{
			//	cerr << st;
			//	for (uint8_t dp : DP[st])
			//		cerr << ' ' << (int)dp;
			//	cerr << endl;
			//}
			for (auto &row : DP)
				sort(all(row));
			vector<int> I(l);
			const auto incr = [&]()
			{
				for (int i = l - 1; i >= 0; i--)
				{
					if (++I[i] >= sz(DP[i]))
						I[i] = 0;
					else
						return true;
				}
				return false;
			};
			do
			{
				cout << "0x" << hex;
				//for (int i : I)
				//	cerr << ' ' << i;
				//cerr << endl;
				rep(i, 0, l)
				{
					uint8_t val = DP[i][I[i]];
					cout << (val / 16) << (val % 16);
				}
				cout << '\n';
				//int idx = 0;
				//for (auto x : s)
				//{
					//cerr << (char)(x ^ DP[idx % l][I[idx % l]]);
					//idx++;
				//}
				//cerr << endl;
			} while (incr());
			return 0;
		}
	}

	/*
	for(int i = 0; i < 256; i++){
		if(good(i)){
			cout << hex << i << endl;
		}
	}*/
}

// g++ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out