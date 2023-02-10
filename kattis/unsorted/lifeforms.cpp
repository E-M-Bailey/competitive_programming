#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#define sz(C) int(size(C))

template<class V>
struct hash_table
{
	typedef pair<u64, T> value_type;
	size_t 
}

//static const u64 RAND = (u64)duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

/*
// A closed-chaining hash table that only supports insertion and does not resize.
//
template<typename T>
struct fast_hash_table
{

};*/

struct hash_window
{
	//constexpr static u32 XOR = 3157132094;
	constexpr static u32 M[]{ 1'000'000'007u, 1'000'000'009u };
	constexpr static int N = sz(M);
	using hash_t = array<u32, N>;
	constexpr static u32 A = 'a', Z = 'z', S = Z - A + 1;
	//using set_t = map<u32, set<u32>>;

	template<class T>
	using map_t = gp_hash_table<u64, gp_hash_table<u64, T>>;
	using set_t = map_t<null_type>;
	//using map_t = map<u64, T>;

	hash_t H{};
	hash_t P{}; // P[i] = -S^len mod M[i]

	void clear()
	{
		for (int i = 0; i < N; i++)
		{
			H[i] = 0;
			P[i] = M[i] - 1;
		}
	}

	hash_window()
	{
		clear();
	}

	void push(u32 x)
	{
		x -= A;
		for (int i = 0; i < N; i++)
		{
			H[i] = u32(((u64)S * H[i] + x) % M[i]);
			P[i] = u32(((u64)S * P[i]) % M[i]);
		}
	}

	void slide(u32 x, u32 y)
	{
		x -= A;
		y -= A;
		for (int i = 0; i < N; i++)
			H[i] = u32(((u64)S * H[i] + x + (u64)y * P[i]) % M[i]);
	}

	static bool insert(set_t& set, const hash_t& key)
	{
		//return set[key[0] ^ XOR].insert(key[1] ^ XOR).second;
		return set[key[0]].insert(key[1]).second;
		//return set.insert((key[0] + 9973 * key[1]) ^ XOR).second;
	}

	template<class T>
	static T& lookup(map_t<T>& map, const hash_t& key)
	{
		//return map[key[0] ^ XOR][key[1] ^ XOR];
		return map[key[0] ^ RAND][key[1] ^ RAND];
		//return map[(key[0] + 9973 * key[1]) ^ XOR];
	}

	void update(int idx, vector<hash_t>& ans, set_t& set, map_t<pair<int, int>>& freq, int& best)
	{
		ans.push_back(H);
		if (insert(set, H))
		{
			auto& [f, i] = lookup(freq, H);
			best = max(best, ++f);
			i = idx;
		}
	}


	// Generates the hashes of each substring of length len of str.
	// Also, updates freq, which stores, for each hash, the set of indices whose strings contain a substring of length len with that hash.
	void hashes(const string& str, int len, int idx, vector<hash_t>& ans, map_t<pair<int, int>>& freq, int& best)
	{
		static set_t set;
		set.clear();
		ans.clear();
		clear();

		int m = (int)str.size();
		if (m < len)
			return;

		for (int i = 0; i < len; i++)
			push(str[i]);
		update(idx, ans, set, freq, best);

		for (int i = len; i < m; i++)
		{
			slide(str[i], str[i - len]);
			update(idx, ans, set, freq, best);
		}
	}

	int all_hashes(const vector<string>& S, int len, vector<vector<hash_t>>& H, map_t<pair<int, int>>& freq)
	{
		freq.clear();
		int best = 0;
		for (int i = 0; i < sz(S); i++)
			hashes(S[i], len, i, H[i], freq, best);
		return best;
	}
};

ostringstream out;

void go(int n)
{
	vector<string> S(n);
	for (string& str : S)
		cin >> str;

	hash_window::map_t<pair<int, int>> freq;

	vector<vector<hash_window::hash_t>> H(n);
	for (int i = 0; i < n; i++)
		H[i].reserve(S[i].size() + 1);

	hash_window HW;

	int lo = 0, hi = 0;
	for (const string& s : S)
		hi = max(hi, (int)s.size());
	while (lo < hi)
	{
		int len = (lo + hi + 1) / 2;
		int best = HW.all_hashes(S, len, H, freq);
		if (best * 2 >= n)
			lo = len;
		else
			hi = len - 1;
	}

	if (lo == 0)
	{
		out << '?' << endl << endl;
		return;
	}

	HW.all_hashes(S, lo, H, freq);

	hash_window::set_t set;
	for (int i = 0; i < n; i++)
	{
		set.clear();
		for (int j = 0; j < sz(H[i]); j++)
		{
			const hash_window::hash_t& h = H[i][j];
			if (!hash_window::insert(set, h))
				continue;
			auto [f, idx] = hash_window::lookup(freq, h);
			if (f * 2 >= n && idx == i)
				out << S[i].substr(j, lo) << endl;
		}
	}
	out << endl;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int n;
	while (cin >> n, n)
		go(n);
	cout << out.str();
}