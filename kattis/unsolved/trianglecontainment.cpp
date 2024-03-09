#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> ppi;
typedef long double ld;
typedef long long ll;

int N, X;
int x[100001];
int y[100001];
int v[100001];
int yy[100001];
ppi pts[100001];
ll res[100001];

map<int, int> mp;
map<pii, int> orig;

struct FT{
	vector<ll> s;
	FT(int n): s(n){}
	void update(int pos, ll dif){
		for(; pos < s.size(); pos |= pos+1) s[pos] += dif;
	}
	ll query(int pos){
		ll res = 0;
		for(; pos > 0; pos &= pos-1){
			res += s[pos-1];
		}
		return res;
	}
};

int main()
{
	cin >> N >> X;
	for(int i = 0; i < N; i++){
		cin >> x[i] >> y[i] >> v[i];
		yy[i] = y[i];
		orig[make_pair(x[i], y[i])] = i;
	}

	sort(yy, yy+N);
	int ind = 1;
	for(int i = 0; i < N; i++){
		if(mp.count(yy[i])) continue;
		mp[yy[i]] = ind;
		ind++;
	}
	for(auto p : mp){
		yy[p.second] = p.first;
	}

	for(int i = 0; i < N; i++){
		pts[i] = make_pair(make_pair(x[i], y[i]), make_pair(mp[y[i]], v[i]));
	}
	
	sort(pts, pts+N, [&](auto &a, auto &b){ return (ld)a.first.first/a.first.second < (ld) b.first.first/b.first.second;});

	for(int i = 0; i < N; i++){
		auto p = pts[i];
		//cout << p.first.first << " " << p.first.second << endl;
	}

	FT ft(N+10);
	for(auto p : pts){
		int ind = orig[p.first];
		res[ind] -= ft.query(p.second.first);
		ft.update(p.second.first, p.second.second);
	}

	sort(pts, pts+N, [&](auto &a, auto &b){ return (ld)(a.first.first-X)/a.first.second < (ld) (b.first.first-X)/b.first.second;});

	for(int i = 0; i < N; i++){
		auto p = pts[i];
		//cout << p.first.first << " " << p.first.second << endl;
	}

	FT ft2(N+10);
	for(auto p : pts){
		int ind = orig[p.first];
		res[ind] += ft2.query(p.second.first);
		ft2.update(p.second.first, p.second.second);
	}

	for(int i = 0; i < N; i++){
		cout << res[i] << endl;
	}

}