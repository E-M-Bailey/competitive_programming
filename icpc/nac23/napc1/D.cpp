#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) int(size(x))
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

typedef long double T;
const T E = 1e-9l;

struct isect_info
{
	T x, y, a;
	int i, c;
};

struct circ
{
	int i;
	T x, y, r;
	//vector<isect_info> IS;
	circ(int i) : i(i)
	{
		cin >> x >> y >> r;
	}
	//void add_isect(T X, T Y, int c)
	//{
	//	IS.push_back({ X, Y, atan2l(Y - y, X - x) }
	//}
};
vector<circ> C;

// sqrt(r^2 - x^2) = sqrt(R^2 - (x - d)^2)
// r^2 - x^2 = R^2 - x^2 + 2xd - d^2
// (r^2 - R^2 + d^2)/(2d) = x
//void isect(circ &a, circ &b)
//{
//	T r2 = a.r * a.r, R2 = b.r * b.r;
//	T dx = b.x - a.x, dy = b.y - a.y, d2 = dx * dx + dy * dy;
//	if (d2 < E) return;
//	T ld = (r2 - R2 + d2) / 2;
//	T l2 = ld * ld / d2;
//	if (r2 - l2 <= 0 || R2 - l2 + 2 * ld - d2 <= 0)
//		return;
//	T d = sqrtl(d2);
//	T ax = dx / d, ay = dy / d;
//	T bx = -ay, by = ax;
//
//}

const int START = 0, END = 1, ISECT = 2;

struct event
{
	T x, y;
	int tp, i, j;
};

bool operator<(event const &a, event const &b)
{
	return a.x > b.x;
}

T cmp_x;
struct arc
{
	circ &c;
	bool top;
};

bool operator<(arc const &a, arc const &b)
{

}

priority_queue<event> PQ;




void proc(event e)
{
	switch (e.tp)
	{
	case START:

		break;
	case END:

		break;
	case ISECT:

		break;
	}
}

void solve(int n)
{
	C.clear();
	rep(i, 0, n)
		C.emplace_back(i);
	priority_queue<event> PQ;
	for (circ &c : C)
	{
		PQ.push(event{ c.x - c.r, c.y, START, c.i });
		PQ.push(event{ c.x + c.r, c.y, END, c.i });
	}

	vector<event> eout;
	while (!PQ.empty())
	{
		event e = PQ.top();
		PQ.pop();
		proc(e);
	}
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int n;
	while (cin >> n, n)
		solve(n);
}

