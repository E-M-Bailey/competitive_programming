#include <bitset>
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	long long sum = 0;
	std::bitset<100> S;
	std::string token;

	for (std::string line; getline(std::cin, line);)
	{
		S.reset();
		std::istringstream is(line);
		is >> token >> token;

		while (is >> token, token != "|")
		{
			S.set(std::stoi(token));
		}
		int cur = 0;
		for (int x; is >> x;)
		{
			cur += S[x];
		}
		sum += (1ll << cur) >> 1;
	}
	std::cout << sum;
}
