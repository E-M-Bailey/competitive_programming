#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int ys, yp, ls, lp;


void process(){
	cin >> yp >> lp >> ys >> ls;
	ll ym = (ll)ys*yp;
	ll lm = (ll)ls*lp;
	if(ys <= ls){
		ll res = ym;
		cout << res << endl;
		return;
	}
	if(yp <= lp){
		ll res = min(ym, lm);
		cout << res << endl;
		return;
	}
	ll m = yp;
	if(2*ls > ys){
		m = lp;
	}
	ll res = m*(2*ls-ys)+ym-lm;
	cout << res << endl;
}

int main()
{
	int t;
	cin >> t;
	for(int i = 0; i < t; i++) process();

}