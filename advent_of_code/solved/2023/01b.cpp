#include <algorithm>
#include <iostream>
#include <string>

std::pair<std::string, int> digits[]{
	{"1", 1},
	{"2", 2},
	{"3", 3},
	{"4", 4},
	{"5", 5},
	{"6", 6},
	{"7", 7},
	{"8", 8},
	{"9", 9},
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9},
};

int main()
{
	long long sum = 0;
	for (std::string line; std::getline(std::cin, line);)
	{
		int tens = 0, ones = 0;
		for (size_t i = 0; i < size(line); i++)
		{
			for (auto const &[name, value] : digits)
			{
				if (std::equal(begin(name), end(name), begin(line) + i))
				{
					if (tens == 0)
					{
						tens = value;
					}
					ones = value;
				}
			}
		}
		sum += tens * 10 + ones;
	}
	std::cout << sum;
}
