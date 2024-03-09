#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int tests;cin >> tests;
	while (tests--)
	{
		int n;cin >> n;
		vector<pair<pii, int>> queries;
		vector<pii> el;
		rep(i, 0, n)
		{
			char op;cin >> op;
			if (op == '+')
			{
				int x, w;cin >> x >> w;
				el.pb({ x - 1,w });
			}
			else
			{
				assert(op == '?');
				int a, b, k;cin >> a >> b >> k;
				a--;b--;
				queries.pb({ {a,b},k });
			}
		}
		int z = sz(el) + 1;
		vi cur(z, 0), smol(z, 0), larg(z, 0), shrinking(z, 0), growing(z, 0), itsy(z, 0), woah(z, 0);
		cur[0] = 1;
		larg[0] = 1;
		growing[0] = 1;
		woah[0] = 1;
		rep(i, 0, z - 1)
		{
			int x = el[i].F;
			int w = el[i].S;
			int c = i + 1;
			cur[c] = cur[x] + w;
			smol[c] = min(smol[x], cur[c]);
			larg[c] = max(larg[x], cur[c]);
			shrinking[c] = min(0, shrinking[x] + w);
			growing[c] = max(0, growing[x] + w);
			itsy[c] = min(itsy[x], shrinking[c]);
			woah[c] = max(woah[x], growing[c]);
		}
		rep(i, 0, n - (z - 1))
		{
			int a = queries[i].F.F;
			int b = queries[i].F.S;
			while (a >= z || b >= z);
			int k = queries[i].S;
			int anc = 0;
			int hi = woah[a] + woah[b] - cur[anc];
			int lo = itsy[a] + itsy[b];
			// cout<<smol[a]<<' '<<larg[a]<<endl;
			// cout<<smol[b]<<' '<<larg[b]<<endl;
			// cout<<lo<<' '<<hi<<endl;
			if ((k >= smol[a] && k <= larg[a]) || (k >= smol[b] && k <= larg[b]) || (k >= lo && k <= hi))
			{
				cout << "YES\n";
			}
			else
			{
				cout << "NO\n";
			}
		}
	}
}