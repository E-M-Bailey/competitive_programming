#include <bits/stdc++.h>
using namespace std;
typedef long double ldf;

const ldf EPS = 1e-9;
const ldf INF = numeric_limits<ldf>::infinity();
const ldf PI = 4 * atanl(1);

struct Circ {
	ldf x, y, m, b;
	ldf rad(ldf t) const {
		return m * t + b;
	}
	ldf area(ldf t) const {
		ldf r = rad(t);
		return PI * r * r;
	}
	friend ldf cdist(const Circ& a, const Circ& b) {
		ldf dx = b.x - a.x, dy = b.y - a.y;
		return sqrtl(dx * dx + dy * dy);
	}
	friend ldf sdist(const Circ& a, const Circ& b, ldf t) {
		ldf m = -(a.m + b.m);
		ldf h = cdist(a, b) - a.b - b.b;
		return m * t + h;
	}
	friend ldf time(const Circ& a, const Circ& b) {
		ldf m = -(a.m + b.m);
		ldf h = cdist(a, b) - a.b - b.b;
		return -h / m;
	}
	friend istream& operator>>(istream& strm, Circ& c) {
		return strm >> c.x >> c.y >> c.b >> c.m;
	}
	friend Circ merge(const vector<Circ>& C, ldf t) {
		int n = C.size();
		ldf x = 0, y = 0, m = 0, a = 0;
		for (const Circ& c : C) {
			x += c.x;
			y += c.y;
			a += c.area(t);
			m = max(m, c.m);
		}
		return Circ{x / n, y / n, m, sqrtl(a / PI) - m * t};
	}
};

int main() {
	int n;
	cin >> n;
	vector<Circ> C(n);
	for (Circ& c : C)
		cin >> c;
	unordered_set<int> M;
	ldf ans = C[0].rad(0);
	while (C.size() > 1) {
		n = C.size();
		//int bi = -1, bj = -1;
		ldf bt = INF;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				ldf t = time(C[i], C[j]);
				if (t < bt) {
					//bi = i;
					//bj = j;
					bt = t;
				}
			}
		while (true) {
            M.clear();
            n = C.size();
		    //vector<Circ> C2;
            //vector<bool> D(n);
            n = C.size();
			for (int i = 0; i < n; i++)
				for (int j = i + 1; j < n; j++) {
					ldf t = time(C[i], C[j]);
					if (t < bt + EPS) {
						M.insert(i);
                        M.insert(j);
					}
				}
            if (M.empty())
                break;
            vector<Circ> MC;
            for (int i : M)
                MC.push_back(C[i]);
            Circ mc = merge(MC, bt);
            vector<Circ> C2;
            for (int i = 0; i < n; i++)
                if (M.find(i) == M.end())
                    C2.push_back(C[i]);
            C2.push_back(mc);
            C = move(C2);
            ans = mc.rad(bt);
		}
	}
	cout << fixed << setprecision(7);
    cout << C[0].x << ' ' << C[0].y << endl;
    cout << ans;
}
