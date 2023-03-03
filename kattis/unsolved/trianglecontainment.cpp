#include <bits/stdc++.h>
using namespace std;

// 0-indexed Fenwick tree; based on KACTL implementation
struct BIT
{
	int n;
	vector<int64_t> S;
	BIT(int n): n(n), S(n) {}
	// Add d to position i
	void upd(int i, int d)
	{
		for (; i < n; i |= i + 1)
			S[i] += d;
	}
	int64_t sum(int i)
	{
		int64_t s = 0;
		for (; i > 0; i &= i - 1)
			s += S[i - 1];
		return s;
	}
};

// Coordinate compression. Y becomes the inverse mapping.
unordered_map<int, int> compress(vector<int>& Y)
{
	// Sort and remove duplicates, then construct inverse map
	sort(begin(Y), end(Y));
	Y.resize(unique(begin(Y), end(Y)) - begin(Y));
	unordered_map<int, int> CC;
	CC.reserve(size(Y));
	for (int i = 0; i < size(Y); i++)
		CC[Y[i]] = i;
	return CC;
}

struct point
{
	int i, x, y, v;
};

// Orders points with positive y-coordinates by angle in clockwise order
struct cmp
{
	int x;
	cmp(int x): x(x) {}
	bool operator()(const point& l, const point& r) const
	{
		// (x1 - x) / y1 < (x2 - x) / y2
		return (int64_t)(l.x - x) * r.y < (int64_t)(r.x - x) * l.y;
	}
};

// For each treasure point (x0, y0), finds the total value of all points in the region
//  - below the horizontal line at y0, and
//  - left of the line connecting (x0, y0) with (x, 0).
// Values are multiplied by mul and added to the point's entry in S.
void go(vector<point>& P, vector<int64_t>& S, const unordered_map<int, int>& CC, int x, int mul)
{
	// Sweep radially about (x, 0) in clockwise order
	sort(begin(P), end(P), cmp(x));
	// Stores values encountered so far, keyed by compressed y-coordinate
	int k = size(CC);
	BIT T(k);
	for (auto& [i, x, y, v] : P)
	{
		int cc = CC.find(y)->second;
		// Compute sum for this point
		S[i] += mul * T.sum(cc);
		// Update T for later points
		T.upd(cc, v);
	}
	cerr << endl;
}

int main()
{
	int n, x;
	cin >> n >> x;
	vector<point> P(n);
	for (int i = 0; i < n; i++)
	{
		auto& [j, x, y, v] = P[i];
		j = i;
		cin >> x >> y >> v;
	}

	// Coordinate compression: map each of the k unique y-coordinates to a number in [0, k), preserving order
	vector<int> Y(n);
	for (int i = 0; i < n; i++)
		Y[i] = P[i].y;
	unordered_map<int, int> CC = compress(Y);

	vector<int64_t> S(n);
	go(P, S, CC, 0, -1);
	go(P, S, CC, x, 1);

	for (int64_t s : S)
		cout << s << '\n';
}