#include <array>
#include <algorithm>
#include <iostream>
#include <string>

std::array<long long, 10> POW_10;

void increment(std::string &n)
{
	bool carry = true;
	for (int i = 0; i < static_cast<int>(n.size()) && carry; i++)
	{
		n[i]++;
		carry = false;
		if (n[i] > '9')
		{
			n[i] = '0';
			carry = true;
		}
	}
	if (carry)
	{
		n.push_back('1');
	}
}

// without changing prefix
long long next_match(long long from, long long pattern, int start, int len)
{
	long long from_trimmed = from / POW_10[start] % POW_10[len];
	long long pattern_trimmed = pattern % POW_10[len];
	long long ans = pattern_trimmed - from_trimmed;
	if (ans < 0)
	{
		ans += POW_10[len];
	}
	// std::cout << "   " << from << ' ' << pattern << ' ' << start << ' ' << len << '\n';
	return from + ans * POW_10[start];
}

long long solve(long long lo, std::string const &hi, long long m)
{
	std::string m_str = std::to_string(m);
	std::reverse(m_str.begin(), m_str.end());
	int len = static_cast<int>(m_str.size());

	if (hi.find(m_str) != std::string::npos)
	{
		return lo;
	}

	long long ans = 2'000'000'000;
	for (int start = 0; start < 9; start++)
	{
		int mid = std::min(9 - start, len);
		
		if (m_str.substr(mid) != hi.substr(0, len - mid))
		{
			continue;
		}

		long long lo_carry = lo;
		
		if (lo_carry % POW_10[start] != 0)
		{
			lo_carry += POW_10[start] - lo_carry % POW_10[start];
		}

		long long cur_nocarry = next_match(lo, m, start, mid);
		long long cur_carry = next_match(lo_carry, m, start, mid);

		// std::cout << "  " << cur_nocarry << ' ' << cur_carry << '\n';

		ans = std::min(ans, cur_nocarry);
		ans = std::min(ans, cur_carry);
	}

	return ans;
}

int main()
{
	POW_10[0] = 1;
	for (int i = 0; i < 9; i++)
	{
		POW_10[i + 1] = POW_10[i] * 10;
	}

	int T;
	std::cin >> T;
	for (int tcase = 0; tcase < T; tcase++)
	{
		std::string n;
		long long m;
		std::cin >> n >> m;
		std::reverse(n.begin(), n.end());
		increment(n);
		n.resize(std::max(n.size(), static_cast<size_t>(10)), '0');

		long long lo = 0;
		for (int i = 8; i >= 0; i--)
		{
			lo = 10 * lo + (n[i] - '0');
		}
		std::string hi = n.substr(9);
		std::string hi_carry = hi;
		increment(hi_carry);

		long long mod = 0;
		for (int i = (int)n.size() - 1; i >= 0; i--)
		{
			mod = (mod * 10ll + (n[i] - '0')) % m;
		}

		long long ans = m - mod;
		if (ans == m)
		{
			ans = 0;
		}
		long long ans_nocarry = solve(lo, hi, m) - lo;
		if (ans_nocarry + lo >= 1'000'000'000)
		{
			ans_nocarry = 1'000'000'000;
		}
		long long ans_carry = solve(0, hi_carry, m) + 1'000'000'000 - lo;
	
		// std::cout << ' ' << ans << ' ' << ans_nocarry << ' ' << ans_carry << '\n';

		ans = std::min(ans, ans_nocarry);
		ans = std::min(ans, ans_carry);

		long long carry = ans;
		for (int i = 0; i < (int)n.size() && carry > 0; i++)
		{
			n[i] += carry % 10;
			carry /= 10;
			if (n[i] > '9')
			{
				n[i] -= 10;
				carry++;
			}
		}
		while (carry > 0)
		{
			n.push_back(static_cast<char>(carry % 10 + '0'));
			carry /= 10;
		}
		while (n.back() == '0')
		{
			n.pop_back();
		}

		std::reverse(n.begin(), n.end());

		std::cout << n << '\n';
	}

}

