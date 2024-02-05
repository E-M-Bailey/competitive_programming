#include <bits/stdc++.h>

using namespace std;

struct line
{
	int	 x1, y1, dx, dy;
	bool side(int x, int y) const
	{
		return dx * (y - y1) > dy * (x - x1);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int S;
	cin >> S;
	vector<line> L(S);
	for (line &l : L)
	{
		cin >> l.x1 >> l.y1 >> l.dx >> l.dy;
		l.dx -= l.x1;
		l.dy -= l.y1;
	}

	int T;
	cin >> T;
	while (T--)
	{
		int x3, y3, x4, y4;
		cin >> x3 >> y3 >> x4 >> y4;
		bool ct = 0;
		for (const line &l : L)
			ct ^= l.side(x3, y3) ^ l.side(x4, y4);
		cout << (ct ? "different\n" : "same\n");
	}
}
