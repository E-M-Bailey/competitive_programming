#include <bits/stdc++.h>

using namespace std;

int arr[500];
int N;

void process(){
	cin >> N;
	for(int i = 0; i < 3*N; i++) cin >> arr[i];
	sort(arr, arr+3*N);
	int res = 0;
	for(int i = N; i < 3*N; i += 2){
		res += arr[i];
	}
	cout << res << endl;
}

int main()
{
	int t;
	cin >> t;
	for(int i = 0; i < t; i++) process();

}