/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/heimavinna
TAGS: String, Parsing
EXPLANATION:
Read a line and split it about semicolons to get strings representing each range. Keep a running total
initialized to 0. For each range, if it contains a '-', split it about the '-' and parse the two resulting
strings as ints to get the endpoints, called start and end respectively. Add end - start + 1 to the total.
Otherwise, just increment the running total. Print the total at the end.
END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;

int process(const string& str)
{
	//cerr << st << ' ' << ed << endl;
	int dash;
	if ((dash = str.find('-')) == str.npos)
    {
		return 1;
    }
	else
	{
	    //cerr << dash << endl;
		string A = str.substr(0, dash), B = str.substr(dash + 1, str.size() - dash - 1);
		stringstream a(A), b(B);
		int rst, red;
		a >> rst;
		b >> red;
		return red - rst + 1;
	}
}

int main()
{
	string str;
	cin >> str;
	int st = 0, ed = -1, ans = 0;
	while (st = ed + 1, (ed = str.find(';', st)) != str.npos)
	{
	    ans += process(str.substr(st, ed - st));
	    //cerr << ans << endl;
	}
	ans += process(str.substr(st, str.size()));
	cout << ans;
}
