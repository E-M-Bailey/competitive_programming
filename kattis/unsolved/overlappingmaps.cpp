#include <bits/stdc++.h>

using namespace std;

typedef double T;
typedef complex<T> C;

T const conv = atan(1) / 45;

int main()
{
	int w, h, x, y, s, r;
	while (cin >> w >> h >> x >> y >> s >> r, w)
	{
		C ans = C(x, y) / (1. - polar<T>(s * .01, r * conv));
		cout << fixed << setprecision(2) << real(ans) << ' ' << imag(ans) << '\n';
	}
}