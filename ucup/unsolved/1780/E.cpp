#include <algorithm>
#include <array>
#include <bit>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int const SMALL = numeric_limits<int>::min() / 2;

int n;
vector<pair<int, int>> A;
vector<int> W;
int ans = SMALL;

vector<int> cur;

array<int, 61> pq_freq;
unsigned long long pq_mask;

bool pq_empty()
{
	return pq_mask == 0;
}
int pq_top()
{
	// assume nonempty
	return countr_zero(pq_mask);
}
void pq_push(int x)
{
	pq_freq[x]++;
	pq_mask |= 1ull << x;
}
void pq_pop()
{
	int x = pq_top();
	pq_freq[x]--;
	if (pq_freq[x] == 0)
		pq_mask &= pq_mask - 1;
}

void part(int remaining_n, int lim)
{
	if (remaining_n == 0)
	{
		int k = (int)size(cur);
		int ptr = 0;
		int weight = 0;
		bool bad = false;
		for (int i = k - 1; i >= 0; i--)
		{
			int x = cur[i];
			while (ptr < n && A[ptr].first <= x)
			{
				pq_push(A[ptr].second);
				ptr++;
			}
			int rem = x;
			while (rem > 0)
			{
				if (pq_empty() || pq_top() < x)
				{
					bad = true;
				bad = true;
					break;
				}
				rem--;
				pq_pop();
			}
			if (bad)
			{
				break;
			}
			weight += W[x - 1];
		}
		if (ptr == n && !bad)
		{
			ans = max(ans, weight);
		}
		while (!pq_empty())
		{
			pq_pop();
		}

		return;
	}

	for (int x = 1; x <= lim; x++)
	{
		cur.push_back(x);
		part(remaining_n - x, min(remaining_n - x, x));
		cur.pop_back();
	}
}

int main()
{
	cin >> n;
	A.resize(n);
	W.resize(n);

	for (auto &[l, r] : A)
		cin >> l >> r;
	for (int &w : W)
		cin >> w;

	sort(begin(A), end(A));

	part(n, n);

	if (ans == SMALL)
	{
		cout << "impossible";
	}
	else
	{
		cout << ans;
	}
}

