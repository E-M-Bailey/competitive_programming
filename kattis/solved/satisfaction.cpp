#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma")
#ifndef GODBOLT
#pragma GCC target("tune=native")
#endif

#include <bits/stdc++.h>
#include <immintrin.h>
#include <nmmintrin.h>

using namespace std;

int k = 0, ids[91];
char vars[20];

vector<string> tokens;

alignas(256) uint64_t const BITS[256 * 4]
{
	0, 0, 0, 0x0000000000000001ll,
	0, 0, 0, 0x0000000000000002ll,
	0, 0, 0, 0x0000000000000004ll,
	0, 0, 0, 0x0000000000000008ll,
	0, 0, 0, 0x0000000000000010ll,
	0, 0, 0, 0x0000000000000020ll,
	0, 0, 0, 0x0000000000000040ll,
	0, 0, 0, 0x0000000000000080ll,
	0, 0, 0, 0x0000000000000100ll,
	0, 0, 0, 0x0000000000000200ll,
	0, 0, 0, 0x0000000000000400ll,
	0, 0, 0, 0x0000000000000800ll,
	0, 0, 0, 0x0000000000001000ll,
	0, 0, 0, 0x0000000000002000ll,
	0, 0, 0, 0x0000000000004000ll,
	0, 0, 0, 0x0000000000008000ll,
	0, 0, 0, 0x0000000000010000ll,
	0, 0, 0, 0x0000000000020000ll,
	0, 0, 0, 0x0000000000040000ll,
	0, 0, 0, 0x0000000000080000ll,
	0, 0, 0, 0x0000000000100000ll,
	0, 0, 0, 0x0000000000200000ll,
	0, 0, 0, 0x0000000000400000ll,
	0, 0, 0, 0x0000000000800000ll,
	0, 0, 0, 0x0000000001000000ll,
	0, 0, 0, 0x0000000002000000ll,
	0, 0, 0, 0x0000000004000000ll,
	0, 0, 0, 0x0000000008000000ll,
	0, 0, 0, 0x0000000010000000ll,
	0, 0, 0, 0x0000000020000000ll,
	0, 0, 0, 0x0000000040000000ll,
	0, 0, 0, 0x0000000080000000ll,
	0, 0, 0, 0x0000000100000000ll,
	0, 0, 0, 0x0000000200000000ll,
	0, 0, 0, 0x0000000400000000ll,
	0, 0, 0, 0x0000000800000000ll,
	0, 0, 0, 0x0000001000000000ll,
	0, 0, 0, 0x0000002000000000ll,
	0, 0, 0, 0x0000004000000000ll,
	0, 0, 0, 0x0000008000000000ll,
	0, 0, 0, 0x0000010000000000ll,
	0, 0, 0, 0x0000020000000000ll,
	0, 0, 0, 0x0000040000000000ll,
	0, 0, 0, 0x0000080000000000ll,
	0, 0, 0, 0x0000100000000000ll,
	0, 0, 0, 0x0000200000000000ll,
	0, 0, 0, 0x0000400000000000ll,
	0, 0, 0, 0x0000800000000000ll,
	0, 0, 0, 0x0001000000000000ll,
	0, 0, 0, 0x0002000000000000ll,
	0, 0, 0, 0x0004000000000000ll,
	0, 0, 0, 0x0008000000000000ll,
	0, 0, 0, 0x0010000000000000ll,
	0, 0, 0, 0x0020000000000000ll,
	0, 0, 0, 0x0040000000000000ll,
	0, 0, 0, 0x0080000000000000ll,
	0, 0, 0, 0x0100000000000000ll,
	0, 0, 0, 0x0200000000000000ll,
	0, 0, 0, 0x0400000000000000ll,
	0, 0, 0, 0x0800000000000000ll,
	0, 0, 0, 0x1000000000000000ll,
	0, 0, 0, 0x2000000000000000ll,
	0, 0, 0, 0x4000000000000000ll,
	0, 0, 0, 0x8000000000000000ll,
	0, 0, 0x0000000000000001ll, 0,
	0, 0, 0x0000000000000002ll, 0,
	0, 0, 0x0000000000000004ll, 0,
	0, 0, 0x0000000000000008ll, 0,
	0, 0, 0x0000000000000010ll, 0,
	0, 0, 0x0000000000000020ll, 0,
	0, 0, 0x0000000000000040ll, 0,
	0, 0, 0x0000000000000080ll, 0,
	0, 0, 0x0000000000000100ll, 0,
	0, 0, 0x0000000000000200ll, 0,
	0, 0, 0x0000000000000400ll, 0,
	0, 0, 0x0000000000000800ll, 0,
	0, 0, 0x0000000000001000ll, 0,
	0, 0, 0x0000000000002000ll, 0,
	0, 0, 0x0000000000004000ll, 0,
	0, 0, 0x0000000000008000ll, 0,
	0, 0, 0x0000000000010000ll, 0,
	0, 0, 0x0000000000020000ll, 0,
	0, 0, 0x0000000000040000ll, 0,
	0, 0, 0x0000000000080000ll, 0,
	0, 0, 0x0000000000100000ll, 0,
	0, 0, 0x0000000000200000ll, 0,
	0, 0, 0x0000000000400000ll, 0,
	0, 0, 0x0000000000800000ll, 0,
	0, 0, 0x0000000001000000ll, 0,
	0, 0, 0x0000000002000000ll, 0,
	0, 0, 0x0000000004000000ll, 0,
	0, 0, 0x0000000008000000ll, 0,
	0, 0, 0x0000000010000000ll, 0,
	0, 0, 0x0000000020000000ll, 0,
	0, 0, 0x0000000040000000ll, 0,
	0, 0, 0x0000000080000000ll, 0,
	0, 0, 0x0000000100000000ll, 0,
	0, 0, 0x0000000200000000ll, 0,
	0, 0, 0x0000000400000000ll, 0,
	0, 0, 0x0000000800000000ll, 0,
	0, 0, 0x0000001000000000ll, 0,
	0, 0, 0x0000002000000000ll, 0,
	0, 0, 0x0000004000000000ll, 0,
	0, 0, 0x0000008000000000ll, 0,
	0, 0, 0x0000010000000000ll, 0,
	0, 0, 0x0000020000000000ll, 0,
	0, 0, 0x0000040000000000ll, 0,
	0, 0, 0x0000080000000000ll, 0,
	0, 0, 0x0000100000000000ll, 0,
	0, 0, 0x0000200000000000ll, 0,
	0, 0, 0x0000400000000000ll, 0,
	0, 0, 0x0000800000000000ll, 0,
	0, 0, 0x0001000000000000ll, 0,
	0, 0, 0x0002000000000000ll, 0,
	0, 0, 0x0004000000000000ll, 0,
	0, 0, 0x0008000000000000ll, 0,
	0, 0, 0x0010000000000000ll, 0,
	0, 0, 0x0020000000000000ll, 0,
	0, 0, 0x0040000000000000ll, 0,
	0, 0, 0x0080000000000000ll, 0,
	0, 0, 0x0100000000000000ll, 0,
	0, 0, 0x0200000000000000ll, 0,
	0, 0, 0x0400000000000000ll, 0,
	0, 0, 0x0800000000000000ll, 0,
	0, 0, 0x1000000000000000ll, 0,
	0, 0, 0x2000000000000000ll, 0,
	0, 0, 0x4000000000000000ll, 0,
	0, 0, 0x8000000000000000ll, 0,
	0, 0x0000000000000001ll, 0, 0,
	0, 0x0000000000000002ll, 0, 0,
	0, 0x0000000000000004ll, 0, 0,
	0, 0x0000000000000008ll, 0, 0,
	0, 0x0000000000000010ll, 0, 0,
	0, 0x0000000000000020ll, 0, 0,
	0, 0x0000000000000040ll, 0, 0,
	0, 0x0000000000000080ll, 0, 0,
	0, 0x0000000000000100ll, 0, 0,
	0, 0x0000000000000200ll, 0, 0,
	0, 0x0000000000000400ll, 0, 0,
	0, 0x0000000000000800ll, 0, 0,
	0, 0x0000000000001000ll, 0, 0,
	0, 0x0000000000002000ll, 0, 0,
	0, 0x0000000000004000ll, 0, 0,
	0, 0x0000000000008000ll, 0, 0,
	0, 0x0000000000010000ll, 0, 0,
	0, 0x0000000000020000ll, 0, 0,
	0, 0x0000000000040000ll, 0, 0,
	0, 0x0000000000080000ll, 0, 0,
	0, 0x0000000000100000ll, 0, 0,
	0, 0x0000000000200000ll, 0, 0,
	0, 0x0000000000400000ll, 0, 0,
	0, 0x0000000000800000ll, 0, 0,
	0, 0x0000000001000000ll, 0, 0,
	0, 0x0000000002000000ll, 0, 0,
	0, 0x0000000004000000ll, 0, 0,
	0, 0x0000000008000000ll, 0, 0,
	0, 0x0000000010000000ll, 0, 0,
	0, 0x0000000020000000ll, 0, 0,
	0, 0x0000000040000000ll, 0, 0,
	0, 0x0000000080000000ll, 0, 0,
	0, 0x0000000100000000ll, 0, 0,
	0, 0x0000000200000000ll, 0, 0,
	0, 0x0000000400000000ll, 0, 0,
	0, 0x0000000800000000ll, 0, 0,
	0, 0x0000001000000000ll, 0, 0,
	0, 0x0000002000000000ll, 0, 0,
	0, 0x0000004000000000ll, 0, 0,
	0, 0x0000008000000000ll, 0, 0,
	0, 0x0000010000000000ll, 0, 0,
	0, 0x0000020000000000ll, 0, 0,
	0, 0x0000040000000000ll, 0, 0,
	0, 0x0000080000000000ll, 0, 0,
	0, 0x0000100000000000ll, 0, 0,
	0, 0x0000200000000000ll, 0, 0,
	0, 0x0000400000000000ll, 0, 0,
	0, 0x0000800000000000ll, 0, 0,
	0, 0x0001000000000000ll, 0, 0,
	0, 0x0002000000000000ll, 0, 0,
	0, 0x0004000000000000ll, 0, 0,
	0, 0x0008000000000000ll, 0, 0,
	0, 0x0010000000000000ll, 0, 0,
	0, 0x0020000000000000ll, 0, 0,
	0, 0x0040000000000000ll, 0, 0,
	0, 0x0080000000000000ll, 0, 0,
	0, 0x0100000000000000ll, 0, 0,
	0, 0x0200000000000000ll, 0, 0,
	0, 0x0400000000000000ll, 0, 0,
	0, 0x0800000000000000ll, 0, 0,
	0, 0x1000000000000000ll, 0, 0,
	0, 0x2000000000000000ll, 0, 0,
	0, 0x4000000000000000ll, 0, 0,
	0, 0x8000000000000000ll, 0, 0,
	0x0000000000000001ll, 0, 0, 0,
	0x0000000000000002ll, 0, 0, 0,
	0x0000000000000004ll, 0, 0, 0,
	0x0000000000000008ll, 0, 0, 0,
	0x0000000000000010ll, 0, 0, 0,
	0x0000000000000020ll, 0, 0, 0,
	0x0000000000000040ll, 0, 0, 0,
	0x0000000000000080ll, 0, 0, 0,
	0x0000000000000100ll, 0, 0, 0,
	0x0000000000000200ll, 0, 0, 0,
	0x0000000000000400ll, 0, 0, 0,
	0x0000000000000800ll, 0, 0, 0,
	0x0000000000001000ll, 0, 0, 0,
	0x0000000000002000ll, 0, 0, 0,
	0x0000000000004000ll, 0, 0, 0,
	0x0000000000008000ll, 0, 0, 0,
	0x0000000000010000ll, 0, 0, 0,
	0x0000000000020000ll, 0, 0, 0,
	0x0000000000040000ll, 0, 0, 0,
	0x0000000000080000ll, 0, 0, 0,
	0x0000000000100000ll, 0, 0, 0,
	0x0000000000200000ll, 0, 0, 0,
	0x0000000000400000ll, 0, 0, 0,
	0x0000000000800000ll, 0, 0, 0,
	0x0000000001000000ll, 0, 0, 0,
	0x0000000002000000ll, 0, 0, 0,
	0x0000000004000000ll, 0, 0, 0,
	0x0000000008000000ll, 0, 0, 0,
	0x0000000010000000ll, 0, 0, 0,
	0x0000000020000000ll, 0, 0, 0,
	0x0000000040000000ll, 0, 0, 0,
	0x0000000080000000ll, 0, 0, 0,
	0x0000000100000000ll, 0, 0, 0,
	0x0000000200000000ll, 0, 0, 0,
	0x0000000400000000ll, 0, 0, 0,
	0x0000000800000000ll, 0, 0, 0,
	0x0000001000000000ll, 0, 0, 0,
	0x0000002000000000ll, 0, 0, 0,
	0x0000004000000000ll, 0, 0, 0,
	0x0000008000000000ll, 0, 0, 0,
	0x0000010000000000ll, 0, 0, 0,
	0x0000020000000000ll, 0, 0, 0,
	0x0000040000000000ll, 0, 0, 0,
	0x0000080000000000ll, 0, 0, 0,
	0x0000100000000000ll, 0, 0, 0,
	0x0000200000000000ll, 0, 0, 0,
	0x0000400000000000ll, 0, 0, 0,
	0x0000800000000000ll, 0, 0, 0,
	0x0001000000000000ll, 0, 0, 0,
	0x0002000000000000ll, 0, 0, 0,
	0x0004000000000000ll, 0, 0, 0,
	0x0008000000000000ll, 0, 0, 0,
	0x0010000000000000ll, 0, 0, 0,
	0x0020000000000000ll, 0, 0, 0,
	0x0040000000000000ll, 0, 0, 0,
	0x0080000000000000ll, 0, 0, 0,
	0x0100000000000000ll, 0, 0, 0,
	0x0200000000000000ll, 0, 0, 0,
	0x0400000000000000ll, 0, 0, 0,
	0x0800000000000000ll, 0, 0, 0,
	0x1000000000000000ll, 0, 0, 0,
	0x2000000000000000ll, 0, 0, 0,
	0x4000000000000000ll, 0, 0, 0,
	0x8000000000000000ll, 0, 0, 0,
};

template<int K>
struct fast_bitset_large
{
	static constexpr int N = 1 << K, M = N / 256;
	alignas(256) __m256i data[M];

	[[gnu::always_inline]] inline fast_bitset_large &operator|=(fast_bitset_large const &B) noexcept
	{
		for (int i = 0; i < M; i++)
			data[i] = _mm256_or_si256(data[i], B.data[i]);
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &operator&=(fast_bitset_large const &B) noexcept
	{
		for (int i = 0; i < M; i++)
			data[i] = _mm256_and_si256(data[i], B.data[i]);
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &set() noexcept
	{
		__m256i const ONES = _mm256_set1_epi64x(-1ll);
		for (int i = 0; i < M; i++)
			data[i] = ONES;
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &set(int i) noexcept
	{
		data[i / 256] = _mm256_or_si256(data[i / 256], _mm256_load_si256((__m256i *)(BITS + i % 256 * 4)));
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &flip() noexcept
	{
		__m256i const ONES = _mm256_set1_epi64x(-1ll);
		for (int i = 0; i < M; i++)
			data[i] = _mm256_xor_si256(data[i], ONES);
		return *this;
	}
	[[gnu::always_inline]] inline bool none() const noexcept
	{
		for (int i = 0; i < M; i++)
			if (!_mm256_testz_si256(data[i], data[i]))
				return false;
		return true;
	}

	inline friend ostream &operator<<(ostream &os, fast_bitset_large const &A)
	{
		for (int i = M; i-- > 0;)
		{
			for (int j = 4; j-- > 0;)
				os << bitset<64>(((uint64_t *)(A.data + i))[j]);
		}
		return os;
	}
};

template<int K>
[[gnu::always_inline]] inline fast_bitset_large<K> operator|(fast_bitset_large<K> const &A, fast_bitset_large<K> const &B) noexcept
{
	fast_bitset_large<K> ans;
	for (int i = 0; i < fast_bitset_large<K>::M; i++)
		ans.data[i] = _mm256_or_si256(A.data[i], B.data[i]);
	return ans;
}
template<int K>
[[gnu::always_inline]] inline fast_bitset_large<K> operator&(fast_bitset_large<K> const &A, fast_bitset_large<K> const &B) noexcept
{
	fast_bitset_large<K> ans;
	for (int i = 0; i < fast_bitset_large<K>::M; i++)
		ans.data[i] = _mm256_and_si256(A.data[i], B.data[i]);
	return ans;
}
template<int K>
[[gnu::always_inline]] inline pair<bool, bool> test_cz(fast_bitset_large<K> const &A, fast_bitset_large<K> const &B) noexcept
{
	bool a = true, b = true;
	for (int i = 0; i < fast_bitset_large<K>::M; i++)
	{
		a &= _mm256_testc_si256(A.data[i], B.data[i]);
		b &= _mm256_testz_si256(A.data[i], B.data[i]);
	}
	return { a, b };
}

template<size_t N>
[[gnu::always_inline]] inline pair<bool, bool> test_cz(bitset<N> const &A, bitset<N> const &B) noexcept
{
	return { (~A & B).none(), (A & B).none() };
}

template<int K>
struct solver
{
	typedef conditional_t < K < 8, bitset<1 << K>, fast_bitset_large<K>> state;
	//typedef bitset<1 << K> state;
	static state var_st[K];
	static constexpr state parse_or(char const *&ptr) noexcept
	{
		state ans = parse_and(ptr);
		while (*ptr == '|')
		{
			ptr++;
			ans |= parse_and(ptr);
		}
		return ans;
	}
	static constexpr state parse_and(char const *&ptr) noexcept
	{
		state ans = parse_literal(ptr);
		while (*ptr == '&')
		{
			ptr++;
			ans &= parse_literal(ptr);
		}
		return ans;
	}
	static constexpr state parse_literal(char const *&ptr) noexcept
	{
		bool flip = false;
		while (*ptr == '~')
		{
			ptr++;
			flip = !flip;
		}
		auto ans = *ptr == '(' ? parse_or(++ptr) : var_st[ids[(int)*ptr]];
		ptr++;
		if (flip)
			ans.flip();
		return ans;
	}

	static void run(vector<string>::const_iterator &it, state st)
	{
		for (;; it++)
		{
			if (it->front() == 'i')
			{
				char const *ptr = (++it)->c_str();
				auto cond = parse_or(ptr);
				run(it += 2, cond & st);
				if (*it == "else")
				{
					cond.flip();
					run(++it, cond &= st);
				}
			}
			else if (it->front() == 'c')
			{
				cout << '>';
				if (st.none())
					cout << "unreachable\n";
				else
				{
					for (int i = 0; i < K; i++)
					{
						auto [c, z] = test_cz(var_st[i], st);
						if (c)
							cout << vars[i];
						else if (z)
							cout << char(vars[i] | 32);
					}
					cout << '\n';
				}
			}
			else
				break;
		}
	}

	static void solve()
	{
		for (int i = 0; i < K; i++)
			for (int j = 0; j < (1 << K); j++)
				if ((1 << i) & j)
					var_st[i].set(j);

		state st;
		st.set();
		auto it = cbegin(tokens);
		run(it, st);
	}
};
template<int K>
typename solver<K>::state solver<K>::var_st[K];

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	{
		string token;
		while (cin >> token)
			tokens.push_back(move(token));
		tokens.push_back("e");
	}

	for (string const &token : tokens)
		for (char c : token)
			if ('A' <= c && c <= 'Z' && find(vars, vars + k, c) == vars + k)
				vars[k++] = c;
	sort(vars, vars + k);
	for (int i = 0; i < k; i++)
		ids[(int)vars[i]] = i;

	switch (k)
	{
#ifndef GODBOLT
	case 1: solver<1>::solve(); break;
	case 2: solver<2>::solve(); break;
	case 3: solver<3>::solve(); break;
	case 4: solver<4>::solve(); break;
	case 5: solver<5>::solve(); break;
	case 6: solver<6>::solve(); break;
	case 7: solver<7>::solve(); break;
	case 8: solver<8>::solve(); break;
	case 9: solver<9>::solve(); break;
	case 10: solver<10>::solve(); break;
	case 11: solver<11>::solve(); break;
	case 12: solver<12>::solve(); break;
	case 13: solver<13>::solve(); break;
	case 14: solver<14>::solve(); break;
	case 15: solver<15>::solve(); break;
	case 16: solver<16>::solve(); break;
	case 17: solver<17>::solve(); break;
	case 18: solver<18>::solve(); break;
	case 19: solver<19>::solve(); break;
#endif
	case 20: solver<20>::solve(); break;
	}
}