#include <bits/stdc++.h>

using namespace std;

using ll = long long;
constexpr int MAXN = 1e6 + 100;


int main() {
    ll a,b;
    cin >> a >> b;

    using prime_t = pair<vector<ll>, vector<int>>;
    auto division = [&](ll x) -> prime_t {
        prime_t ret{{}, {}};
        for (ll i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                ret.first.push_back(i);
                ret.second.push_back(0);
                do {
                    ret.second.back()++;
                    x /= i;
                } while (x % i == 0);
            }
        }
        if (x > 1) {
            ret.first.push_back(x);
            ret.second.push_back(1);
        }
        return ret;
    };

    auto check_prime = [&](const prime_t& pp) {
        return pp.second.size() == 1 && pp.second[0] == 1;
    };

    auto pa = division(a);
    auto pb = division(b);

    if (a != b && check_prime(pa) && check_prime(pb)) {
        cout << "full credit" << '\n';
        return 0;
    }

    unordered_map<ll, int> pcnt;
    for (int i = 0; i<int(pa.first.size()); i++) {
        pcnt[pa.first[i]] += pa.second[i];
    }
    for (int i = 0; i<int(pb.first.size()); i++) {

        pcnt[pb.first[i]] += pb.second[i];
    }

    for (const auto& [k, v] : pcnt) {
        if (v >= 2) {
            cout << "no credit" << '\n';
            return 0;
        }
    }

    cout << "partial credit" << '\n';

    return 0;

}
