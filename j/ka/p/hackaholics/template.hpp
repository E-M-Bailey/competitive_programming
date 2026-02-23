#ifndef EMBAILEY_TEMPLATE_ABBREV_H
#define EMBAILEY_TEMPLATE_ABBREV_H

#ifndef EMBAILEY_TEMPLATE_BASIC_H
#ifndef EMBAILEY_TEMPLATE_BASIC_H
#define EMBAILEY_TEMPLATE_BASIC_H

#include <bits/extc++.h>

#define stringify(x) #x
#define xstringify(x) stringify(x)

#define ainline [[gnu::always_inline]]

namespace
{

template<std::unsigned_integral T>
[[nodiscard]] constexpr T rup2(T x) { return T{ 1 } << (sizeof(T) * CHAR_BIT - std::countl_zero<T>(x) - 1); }

} // namespace

#endif // EMBAILEY_TEMPLATE_BASIC_H

#endif // EMBAILEY_TEMPLATE_BASIC_H

namespace
{
template<typename T> using set_tr = std::set<T, std::less<>>;
template<typename T> using multiset_tr = std::set<T, std::less<>>;
template<typename T> using map_unsigned = std::map<T, unsigned, std::less<>>;
template<typename T> using map_size = std::map<T, size_t, std::less<>>;
template<typename T> using unordered_map_unsigned = std::unordered_map<T, unsigned>;
template<typename T> using unordered_map_size = std::unordered_map<T, size_t>;
} // namespace

#define TYPEDEFS_1(abbrev, type) \
	template<size_t N1> using a ## abbrev = std::array<abbrev, N1>; \
	using d ## abbrev = std::deque<abbrev>; \
	using fl ## abbrev = std::forward_list<abbrev>; \
	using l ## abbrev = std::list<abbrev>; \
	/* using ms ## abbrev = multiset_tr<abbrev>; */ \
	/* using mu ## abbrev = map_unsigned<abbrev>; */ \
	/* using mz ## abbrev = map_size<abbrev>; */ \
	/* using o ## abbrev = std::optional<abbrev>; */ \
	using s ## abbrev = set_tr<abbrev>; \
	using us ## abbrev = std::unordered_set<abbrev>; \
	/* using ums ## abbrev = std::unordered_multiset<abbrev>; */ \
	/* using umu ## abbrev = unordered_map_unsigned<abbrev>; */ \
	/* using umz ## abbrev = unordered_map_size<abbrev>; */ \
	using v ## abbrev = std::vector<abbrev>;
#define TYPEDEFS_2(abbrev, type) \
	template<size_t N1, size_t N2> using aa ## abbrev = std::array<a ## abbrev<N2>, N1>; \
	TYPEDEFS_1(d ## abbrev, std::deque<abbrev>) \
	TYPEDEFS_1(fl ## abbrev, std::forward_list<abbrev>) \
	TYPEDEFS_1(l ## abbrev, std::list<abbrev>) \
	/* TYPEDEFS_1(ms ## abbrev, multiset_tr<abbrev>) */ \
	/* TYPEDEFS_1(mu ## abbrev, map_unsigned<abbrev>) */ \
	/* TYPEDEFS_1(mz ## abbrev, map_size<abbrev>) */ \
	/* TYPEDEFS_1(o ## abbrev, std::optional<abbrev>) */ \
	TYPEDEFS_1(s ## abbrev, set_tr<abbrev>) \
	TYPEDEFS_1(us ## abbrev, std::unordered_set<abbrev>) \
	/* TYPEDEFS_1(ums ## abbrev, std::unordered_multiset<abbrev>) */ \
	/* TYPEDEFS_1(umu ## abbrev, unordered_map_unsigned<abbrev>) */ \
	/* TYPEDEFS_1(umz ## abbrev, unordered_map_size<abbrev>) */ \
	TYPEDEFS_1(v ## abbrev, std::vector<abbrev>);
#define TYPEDEFS_3(abbrev, type) \
	template<size_t N1, size_t N2, size_t N3> using aaa ## abbrev = std::array<aa ## abbrev<N2, N3>, N1>; \
	TYPEDEFS_2(d ## abbrev, std::deque<abbrev>) \
	TYPEDEFS_2(fl ## abbrev, std::forward_list<abbrev>) \
	TYPEDEFS_2(l ## abbrev, std::list<abbrev>) \
	/* TYPEDEFS_2(ms ## abbrev, multiset_tr<abbrev>) */ \
	/* TYPEDEFS_2(mu ## abbrev, map_unsigned<abbrev>) */ \
	/* TYPEDEFS_2(mz ## abbrev, map_size<abbrev>) */ \
	/* TYPEDEFS_2(o ## abbrev, std::optional<abbrev>) */ \
	TYPEDEFS_2(s ## abbrev, set_tr<abbrev>) \
	TYPEDEFS_2(us ## abbrev, std::unordered_set<abbrev>) \
	/* TYPEDEFS_2(ums ## abbrev, std::unordered_multiset<abbrev>) */ \
	/* TYPEDEFS_2(umu ## abbrev, unordered_map_unsigned<abbrev>) */ \
	/* TYPEDEFS_2(umz ## abbrev, unordered_map_size<abbrev>) */ \
	TYPEDEFS_2(v ## abbrev, std::vector<abbrev>);
// #define TYPEDEFS_4(abbrev, type) \
// 	template<size_t N1, size_t N2, size_t N3, size_t N4> using aaaa ## abbrev = std::array<aaa ## abbrev<N2, N3, N4>, N1>; \
// 	TYPEDEFS_3(d ## abbrev, std::deque<abbrev>) \
// 	TYPEDEFS_3(fl ## abbrev, std::forward_list<abbrev>) \
// 	TYPEDEFS_3(l ## abbrev, std::list<abbrev>) \
// 	/* TYPEDEFS_3(ms ## abbrev, multiset_tr<abbrev>) */ \
// 	/* TYPEDEFS_3(mu ## abbrev, map_unsigned<abbrev>) */ \
// 	/* TYPEDEFS_3(mz ## abbrev, map_size<abbrev>) */ \
// 	/* TYPEDEFS_3(o ## abbrev, std::optional<abbrev>) */ \
// 	TYPEDEFS_3(s ## abbrev, set_tr<abbrev>) \
// 	TYPEDEFS_3(us ## abbrev, std::unordered_set<abbrev>) \
// 	/* TYPEDEFS_3(ums ## abbrev, std::unordered_multiset<abbrev>) */ \
// 	/* TYPEDEFS_3(umu ## abbrev, unordered_map_unsigned<abbrev>) */ \
// 	/* TYPEDEFS_3(umz ## abbrev, unordered_map_size<abbrev>) */ \
// 	TYPEDEFS_3(v ## abbrev, std::vector<abbrev>);
#define TYPEDEFS(abbrev, type) \
	using abbrev = type; \
	TYPEDEFS_1(abbrev, type) \
	TYPEDEFS_2(abbrev, type) \
	TYPEDEFS_3(abbrev, type) \
	/* TYPEDEFS_4(abbrev, type) */ \
	using p ## abbrev = std::pair<abbrev, abbrev>; \
	TYPEDEFS_1(p ## abbrev, type) \
	TYPEDEFS_2(p ## abbrev, type) \
	TYPEDEFS_3(p ## abbrev, type) \
	/* TYPEDEFS_4(p ## abbrev, type) */ \

namespace
{
namespace abbrev
{
inline namespace basic
{
TYPEDEFS(b, bool)
TYPEDEFS(c, char)
TYPEDEFS(uc, unsigned char)
TYPEDEFS(i8, int8_t)
TYPEDEFS(u8, uint8_t)
TYPEDEFS(i16, int16_t)
TYPEDEFS(u16, uint16_t)
TYPEDEFS(i32, int32_t)
TYPEDEFS(u32, uint32_t)
TYPEDEFS(i64, int64_t)
TYPEDEFS(u64, uint64_t)
TYPEDEFS(i128, __int128_t)
TYPEDEFS(u128, __uint128_t)
TYPEDEFS(iz, ptrdiff_t)
TYPEDEFS(uz, size_t)
TYPEDEFS(f32, float)
TYPEDEFS(f64, double)
TYPEDEFS(f80, long double)
TYPEDEFS(str, std::string)

template<size_t N> using bs = std::bitset<N>;
template<size_t N> using vbs = std::vector<bs<N>>;
template<size_t N> using vvbs = std::vector<vbs<N>>;
} // inline namespace basic
} // namespace abbrev
} // namespace

#endif // EMBAILEY_TEMPLATE_ABBREV_H

