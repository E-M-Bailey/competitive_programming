#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

int main()
{
	std::string line, dummy;
	std::vector<long long> nums;
	{
		std::getline(std::cin, line);
		std::istringstream is(line);
		is >> dummy;
		long long x;
		while (is >> x)
		{
			nums.push_back(x);
		}
	}
	getline(std::cin, dummy);

	std::map<long long, std::pair<long long, long long>> transitions;

	while (std::getline(std::cin, dummy))
	{
		transitions.clear();
		while (std::getline(std::cin, line) && !line.empty())
		{
			std::istringstream is(line);
			long long d, s, l;
			is >> d >> s >> l;
			transitions.emplace(s + l, std::pair{ s, d - s });
		}
		for (long long &num : nums)
		{
			auto it = transitions.upper_bound(num);
			auto [a, d] = it->second;
			if (num >= a)
			{
				num += d;
			}
		}
	}

	std::cout << *std::min_element(begin(nums), end(nums));
}
