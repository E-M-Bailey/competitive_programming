#include "template.hpp"

using namespace std;
namespace rng = ranges;
namespace vws = views;
using namespace abbrev;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k = 0, s = 0;
	cin >> n;
	vpi32 T(n);
	for (auto &[t, d] : T)
		cin >> t >> d;
	rng::sort(T, {}, &pi32::second);
	for (int i = 0; i < n; ++i)
	{
		auto [t, d] = T[i];
		s += t;
		rng::push_heap(T | vws::take(i + 1), {}, &pi32::first);
		while (s > d)
		{
			s -= (T[0].first + 1) / 2;
			T[0].first /= 2;
			for (int j = 0, j2; (j2 = j * 2 + 1) <= i && T[j2 += (j2 + 1 <= i && T[j2 + 1].first >= T[j2].first)].first > T[j].first; j = j2)
				swap(T[j], T[j2]);
			++k;
		}
	}
	cout << k;
}
