#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, K, P;
bool works(ll v){
	return (v <= K && N/v <= P);
}

int main() {
	cin >> N >> K >> P;
	vector<ll> res;
	for(ll i = 1; (ll)i*i <= N; i++){
		if(N%i != 0) continue;
		if(works(i)) res.push_back(i);
		if(N/i != i){
			if(works(N/i)) res.push_back(N/i);
		}
	}
	sort(res.begin(), res.end());
	cout << res.size() << endl;
	for(ll i : res) cout << i << endl;
	return 0;
}