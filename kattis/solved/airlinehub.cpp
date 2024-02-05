#include <bits/stdc++.h>

using namespace std;

typedef long double T;

T const DEG = atanl(1) / 45;

struct airport
{
	T la, lo;
	T x, y, z;
	T M = 0;
	airport(T lat, T lon) : la(lat), lo(lon)
	{
		T c;
		sincosl(lat * DEG, &z, &c);
		sincosl(lon * DEG, &y, &x);
		x *= c;
		y *= c;
	}
	friend T dist2(airport const &a, airport const &b)
	{
		T dx = b.x - a.x, dy = b.y - a.y, dz = b.z - a.z;
		return dx * dx + dy * dy + dz * dz;
	}
	friend bool operator<(airport const &a, airport const &b)
	{
		return a.M < b.M;
	}
};

T const EPS = 1e-9l;

int main()
{
	int				n;
	vector<airport> A;
	while (cin >> n)
	{
		A.clear();
		A.reserve(n);
		for (int i = 0; i < n; i++)
		{
			T la, lo;
			cin >> la >> lo;
			A.emplace_back(la, lo);
			for (int j = 0; j < i; j++)
			{
				T d2   = dist2(A[i], A[j]);
				A[i].M = max(A[i].M, d2 - i * EPS);
				A[j].M = max(A[j].M, d2 - j * EPS);
			}
		}
		auto &a = *min_element(begin(A), end(A));
		cout << fixed << setprecision(2) << a.la << ' ' << a.lo << '\n';
	}
}
