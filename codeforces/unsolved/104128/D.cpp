#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, K, M, C, D;
vector<ll> A;

bool works(ll v){
	//cout << v << endl;
	vector<ll> arr(N);
	vector<int> ev(N+1);
	for(int i = 0; i < N; i++){
		if(D > 0)
			arr[i] = (v-A[i]-C+D-1) / D;
		else
			if(A[i]+C >= v) {
				arr[i] = 0;
			}
			else{
				arr[i] = 100000000;
			}
		ll l = 0;
		ll r = N-M;
		arr[i] = max(arr[i], (ll)0);
		if(A[i] >= v){
			ev[0]++;
			continue;
		}
		//cout << i << " " << arr[i] << endl;
		if(arr[i] >= M || i - arr[i] < 0 || i+1-M > N-M) continue;
		l = max(l, (i+1-M));
		r = min(r, (i-arr[i]));
		assert(l <= r);
		//if(arr[i] > N) continue;
		//cout << i << " " << arr[i] << " " << max(i+1-M, 0) << " " << (i+1-arr[i]) << endl;
		ev[l]++;
		ev[r+1]--;
		/*
		else if(arr[i] <= M){
			ev[max((int)(i+1-M), 0)]++;
			if(i+1-arr[i] < N){
				ev[max(0, (int)(i+1-arr[i]))]--;
			}
		}*/
	}
	int cnt = 0;
	//cout << v << endl;
	for(int i = 0; i < N; i++){
		cnt += ev[i];
		if(cnt >= K) return true;
	}
	return false;
}

int main(){
	cin >> N >> K >> M >> C >> D;
	A = vector<ll>(N);
	for(int i = 0; i < N; i++) cin >> A[i];
	ll b = 0;
	ll e = 1e9;
	e *= 10000000;
	
	while(e-b > 1){
		ll m = (e+b)/2;
		if(works(m)){
			b = m;
		}
		else{
			e = m;
		}
	}
	cout << b << endl;

}