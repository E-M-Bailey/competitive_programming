#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> A(n + 2 * (m - 1)), B = A;
	deque<int> S;
	int paid = 0;
	for (int i = m - 1; i < n + m - 1; i++)
	{
		cin >> A[i];
		if (A[i])
			S.push_back(i);
		if (i >= m)
		{
			paid -= A[S.front()];
			S.pop_front();
		}

	}
}