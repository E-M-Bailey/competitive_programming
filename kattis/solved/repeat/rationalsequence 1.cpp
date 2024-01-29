#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--)
    {
		int num;
		string s;
		cin >> num >> s;
		s[s.find('/')] = ' ';
		istringstream in(s);
        long long p, q;
        in >> p >> q;
        long long d = p / q;
        p -= d * q;
        q -= p;
        p += q;
        q += d * p;
        cout << num << ' ' << p << '/' << q << '\n';
    }
}