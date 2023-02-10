#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100000;
int X[MAXN], Y[MAXN];

int64_t imerge(int* D, int* AS, int* AE, int* BS, int* BE) {
    int64_t ans = 0;
    while (AS < AE && BS < BE) {
        bool b = *AS > *BS;
        ans += b * (AE - AS);
        *D++ = *(b ? BS : AS)++;
    }
    copy(AS, AE, D);
    copy(BS, BE, D);
    return ans;
}

int64_t isort(int* AS, int* AE) {
    if (AE - AS <= 1)
        return 0;
    int64_t ans = 0;
    int n = AE - AS;
    int* AM = AS + n / 2;
    ans += isort(AS, AM);
    ans += isort(AM, AE);
    int* XE = copy(AS, AM, X);
    int* YE = copy(AM, AE, Y);
    ans += imerge(AS, X, XE, Y, YE);
    return ans;
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n], *b = new int[n];
    copy_n(istream_iterator<int>(cin), n, a);
    copy_n(istream_iterator<int>(cin), n, b);
    bool ans = isort(a, a + n) % 2 == isort(b, b + n) % 2;
    cout << (ans ? "Possible" : "Impossible") << endl;
    delete[] a;
    delete[] b;
}