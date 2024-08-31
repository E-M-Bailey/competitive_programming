#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

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

void go()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> A(n), D(m), F(k);
	for (int &a : A)
		cin >> a;
	for (int &d : D)
		cin >> d;
	for (int &f : F)
		cin >> f;

	sort(ALL(D));
	sort(ALL(F));

	vector<int> AD(n - 1);
	for (int i = 1; i < n; i++)
		AD[i - 1] = A[i] - A[i - 1];

	int idx = int(max_element(ALL(AD)) - begin(AD));
	int l	= A[idx];
	int r	= A[idx + 1];
	int lo	= max(idx == 0 ? 0 : *max_element(begin(AD), begin(AD) + idx),
				  idx == n - 2 ? 0 : *max_element(begin(AD) + idx + 1, end(AD)));
	int hi = AD[idx];
	for (int d : D)
	{
		// minimize max(f - (l - d), r - f - d)
		int	 cl = l - d, cr = r - d, cm = cl + (cr - cl) / 2;
		auto it = upper_bound(ALL(F), cm);
		if (it != end(F) && cl < *it && *it < cr)
			hi = min(hi, max(*it - cl, cr - *it));
		if (it != begin(F) && cl < *--it && *it < cr)
			hi = min(hi, max(*it - cl, cr - *it));
	}
	cout << max(hi, lo) << '\n';
}
