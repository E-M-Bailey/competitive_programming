#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;
namespace vws = views;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	cout << n / 3600 << " : " << n / 60 % 60 << " : " << n % 60;
}
