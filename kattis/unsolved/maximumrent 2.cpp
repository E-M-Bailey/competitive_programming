#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll a, b, m, o;

int main()
{
	cin >> a >> b >> m >> o;
	ll ans = 0;
	if(a > b){
		ans = (m-1)*a+b;
	}
	else{
		int x = max((ll)1, o-m);
		ans = a*x + b*(m-x);
	}

	cout << ans << endl;
}