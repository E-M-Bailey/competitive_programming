#include <bits/stdc++.h>

using namespace std;

typedef double F;
typedef complex<F> C;

C buf[1 << 19];

// use trie for length < l, where k patterns have length >= l: m + n (l + a k log(m + n))
// kl <= m, so this is <= m + n (l + a m log(m + n) / l), so let l = sqrt(a m log(m + n))
// O(m + n sqrt(a m log(m + n)))
// (this idea doesn't work)

void fft_impl(C *start, C *end, int dep, C w)
{
	int n = (end - start) >> dep;
	if (n <= 1)
		return;
	int stride = 1 << dep;
	C w2 = w * w;

	fft_impl(start, end - stride, dep + 1, w2);
	fft_impl(start + stride, end, dep + 1, w2);

	C wi = 1;
	n /= 2;
	for (int i = 0, j = 0; i < n; i++, j += 2 * stride, wi *= w)
	{
		buf[i] = start[j] + wi * start[j + stride];
		buf[i + n] = start[j] - wi * start[j + stride];
	}
	for (C *a = buf, *b = start; b != end; a++, b += stride)
		*b = *a;
}

int main()
{
	int n;
	while (cin >> n)
	{
		vector<string> S;

	}
}