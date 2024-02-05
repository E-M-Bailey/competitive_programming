#include <bits/stdc++.h>

using namespace std;

// Incantation to define a custom hash function in C++
template<>
struct std::hash<array<int, 5>>
{
	size_t operator()(array<int, 5> const &AA) const
	{
		size_t ans = 0;
		for (int a : AA)
			ans = 400 * ans + a - 100;
		return ans;
	}
};

int main()
{
	int n;
	cin >> n;
	vector<array<int, 5>>			  A(n);
	unordered_map<array<int, 5>, int> F;
	for (auto &AA : A)
	{
		for (int &a : AA)
			cin >> a;
		sort(begin(AA), end(AA));
		F[AA]++;
	}

	int maxf = 0, sumf = 0;
	for (auto const &[AA, f] : F)
	{
		if (f > maxf)
		{
			maxf = f;
			sumf = f;
		}
		else if (f == maxf)
		{
			sumf += f;
		}
	}

	cout << sumf;
}
