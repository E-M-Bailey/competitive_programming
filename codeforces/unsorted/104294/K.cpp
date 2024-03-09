#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <iomanip>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <assert.h>
#include <fstream>
#include <random>

using namespace std;

typedef int64_t i64;

typedef pair<int, int> pii;
typedef long double ld;
typedef pair<pii, ld> prob;

set<i64> s;
//int arr[100000];
i64 A, B, N;

int main()
{
	cin >> N >> A >> B;
	//if (N < 1)
	//	return -1;
	//if (min({ N, A, B }) < 1)
	//	return -1;
	vector<i64> arr(N);
	for (i64 i = 0; i < N; i++)
	{
		cin >> arr[i];
		//if (arr[i] < 1)
		//	return -1;
		//if (arr[i] < 1)
		//	return -1;
		s.insert(arr[i]);
	}

	i64 change = N;
	for (i64 i = 0; i <= N; i++)
	{
		if (s.count(i)) change--;
	}
	i64 ans = change * A;
	if (N == 0)
		ans = B;
	i64 ub = N;
	if (!s.empty())
		ub = max(*prev(s.end()), ub);
	for (i64 k = N + 1; k <= ub; k++)
	{
		if (s.count(k)) change--;
		ans = min(ans, change * A + (k - N) * B);
	}
	cout << ans << endl;

	return 0;
}


