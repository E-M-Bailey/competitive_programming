#include <bits/stdc++.h>

using namespace std;

int main()
{
	int N, M, K;
	cin >> N >> M >> K;
	if(K <= (N+1)*(1<<M)){
		cout << "yes\n";
	}
	else{
		cout << "no\n";
	}

}