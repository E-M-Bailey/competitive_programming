#include <bits/stdc++.h>

using namespace std;

/*void sim(vector<int>& R, string src)
{
	f
}*/

ostringstream A;

void cas(int i, int j)
{
	string ans = "a(YZa)b(AYzb)a(Za)z(yBz)y(Ay)";
	for (char& c : ans)
	{
		if (c == 'a' || c == 'A') c += i;
		else if (c == 'b' || c == 'B') c += j - 1;
	}
	A << ans;
}

int main()
{
	constexpr int n = 24;
	for (int i = n - 1; i >= 1; i--)
		for (int j = 0; j < i; j++)
			cas(j, j + 1);
	cout << A.str().size();
}