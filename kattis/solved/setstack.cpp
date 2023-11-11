#include <bits/stdc++.h>

using namespace std;

map<vector<int>, int> A;
vector<vector<int>> B;
vector<int> T;

int main()
{
	int tc;
	cin >> tc;
	string s;
	vector<int> res;
	while (tc--)
	{
		A.clear();
		B.clear();
		T.clear();
		B.emplace_back();
		A.emplace(B.back(), 0);

		int n;
		cin >> n;
		while (n--)
		{
			cin >> s;
			switch (s[0])
			{
			case 'P':
				T.push_back(0);
				break;
			case 'D':
				T.push_back(T.back());
				break;
			case 'U':
			{
				int i = T.back();
				T.pop_back();
				int j = T.back();
				res.resize(B[i].size() + B[j].size());
				res.erase(set_union(cbegin(B[i]), cend(B[i]), cbegin(B[j]), cend(B[j]), begin(res)), end(res));
				auto [it, ins] = A.try_emplace(res, A.size());
				if (ins)
					B.push_back(move(res));
				T.back() = it->second;
				break;
			}
			case 'I':
			{
				int i = T.back();
				T.pop_back();
				int j = T.back();
				res.resize(min(B[i].size(), B[j].size()));
				res.erase(set_intersection(cbegin(B[i]), cend(B[i]), cbegin(B[j]), cend(B[j]), begin(res)), end(res));
				auto [it, ins] = A.try_emplace(res, A.size());
				if (ins)
					B.push_back(move(res));
				T.back() = it->second;
				break;
			}
			case 'A':
			{
				int i = T.back();
				T.pop_back();
				int j = T.back();
				auto it = lower_bound(cbegin(B[j]), cend(B[j]), i);
				if (it != cend(B[j]) && *it == i)
					break;
				res = B[j];
				res.insert(it - cbegin(B[j]) + cbegin(res), i);
				auto [it2, ins] = A.try_emplace(res, A.size());
				if (ins)
					B.push_back(move(res));
				T.back() = it2->second;
				break;
			}
			}
			cout << B[T.back()].size() << '\n';
		}
		cout << "***\n";
	}
}
