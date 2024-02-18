#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, w, h;
	cin >> n >> w >> h;
	int hyp = w * w + h * h;
	while (n--)
	{
		int l;
		cin >> l;
		cout << (l * l <= hyp ? "DA\n" : "NE\n");
	}
}
