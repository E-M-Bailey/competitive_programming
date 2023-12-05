#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

struct transition
{
	long long a, b, d;
	friend constexpr bool operator<(transition const &lhs, transition const &rhs)
	{
		return lhs.a < rhs.a;
	}
};

int main()
{
	std::string line, dummy;
	std::vector<std::pair<long long, long long>> ranges, ranges_temp;
	{
		std::getline(std::cin, line);
		std::istringstream is(line);
		is >> dummy;
		for (long long a, l; is >> a >> l;)
		{
			ranges.emplace_back(a, a + l);
		}
	}
	std::sort(begin(ranges), end(ranges));

	std::vector<transition> transitions, transitions_temp;

	auto const add_range = [&](long long a, long long b)
		{
			if (a >= b) {}
			else if (!ranges.empty() && ranges.back().second >= a)
			{
				ranges.back().second = std::max(ranges.back().second, b);
			}
			else
			{
				ranges.emplace_back(a, b);
			}

		};
	auto const add_transition = [&](long long a, long long b, long long d)
		{
			if (a >= b) {}
			else if (!transitions.empty() && d == transitions.back().d)
			{
				transitions.back().b = b;
			}
			else
			{
				transitions.push_back({ a, b, d });
			}
		};

	std::getline(std::cin, dummy);
	while (std::getline(std::cin, dummy))
	{
		transitions_temp.clear();
		transitions.clear();
		while (std::getline(std::cin, line) && !line.empty())
		{
			std::istringstream is(line);
			long long d, s, l;
			is >> d >> s >> l;
			transitions_temp.emplace_back(s, s + l, d - s);
		}
		std::sort(begin(transitions_temp), end(transitions_temp));

		long long prev_b = 0;
		for (auto [a, b, d] : transitions_temp)
		{
			add_transition(prev_b, a, 0);
			add_transition(a, b, d);
			prev_b = b;
		}
		add_transition(prev_b, std::numeric_limits<long long>::max(), 0);

		ranges_temp.clear();
		auto it = begin(transitions);
		for (auto [a, b] : ranges)
		{
			while (it->b <= a)
			{
				++it;
			}
			while (it->b <= b)
			{
				ranges_temp.emplace_back(std::max(a, it->a) + it->d, it->b + it->d);
				++it;
			}
			ranges_temp.emplace_back(std::max(a, it->a) + it->d, b + it->d);
		}
		std::sort(begin(ranges_temp), end(ranges_temp));

		ranges.clear();
		for (auto [a, b] : ranges_temp)
			add_range(a, b);
	}

	std::cout << ranges.front().first;
}
