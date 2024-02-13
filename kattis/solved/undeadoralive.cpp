#include <bits/stdc++.h>

using namespace std;

int main()
{
	string l;
	getline(cin, l);
	bool s = l.find(":)") != string::npos, f = l.find(":(") != string::npos;
	cout << (s ? f ? "double agent" : "alive" : f ? "undead" : "machine");
}
