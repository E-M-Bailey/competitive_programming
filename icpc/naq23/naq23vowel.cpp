#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int cnt1 = 0;
	int y = 0;
	for(char c : s){
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') cnt1++;
		if(c == 'y') y++;
	}
	cout << cnt1 << " " << (cnt1+y) << endl;
}