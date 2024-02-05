#include <bits/stdc++.h>

using namespace std;

int main()
{
	size_t n, k;
	cin >> n >> k;

	vector<size_t> par(n);
	for (auto &p : par)
	{
		cin >> p;
		p--;
	}

	vector<bool>		   vis(n);
	vector<vector<size_t>> ch(n);
	vector<vector<size_t>> cy;
	vector<size_t>		   st;
	vector<size_t>		   pos(n, SIZE_MAX);

	for (size_t i = 0; i < n; i++)
	{
		if (vis[i])
			continue;
		st.push_back(i);
		pos[i] = 0;
		for (;;)
		{
			auto v = par[st.back()];
			if (pos[v] != SIZE_MAX)
			{
				cy.emplace_back(rbegin(st), rend(st) - pos[v]);
				st.resize(pos[v]);
				for (auto w : cy.back())
				{
					vis[w] = true;
					pos[w] = SIZE_MAX;
				}
			}
			if (vis[v])
			{
				while (!st.empty())
				{
					ch[v].push_back(st.back());
					vis[st.back()] = true;
					pos[st.back()] = SIZE_MAX;
					v			   = st.back();
					st.pop_back();
				}
				break;
			}
			pos[v] = pos[st.back()] + 1;
			st.push_back(v);
		}
	}

	vector<bool>	   state(n);
	vector<deque<int>> dq(n);
	vector<int>		   ksum(n), ans(n);

	for (auto const &cyc : cy)
	{
		for (auto i : cyc)
		{
			st.push_back(i);
			while (!st.empty())
			{
				auto v = st.back();
				if (!state[v])
				{
					state[v] = true;
					for (auto w : ch[v])
						st.push_back(w);
					continue;
				}
				st.pop_back();
				for (auto w : ch[v])
				{
					if (dq[w].size() > dq[v].size())
					{
						dq[w].swap(dq[v]);
						swap(ksum[w], ksum[v]);
					}
					for (size_t j = 0; j < dq[w].size(); j++)
						dq[v][j] += dq[w][j];
					ksum[v] += ksum[w];
				}
				if (dq[v].size() == k + 1)
				{
					ksum[v] -= dq[v].back();
					dq[v].pop_back();
				}
				dq[v].push_front(1);
				ksum[v]++;
				ans[v] = ksum[v];
			}
		}

		size_t sz = 0;
		for (auto v : cyc)
			sz = max(sz, dq[v].size());
		sz += cyc.size() - 1;
		deque<int> dcyc(sz);
		for (size_t i = 0; i < cyc.size(); i++)
		{
			for (size_t j = 0; j < dq[cyc[i]].size(); j++)
				dcyc[j + i] += dq[cyc[i]][j];
		}
		int ks = accumulate(begin(dcyc), begin(dcyc) + min(k + 1, size(dcyc)), 0);
		for (size_t i = 0; i < cyc.size(); i++)
		{
			ans[cyc[i]] = ks;
			dcyc.push_back(0);
			for (size_t j = 0; j < dq[cyc[i]].size(); j++)
			{
				int x = dq[cyc[i]][j];
				if (j <= k && j + cyc.size() > k)
					ks -= x;
				dcyc[j] -= x;
				dcyc[j + cyc.size()] += x;
			}
			ks -= dcyc.front();
			dcyc.pop_front();
			if (dcyc.size() > k)
				ks += dcyc[k];
		}
	}

	for (int ks : ans)
		cout << ks << '\n';
}
