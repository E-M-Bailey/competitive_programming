#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef pair<int, ld> pdi;

int N, K;
vector<int> Q, F;

bool works(ld v){
	priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
	for(int i = 0; i < N; i++){
		ld needed = v*K;
		while(!pq.empty() && pq.top().first <= i) pq.pop();
		pq.push(make_pair(F[i], (ld)Q[i]));
		while(!pq.empty() && needed > 1e-12){
			pdi p = pq.top();
			pq.pop();
			if(needed > p.second){
				needed -= p.second;
			}
			else{
				p.second -= needed;
				needed = 0.0;
				pq.push(p);
			}
		}
		if(needed > 1e-12){
			return false;
		}
	}
	return true;
}

int main()
{
	cin >> N >> K;
	Q = vector<int>(N);
	F = vector<int>(N);
	for(int i = 0; i < N; i++){
		cin >> Q[i] >> F[i];
	}

	if(!works(1e-9)){
		cout << -1 << endl;
		return 0;
	}

	ld b = 0.0;
	ld e = 1e12;
	while(e-b > 1e-10){
		ld m = (b+e)/2;
		if(works(m)){
			b = m;
		}
		else{
			e = m;
		}
	}
	cout << fixed << setprecision(12) << b << endl;
}