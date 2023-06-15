#include <bits/stdc++.h>

using namespace std;

struct v2
{
	int x, y;
};

v2 operator-(v2 a, v2 b)
{
	return { a.x - b.x, a.y - b.y };
}

int operator*(v2 a, v2 b)
{
	return a.x * b.x + a.y * b.y;
}

int operator^(v2 a, v2 b)
{
	return a.x * b.y - a.y * b.x;
}

bool operator<(v2 a, v2 b)
{
	return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(v2 a, v2 b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator!=(v2 a, v2 b)
{
	return a.x != b.x || a.y != b.y;
}

int main()
{
	v2 T[4];
	int z;
	while (cin >> T[0].x >> T[0].y >> z, T[0].x + T[0].y + z > 0)
	{
		for (int i = 1; i < 4; i++)
			cin >> T[i].x >> T[i].y >> z;

		sort(T, T + 3);

		bool ans;
		if (T[0] == T[1] && T[1] == T[2])
		{
			ans = T[3] == T[2];
		}
		else if (T[0] == T[1])
		{
			v2 d1 = T[2] - T[1], d2 = T[3] - T[1];
			int cp = d1 ^ d2, dp1 = d1 * d1, dp2 = d1 * d2;
			ans = cp == 0 && dp2 > 0 && dp2 < dp1;
			// cout << d1.x << ' ' << d1.y << ' ' << d2.x << ' ' << d2.y << endl;
			// cout << cp << ' ' << dp1 << ' ' << dp2 << endl;
		}
		else if (T[1] == T[2])
		{
			v2 d1 = T[0] - T[1], d2 = T[3] - T[1];
			int cp = d1 ^ d2, dp1 = d1 * d1, dp2 = d1 * d2;
			ans = cp == 0 && dp2 > 0 && dp2 < dp1;
		}
		else if (((T[2] - T[1]) ^ (T[1] - T[0])) == 0)
		{
			v2 d1 = T[2] - T[0], d2 = T[3] - T[0];
			int cp = d1 ^ d2, dp1 = d1 * d1, dp2 = d1 * d2;
			ans = cp == 0 && dp2 > 0 && dp2 < dp1;
		}
		else
		{
			bool pos = true, neg = true;
			for (int i = 0; i < 3; i++)
			{
				int cp = (T[(i + 1) % 3] - T[i]) ^ (T[3] - T[i]);
				pos &= cp > 0;
				neg &= cp < 0;
			}
			ans = pos || neg;
		}
		cout << (ans ? "YES\n" : "NO\n");
	}
}

/*
0 0 10000
0 10000 0
10000 0 0
3000 4000 3000

0 0 10000
10000 0 0
0 10000 0
3000 4000 3000

0 10000 0
0 0 10000
10000 0 0
3000 4000 3000

0 10000 0
10000 0 0
0 0 10000
3000 4000 3000

10000 0 0
0 0 10000
0 10000 0
3000 4000 3000

10000 0 0
0 10000 0
0 0 10000
3000 4000 3000

0 0 10000
0 10000 0
3000 4000 3000
10000 0 0

0 0 10000
3000 4000 3000
0 10000 0
10000 0 0

0 10000 0
0 0 10000
3000 4000 3000
10000 0 0

0 10000 0
3000 4000 3000
0 0 10000
10000 0 0

3000 4000 3000
0 0 10000
0 10000 0
10000 0 0

3000 4000 3000
0 10000 0
0 0 10000
10000 0 0

0 0 0
*/