#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		string str, A;
		cin >> str;
		vector<int> ans;
		int a = 0;
		for (int l = 0; l < 5 && l < (int)size(str); l++)
		{
			
			a = 10 * a + str[l] - '0';
			int cur = a, curans = -1;
			bool bad = false;
			for (int ptr = 0; ptr < (int)size(str);)
			{
				if (cur > 99999)
				{
					bad = true;
					break;
				}
				A = to_string(cur);
				if (A.size() > str.size() - ptr || str.substr(ptr, A.size()) != A)
				{
					if (curans == -1)
						curans = cur;
					else
					{
						bad = true;
						break;
					}
				}
				else
					ptr += (int)A.size();
				cur++;
			}
			if (!bad && curans != -1)
				ans.push_back(curans);
			else if (!bad)
			{
				ans.push_back(cur);
				ans.push_back(a - 1);
			}
		}
		for (int i = 0; i < (int)ans.size(); i++)
		{
			int &x = ans[i];
			if (x < 1 || x > 99999)
			{
				swap(x, ans.back());
				ans.pop_back();
			}
		}
		sort(begin(ans), end(ans));
		
		cout << ans.size() << '\n';
		for (auto x : ans)
			cout << x << ' ';
		cout << '\n';
	}
}