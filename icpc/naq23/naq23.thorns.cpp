#include <bits/stdc++.h>

using namespace std;


template<class T> int sgn(T x) { return (x > 0) - (x < 0);}
template<class T>
struct Point{
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0): x(x), y(y) {}
	
	P operator+(P p) const { return P(x+p.x, y+p.y);}
	P operator-(P p) const { return P(x-p.x, y-p.y);}
	P operator*(T p) const { return P(x*p, y*p);}
	P operator/(T p) const { return P(x/p, y/p);}
	T dot(P p) const {return x*p.x + y*p.y;}
	T cross(P p) const {return x*p.y - y*p.x;}
	T dist2() const {return x*x+y*y;}

};

typedef long double ld;
typedef pair<int, ld> pdi;
typedef Point<double> P;
#define arg(p, q) atan2(p.cross(q), p.dot(q))


double circlePoly(P c, double r, vector<P> ps){
	auto tri = [&](P p, P q){
		auto r2 = r*r/2;
		P d = q-p;
		double a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
		double det = a * a - b;
		if(det <= 0) return arg(p, q) * r2;
		auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
		if(t < 0 || 1 <= s) return arg(p, q) * r2;
		P u = p+d*s, v = p+d*t;
		return arg(p, u)*r2 + u.cross(v)/2 + arg(v, q)*r2;
	};
	auto sum = 0.0;
	for(int i = 0; i < ps.size(); i++){
		sum += tri(ps[i]-c, ps[(i+1)%ps.size()]-c);
	}
	return sum;
}

int N, R, W, H;

int main()
{
	cin >> N >> R >> W >> H;

	P A(0, 0), B(W, 0), C(W, H), D(0, H);
	vector<P> pol{A, B, C, D, A};

	ld res=0.0;
	for(int i = 0; i < N; i++){
		int x, y, v;
		cin >> x >> y >> v;
		P cent((double)x, (double) y);
		ld area = circlePoly(cent, R, pol);
		res += area*v;
	}
	res /= (W*H);
	cout << fixed << setprecision(12) << res << endl;
}