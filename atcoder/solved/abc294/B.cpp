#include <bits/stdc++.h>
using namespace std;

int main() {
	int h, w;
	cin >> h >> w;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int a;
			cin >> a;
			cout << (a == 0 ? '.' : char(a + 'A' - 1));
		}
		cout << endl;
	}
}