#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

using ui = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

constexpr int iinf = 0x3f3f3f3f;
constexpr ll inf = 1'000'000'000'000'000'000;
constexpr ll mod = 1e9 + 7;

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string ccurr = "";                     \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ') continue;       \
            if (_s[zz] == ',') {               \
                _ss << ' ' + ccurr;            \
                ccurr = "";                    \
            } else                             \
                ccurr += _s[zz];               \
        }                                      \
        _ss << ' ' + ccurr;                    \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) { cerr << '\n'; }
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args)
{
	cerr << " [" << *it << ": " << a << "] ";
	vars(++it, args...);
}

#define printVerdict(verdict) \
    cout << (verdict ? "Yes" : "No") << '\n'
#define printDecimal(d) \
    cout << setprecision(d) << fixed
#define printCase(_) \
    cout << "Case #" << (_) << ": "

template <int I, typename TupleT>
ostream &printTupleImpl(ostream &out, const TupleT &t)
{
	if constexpr (I < tuple_size_v<TupleT>)
	{
		out << get<I>(t) << " ";
		printTupleImpl<I + 1, TupleT>(out, t);
	}
	return out;
}
template <typename... Ts>
ostream &operator<<(ostream &out, const tuple<Ts...> &t)
{
	return printTupleImpl<0>(out, t);
}

template <int I, typename TupleT>
istream &readTupleImpl(istream &in, TupleT &t)
{
	if constexpr (I < tuple_size_v<TupleT>)
	{
		in >> get<I>(t);
		readTupleImpl<I + 1, TupleT>(in, t);
	}
	return in;
}

template <typename... Ts>
istream &operator>>(istream &in, tuple<Ts...> &t)
{
	return readTupleImpl<0>(in, t);
}

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) { return out << p.first << " " << p.second; }
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &arr)
{
	for (const T &a : arr) out << a << " ";
	return out;
}
template <typename T>
ostream &operator<<(ostream &out, const vector<vector<T>> &grid)
{
	for (const vector<T> &row : grid) out << row << '\n';
	return out;
}
template <typename T>
istream &operator>>(istream &in, vector<T> &arr)
{
	for (T &a : arr) in >> a;
	return in;
}
template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &a)
{
	in >> a.first >> a.second;
	return in;
}

inline void prayGod()
{
	int t; std::cin >> t;
	while (t--)
	{
		std::multiset<std::pair<int, int>> bid, ask;
		int curr_price = -1;
		int n; std::cin >> n;
		while (n--)
		{
			std::string order_type, buff;
			int x, y;
			std::cin >> order_type >> x >> buff;
			std::cin >> buff >> y;
			if (order_type == "buy")
			{
				bid.emplace(y, x);
			}
			else
			{
				ask.emplace(y, x);
			}
			int curr_bid = -1, curr_ask = -1;
			for (;;)
			{
				bool good = false;
				if (!bid.empty())
				{
					curr_bid = std::prev(bid.end())->first;
				}
				if (!ask.empty())
				{
					curr_ask = ask.begin()->first;
				}
				if (!bid.empty() && !ask.empty())
				{
					if (curr_bid >= curr_ask)
					{
						good = true;
						curr_price = curr_ask;
						int bid_vol = std::prev(bid.end())->second, ask_vol = ask.begin()->second;
						auto delta = std::min(std::prev(bid.end())->second, ask.begin()->second);
						bid.erase(std::prev(bid.end()));
						ask.erase(ask.begin());
						if (delta < bid_vol)
						{
							bid.emplace(curr_bid, bid_vol - delta);
						}
						if (delta < ask_vol)
						{
							ask.emplace(curr_ask, ask_vol - delta);
						}
					}
				}
				if (!bid.empty())
				{
					curr_bid = std::prev(bid.end())->first;
				}
				else  curr_bid = -1;
				if (!ask.empty())
				{
					curr_ask = ask.begin()->first;
				}
				else curr_ask = -1;
				if (!good)
					break;
			}
			if (curr_ask != -1) std::cout << curr_ask << " ";
			else std::cout << "- ";

			if (curr_bid != -1) std::cout << curr_bid << " ";
			else std::cout << "- ";

			if (curr_price != -1) std::cout << curr_price << " ";
			else std::cout << "- ";

			std::cout << '\n';
		}
	}

}

int main()
{
#ifdef LLOCAL
	clock_t start = clock();
#endif
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);

	prayGod();
#ifdef LLOCAL
	clock_t end = clock();

	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	debugDecimal(5) << time_taken << " s" << '\n';
#endif
}