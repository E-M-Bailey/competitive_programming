#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	ai32<5> A;
	for (int &a : A)
		cin >> a;
	for (int i = 4; i > 0; --i)
		for (int j = 0; j < i; ++j)
			if (A[j] > A[j + 1])
			{
				swap(A[j], A[j + 1]);
				for (int k = 0; k < 5; ++k)
					cout << A[k] << ' ';
				cout << '\n';
			}
}
