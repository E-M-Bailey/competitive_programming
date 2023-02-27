#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

int N;
deque<ll> q;
ll arr[500000];
ll pref[500000];
pii sorted[500000];
ll MAX = (ll)1000000000*1000000000;

typedef struct Tree {
	typedef int T;
	static constexpr T unit = INT_MIN;
	vector<T> s; int n;
	T f(T a, T b) {
		return (arr[a] > arr[b]) ? a : b; 
	} // (any associative fn)
	Tree(int n = 0, T def = 0) : s(2*n, def), n(n) {
	}
	void update(int pos, T val) {
		for (s[pos += n] = pos; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b , e)
		T ra = b, rb = b;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
} tree;

tree t;

void pointSort(int l, int ind, int r){
	int b1 = l;
	int b2 = ind+1;
	while(b1 < ind && b2 <= r){
		if(sorted[b1].second > ind){
			swap(sorted[b1], sorted[b2]);
			b2++;
		}
		else{
			b1++;
		}
	}
}

ll solve(int l, int r, ll ex){
	//cerr << "call: " << l << " " << r << " " << ex << endl;
	//for(int i = l; i <= r; i++) cerr << arr[i] << " ";
	//cerr << endl;
	if(r < l) return MAX;
	if(l == r) return max(arr[l], ex);
	int ind = t.query(l, r+1);
	ll v = arr[ind];
	return min(max(v, ex), min(solve(l, ind-1, max(ex, v-pref[ind]+pref[l])), solve(ind+1, r, max(ex, v-pref[r+1]+pref[ind+1]))));
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin >> N;
	ll big = 0;
	for(int i = 0; i < N; i++){
		ll x;
		cin >> x;
		if(x > big){
			big = x;
		}
		q.push_back(x);
	}
	while(q.front() != big){
		ll x = q.front();
		q.pop_front();
		q.push_back(x);
	}
	q.pop_front();
	pref[0] = 0;
	for(int i = 0; !q.empty(); i++) {
		arr[i] = q.front();
		sorted[i] = make_pair(arr[i], i);
		pref[i+1] = pref[i] + arr[i];
		q.pop_front();
	}
	ll x = big - pref[N-1];

	t = tree(N-1);
	for(int i = 0; i < N-1; i++){
		t.update(i, arr[i]);
	}

	sort(sorted, sorted+N-1);
	reverse(sorted, sorted+N-1);
	cerr << MAX << endl;
	cout << solve(0, N-2, max(x, (ll)0)) << endl;;
}