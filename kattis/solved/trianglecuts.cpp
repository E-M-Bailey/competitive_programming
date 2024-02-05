#include <bits/stdc++.h>

using namespace std;

vector<int> glue(const vector<int> &A, const vector<int> &B)
{
	vector<int> C;
	for (int i = 1; i < A.size(); i++)
		C.push_back(A[i]);
	C.back() += B.front();
	if (C.back() == 180)
		C.pop_back();
	for (int i = 1; i < B.size(); i++)
		C.push_back(B[i]);
	C.back() += A.front();
	if (C.back() == 180)
		C.pop_back();
	return C;
}

bool valid(const vector<int> &A)
{
	return A.size() <= 4 && *max_element(A.begin(), A.end()) < 180;
}

bool same(const vector<int> &A, const vector<int> &B)
{
	if (A.size() != B.size())
		return false;
	for (int i = 0; i < A.size(); i++)
		if (equal(A.begin() + i, A.end(), B.begin()) && equal(A.begin(), A.begin() + i, B.end() - i))
			return true;
	return false;
}

bool test(const vector<int> &large, const vector<vector<int>> &small)
{
	if (small.size() == 1)
		return same(large, small.front());
	for (int i = 0; i < small.size(); i++)
		for (int j = 0; j < small.size(); j++)
		{
			if (i == j)
				continue;
			vector<vector<int>> small2;
			for (int k = 0; k < small.size(); k++)
				if (k != i && k != j)
					small2.push_back(small[k]);
			vector<int> A(small[i].size()), B(small[j].size());
			for (int k = 0; k < A.size(); k++)
			{
				rotate_copy(small[i].begin(), small[i].begin() + k, small[i].end(), A.begin());
				for (int l = 0; l < B.size(); l++)
				{
					rotate_copy(small[j].begin(), small[j].begin() + l, small[j].end(), B.begin());
					vector<int> glued = glue(A, B);
					if (!valid(glued))
						continue;
					small2.push_back(move(glued));
					if (test(large, small2))
						return true;
					small2.pop_back();
				}
			}
		}
	return false;
}

int main()
{
	vector<int>			large(3);
	vector<vector<int>> small(4, vector<int>(3));
	for (;;)
	{
		for (int &a : large)
			cin >> a;
		if (large.front() == 0)
			break;
		for (vector<int> &s : small)
			for (int &a : s)
				cin >> a;
		cout << (test(large, small) ? "yes\n" : "no\n");
	}
}
