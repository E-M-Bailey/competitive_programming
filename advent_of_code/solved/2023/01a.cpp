#include <iostream>
#include <string>

int main()
{
	long long sum = 0;
	for (std::string line; std::getline(std::cin, line);)
	{
		auto first = line.find_first_of("0123456789"), last = line.find_last_of("0123456789");
		sum += (line[first] - '0') * 10 + line[last] - '0';
	}
	std::cout << sum;
}
