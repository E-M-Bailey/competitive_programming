#include <bits/stdc++.h>

using namespace std;

int main()
{
	string enc, msg;
	getline(cin, enc) >> msg;
	for (int i = 0; i < (int)size(msg); i += 3)
		cout << enc[stoi(msg.substr(i, 3)) - 1];
}
