#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	ai32<9> A;
	int s = -100;
	for (auto &a : A)
	{
		cin >> a;
		s += a;
	}
	for (int i = 0;; ++i)
		for (int j = i + 1; j < 9; ++j)
			if (A[i] + A[j] == s)
			{
				for (int k = 0; k < 9; ++k)
					if (k != i && k != j)
						cout << A[k] << '\n';
				return 0;
			}
}
