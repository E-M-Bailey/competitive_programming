#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		go();
	}
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	sort(begin(A), end(A));
	A.erase(unique(begin(A), end(A)), end(A));

	for (int i = n; i-- > 1;)
		A[i] -= A[i - 1];
	
	bool win = false;
	for (int i = (int)size(A); i-- > 0;)
	{
		if (A[i] == 1)
			win = !win;
		else
			win = true;
	}

	cout << (win ? "Alice\n" : "Bob\n");
}
