#include <bits/stdc++.h>

using ll = long long;
using namespace std;

struct Payload {
    vector<pair<int,ll>> sorted;
    vector<ll> pref;
    Payload() = default;
};

struct SegmentTree {
    vector<Payload> tree;
    int arr_size;
    SegmentTree(const vector<pair<int, ll>>& a) : arr_size{int(a.size())}, tree(int(a.size()) * 4) {
        for (int i = 0; i < int(a.size()); i++) {
            add(i, a[i]);
        }
        merge(0, 0, arr_size -1);
    }
    void merge(int idx, int curr_l, int curr_r) {
        if (curr_l == curr_r) return;
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (idx * 2 + 1 < int(tree.size())) {
            merge(idx * 2 + 1, curr_l, mid);
        }
        if (idx * 2 + 2 < int(tree.size())) {
            merge(idx * 2 + 2, mid + 1, curr_r);
        }

        auto& [sorted, pref] = tree[idx];
        for (int i = 1; i<=2; i++) {
            int child_idx = idx * 2 + i;
            if (child_idx >= int(tree.size())) continue;
            auto& [ss, pp] = tree[idx *2 + i];
            for (auto&& s : ss) sorted.push_back(s);
        }
        sort(sorted.begin(), sorted.end());
        for (auto&& p : sorted) {
            pref.push_back(p.second);
        }
        partial_sum(pref.begin(), pref.end(), pref.begin());
    }

    void add(int idx, int curr_l, int curr_r, int i, pair<int,ll> x) {
        if (curr_l == curr_r) {
            tree[idx].sorted.push_back(x);
            tree[idx].pref.push_back(x.second * 1ll);
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid) {
            add(idx * 2 + 1, curr_l, mid, i, x);
        } else {
            add(idx * 2 + 2, mid + 1, curr_r, i, x);
        }
    }

    void add(int i, pair<int, ll> x) {
        add(0, 0, arr_size - 1, i, x);
    }

    ll query(int l, int r, int bound) {
        return query(0, 0, arr_size - 1, l, r, bound);
    }

    ll eval(int idx, int bound) {
        int low = 0, high = int(tree[idx].sorted.size())-1, pos = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (tree[idx].sorted[mid].first < bound) {
                pos = mid;
                low = mid+1;
            } else {
                high = mid-1;
            }
        }
        if (pos == -1) return 0ll;
        return tree[idx].pref[pos];
    }

    ll query(int idx, int curr_l, int curr_r, int l, int r, int bound) {
        if (curr_l > curr_r || curr_r < l || r < curr_l) return 0ll;
        if (curr_l >= l && curr_r <= r) {
            return eval(idx, bound);
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        auto left = query(idx *2 + 1, curr_l, mid, l, r, bound);
        auto right = query(idx * 2 + 2, mid + 1, curr_r, l, r, bound);
        return left + right;
    }

};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);

    int root = -1;

    vector<pair<int, ll>> employees(n);
    for (int i = 0; i<n; i++) {
        int manager;
        cin >> manager >> employees[i].first >> employees[i].second;
        if (manager == -1) {
            root = i;
        } else {
            graph[--manager].push_back(i);
        }
    }

    vector<int> tin(n), tout(n);
    int timer = 0;

    function<void(int)> establish_order = [&](int curr) {
        tin[curr] = timer++;
        for (auto&& neighbor : graph[curr]) {
            establish_order(neighbor);
        }
        tout[curr] = timer;
    };

    establish_order(root);
    vector<pair<int, ll>> employees_order(n);
    for (int i = 0; i<n; i++) {
        employees_order[tin[i]] = employees[i];
    }

    SegmentTree tree{employees_order};

    for (int i = 0; i<n; i++) {
        cout << tree.query(tin[i], tout[i], employees[i].first) << '\n';
    }





}
