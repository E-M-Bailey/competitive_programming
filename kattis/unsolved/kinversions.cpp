#include <bits/stdc++.h>

using namespace std;

typedef double			db;
typedef complex<double> cp;
typedef vector<cp>		vc;

db const PI2 = 8 * atan(1);

template<bool I, bool T = true>
vc fft(vc X)
{
	int n = (int)size(X);
	if (n <= 1)
		return X;
	vc E(n / 2), O(n / 2);
	for (int i = 0; i < n; i += 2)
	{
		E[i / 2] = X[i];
		O[i / 2] = X[i + 1];
	}
	E = fft<I, false>(E);
	O = fft<I, false>(O);
	vc Y(n);
	cp w = polar(1., PI2 / n), wi = 1.;
	for (int i = 0; i < n / 2; i++, wi *= w)
	{
		Y[i]		 = E[i] + wi * O[i];
		Y[i + n / 2] = E[i] - wi * O[i];
	}
	if (T && I)
		for (auto &y : Y)
			y /= n;
	return Y;
}

vc conv(vc const &A, vc const &B)
{
	vc C = fft<0>(A), D = fft<0>(B);
	vc E(size(C));
	for (int i = 0; i < (int)size(C); i++)
		E[i] = C[i] * D[i];
	return fft<1>(E);
}

int main()
{
	string s;
	cin >> s;
	int n = (int)size(s);
	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= N >> i;
	N = (N + 1) * 2;
	vc A(N), B(N);
	for (int i = 0; i < n; i++)
		(s[i] == 'A' ? A : B)[i] = 1.;
	reverse(begin(A), end(A));
	vc C = conv(A, B);
	C.erase(begin(C), begin(C) + 2);
	C.erase(begin(C) + n - 1, end(C));
	for (cp c : C)
		cout << (int)round(real(c)) << '\n';
}
