#include <bits/stdc++.h>

using namespace std;

uint64_t constexpr A1 = 11, A2 = 13, M1 = 1e9 + 7, M2 = 1e9 + 9, I1 = 818181824, I2 = 615384621;

struct hash_deque
{
	deque<char> S;
	uint64_t h1 = 0, h2 = 0, p1 = 1, p2 = 1;

	size_t size() const
	{
		return S.size();
	}
	bool empty() const
	{
		return S.empty();
	}
	uint64_t hash() const
	{
		return h1 << 32 | h2;
	}

	char front() const
	{
		return S.front();
	}
	char back() const
	{
		return S.back();
	}
	char operator[](size_t n) const
	{
		return S[n];
	}

	void push_front(char c)
	{
		S.push_front(c);
		h1 = (h1 + (c - '0') * p1) % M1, p1 = p1 * A1 % M1;
		h2 = (h2 + (c - '0') * p2) % M2, p2 = p2 * A2 % M2;
	}
	void push_back(char c)
	{
		S.push_back(c);
		h1 = (h1 * A1 + c - '0') % M1, p1 = p1 * A1 % M1;
		h2 = (h2 * A2 + c - '0') % M2, p2 = p2 * A2 % M2;
	}
	void pop_front()
	{
		char c = front();
		S.pop_front();
		p1 = p1 * I1 % M1, h1 = (h1 + M1 - (c - '0') * p1 % M1) % M1;
		p2 = p2 * I2 % M2, h2 = (h2 + M2 - (c - '0') * p2 % M2) % M2;
	}
	void pop_back()
	{
		char c = back();
		S.pop_back();
		p1 = p1 * I1 % M1, h1 = (h1 + M1 - (c - '0')) * I1 % M1;
		p2 = p2 * I2 % M2, h2 = (h2 + M2 - (c - '0')) * I2 % M2;
	}

	void clear()
	{
		S.clear();
		h1 = h2 = 0;
		p1 = p2 = 1;
	}
};

int main()
{
	string s;
	cin >> s;
	int n = (int)s.size();
	int i = 0, j = n - 1;
	hash_deque A, B;
	int ans = 0;
	while (i < j)
	{
		A.push_back(s[i++]);
		B.push_front(s[j--]);
		if (A.hash() == B.hash())
		{
			ans += 2;
			A.clear();
			B.clear();
		}
	}
	if (!A.empty() || n % 2 == 1)
		ans++;
	
	cout << ans;
}