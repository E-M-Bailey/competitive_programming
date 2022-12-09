#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using point = complex<ll>;
typedef long double ld;

#define x real()
#define y imag()

long double shoe(point &a, point &b){
    return 0.5*(a.x*b.y-a.y*b.x);
}

long double area(vector<point> &v){
    long double area = 0.0;
    for(int i = 0; i < v.size(); i++){
        area += shoe(v[i], v[i+1]);
    }
    area += shoe(v[v.size()-1], v[0]);
    return abs(area);
}

ll dot(point a, point b) { return (conj(a)*b).x; }
long double len(point &a){
    return sqrt(dot(a, a));
}
ld angle(point v, point w) {
    return acos(clamp(dot(v,w)/len(v)/len(w),ld(-1),ld(1)));
}

int N;
vector<point> P;
stack<point> add;
vector<point> R, D;
string s;

bool sortbysec(point &a, point &b){
    return (a.y < b.y);
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++){
        int x1, y1;
        cin >> x1 >> y1;
        P.push_back(point(x1, y1));
    }
    cin >> s;

    R = vector<point>(N);
    D = vector<point>(N);
    for(int i = 0; i < N; i++) R[i] = D[i] = P[i];
    sort(R.begin(), R.end());
    sort(D.begin(), D.end(), sortbysec);
    for(int i = 0; i < N-2; i++){

    }
}
