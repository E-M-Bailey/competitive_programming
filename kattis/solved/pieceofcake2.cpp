#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, h, v;
	cin >> n >> h >> v;
	cout << max(h, n - h) * max(v, n - v) * 4;
}
