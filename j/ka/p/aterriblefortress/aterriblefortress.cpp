#include <bits/stdc++.h>

using namespace std;

int main()
{
	cout << accumulate(++istream_iterator<int>{cin}, istream_iterator<int>{}, 0);
}
