#include <bits/stdc++.h>

using namespace std;

int N, L;
vector<int> lines;

int main() {
	cin >> N >> L;
	L *= 5;
	lines = vector<int>(N);
	for(int i = 0; i < N; i++){
		cin >> lines[i];
	}
	sort(lines.begin(), lines.end());
	int sum = 0;
	int res = 0;
	while(res < N && sum+lines[res] <= L){
		sum += lines[res];
		res++;
	}
	cout << res << endl;
}