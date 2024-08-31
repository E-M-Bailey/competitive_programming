#include <bits/stdc++.h>

using namespace std;

string s;

int main(){
	int N;
	cin >> N;
	for(int i = 0;  i < N; i++){
		cin >> s;
		map<char, int> freq;
		int mx = 0;
		for(char c : s){
			freq[c]++;
			mx = max(mx, freq[c]);
		}
		cout << (s.size()-mx) << endl;
	}
}