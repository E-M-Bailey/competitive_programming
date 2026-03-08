#include "template.hpp"

using namespace std;
using namespace abbrev;

int operator^(pi32 a, pi32 b)
{
	return a.first * b.second - a.second * b.first;
}
pi32 operator-(pi32 a, pi32 b)
{
	return { a.first - b.first, a.second - b.second };
}

int main()
{
	api32<4> T;
	for (int i = 0; i < 3; ++i)
		cin >> T[i].first >> T[i].second;
	T[3] = T[0];
	int n, A = (T[0] - T[1]) ^ (T[2] - T[1]), k = 0;
	cout << abs(A) / 2 << '.' << (A & 1) * 5 << '\n';
	cin >> n;
	while (n--)
	{
		pi32 p;
		cin >> p.first >> p.second;
		int npos = 0, nneg = 0;
		for (int i = 0; i < 3; ++i)
		{
			int c = (T[i] - p) ^ (T[i + 1] - p);
			npos += c <= 0;
			nneg += c >= 0;
		}
		k += max(npos, nneg) == 3;
	}
	cout << k;
}
