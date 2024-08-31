#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int arr[200000];

map<int, vector<int>> inds;

int main(){
	int N;
	cin >> N;
	ll S = 0;
	for(int i = 0; i < N; i++){
		cin >> arr[i];
		S += arr[i];
		inds[arr[i]].push_back(i);
	}
	S *= 2;
	if(S%N != 0){
		cout << -1 << endl;
		return 0;
	}
	S /= N;

	vector<int> res;
	for(int i = 0; i < N; i++){
		int needed = S - arr[i];
		if(!(inds.count(needed)) || inds[needed].empty()){
			cout << -1 << endl;
			return 0;
		}
		res.push_back(inds[needed].back());
		inds[needed].pop_back();
	}
	for(int i : res){
		cout << (i+1) << " ";
	}
	cout << endl;

}