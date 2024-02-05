#include <bits/stdc++.h>

using namespace std;

const double PI2 = 8 * atan(4);

void fft_helper(vector<complex<double>> &X, complex<double> w)
{
	int n = size(X);
	if (n <= 1)
		return;

	vector<complex<double>> A(n / 2), B(n / 2);
	for (int i = 0; i < n; i++)
		(i % 2 ? B : A)[i / 2] = X[i];

	fft_helper(A, w * w);
	fft_helper(B, w * w);

	complex<double> wi = 1;
	for (int i = 0; i < n / 2; i++)
	{
		X[i]		 = A[i] + wi * B[i];
		X[i + n / 2] = A[i] - wi * B[i];
		wi *= w;
	}
}

void fft(vector<complex<double>> &X)
{
	double a = PI2 / size(X);
	fft_helper(X, {cos(a), -sin(a)});
}

void ifft(vector<complex<double>> &X)
{
	double a = PI2 / size(X);
	fft_helper(X, {cos(a), sin(a)});
	for (auto &x : X)
		x /= size(X);
}

int main()
{
	vector<complex<double>> A(256), B(256);

	string s;
	getline(cin, s);
	for (char c : s)
		A[c] += 1;
	for (char c : {'a', 'e', 'i', 'o', 'u'})
		B[c] = B[c - 32] = 1;
	reverse(begin(B), begin(B) + 128);

	fft(A);
	fft(B);
	for (int i = 0; i < 256; i++)
		A[i] *= B[i];
	ifft(A);

	cout << round(real(A[127]));
}
