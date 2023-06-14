#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int LIM = 1e7 + 1;

int C;
vector<pii> v;

double dist(pii a){
	return sqrt(a.first*a.first + a.second*a.second);
}

bool cw(pii a, pii b, pii c){
	pii p1 = {b.first-a.first, b.second - a.second};
	pii p2 = {c.first-b.first, c.second-b.second};
	return (p1.first * p2.second - p1.second * p1.first < 0);
}

bool ccw(pii a, pii b, pii c){
	return cw(c, b, a);
}

int cross(pii a, pii b, pii c){
	pii p1 = {b.first-a.first, b.second - a.second};
	pii p2 = {c.first-a.first, c.second - a.second};
	return p1.first*p2.second - p1.second*p2.first;
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	cin >> C;
	v = vector<pii>(C);
	for(int i = 0; i < C; i++){
		cin >> v[i].first >> v[i].second;
		v[i].first += 1000;
		v[i].second += 1000;
	}
	sort(v.begin(), v.end());

/*
	vector<pii> pts;
	vector<pii> h;
	int s = 0, t = 0;
	for(int it = 2; it--; s = --t, reverse(all(pts))){
		for(auto p : pts){
			while(t >= s+2 && cross(h[t-2], h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	}
	pts = {h.begin(), h.begin()+t - (t==2 && h[0] == h[1])};

	double res = 0.0;
	int n = sz(pts);
	int j = (n<2 ? 0 : 1);
	for (int i = 0; i<j; i++) {
		for (;; j = (j+1)%n) {
			res = max(res, dist(make_pair(pts[i].first - pts[j].first, pts[i].second - pts[j].second)));
			auto p1 = make_pair(pts[(j+1)%n].first - pts[j].first, pts[(j+1)%n].second - pts[j].second);
			auto p2 = make_pair(pts[i+1].first- pts[i].first, pts[i+1].second - pts[i].second);
			if (p1.first * p2.second - p1.second * p2.first >= 0) break;
		}
	}

	// for(int i = 0; i < pts.size(); i++){
	// 	for(int e = 0; e < i; e++){
	// 		res = max(res, dist({pts[i].first-pts[e].first, pts[i].second-pts[e].second}));
	// 	}
	// }*/

	int mx[2001];
	int my[2001];
	int x[2001];
	int y[2001];
	fill_n(mx, 2001, -100000);
	fill_n(my, 2001, -100000);
	fill_n(x, 2001, 100000);
	fill_n(y, 2001, 100000);
	for(int i = 0; i < C; i++){
		mx[v[i].first] = max(mx[v[i].first], v[i].second);
		x[v[i].first] = min(x[v[i].first], v[i].second);
		my[v[i].second] = max(my[v[i].second], v[i].first);
		y[v[i].second] = min(y[v[i].second], v[i].first);
	}
	vector<pii> pts;
	for(int i = 0; i <= 2000; i++){
		if(abs(x[i]) < 10000)pts.push_back({i, x[i]});
		if(abs(mx[i]) < 10000)pts.push_back({i, mx[i]});
		if(abs(y[i]) < 10000)pts.push_back({y[i], i});
		if(abs(my[i]) < 10000)pts.push_back({my[i], i});
	}
	double res = 0.0;
	 for(int i = 0; i < pts.size(); i++){
	 	for(int e = 0; e < i; e++){
	 		res = max(res, dist({pts[i].first-pts[e].first, pts[i].second-pts[e].second}));
	 	}
	 }
	
	cout << fixed << setprecision(9) << res << endl;
}

// g+ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out