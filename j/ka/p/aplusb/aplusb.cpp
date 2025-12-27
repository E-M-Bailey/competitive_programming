#include <bits/stdc++.h>

using namespace std;

typedef long double T;
typedef complex<T> C;

constexpr int rup2(int n)
{
	n--;
	for (int i = 1; i < 32; i *= 2)
		n |= n >> i;
	return n + 1;
}

void fft(C w, vector<C> &A)
{
	int n = (int)A.size();
	if (n <= 1)
		return;
	int m = n / 2;
	vector<C> E(m), O(m);
	for (int i = 0; i < m; i++)
	{
		E[i] = A[i * 2];
		O[i] = A[i * 2 + 1];
	}

	C w2 = w * w;
	fft(w2, E);
	fft(w2, O);

	C wi = 1;
	for (int i = 0; i < m; i++)
	{
		A[i] = E[i] + wi * O[i];
		A[i + m] = E[i] - wi * O[i];
		wi *= w;
	}
}

const T PI = 4 * atanl(1);

void fft(vector<C> &A)
{
	int n = (int)A.size();
	T theta = 2 * PI / n;
	fft(polar<T>(1, -theta), A);
}

void ifft(vector<C> &A)
{
	int n = (int)A.size();
	T theta = 2 * PI / n;
	fft(polar<T>(1, theta), A);
	for (auto &a : A)
		a /= n;
}

constexpr int N = rup2(200001);

int main()
{
	int n;
	cin >> n;
	vector<int64_t> A(n), F(100001), G(100001);
	for (auto &a : A)
	{
		cin >> a;
		F[a + 50000]++;
	}

	vector<C> X(N);
	for (int i = -50000; i <= 50000; i++)
		X[i + 50000] = F[i + 50000];
	fft(X);
	for (int i = 0; i < N; i++)
		X[i] *= X[i];
	ifft(X);
	for (int i = -50000; i <= 50000; i++)
		G[i + 50000] = (int64_t)round(X[i + 100000].real());

	int64_t f0 = F[50000], ans = 0;

	for (int a = -50000; a <= 50000; a++)
	{
		int64_t fa = F[a + 50000], ga = G[a + 50000], fa2 = F[a / 2 + 50000];
		// all
		ans += ga * fa;
		// i = j
		if (a % 2 == 0)
			ans -= fa2 * fa;
		// i = k, j = k
		ans -= 2 * f0 * fa;
	}
	// i = j = k
	ans += 2 * f0;

	cout << ans;
}