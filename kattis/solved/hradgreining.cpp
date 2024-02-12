#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	cout << (s.find("COV") == string::npos ? "Ekki veikur!" : "Veikur!");
}
