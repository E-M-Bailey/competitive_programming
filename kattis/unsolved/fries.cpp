#include <bits/stdc++.h>

using namespace std;

typedef float F;
typedef complex<F> C;

int constexpr PN = 27;
int constexpr N = 1 << PN;
C W[PN + 1];

int rev(int i)
{
	unsigned r = i;
	r = (r >> 16) | (r << 16);
	r = ((r & 0xff00ff00) >> 8) | ((r & 0x00ff00ff) << 8);
	r = ((r & 0xf0f0f0f0) >> 4) | ((r & 0x0f0f0f0f) << 4);
	r = ((r & 0xcccccccc) >> 2) | ((r & 0x33333333) << 2);
	r = ((r & 0xaaaaaaaa) >> 1) | ((r & 0x55555555) << 1);
	return r >> 5;
}

C buf[N];

// based on https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
template<bool I>
void fft_helper(C const *X, C *Y)
{
	for (int i = 0; i < N; i++)
		Y[i] = X[rev(i)];
	for (int s = 1, m = 1; m < N; s++, m *= 2)
	{
		C wm = I ? W[s] : conj(W[s]);
		for (int k = 0; k < N; k += 2 * m)
		{
			C w = 1;
			for (int j = k; j < k + m; j++, w *= wm)
			{
				C e = Y[j], o = w * Y[j + m];
				Y[j] = e + o;
				Y[j + m] = e - o;
			}
		}
	}
}

C A[N], B[N];
void conv_times_n(C *X, C const *Y)
{
	fft_helper<0>(X, A);
	fft_helper<0>(Y, B);
	for (int i = 0; i < N; i++)
		A[i] *= B[i];
	fft_helper<1>(A, X);
}

C X[N], Y[N], Z[N];
int main()
{
	for (int i = 0; i < N; i++)
	{
		unsigned r = i;
		r = (r >> 16) | (r << 16);
		r = ((r & 0xff00ff00) >> 8) | ((r & 0x00ff00ff) << 8);
		r = ((r & 0xf0f0f0f0) >> 4) | ((r & 0x0f0f0f0f) << 4);
		r = ((r & 0xcccccccc) >> 2) | ((r & 0x33333333) << 2);
		r = ((r & 0xaaaaaaaa) >> 1) | ((r & 0x55555555) << 1);
		R[i] = r >> 5;
	}
	F theta = 8 * (F)atan(1);
	for (int i = 0; i <= PN; i++, theta /= 2)
		W[i] = exp(C(0, theta));

	int n, m;
	float l;
	cin >> n >> m >> l;
	l *= N;
	for (int i = 0; i < n; i++)
	{
		int p;
		cin >> p;
		X[i] += 1;
	}

	F y = 1;
	for (int i = 1; i <= m / 2; i++)
		y = y * (m / 2 + i) / (4 * i);
	if (m % 2 == 0)
	{
		for (int i = m / 2; i <= m; y = y * (F)(m - i) / (F)i)
			Y[m - i * 2] = Y[m + i * 2] = y;
	}
	else
	{

	}
	conv_times_n(X, Y);
	int ans = 0;
	for (auto x : X)
		ans += real(x) >= l;
	cout << ans;
}