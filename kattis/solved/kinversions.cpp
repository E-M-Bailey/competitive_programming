#include <bits/stdc++.h>

using namespace std;
using namespace std::complex_literals;

template<typename T>
T rup2(T x)
{
	x--;
	for (int i = 1; i < 8 * (int)sizeof(T); i *= 2)
		x |= x >> i;
	return x + 1;
}

const double PI2 = atan(1) * 8;

void fft(vector<complex<double>>& X)
{
	int n = X.size();
	if (n <= 1)
		return;

	assert(n % 2 == 0);

	vector<complex<double>> X0(n / 2), X1(n / 2);
	for (int i = 0; i < n / 2; i++)
	{
		X0[i] = X[2 * i];
		X1[i] = X[2 * i + 1];
	}

	fft(X0);
	fft(X1);

	complex<double> w = polar<double>(1, PI2 / n), wi = 1.+0i;
	for (int i = 0; i < n / 2; i++)
	{
		X[i] = X0[i] + wi * X1[i];
		X[i + n / 2] = X0[i] - wi * X1[i];
		wi *= w;
	}
}

void ifft(vector<complex<double>>& X)
{
	int n = X.size();
	if (n <= 1)
		return;

	for (auto& x : X)
		x = conj(x);

	fft(X);

	double f = 1. / n;
	for (auto& x : X)
		x = conj(x) * f;
}

vector<int> convolve(const vector<int>& A, const vector<int>& B)
{
	int na = A.size(), nb = B.size();
	int nc = na + nb - 1;
	int n = rup2(nc);

	vector<int> C(nc);
	vector<complex<double>> AA(n), BB(n), CC(n);
	for (int i = 0; i < na; i++)
		AA[i] = complex<double>(A[i], 0);
	for (int i = 0; i < nb; i++)
		BB[i] = complex<double>(B[i], 0);

	fft(AA);
	fft(BB);

	for (int i = 0; i < n; i++)
		CC[i] = AA[i] * BB[i];
	ifft(CC);

	for (int i = 0; i < nc; i++)
		C[i] = int(round(real(CC[i])));

	return C;
}

vector<int> cross_correlate(const vector<int>& A, const vector<int>& B)
{
	vector<int> RA(A.crbegin(), A.crend());
	return convolve(RA, B);
}


int main()
{
    string S;
	cin >> S;
	int n = S.size();

	vector<int> A, B;
	A.reserve(n);
	B.reserve(n);
	for (char c : S)
	{
		A.push_back(c == 'A');
		B.push_back(c == 'B');
	}

	vector<int> C = cross_correlate(B, A);

	for (int k = n; k < n * 2 - 1; k++)
		cout << C[k] << endl;
}
