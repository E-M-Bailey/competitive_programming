#include <bits/stdc++.h>

using namespace std;

string const DIG[11]{
	"xxxxx"
	"x...x"
	"x...x"
	"x...x"
	"x...x"
	"x...x"
	"xxxxx",

	"....x"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x",

	"xxxxx"
	"....x"
	"....x"
	"xxxxx"
	"x...."
	"x...."
	"xxxxx",

	"xxxxx"
	"....x"
	"....x"
	"xxxxx"
	"....x"
	"....x"
	"xxxxx",

	"x...x"
	"x...x"
	"x...x"
	"xxxxx"
	"....x"
	"....x"
	"....x",

	"xxxxx"
	"x...."
	"x...."
	"xxxxx"
	"....x"
	"....x"
	"xxxxx",

	"xxxxx"
	"x...."
	"x...."
	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx",

	"xxxxx"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x",

	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx",

	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx"
	"....x"
	"....x"
	"xxxxx",

	"....."
	"..x.."
	"..x.."
	"xxxxx"
	"..x.."
	"..x.."
	".....",
};

int main()
{
	string A[7];
	for (auto &row : A)
		cin >> row;
	int n = ((int)A[0].size() + 1) / 6;

	string cur;
	cur.reserve(35);
	string msg;
	for (int i = 0; i < n; i++)
	{
		cur.clear();
		for (int j = 0; j < 7; j++)
			cur += A[j].substr(i * 6, 5);
		for (int j = 0; j < 10; j++)
			if (cur == DIG[j])
				msg += char(j + '0');
		if (cur == DIG[10])
			msg += '+';
	}
	auto pos = msg.find('+');
	msg = to_string(stoi(msg.substr(0, pos)) + stoi(msg.substr(pos + 1)));
	for (int i = 0; i < 7; i++)
	{
		bool nfst = false;
		for (char c : msg)
		{
			if (nfst)
				cout << '.';
			nfst = true;
			cout << DIG[c - '0'].substr(i * 5, 5);
		}
		cout << '\n';
	}
}