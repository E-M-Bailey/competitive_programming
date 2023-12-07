#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

std::string enc(std::string hand)
{
	char type;
	std::string sorted = hand;
	int freq[256]{};
	char best = 'J';
	for (char c : sorted)
	{
		if (c != 'J')
		{
			if (++freq[(int)c] > freq[(int)best])
			{
				best = c;
			}
		}
	}
	for (char &c : sorted)
	{
		if (c == 'J')
		{
			c = best;
		}
	}
	std::sort(begin(sorted), end(sorted));

	if (sorted[0] == sorted[4])
	{
		type = '7';
	}
	else if (sorted[0] == sorted[3] || sorted[1] == sorted[4])
	{
		type = '6';
	}
	else if ((sorted[0] == sorted[2] && sorted[3] == sorted[4]) || (sorted[0] == sorted[1] && sorted[2] == sorted[4]))
	{
		type = '5';
	}
	else if (sorted[0] == sorted[2] || sorted[1] == sorted[3] || sorted[2] == sorted[4])
	{
		type = '4';
	}
	else if ((sorted[0] == sorted[1] && (sorted[2] == sorted[3] || sorted[3] == sorted[4])) || (sorted[1] == sorted[2] && sorted[3] == sorted[4]))
	{
		type = '3';
	}
	else if (sorted[0] == sorted[1] || sorted[1] == sorted[2] || sorted[2] == sorted[3] || sorted[3] == sorted[4])
	{
		type = '2';
	}
	else
	{
		type = '1';
	}

	for (char &ch : hand)
	{
		if (ch == 'T')
		{
			ch = 'a';
		}
		else if (ch == 'J')
		{
			ch = '1';
		}
		else if (ch == 'Q')
		{
			ch = 'c';
		}
		else if (ch == 'K')
		{
			ch = 'd';
		}
		else if (ch == 'A')
		{
			ch = 'e';
		}
	}

	return type + hand;
}

int main()
{
	std::vector<std::pair<std::string, int>> hands;
	for (std::string hand, bid; std::cin >> hand >> bid;)
	{
		hands.emplace_back(enc(hand), std::stoi(bid));
	}

	std::sort(begin(hands), end(hands));

	long long sum = 0;
	for (size_t i = 0; i < size(hands); i++)
		sum += hands[i].second * (long long)(i + 1);
	std::cout << sum;
}
