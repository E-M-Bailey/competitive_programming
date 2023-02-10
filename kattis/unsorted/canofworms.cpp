#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#ifndef DEBUG
#define assert(x) do {} while (false)
#endif // DEBUG

using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

template<size_t S, class... Ts>
struct TupleHashHelper {
	typedef std::tuple<Ts...> Tup;
	typedef TupleHashHelper<S - 1, Ts...> Helper;
	typedef std::tuple_element_t<S - 1, Tup> T;
	inline constexpr size_t operator()(const Tup& t) const noexcept {
		return (size_t)31 * Helper()(t) + std::hash<T>()(std::get<S - 1>(t));
	}
};

template<class... Ts>
struct TupleHashHelper<0, Ts...> {
	typedef std::tuple<Ts...> Tup;
	inline constexpr size_t operator()(const Tup&) const noexcept {
		return 0;
	}
};

template<class... Ts>
struct std::hash<tuple<Ts...>> {
	typedef std::tuple<Ts...> Tup;
	static constexpr size_t S = sizeof...(Ts);
	typedef TupleHashHelper<S, Ts...> Helper;
	inline constexpr size_t operator()(const Tup& t) const noexcept {
		return Helper()(t);
	}
};

template<class T, class U>
struct std::hash<pair<T, U>> {
	inline constexpr size_t operator()(const pair<T, U>& p) const noexcept {
		return (size_t)31 * hash<T>()(p.first) + hash<U>()(p.second);
	}
};

template<class T>
inline T read(istream& strm = cin) {
	T x;
	strm >> x;
	return x;
}

template<class T>
constexpr T rup2(T x) {
	static_assert(std::is_integral_v<T>);
	if (x == 0)
		return 1;
	x--;
	for (int i = 1; i < int(CHAR_BIT * sizeof(T)); i *= 2)
		x |= x >> i;
	return x + 1;
}

template<class T>
using os_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MK_TYPES(TYPE, NAME)using NAME=TYPE;using p##NAME=pair<NAME, NAME>;using a2##NAME=array<NAME, 2>;using v##NAME=vector<NAME>;using v##p##NAME=vector<p##NAME>;using v##a2##NAME=vector<a2##NAME>;using vv##NAME=vector<v##NAME>;using vv##p##NAME=vector<v##p##NAME>;using vv##a2##NAME=vector<v##a2##NAME>;using vvv##NAME=vector<vv##NAME>;using vvv##p##NAME=vector<vv##p##NAME>;using vvv##a2##NAME=vector<vv##a2##NAME>;using vvvv##NAME=vector<vvv##NAME>;using vvvv##p##NAME=vector<vvv##p##NAME>;using vvvv##a2##NAME=vector<vvv##a2##NAME>;using l##NAME=list<NAME>;using l##p##NAME=list<p##NAME>;using l##a2##NAME=list<a2##NAME>;using vl##NAME=vector<l##NAME>;using vl##p##NAME=vector<l##p##NAME>;using vl##a2##NAME=vector<l##a2##NAME>;using s##NAME=set<NAME>;using s##p##NAME=set<p##NAME>;using s##a2##NAME=set<a2##NAME>;using vs##NAME=vector<s##NAME>;using vs##p##NAME=vector<s##p##NAME>;using vs##a2##NAME=vector<s##a2##NAME>;template<class Pr> using S##NAME=set<NAME, Pr>;template<class Pr> using S##p##NAME=set<p##NAME, Pr>;template<class Pr> using S##a2##NAME=set<a2##NAME, Pr>;template<class Pr> using vS##NAME=vector<S##NAME<Pr>>;template<class Pr> using vS##p##NAME=vector<S##p##NAME<Pr>>;template<class Pr> using vS##a2##NAME=vector<S##a2##NAME<Pr>>;using ms##NAME=multiset<NAME>;using ms##p##NAME=multiset<p##NAME>;using ms##a2##NAME=multiset<a2##NAME>;using vms##NAME=vector<ms##NAME>;using vms##p##NAME=vector<ms##p##NAME>;using vms##a2##NAME=vector<ms##a2##NAME>;template<class Pr> using MS##NAME=multiset<NAME, Pr>;template<class Pr> using MS##p##NAME=multiset<p##NAME, Pr>;template<class Pr> using MS##a2##NAME=multiset<a2##NAME, Pr>;template<class Pr> using vMS##NAME=vector<MS##NAME<Pr>>;template<class Pr> using vMS##p##NAME=vector<MS##p##NAME<Pr>>;template<class Pr> using vMS##a2##NAME=vector<MS##a2##NAME<Pr>>;using us##NAME=unordered_set<NAME>;using us##p##NAME=unordered_set<p##NAME>;using us##a2##NAME=unordered_set<a2##NAME>;using vus##NAME=vector<us##NAME>;using vus##p##NAME=vector<us##p##NAME>;using vus##a2##NAME=vector<us##a2##NAME>;template<class H, class Eq> using US##NAME=unordered_set<NAME, H, Eq>;template<class H, class Eq> using US##p##NAME=unordered_set<p##NAME, H, Eq>;template<class H, class Eq> using US##a2##NAME=unordered_set<a2##NAME, H, Eq>;template<class H, class Eq> using vUS##NAME=vector<US##NAME<H, Eq>>;template<class H, class Eq> using vUS##p##NAME=vector<US##p##NAME<H, Eq>>;template<class H, class Eq> using vUS##a2##NAME=vector<US##a2##NAME<H, Eq>>;using ums##NAME=unordered_multiset<NAME>;using ums##p##NAME=unordered_multiset<p##NAME>;using ums##a2##NAME=unordered_multiset<a2##NAME>;using vums##NAME=vector<ums##NAME>;using vums##p##NAME=vector<ums##p##NAME>;using vums##a2##NAME=vector<ums##a2##NAME>;template<class H, class Eq> using UMS##NAME=unordered_multiset<NAME, H, Eq>;template<class H, class Eq> using UMS##p##NAME=unordered_multiset<p##NAME, H, Eq>;template<class H, class Eq> using UMS##a2##NAME=unordered_multiset<a2##NAME, H, Eq>;template<class H, class Eq> using vUMS##NAME=vector<UMS##NAME<H, Eq>>;template<class H, class Eq> using vUMS##p##NAME=vector<UMS##p##NAME<H, Eq>>;template<class H, class Eq> using vUMS##a2##NAME=vector<UMS##a2##NAME<H, Eq>>;using q##NAME=queue<NAME>;using q##p##NAME=queue<p##NAME>;using q##a2##NAME=queue<a2##NAME>;using vq##NAME=vector<q##NAME>;using vq##p##NAME=vector<q##p##NAME>;using vq##a2##NAME=vector<q##a2##NAME>;using d##NAME=deque<NAME>;using d##p##NAME=deque<p##NAME>;using d##a2##NAME=deque<a2##NAME>;using vd##NAME=vector<d##NAME>;using vd##p##NAME=vector<d##p##NAME>;using vd##a2##NAME=vector<d##a2##NAME>;using pq##NAME=priority_queue<NAME>;using pq##p##NAME=priority_queue<p##NAME>;using pq##a2##NAME=priority_queue<a2##NAME>;using vpq##NAME=vector<pq##NAME>;using vpq##p##NAME=vector<pq##p##NAME>;using vpq##a2##NAME=vector<pq##a2##NAME>;template<class Pr> using PQ##NAME=priority_queue<NAME, v##NAME, Pr>;template<class Pr> using PQ##p##NAME=priority_queue<p##NAME, v##p##NAME, Pr>;template<class Pr> using PQ##a2##NAME=priority_queue<a2##NAME, v##a2##NAME, Pr>;template<class Pr> using vPQ##NAME=vector<PQ##NAME<Pr>>;template<class Pr> using vPQ##p##NAME=vector<PQ##p##NAME<Pr>>;template<class Pr> using vPQ##a2##NAME=vector<PQ##a2##NAME<Pr>>;
MK_TYPES(bool, bl);
MK_TYPES(char, c8);
MK_TYPES(unsigned char, uc8);
MK_TYPES(int8_t, i8);
MK_TYPES(int16_t, i16);
MK_TYPES(int32_t, i32);
MK_TYPES(int64_t, i64)
MK_TYPES(__int128, i128);
MK_TYPES(uint8_t, u8);
MK_TYPES(uint16_t, u16);
MK_TYPES(uint32_t, u32);
MK_TYPES(uint64_t, u64);
MK_TYPES(unsigned __int128, u128);
MK_TYPES(float, f32);
MK_TYPES(double, f64);
MK_TYPES(long double, fld);
MK_TYPES(__float128, f128);
MK_TYPES(string, str8);

// TODO map typedefs

template<typename T>
constexpr T MIN = numeric_limits<T>::min();
template<class T>
constexpr T MAX = numeric_limits<T>::max();
template<class T>
constexpr T INF = numeric_limits<T>::infinity();

#define ALL(c) begin(c), end(c)
#define CALL(c) cbegin(c), cend(c)
#define RALL(c) rbegin(c), rend(c)
#define CRALL(c) crbegin(c), crend(c)

// Compatibility with ICPC notebook code
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
typedef long long ll;
typedef pi32 pii;
typedef a2i32 aii;
typedef vi32 vi;
typedef vvi32 vvi;
mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

// Settings Macros:
//#define T_CASES
//#define PRECOMP
//#define PT_NUMS

#ifdef PRECOMP
void pre();
#endif // PRECOMP
void go();

int main(int argc, const char* argv[]) {
	if (argc > 1) {
		freopen(argv[1],"r",stdin);
		freopen(argv[2],"w",stdout);
	}

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef PRECOMP
	pre();
#endif // PRECOMP

#ifdef T_CASES
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++) {
#ifdef PT_NUMS
		cout << "Case #" << tt << ": ";
#endif // PT_NUMS
		go();
	}
#else
	go();
#endif // T_CASES
}

#endif // TEMPLATE_H_INCLUDED

vi64 val, comp, z, cont;
i64 Time, ncomps;
template<class G, class F>
i64 dfs(i64 j, G& g, F& f) {
    i64 low = val[j] = ++Time, x;
    z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ? val[e] : dfs(e, g, f));
    if (low == val[j]) {
        do {
            x = z.back();
            z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont);
        cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F& f) {
    int n = g.size();
    val.assign(n, 0);
    comp.assign(n, -1);
    Time = ncomps = 0;
    for (int i = 0; i < n; i++)
        if (comp[i] < 0) dfs(i, g, f);
}

vi64 DPL, DPR, QL, QR;

void dfs2(int u, const vusi64& Q) {
    if (DPL[u] >= 0)
        return;
    DPL[u] = QL[u];
    DPR[u] = QR[u];
    for (i64 v : Q[u]) {
        dfs2(v, Q);
        DPL[u] = min(DPL[u], QL[v]);
        DPR[u] = max(DPR[u], QR[v]);
    }
}
/*
void rup2(i64& x) {
	x--;
	for (i64 i = 1; i < 64; i *= 2)
		x |= x >> i;
	x++;
}*/

struct MinTree {
	static constexpr i64 UNIT = MAX<i64>;
	i64 f(i64 l, i64 r) {return min(l, r);}
	i64 n, m;
	vvi64 data;
	MinTree(const vector<i64>& leaves) :
		n(leaves.size()) {
		data.push_back(leaves);
		while (data.back().size() > 1) {
			vector<i64> next(data.back().size() / 2);
			for (i64 i = 0; i < data.back().size(); i += 2)
				next[i / 2] = f(data.back()[i], data.back()[i + 1]);
			data.emplace_back(move(next));
		}
		m = data.size();
	}
	void update(i64 pos, i64 val) {
		data[0][pos] = val;
		for (i64 i = 1, j = pos / 2; i < m; i++, j /= 2)
			data[i][j] = f(data[i - 1][j * 2], data[i - 1][j * 2 + 1]);
	}
	i64 query(i64 lo, i64 hi, i64 nlo, i64 nhi, i64 i, i64 j) {
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (lo >= hi) return UNIT;
		if (lo == nlo && hi == nhi) return data[i][j];
		i64 mid = (nlo + nhi) / 2;
		i64 L = query(lo, hi, nlo, mid, i - 1, j * 2);
		i64 R = query(lo, hi, mid, nhi, i - 1, j * 2 + 1);
		return f(L, R);
	}
	i64 query(i64 lo, i64 hi) {
		return query(lo, hi, 0, n, m - 1, 0);
	}
	i64 get(i64 pos) {
        return data[0][pos];
	}
	void dbg() {
        for (const auto& row : data) {
            for (auto x : row)
                cerr << x << ' ';
            cerr << endl;
        }
	}
};

struct MaxTree {
	static constexpr i64 UNIT = MIN<i64>;
	i64 f(i64 l, i64 r) {return max(l, r);}
	i64 n, m;
	vvi64 data;
	MaxTree(const vector<i64>& leaves) :
		n(leaves.size()) {
		data.push_back(leaves);
		while (data.back().size() > 1) {
			vector<i64> next(data.back().size() / 2);
			for (i64 i = 0; i < data.back().size(); i += 2)
				next[i / 2] = f(data.back()[i], data.back()[i + 1]);
			data.emplace_back(move(next));
		}
		m = data.size();
	}
	void update(i64 pos, i64 val) {
		data[0][pos] = val;
		for (i64 i = 1, j = pos / 2; i < m; i++, j /= 2)
			data[i][j] = f(data[i - 1][j * 2], data[i - 1][j * 2 + 1]);
	}
	i64 query(i64 lo, i64 hi, i64 nlo, i64 nhi, i64 i, i64 j) {
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (lo >= hi) return UNIT;
		if (lo == nlo && hi == nhi) return data[i][j];
		i64 mid = (nlo + nhi) / 2;
		i64 L = query(lo, hi, nlo, mid, i - 1, j * 2);
		i64 R = query(lo, hi, mid, nhi, i - 1, j * 2 + 1);
		return f(L, R);
	}
	i64 query(i64 lo, i64 hi) {
		return query(lo, hi, 0, n, m - 1, 0);
	}
	i64 get(i64 pos) {
        return data[0][pos];
	}
	void dbg() {
        for (const auto& row : data) {
            for (auto x : row)
                cerr << x << ' ';
            cerr << endl;
        }
	}
};

void go() {
	i64 n;
	cin >> n;
	vector<i64> ord;
	map<i64, i64> input;
	for (i64 i = 0; i < n; i++) {
		i64 x, r;
		cin >> x >> r;
		ord.push_back(x);
		input[x] = r;
	}
	vector<i64> ICC;
	for (auto [x, r] : input)
		ICC.push_back(x);
	map<i64, i64> CC;
	vi64 R(n);
	for (i64 i = 0; i < n; i++) {
		R[i] = input[ICC[i]];
		CC[ICC[i]] = i;
	}

	const auto gt = [&](map<i64, i64>::iterator it) {
		return it == CC.end() ? n : it->second;
	};

	vector<i64> DL(n, MAX<i64>), DR(n, MIN<i64>);
	for (i64 i = 0; i < n; i++) {
		i64 x = ICC[i];
		i64 rng = input[x];
		i64 lx = x - rng, rx = x + rng;
		DL[i] = gt(CC.lower_bound(lx));
		DR[i] = gt(CC.upper_bound(rx)) - 1;
	}

	vvi64 G(n);
	for (i64 i = 0; i < n; i++) {
		if (DL[i] < i)
			G[i].push_back(DL[i]);
		if (DR[i] > i)
			G[i].push_back(DR[i]);
	}

	vvi64 comps;
	const auto cons = [&](vi64& v) {comps.push_back(move(v));};
	scc(G, cons);

	QL.resize(ncomps);
	QR.resize(ncomps);

	for (int i = 0; i < ncomps; i++) {
        QL[i] = MAX<i64>;
        QR[i] = MIN<i64>;
        for (int u : comps[i]) {
            QL[i] = min(QL[i], DL[u]);
            QR[i] = max(QR[i], DR[u]);
        }
	}

	for (const auto& cmp : comps) {
        for (auto v : cmp)
            cerr << v << ' ';
        cerr << endl;
	}

	vusi64 Q(ncomps);
	for (i64 i = 0; i < n; i++) {
        for (int u : comps[i])
            for (int v : G[u])
                Q[u].insert(comp[v]);
	}

    DPL.resize(ncomps, -1);
    DPR.resize(ncomps, -1);
    for (i64 i = 0; i < ncomps; i++) {
        if (DPL[i] < 0)
            dfs2(i, Q);
    }

    int N = rup2(n);
    DL.resize(N, MAX<i64>);
    DR.resize(N, MIN<i64>);

    MinTree STL(DL);
    MaxTree STR(DR);

    for (int x : ord) {
        int i = CC[x];
        cerr << i << endl;
        int v = comp[i];
        cerr << v << ' ' << ncomps << endl;
        i64 l = DPL[v], r = DPR[v];
        cerr << l << ' ' << r << ' ' << N << endl;
        i64 l2 = STL.query(l, r + 1);
        i64 r2 = STR.query(l, r + 1);
        cout << r2 - l2 + 1 << ' ';
    }
}

/*
void rup2(i64& x) {
	x--;
	for (i64 i = 1; i < 64; i *= 2)
		x |= x >> i;
	x++;
}

struct MinTree {
	static constexpr i64 UNIT = MAX<i64>;
	i64 f(i64 l, i64 r) {return min(l, r);}
	i64 n, m;
	vvi64 data;
	MinTree(const vector<i64>& leaves) :
		n(leaves.size()) {
		data.push_back(leaves);
		while (data.back().size() > 1) {
			vector<i64> next(data.back().size() / 2);
			for (i64 i = 0; i < data.back().size(); i += 2)
				next[i / 2] = f(data.back()[i], data.back()[i + 1]);
			data.emplace_back(move(next));
		}
		m = data.size();
	}
	void update(i64 pos, i64 val) {
		data[0][pos] = val;
		for (i64 i = 1, j = pos / 2; i < m; i++, j /= 2)
			data[i][j] = f(data[i - 1][j * 2], data[i - 1][j * 2 + 1]);
	}
	i64 query(i64 lo, i64 hi, i64 nlo, i64 nhi, i64 i, i64 j) {
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (lo >= hi) return UNIT;
		if (lo == nlo && hi == nhi) return data[i][j];
		i64 mid = (nlo + nhi) / 2;
		i64 L = query(lo, hi, nlo, mid, i - 1, j * 2);
		i64 R = query(lo, hi, mid, nhi, i - 1, j * 2 + 1);
		return f(L, R);
	}
	i64 query(i64 lo, i64 hi) {
		return query(lo, hi, 0, n, m - 1, 0);
	}
	i64 get(i64 pos) {
        return data[0][pos];
	}
	void dbg() {
        for (const auto& row : data) {
            for (auto x : row)
                cerr << x << ' ';
            cerr << endl;
        }
	}
};

struct MaxTree {
	static constexpr i64 UNIT = MIN<i64>;
	i64 f(i64 l, i64 r) {return max(l, r);}
	i64 n, m;
	vvi64 data;
	MaxTree(const vector<i64>& leaves) :
		n(leaves.size()) {
		data.push_back(leaves);
		while (data.back().size() > 1) {
			vector<i64> next(data.back().size() / 2);
			for (i64 i = 0; i < data.back().size(); i += 2)
				next[i / 2] = f(data.back()[i], data.back()[i + 1]);
			data.emplace_back(move(next));
		}
		m = data.size();
	}
	void update(i64 pos, i64 val) {
		data[0][pos] = val;
		for (i64 i = 1, j = pos / 2; i < m; i++, j /= 2)
			data[i][j] = f(data[i - 1][j * 2], data[i - 1][j * 2 + 1]);
	}
	i64 query(i64 lo, i64 hi, i64 nlo, i64 nhi, i64 i, i64 j) {
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (lo >= hi) return UNIT;
		if (lo == nlo && hi == nhi) return data[i][j];
		i64 mid = (nlo + nhi) / 2;
		i64 L = query(lo, hi, nlo, mid, i - 1, j * 2);
		i64 R = query(lo, hi, mid, nhi, i - 1, j * 2 + 1);
		return f(L, R);
	}
	i64 query(i64 lo, i64 hi) {
		return query(lo, hi, 0, n, m - 1, 0);
	}
	i64 get(i64 pos) {
        return data[0][pos];
	}
	void dbg() {
        for (const auto& row : data) {
            for (auto x : row)
                cerr << x << ' ';
            cerr << endl;
        }
	}
};

void go() {
	i64 n;
	cin >> n;
	vector<i64> ord;
	map<i64, i64> input;
	for (i64 i = 0; i < n; i++) {
		i64 x, r;
		cin >> x >> r;
        ord.push_back(x);
		input[x] = r;
	}
	vector<i64> ICC;
	for (auto [x, r] : input)
		ICC.push_back(x);
	map<i64, i64> CC;
	vi64 R(n);
	for (i64 i = 0; i < n; i++) {
		R[i] = input[ICC[i]];
		CC[ICC[i]] = i;
	}
	i64 N = n;
	rup2(N);

	const auto gt = [&](map<i64, i64>::iterator it) {
        return it == CC.end() ? n : it->second;
	};

    vector<i64> DL(N, INT_MAX), DR(N, INT_MIN);
    for (i64 i = 0; i < n; i++) {
        i64 x = ICC[i];
        i64 rng = input[x];
        i64 lx = x - rng, rx = x + rng;
        DL[i] = gt(CC.lower_bound(lx));
        DR[i] = gt(CC.upper_bound(rx));
    }
    //for (i64 i = 0; i < n; i++)
    //    cerr << DL[i] << ' ' << DR[i] << endl;
    vector<i64> I(n);
    iota(all(I), 0);
    sort(all(I), [&](i64 i, i64 j) {return DL[i] == DL[j] ? DR[i] > DR[j] : DL[i] < DL[j];});
    MinTree STL(DL);
    for(i64 i : I){
        i64 l = STL.query(DL[i], DR[i]);
        STL.update(i, l);
    }
    sort(all(I), [&](i64 i, i64 j) {return DR[i] == DR[j] ? DL[i] < DL[j] : DR[i] > DR[j];});
    MaxTree STR(DR);
	//STR.dbg();
    for (i64 i : I) {
        i64 r = STR.query(DL[i], DR[i]);
        //cerr << i << ": " << r << endl;
        STR.update(i, r);
        //STR.dbg();
    }
    for (i64 x : ord) {
        i64 i = CC[x];
        //cerr << i << ' ' << DL[i] << ' ' << DR[i] << ' ' << ' ' << STR.get(i) << ' ' << STL.get(i) << endl;
        cout << STR.get(i) - STL.get(i) << ' ';
    }
}
*/
