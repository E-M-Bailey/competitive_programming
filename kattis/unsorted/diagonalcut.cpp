#include <bits/stdc++.h>
using namespace std;

int main() {
	int64_t a, b;
	cin >> a >> b;
	int64_t g = gcd(a, b);
	if (a / g % 2 != b / g % 2)
		cout << 0;
	else
		cout << g;
}