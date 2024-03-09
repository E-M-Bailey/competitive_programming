#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, q;
	cin >> n >> q;
	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= N >> i;
	N++;

	vector<long long> S(2 * N);
	for (int i = 0; i < n; i++)
		cin >> S[i + N];
	for (int i = N - 1; i; i--)
		S[i] = S[i * 2] + S[i * 2 + 1];

	while (q--)
	{
		int i;
		cin >> i;
		for (cin >> S[i += N]; i /= 2;)
			S[i] = S[i * 2] + S[i * 2 + 1];

		//for (auto s : S)
		//	cerr << s << ' ';
		//cerr << endl;

		int lo = 0, hi = n - 1;
		long long best = LLONG_MAX;
		int besti = n - 1;
		while (lo <= hi)
		{
			int mid = (lo + hi) / 2;
			long long left = 0;
			for (int l = N, r = mid + N; l < r; l /= 2, r /= 2)
			{
				if (l & 1) left += S[l++];
				if (r & 1) left += S[--r];
			}
			long long right = S[1] - left - S[mid + N];
			left += S[mid + N] / 2;
			right += S[mid + N] / 2;

			(left <= right ? left : right) += S[mid + N] % 2;
			//cerr << mid << ' ' << left << ' ' << right << endl;

			long long cur = abs(right - left);
			if (cur < best || (cur == best && mid < besti))
			{
				best = cur;
				besti = mid;
			}
			if (left >= right)
				hi = mid - 1;
			else
				lo = mid + 1;
		}
		cout << besti << '\n';

		//cerr << endl;
		//while ((i *= 2) < N * 2)
		//{
		//	auto l = cur + S[i], r = sum - l;
		//	cerr << ' ' << i << ' ' << cur << ' ' << S[i] << ' ' << l << ' ' << r << endl;
		//	if (l < r)
		//	{
		//		cur += S[i];
		//		i++;
		//	}
		//}
		//cout << i / 2 - N << '\n';
	}
}