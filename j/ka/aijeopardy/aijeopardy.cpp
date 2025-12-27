#include <bits/stdc++.h>

using namespace std;

struct ubig
{
	static constexpr uint32_t RAD = 1'000'000'000;
	static string			  buf;

	vector<uint32_t> D{};

	explicit ubig(vector<uint32_t> &&d = {}) : D(d)
	{
		while (!D.empty() && D.back() == 0)
			D.pop_back();
	}
	ubig(uint32_t x) : ubig(vector{x}) {}

	friend ubig &operator--(ubig &x)
	{
		for (size_t i = 0; i < size(x.D); i++)
		{
			if (x.D[i]-- == 0)
				x.D[i] += RAD;
			else
				break;
		}
		while (!x.D.empty() && x.D.back() == 0)
			x.D.pop_back();
		return x;
	}
	friend ubig &operator+=(ubig &x, ubig const &y)
	{
		bool c = 0;
		x.D.resize(max(size(x.D), size(y.D)));
		for (size_t i = 0; i < size(y.D); i++)
		{
			x.D[i] += c + y.D[i];
			if ((c = x.D[i] >= RAD))
				x.D[i] -= RAD;
		}
		for (size_t i = size(y.D); c && i < size(x.D); i++)
		{
			x.D[i] += c;
			if ((c = x.D[i] >= RAD))
				x.D[i] -= RAD;
		}
		if (c)
			x.D.push_back(1);
		return x;
	}
	friend ubig &halve(ubig &x)
	{
		bool c = 0;
		for (size_t i = size(x.D); i--;)
		{
			x.D[i] += c * RAD;
			c = x.D[i] % 2;
			x.D[i] /= 2;
		}
		if (!x.D.empty() && x.D.back() == 0)
			x.D.pop_back();
		return x;
	}
	friend ubig &operator*=(ubig &x, uint32_t y)
	{
		uint64_t c = 0;
		for (auto &d : x.D)
		{
			c += (uint64_t)d * y;
			d = (uint32_t)(c % RAD);
			c /= RAD;
		}
		if (c)
			x.D.push_back((uint32_t)c);
		return x;
	}

	friend ubig operator+(ubig const &x, ubig const &y)
	{
		ubig ans = x;
		return ans += y;
	}
	friend ubig operator*(ubig const &x, ubig const &y)
	{
		ubig ans;
		ans.D.resize(size(x.D) + size(y.D));
		for (size_t i = 0; i < size(x.D); i++)
			for (size_t j = 0; j < size(y.D); j++)
			{
				uint64_t prod	 = (uint64_t)x.D[i] * y.D[j] + ans.D[i + j] + (uint64_t)RAD * ans.D[i + j + 1];
				ans.D[i + j]	 = (uint32_t)(prod % RAD);
				ans.D[i + j + 1] = (uint32_t)(prod / RAD);
				for (size_t k = i + j + 1; ans.D[k] >= RAD; k++)
				{
					ans.D[k] -= RAD;
					ans.D[k + 1]++;
				}
			}
		while (!ans.D.empty() && ans.D.back() == 0)
			ans.D.pop_back();
		return ans;
	}

	friend bool operator==(ubig const &x, ubig const &y) noexcept
	{
		return x.D == y.D;
	}
	friend bool operator<(ubig const &x, ubig const &y) noexcept
	{
		if (size(x.D) != size(y.D))
			return size(x.D) < size(y.D);
		for (size_t i = size(x.D); i--;)
			if (x.D[i] != y.D[i])
				return x.D[i] < y.D[i];
		return false;
	}

	friend istream &operator>>(istream &is, ubig &x)
	{
		x.D.clear();
		is >> buf;
		while (!buf.empty())
		{
			size_t st = max(size(buf), (size_t)9) - 9;
			x.D.push_back((uint32_t)stoul(buf.substr(st)));
			buf.resize(st);
		}
		while (!x.D.empty() && x.D.back() == 0)
			x.D.pop_back();
		return is;
	}

	friend ostream &operator<<(ostream &os, ubig const &x)
	{
		static string cur;

		if (x.D.empty())
			return os << '0';

		buf.clear();
		for (size_t i = 0; i < size(x.D); i++)
		{
			cur = to_string(x.D[size(x.D) - 1 - i]);
			if (i)
				buf.resize(size(buf) + 9 - size(cur), '0');
			buf += cur;
		}
		return os << buf;
	}
};
string ubig::buf;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	ubig::buf.reserve(108);

	ubig X;
	cin >> X;
	if (X == 1)
	{
		cout << "0 0";
		return 0;
	}

	ubig Y = X;

	ubig bestn = X;
	int	 bestk = 1;

	for (int k = 2; k <= 168; k++)
	{
		Y *= k;
		ubig lo = k + 1, hi = bestn;
		--hi;
		while (!(hi < lo))
		{
			ubig n = hi + lo;
			halve(n);
			ubig n2 = n, cur = 1;
			for (int i = 0; i < k; i++)
			{
				cur = cur * n2;
				--n2;
				if (size(cur.D) > size(Y.D))
					break;
			}
			if (cur == Y)
			{
				bestn = n;
				bestk = k;
				break;
			}
			else if (Y < cur)
				hi = move(--n);
			else
				lo = move(n) + 1;
		}
	}

	cout << bestn << ' ' << bestk;
}
