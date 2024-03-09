#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	int M = *max_element(begin(A), end(A));
	for (int i = 0; i < n; i++)
		if (A[i] == M / 2)
		{
			cout << "yes";
			return 0;
		}
	cout << "no";
}