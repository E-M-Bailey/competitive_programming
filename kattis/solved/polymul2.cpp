#include <bits/stdc++.h>

using namespace std;

int rup2(int n)
{
	n--;
	for (int i = 1; i < 32; i *= 2)
		n |= n >> i;
	return n + 1;
}

typedef long double F;

template<typename T>
const T PI2 = atan((T)1) * 8;

template<typename T>
inline void dft(vector<complex<T>> &X)
{
	int n = (int)X.size();
	if (n <= 1)
		return;

	int				   m = n / 2;
	vector<complex<T>> X0(m), X1(m);
	for (int i = 0; i < m; i++)
	{
		X0[i] = X[i * 2];
		X1[i] = X[i * 2 + 1];
	}

	dft(X0);
	dft(X1);

	for (int i = 0; i < m; i++)
	{
		complex<T> wi = polar((T)1, -PI2<T> * i / n);
		X[i]		  = X0[i] + wi * X1[i];
		X[i + m]	  = X0[i] - wi * X1[i];
	}
}

template<typename T>
inline void idft(vector<complex<T>> &X)
{
	int n = (int)X.size();
	if (n <= 1)
		return;
	for (auto &x : X)
		x = conj(x);
	dft(X);
	T f = (T)1 / n;
	for (auto &x : X)
		x = conj(x) * f;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		int da;
		cin >> da;

		vector<complex<F>> A(da + 1);
		for (auto &a : A)
			cin >> a;
		int db;
		cin >> db;

		vector<complex<F>> B(db + 1);
		for (auto &b : B)
			cin >> b;

		int d = da + db;
		int n = rup2(d + 1);
		A.resize(n);
		B.resize(n);

		dft(A);
		dft(B);
		for (int i = 0; i < n; i++)
			A[i] *= B[i];
		idft(A);
		cout << d << '\n';
		for (int i = 0; i <= d; i++)
			cout << (int)round(real(A[i])) << ' ';
		cout << '\n';
	}
}
