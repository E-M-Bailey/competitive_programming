#include <bits/stdc++.h>
using namespace std;
typedef float T;
typedef pair<T, T> P;
typedef vector<T> VT;
typedef vector<P> VP;

template<class N, class F>
N select(N* arr, int n, int k, const F& cmp) {
    if (n <= 10) {
        sort(arr, arr + n, cmp);
        return arr[k];
    }
    for (int i = 0; i < n; i += 5)
        sort(arr + i, arr + min(i + 5, n), cmp);
    int lim = (n + 2) / 5;
    for (int i = 0; i < lim; i++)
        swap(arr[i], arr[i * 5 + 2]);
    for (int i = 0; i < n; i++)
        std::cerr << ' ' << arr[i];
    cerr << endl;
    N pivot = select(arr, lim, lim / 2, cmp);
    int mid = partition(arr, arr + n, [&](const N& val) {return !cmp(pivot, val);}) - arr;
    std::cerr << lim << ' ' << pivot << ' ' << n << ' ' << k << ' ' << mid << endl;
    for (int i = 0; i < n; i++)
        std::cerr << ' ' << arr[i];
    std::cerr << endl;
    if (k < mid)
        return select(arr, mid, k, cmp);
    else
        return select(arr + mid, n - mid, k - mid, cmp);
}
void go(int n) {
}
int main() {
    vector<int> A{4, 3, 5, 6, 2, 1, 7, 3, 2, 4, 3, 5, 10, 20, 30, 10, 2, 5, 17};
    std::cout << select(&A[0], A.size(), 4, less<int>());
    int n;
    while (cin >> n, n)
        go(n);
}
