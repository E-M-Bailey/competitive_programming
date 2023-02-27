#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;
using ll = long long;

int N;
vector<int> arr1, arr2;
set<int> w;
vector<int> weights;

bool works(int w){
	bool unfinished = 0;
	int curr = -1;
	for(int i = 0; i < N; i++){
		if(arr1[i] <= w) continue;
		if(unfinished){
			if(curr != arr1[i]) return false;
			unfinished = 0;
			curr = -1;
		}
		else{
			unfinished = 1;
			curr = arr1[i];
		}
	}
	if(unfinished) return false;
	for(int i = 0; i < N; i++){
		if(arr2[i] <= w) continue;
		if(unfinished){
			if(curr != arr2[i]) return false;
			unfinished = 0;
			curr = -1;
		}
		else{
			unfinished = 1;
			curr = arr2[i];
		}
	}
	return (!unfinished);
}

int main(int argc, const char* argv[]) {
	if (argc > 1) {
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin >> N;
	arr1 = vector<int>(N);
	arr2 = vector<int>(N);
	for(int i = 0; i < N; i++) {
		cin >> arr1[i];
		w.insert(arr1[i]);
	}
	for(int i = 0; i < N; i++) {
		cin >> arr2[i];
		w.insert(arr2[i]);
	}
	for(int i : w) weights.push_back(i);
	if(works(0)) {
		puts("0");
		return 0;
	}
	if(works(weights[0])){
		cout << weights[0] << endl;
		return 0;
	}
	int b = 0;
	int e = N-1;
	while(e-b > 1){
		int m = (b+e)/2;
		if(works(weights[m])) e = m;
		else b = m;
	}
	cout << weights[e] << endl;
	
	return 0;
}