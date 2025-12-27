#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    
    string a = '+' + string(n, '-') + '+';
    string b = '|' + string(n, ' ') + '|';
    cout << a << '\n';
    while (n--)
        cout << b << '\n';
    cout << a << '\n';
}