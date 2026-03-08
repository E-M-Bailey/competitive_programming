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

#ifndef EMBAILEY_TEMPLATE_ABBREV_H
#define EMBAILEY_TEMPLATE_ABBREV_H

#ifndef EMBAILEY_TEMPLATE_BASIC_H
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

#ifndef EMBAILEY_TEMPLATE_RANDOM_H
#define EMBAILEY_TEMPLATE_RANDOM_H

#ifndef EMBAILEY_TEMPLATE_CONCEPTS_H
#define EMBAILEY_TEMPLATE_CONCEPTS_H


namespace
{

template<typename T>
concept copy_assignable = std::is_copy_assignable_v<T>;
template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template<typename T>
struct is_ratio : public std::false_type {};
template<intmax_t N, intmax_t D>
struct is_ratio<std::ratio<N, D>> : public std::true_type {};
template<typename T>
static constexpr bool is_ratio_v = is_ratio<T>::value;
template<typename T>
concept ratio_type = is_ratio_v<T>;

// https://en.cppreference.com/w/cpp/named_req/RandomNumberDistribution.html (some requirements are not checkable)
template<typename D>
concept random_integer_distribution = std::copy_constructible<D> && copy_assignable<D> &&
		std::integral<typename D::result_type> && std::copy_constructible<typename D::param_type> &&
		copy_assignable<typename D::param_type> && std::equality_comparable<typename D::param_type> &&
		std::same_as<typename D::param_type::distribution_type, D>; // TODO more
template<typename D>
concept random_real_distribution = std::copy_constructible<D> && copy_assignable<D> &&
		std::integral<typename D::result_type> && std::copy_constructible<typename D::param_type> &&
		copy_assignable<typename D::param_type> && std::equality_comparable<typename D::param_type> &&
		std::same_as<typename D::param_type::distribution_type, D>; // TODO more
template<typename D>
concept random_number_distribution = random_integer_distribution<D> || random_real_distribution<D>;

} // namespace

#endif // EMBAILEY_TEMPLATE_CONCEPTS_H


namespace
{

constexpr uint64_t random_seed = [](const std::string_view str) -> uint64_t
{
	constexpr uint64_t P = 18446744073709551557u, A = 257;
	uint64_t seed = 0;
	for (char c : str)
		seed = static_cast<uint64_t>((static_cast<__uint128_t>(A) * seed + static_cast<unsigned char>(c)) % P);
	return seed;
}("[" __TIME__ ";" __DATE__ "@" __TIMESTAMP__ "]{" __FILE__ ":" xstringify(__LINE__) "}(" __VERSION__ ")");

template<std::uniform_random_bit_generator R = std::mt19937_64>
R randy{ static_cast<R::result_type>(random_seed) };

template<arithmetic T>
constexpr T default_uniform_lo = std::integral<T> ? std::numeric_limits<T>::min() : static_cast<T>(0);
template<arithmetic T>
constexpr T default_uniform_hi = std::integral<T> ? std::numeric_limits<T>::max() : static_cast<T>(1);
template<arithmetic T>
using uniform_distribution = std::conditional_t<std::integral<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>;
template<arithmetic T, T L = default_uniform_lo<T>, T H = default_uniform_hi<T>>
uniform_distribution<T> uniform{ L, H };

template<arithmetic T, T L = default_uniform_lo<T>, T H = default_uniform_hi<T>, std::uniform_random_bit_generator R = std::mt19937_64>
[[nodiscard]] inline T get_uniform() noexcept { return uniform<T, L, H>(randy<R>); }
template<arithmetic T, std::uniform_random_bit_generator R = std::mt19937_64>
[[nodiscard]] inline T get_uniform(T lo, T hi) noexcept { return uniform_distribution<T>{ lo, hi }(randy<R>); }

namespace abbrev
{
inline namespace random
{
constexpr uint64_t const &seed = random_seed;
template<arithmetic T>
constexpr T const &unif_lo = default_uniform_lo<T>;
template<arithmetic T>
constexpr T const &unif_hi = default_uniform_hi<T>;
template<arithmetic T>
using unif_distr = uniform_distribution<T>;
template<arithmetic T, T L = default_uniform_lo<T>, T H = default_uniform_hi<T>, std::uniform_random_bit_generator R = std::mt19937_64>
[[nodiscard]] inline T unif() noexcept { return get_uniform<T, L, H, R>(); }
template<arithmetic T, std::uniform_random_bit_generator R = std::mt19937_64>
[[nodiscard]] ainline inline T unif(T lo, T hi) noexcept { return get_uniform<T, R>(lo, hi); }

} // inline namespace random
} // namespace abbrev
} // namespace

#endif // EMBAILEY_TEMPLATE_RANDOM_H

