#include <bits/stdc++.h>

using namespace std;

int main()
{
	string S;
	cin >> S;
	auto it = cbegin(S);
	vector<int> T;
	while (it != cend(S))
	{
		if (*it == 'S')
		{
			++it;
			if (*it == 'S')
			{
				++it;
				int val = 0;
				bool neg = *it++ == 'T';
				while (*it != 'N')
					val = 2 * val + (*it++ == 'T');
				T.push_back(neg ? -val : val);
				++it;
			}
			else // N
			{
				++it;
				if (*it == 'S')
				{
					++it;
					if (T.empty())
						cout << "Invalid copy operation\n";
					else
						T.push_back(T.back());
				}
				else if (*it == 'T')
				{
					++it;
					if ((int)T.size() < 2)
						cout << "Invalid swap operation\n";
					else
						swap(T.back(), T[T.size() - 2]);
				}
				else // N
				{
					++it;
					if (T.empty())
						cout << "Invalid remove operation\n";
					else
						T.pop_back();
				}
			}
		}
		else // T
		{
			++it;
			if (*it == 'S')
			{
				++it;
				if (*it == 'S')
				{
					++it;
					if (*it == 'S')
					{
						++it;
						if ((int)T.size() < 2)
							cout << "Invalid addition operation\n";
						else
						{
							T[T.size() - 2] += T.back();
							T.pop_back();
						}
					}
					else if (*it == 'T')
					{
						++it;
						if ((int)T.size() < 2)
							cout << "Invalid subtraction operation\n";
						else
						{
							T[T.size() - 2] -= T.back();
							T.pop_back();
						}
					}
					else // N
					{
						++it;
						if ((int)T.size() < 2)
							cout << "Invalid multiplication operation\n";
						else
						{
							T[T.size() - 2] *= T.back();
							T.pop_back();
						}
					}
				}
				else // T
				{
					++it;
					{ // S
						++it;
						if ((int)T.size() < 2)
							cout << "Invalid division operation\n";
						else if (T.back() == 0)
							cout << "Division by zero\n";
						else
						{
							T[T.size() - 2] /= T.back();
							T.pop_back();
						}
					}
				}
			}
			else // N
			{
				++it;
				{ // S
					++it;
					{ // T
						++it;
						if (T.empty())
							cout << "Invalid print operation\n";
						else
						{
							cout << T.back() << '\n';
							T.pop_back();
						}
					}
				}
			}
		}
	}
}