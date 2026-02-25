#include "template.hpp"

using namespace std;
using namespace abbrev;

static constexpr api32<4> D{ pi32{ -1, 0 }, pi32{ 1, 0 }, pi32{ 0, -1 }, pi32{ 0, 1 } };

int main()
{
	int n, m;
	cin >> n >> m;
	vstr A(n);
	for (auto &AA : A)
		cin >> AA;
	queue<pi32> Q;
	int k = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			if (A[i][j] == 'L')
			{
				++k;
				A[i][j] = 'W';
				Q.emplace(i, j);
				while (!Q.empty())
				{
					auto [ii, jj] = Q.front();
					Q.pop();
					for (auto [di, dj] : D)
						if (ii + di >= 0 && ii + di < n && jj + dj >= 0 && jj + dj < m && A[ii + di][jj + dj] != 'W')
						{
							A[ii + di][jj + dj] = 'W';
							Q.emplace(ii + di, jj + dj);
						}
				}
			}
		}
	cout << k;
}
