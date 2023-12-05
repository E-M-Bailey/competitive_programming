#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector<std::string> grid;
	for (std::string line; std::getline(std::cin, line);)
	{
		for (char &ch : line)
		{
			if ((ch < '0' || ch > '9') && ch != '.')
			{
				ch = '*';
			}
		}
		grid.push_back('.' + line + '.');
	}

	size_t m = size(grid[0]);
	grid.insert(begin(grid), std::string(m, '.'));
	grid.push_back(std::string(m, '.'));
	size_t n = size(grid);

	long long sum = 0;
	for (size_t i = 1; i < n - 1; i++)
	{
		for (size_t j = 1; j < m - 1; j++)
		{
			if (grid[i][j] >= '0' && grid[i][j] <= '9')
			{
				int cur = 0;
				size_t start = j;
				for (; grid[i][j] >= '0' && grid[i][j] <= '9'; j++)
				{
					cur = 10 * cur + grid[i][j] - '0';
				}
				bool good = false;
				for (size_t k = start - 1; k < j + 1; k++)
				{
					good |= grid[i - 1][k] == '*';
					good |= grid[i + 1][k] == '*';
				}
				good |= grid[i][start - 1] == '*';
				good |= grid[i][j] == '*';
				if (good)
				{
					sum += cur;
				}
			}
		}
	}
	std::cout << sum;
}
