#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector<std::string> grid;
	for (std::string line; std::getline(std::cin, line);)
	{
		grid.push_back('.' + line + '.');
	}
	size_t m = size(grid[0]);
	grid.insert(begin(grid), std::string(m, '.'));
	grid.push_back(std::string(m, '.'));
	size_t n = size(grid);

	std::vector<std::vector<std::vector<int>>> gears(n, std::vector<std::vector<int>>(m));

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
				for (size_t k = start - 1; k < j + 1; k++)
				{
					gears[i - 1][k].push_back(cur);
					gears[i + 1][k].push_back(cur);
				}
				gears[i][start - 1].push_back(cur);
				gears[i][j].push_back(cur);
			}
		}
	}

	long long sum = 0;
	for (size_t i = 1; i < n - 1; i++)
	{
		for (size_t j = 1; j < m - 1; j++)
		{
			if (grid[i][j] == '*' && size(gears[i][j]) == 2)
			{
				sum += gears[i][j][0] * gears[i][j][1];
			}
		}
	}
	std::cout << sum;
}
