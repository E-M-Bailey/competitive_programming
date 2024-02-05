#include <bits/stdc++.h>

using namespace std;

struct pt
{
	long double theta;
	int			x;
	int			y;
};

int main()
{
	int n;
	cin >> n;
	vector<pt>	H;
	long double cx = 0, cy = 0;
	while (n--)
	{
		int	 x, y;
		char c;
		cin >> x >> y >> c;
		if (c == 'N')
			continue;
		cx += x;
		cy += y;
		H.push_back({0, x, y});
	}
	cx /= H.size();
	cy /= H.size();
	for (auto &p : H)
		p.theta = atan2l(p.y - cy, p.x - cx);
	sort(begin(H),
		 end(H),
		 [](pt a, pt b)
		 {
			 return a.theta < b.theta;
		 });

	auto it = min_element(begin(H),
						  end(H),
						  [](pt a, pt b)
						  {
							  return make_pair(a.x, a.y) < make_pair(b.x, b.y);
						  });
	rotate(begin(H), it, end(H));

	cout << H.size() << '\n';
	for (auto [theta, x, y] : H)
		cout << x << ' ' << y << '\n';
}
