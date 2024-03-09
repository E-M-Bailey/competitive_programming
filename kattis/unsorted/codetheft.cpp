#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> L;

int id(string const &line)
{
	return L.try_emplace(line, (int)L.size()).first->second;
}

string enc(string const &line)
{
	string ans;
	for (char c : line)
	{
		if (c == ' ' && (ans.empty() || ans.back() == ' '))
			continue;
		ans.push_back(c);
	}
	while (!ans.empty() && ans.back() == ' ')
		ans.pop_back();
	return ans;
}

vector<int> frag()
{
	vector<int> lines;
	for (string line; getline(cin, line) && line != "***END***";)
	{
		line = enc(line);
		if (!line.empty())
			lines.push_back(id(line));
	}
	return lines;
}

int lcs(vector<int> const &A, vector<int> const &B)
{
	int m = (int)size(A), n = (int)size(B);
	vector<int> X(n + 1), Y(n + 1);
	int ans = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i] == B[j])
			{
				Y[j + 1] = X[j] + (A[i] != 0);
				ans = max(ans, Y[j + 1]);
			}
			else
				Y[j + 1] = 0;
		}
		X.swap(Y);
	}
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	L[""] = 0;
	string nstr;
	getline(cin, nstr);
	int n = stoi(nstr);

	vector<pair<string, vector<int>>> D(n);
	for (auto &[name, lines] : D)
	{
		getline(cin, name);
		lines = frag();
	}
	vector<int> code = frag();

	map<int, vector<int>> M;
	for (int i = 0; i < n; i++)
		M[lcs(code, D[i].second)].push_back(i);
	M[0].clear();
	auto it = M.rbegin();
	cout << it->first;
	for (int i : it->second)
		cout << ' ' << D[i].first;


}