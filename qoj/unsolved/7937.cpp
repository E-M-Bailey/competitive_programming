#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)
#define sz(C)		 int(C.size())

typedef long long ll;
typedef pair<int, int> pii;
int N;
vector<int> arr;

ll reg[18] = {0};

void solve(vector<int> &v, int d){
	if(d == -1){
		return;
	}
	vector<int> v1, v2;
	for(int i : v){
		//cout << i << " ";
		if((i>>d)&1){
			v2.push_back(i);
		}
		else{
			v1.push_back(i);
			reg[d] += v2.size();
		}
	}
	//cout << endl;
	solve(v1, d-1);
	solve(v2, d-1);
}


int main(int argc, char const *argv[])
{
	cin >> N;
	arr = vector<int>(N, 0);
	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}
	int D = 0;
	while((1<<D) < N) D++;
	ll C2 = N/2;
	//cout << D << endl;
	solve(arr, D-1);

	ll res = 0;
	ll ans = 0;
	for(int i = 0; i < D; i++){
		//cout << reg[i] << " " << C2 << endl;
		if(2*reg[i] > C2){
			res ^= (1<<i);
			reg[i] = C2-reg[i];
		}
		ans += reg[i];
		C2 *= 2;
	}
	if(res != 0){
		ans++;
	}
	cout << ans << endl;

}
