#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("O3")

struct pp
{
	int p, pp;//, ct;
};

int constexpr LIM = 5e7 + 1;
pp HPP[LIM]{};

/*
vector<pair<int, int>> MOB[LIM]{};

vector<int> D;
void divs(int n)
{
	static vector<pp> PP;
	PP.clear();
	for (int n2 = n; n2 > 1; n2 /= HPP[n2].pp)
		PP.push_back(HPP[n2]);

	D.clear();
	int d = 1;
	do
	{
		D.push_back(d);

		for (int i = 0; i < (int)PP.size(); i++)
		{
			if (d % PP[i].pp == 0)
				d /= PP[i].pp;
			else
			{
				d *= PP[i].p;
				break;
			}
		}
	} while (d != 1);
}*/

int main()
{
	for (int i = 2; i < LIM; i++)
	{
		if (HPP[i].p > 0)
			continue;
		for (int j = 1, k = i; k < LIM; j++, k += i)
		{
			HPP[k] = { i, i };//, 1 };
			if (HPP[j].p == i)
			{
				HPP[k].pp *= HPP[j].pp;
				//HPP[k].ct += HPP[j].ct;
			}
		}
	}
	int N;
	while (cin >> N)
	{
		__int128_t sum = 0;
		for (int i = 2; i <= N; i++)
		{
			int d = N / i;
			int tot = i;
			for (int j = i; j > 1; j /= HPP[j].pp)
			{
				tot = tot / HPP[j].p * (HPP[j].p - 1);
			}
			sum += (__int128_t)d * (d + 1) / 2 * tot;
		}
		string ans;
		do
			ans.push_back(char(sum % 10 + '0'));
		while (sum /= 10);
		reverse(begin(ans), end(ans));
		cout << ans << endl;
	}

	/*
	//int64_t cost = 0, pc = 0;
	vector<int> MP;
	for (int i = 1; i < LIM; i++)
	{
		if (i % 100000 == 0)
			cerr << i << endl;
		MP.clear();
		for (int x = i; x > 1; x /= HPP[x].pp)
			MP.push_back(HPP[x].p);
		MOB[i].reserve(1 << MP.size());
		for (int mask = 0; mask < 1 << (int)MP.size(); mask++)
		{
			int x = 1;
			for (int j = 0; j < (int)MP.size(); j++)
			{
				if (mask & (1 << j))
					x *= MP[j];
				//cost++;
			}
			int sign = __builtin_parity(mask) ? -1 : 1;
			MOB[i].emplace_back(x, sign);
		}
		//if (cost / 100000000 > pc / 100000000)
		//	cerr << cost << endl;
		//pc = cost;
	}

	int N;
	cin >> N;
	int64_t ans = 0;
	for (int i = 1; i <= N; i++)
	{
		divs(i);
		for (int d : D)
		{
			int sum = 0;
			for (auto [n, sign] : MOB[d])
			{
				sum += sign * (d / n - 1);
			}
			//cerr << i << ' ' << d << ' ' << sum << endl;
			ans += (int64_t)i / d * sum;
		}
	}

	cout << ans;
	*/
}