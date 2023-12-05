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

		bool good = true;
		for (std::string round; std::getline(is_game, round, ';');)
		{
			round += ',';
			std::istringstream is_round(round);
			int r = 0, g = 0, b = 0;
			std::string color;
			for (int x; is_round >> x >> color;)
			{
				if (color == "red,")
				{
					r += x;
				}
				else if (color == "green,")
				{
					g += x;
				}
				else
				{
					b += x;
				}
			}
			good &= r <= 12 && g <= 13 && b <= 14;
		}
		if (good)
		{
			sum += i;
		}
	}
	std::cout << sum;
}
