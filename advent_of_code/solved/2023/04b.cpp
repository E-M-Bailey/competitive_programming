#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	long long sum = 0;
	std::bitset<100> S;
	std::string line, token;
	std::vector<long long> DP(1, 1);

	for (size_t i = 0; getline(std::cin, line); i++)
	{
		S.reset();
		std::istringstream is(line);
		is >> token >> token;

		while (is >> token, token != "|")
		{
			S.set(std::stoi(token));
		}
		size_t cur = 0;
		for (size_t x; is >> x;)
		{
			cur += S[x];
		}

		DP.resize(std::max(DP.size(), i + cur + 1), 1);
		for (size_t j = 0; j < cur; j++)
			DP[i + j + 1] += DP[i];
		sum += DP[i];
	}
	std::cout << sum;
}
