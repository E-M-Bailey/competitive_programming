#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
	long long sum = 0;
	std::string game, dummy;
	for (int i = 1; std::getline(std::cin, game); i++)
	{
		game += ';';
		std::istringstream is_game(game);
		is_game >> dummy >> dummy;

		int min_r = 0, min_g = 0, min_b = 0;

		for (std::string round; std::getline(is_game, round, ';');)
		{
			round += ',';
			std::istringstream is_round(round);
			int r = 0, g = 0, b = 0;
			std::string color;
			for (int x; is_round >> x >> color;)
			{
				if (color == "red,")
					r += x;
				else if (color == "green,")
					g += x;
				else
					b += x;
			}
			min_r = std::max(min_r, r);
			min_g = std::max(min_g, g);
			min_b = std::max(min_b, b);
		}
		sum += static_cast<long long>(min_r) * min_g * min_b;
	}
	std::cout << sum;
}
