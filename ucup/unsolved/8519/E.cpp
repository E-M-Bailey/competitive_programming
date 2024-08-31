#include <bits/stdc++.h>

using namespace std;

int constexpr LIM = 450000;

int main()
{
	int	   a = 1, b = 2;
	string s;
	cin >> s;

	string A = "b", B = "a";
	while (size(B) < LIM)
	{
		A = B + A;
		A.swap(B);
	}

	vector<pair<int, char>> J(LIM, {-1, '\0'});
	char					c = 'a', d = 'b';
	while (b - 2 < LIM)
	{
		tie(a, b) = pair{b, a + b};
		swap(c, d);
		J[a - 2] = {b - 1, c};
	}

	unordered_map<int, int> DP, EP;
	DP.emplace(0, 0);
	int	 ans  = -1;
	bool done = false;
	while (!done)
	{
		ans++;
		EP.clear();
		for (auto [i, j] : DP)
		{
			if (j == (int)size(s))
			{
				done = true;
				break;
			}
			if (i >= LIM)
				continue;
			char ch	  = s[j];
			EP[i + 1] = max(EP[i + 1], j + (ch == B[i]));
			if (J[i].second)
				EP[J[i].first] = max(EP[J[i].first], j + (ch == J[i].second));
		}
		EP.swap(DP);
	}
	cout << ans;

	// long long	ans = (int)size(s);
	// deque<char> S(begin(s), end(s)), T;
	// for (;;)
	// {
	// 	tie(a, b) = pair{b, a + b};
	// 	if (S.size() == 1)
	// 		break;
	// 	if (S.front() == 'b')
	// 		S.push_front('a');
	// 	if (S.back() == 'a')
	// 		S.pop_back();
	// 	if (S.size() == 1)
	// 		break;

	// 	T.clear();
	// 	for (int i = 0; i < (int)size(S);)
	// 	{
	// 		if (S[i] == 'a')
	// 		{
	// 			if (i < (int)size(S) - 1 && S[i + 1] == 'b')
	// 			{
	// 				T.push_back('a');
	// 				i += 2;
	// 			}
	// 			else
	// 			{
	// 				T.push_back('b');
	// 				i++;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			T.push_back('a');
	// 			i++;
	// 			ans += b;
	// 		}
	// 	}
	// 	S.swap(T);
	// }
	// cout << ans;
}
