#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;

using u64 = uint64_t;

struct rect
{
	u64 l, r, t, b;
	constexpr operator bool() const
	{
		return l <= r && t <= b;
	}
	constexpr friend rect operator&(rect const &R, rect const &S)
	{
		return { max(R.l, S.l), min(R.r, S.r), max(R.t, S.t), min(R.b, S.b) };
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int N, Q;
	cin >> N >> Q;
	vector<u64> I;
	unordered_map<u64, rect> A;
	string cmd;
	for (u64 i; N--;)
	{
		cin >> i >> cmd;
		rect &R = A[i];
		if (cmd[0] == 'S')
		{
			I.push_back(i);
			cin >> R.l >> hex >> R.t >> dec >> R.b;
			R.b += R.t - 1;
		}
		else
		{
			cin >> R.r;
		}
	}
	rng::sort(I);
	vector<u64> res;
	while (Q--)
	{
		rect R;
		cin >> cmd >> R.l >> R.r >> hex >> R.t >> R.b >> dec;
		for (u64 i : I)
			if (A[i] & R)
				res.push_back(i);
		cout << size(res);
		for (int i = 0; i < min<int>(size(res), 20); ++i)
			cout << ' ' << res[i];
		cout << '\n';
		res.clear();
	}
}
