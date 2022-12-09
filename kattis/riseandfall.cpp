#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
		string N;
		cin >> N;
		reverse(N.begin(), N.end());
		while (N.back() == '0')
			N.pop_back();
		reverse(N.begin(), N.end());
		int n = N.size();
		string ans;
		ans.reserve(n);
		ans.push_back(N[0]);
		for (int i = 1; i < n; i++) {
			if (N[i] < ans.back())
				break;
			ans.push_back(N[i]);
		}
		char lim = ans.back();
		bool done = false;
		while (ans.size() < n) {
			if (N[ans.size()] > lim)
				done = true;
			if (!done)
				lim = min(lim, N[ans.size()]);
			ans.push_back(lim);
		}
		cout << ans << endl;
	}
}
