#include <bits/stdc++.h>

using namespace std;

int main()
{
	unordered_map<string, int> I;
	vector<string>			   J;
	{
		string s = "1";
		I.try_emplace(s, 0);
		J.push_back(s);
		while ((int)size(I) <= 120)
		{
			bool c = 0;
			for (int i = (int)size(s); i-- > 0;)
			{
				char &ch = s[i];
				ch		 = char(2 * ch - '0' + c);
				if ((c = ch > '9'))
					ch = char(ch - 10);
			}
			if (c)
				s = '1' + s;
			I.try_emplace(s, (int)size(I));
			J.push_back(s);
		}
	}

	int n;
	cin >> n;
	vector<int> A;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		int a = I[s];
		while (!A.empty() && A.back() <= a)
		{
			a += A.back() == a;
			A.pop_back();
		}
		A.push_back(a);
	}

	cout << J[*max_element(begin(A), end(A))];
}
