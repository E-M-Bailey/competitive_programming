#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef pair<int, int> pii;

int N;
int K;
vector<int> dig;

bool solve(vector<int> res){
	if(res.size() == K){
		for(int i = 0; i < dig.size(); i++){
			int s = 0;
			for(int e = 0; e <= i; e++){
				if(e < res.size() && (i-e) < res.size()) s += res[e]*res[i-e];
			}
			s %= 10;
			//cout << s << " " << dig[i] << endl;
			if(s != dig[i]) return false;
		}
		for(int i : res) cout << i;
		cout << endl;
		return true;
	}
	int sz = res.size();
	int s = 0;
	for(int i = 1; i < sz; i++){
		s += res[i]*res[sz-i];
	}
	s %= 10;
	int m = (dig[sz] - s + 100) % 10;
	//cout << m << " " << s << " " << dig[sz] << endl;
	for(int d = 0; d < 10; d++){
		if((2*res[0]*d)%10 == m){
			//cout << sz << " " << d << endl;
			res.push_back(d);
			if(solve(res)){
				return true;
			}
			res.pop_back();
		}
	}
	return false;
}

string s;

int main()
{
	cin >> s;
	for(int i = 0; i < s.size(); i++){
		dig.push_back(s[i]-'0');
	}
	K = dig.size()/2 + 1;
	if(2*K-1 != dig.size()){
		cout << -1 << endl;
		return 0;
	}

	for(int i = 0; i < 10; i++){
		if((i*i)%10 == dig[0]){
			vector<int> res(1, i);
			if(solve(res)){
				return 0;
			}
		}
	}
	cout << -1 << endl;
}