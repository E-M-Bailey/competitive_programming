#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#ifndef DEBUG
#define assert(x) do {} while (false)
#endif // DEBUG

using namespace std;
using namespace chrono;

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

using bl=bool;
using c8=char;
using uc8=unsigned char;
using i8=int8_t;
using i16=int16_t;
using i32=int32_t;
using i64=int64_t;
using i128=__int128;
using u8=uint8_t;
using u16=uint16_t;
using u32=uint32_t;
using u64=uint64_t;
using u128=unsigned __int128;
using f32=float;
using f64=double;
using fld=long double;
using f128=__float128;
using str8=string;
using pbl=pair<bl, bl>;
using pc8=pair<c8, c8>;
using puc8=pair<uc8, uc8>;
using pi8=pair<i8, i8>;
using pi16=pair<i16, i16>;
using pi32=pair<i32, i32>;
using pi64=pair<i64, i64>;
using pi128=pair<i128, i128>;
using pu8=pair<u8, u8>;
using pu16=pair<u16, u16>;
using pu32=pair<u32, u32>;
using pu64=pair<u64, u64>;
using pu128=pair<u128, u128>;
using pf32=pair<f32, f32>;
using pf64=pair<f64, f64>;
using pfld=pair<fld, fld>;
using pf128=pair<f128, f128>;
using pstr8=pair<str8, str8>;
using a2bl=array<bl, 2>;
using a2c8=array<c8, 2>;
using a2uc8=array<uc8, 2>;
using a2i8=array<i8, 2>;
using a2i16=array<i16, 2>;
using a2i32=array<i32, 2>;
using a2i64=array<i64, 2>;
using a2i128=array<i128, 2>;
using a2u8=array<u8, 2>;
using a2u16=array<u16, 2>;
using a2u32=array<u32, 2>;
using a2u64=array<u64, 2>;
using a2u128=array<u128, 2>;
using a2f32=array<f32, 2>;
using a2f64=array<f64, 2>;
using a2fld=array<fld, 2>;
using a2f128=array<f128, 2>;
using a2str8=array<str8, 2>;

using vbl=vector<bl>;
using vc8=vector<c8>;
using vuc8=vector<uc8>;
using vi8=vector<i8>;
using vi16=vector<i16>;
using vi32=vector<i32>;
using vi64=vector<i64>;
using vi128=vector<i128>;
using vu8=vector<u8>;
using vu16=vector<u16>;
using vu32=vector<u32>;
using vu64=vector<u64>;
using vu128=vector<u128>;
using vf32=vector<f32>;
using vf64=vector<f64>;
using vfld=vector<fld>;
using vf128=vector<f128>;
using vstr8=vector<str8>;
using vpbl=vector<pbl>;
using vpc8=vector<pc8>;
using vpuc8=vector<puc8>;
using vpi8=vector<pi8>;
using vpi16=vector<pi16>;
using vpi32=vector<pi32>;
using vpi64=vector<pi64>;
using vpi128=vector<pi128>;
using vpu8=vector<pu8>;
using vpu16=vector<pu16>;
using vpu32=vector<pu32>;
using vpu64=vector<pu64>;
using vpu128=vector<pu128>;
using vpf32=vector<pf32>;
using vpf64=vector<pf64>;
using vpfld=vector<pfld>;
using vpf128=vector<pf128>;
using vpstr8=vector<pstr8>;
using va2bl=vector<a2bl>;
using va2c8=vector<a2c8>;
using va2uc8=vector<a2uc8>;
using va2i8=vector<a2i8>;
using va2i16=vector<a2i16>;
using va2i32=vector<a2i32>;
using va2i64=vector<a2i64>;
using va2i128=vector<a2i128>;
using va2u8=vector<a2u8>;
using va2u16=vector<a2u16>;
using va2u32=vector<a2u32>;
using va2u64=vector<a2u64>;
using va2u128=vector<a2u128>;
using va2f32=vector<a2f32>;
using va2f64=vector<a2f64>;
using va2fld=vector<a2fld>;
using va2f128=vector<a2f128>;
using va2str8=vector<a2str8>;

using vvbl=vector<vbl>;
using vvc8=vector<vc8>;
using vvuc8=vector<vuc8>;
using vvi8=vector<vi8>;
using vvi16=vector<vi16>;
using vvi32=vector<vi32>;
using vvi64=vector<vi64>;
using vvi128=vector<vi128>;
using vvu8=vector<vu8>;
using vvu16=vector<vu16>;
using vvu32=vector<vu32>;
using vvu64=vector<vu64>;
using vvu128=vector<vu128>;
using vvf32=vector<vf32>;
using vvf64=vector<vf64>;
using vvfld=vector<vfld>;
using vvf128=vector<vf128>;
using vvstr8=vector<vstr8>;
using vvpbl=vector<vpbl>;
using vvpc8=vector<vpc8>;
using vvpuc8=vector<vpuc8>;
using vvpi8=vector<vpi8>;
using vvpi16=vector<vpi16>;
using vvpi32=vector<vpi32>;
using vvpi64=vector<vpi64>;
using vvpi128=vector<vpi128>;
using vvpu8=vector<vpu8>;
using vvpu16=vector<vpu16>;
using vvpu32=vector<vpu32>;
using vvpu64=vector<vpu64>;
using vvpu128=vector<vpu128>;
using vvpf32=vector<vpf32>;
using vvpf64=vector<vpf64>;
using vvpfld=vector<vpfld>;
using vvpf128=vector<vpf128>;
using vvpstr8=vector<vpstr8>;
using vva2bl=vector<va2bl>;
using vva2c8=vector<va2c8>;
using vva2uc8=vector<va2uc8>;
using vva2i8=vector<va2i8>;
using vva2i16=vector<va2i16>;
using vva2i32=vector<va2i32>;
using vva2i64=vector<va2i64>;
using vva2i128=vector<va2i128>;
using vva2u8=vector<va2u8>;
using vva2u16=vector<va2u16>;
using vva2u32=vector<va2u32>;
using vva2u64=vector<va2u64>;
using vva2u128=vector<va2u128>;
using vva2f32=vector<va2f32>;
using vva2f64=vector<va2f64>;
using vva2fld=vector<va2fld>;
using vva2f128=vector<va2f128>;
using vva2str8=vector<va2str8>;

using vvvbl=vector<vvbl>;
using vvvc8=vector<vvc8>;
using vvvuc8=vector<vvuc8>;
using vvvi8=vector<vvi8>;
using vvvi16=vector<vvi16>;
using vvvi32=vector<vvi32>;
using vvvi64=vector<vvi64>;
using vvvi128=vector<vvi128>;
using vvvu8=vector<vvu8>;
using vvvu16=vector<vvu16>;
using vvvu32=vector<vvu32>;
using vvvu64=vector<vvu64>;
using vvvu128=vector<vvu128>;
using vvvf32=vector<vvf32>;
using vvvf64=vector<vvf64>;
using vvvfld=vector<vvfld>;
using vvvf128=vector<vvf128>;
using vvvstr8=vector<vvstr8>;
using vvvpbl=vector<vvpbl>;
using vvvpc8=vector<vvpc8>;
using vvvpuc8=vector<vvpuc8>;
using vvvpi8=vector<vvpi8>;
using vvvpi16=vector<vvpi16>;
using vvvpi32=vector<vvpi32>;
using vvvpi64=vector<vvpi64>;
using vvvpi128=vector<vvpi128>;
using vvvpu8=vector<vvpu8>;
using vvvpu16=vector<vvpu16>;
using vvvpu32=vector<vvpu32>;
using vvvpu64=vector<vvpu64>;
using vvvpu128=vector<vvpu128>;
using vvvpf32=vector<vvpf32>;
using vvvpf64=vector<vvpf64>;
using vvvpfld=vector<vvpfld>;
using vvvpf128=vector<vvpf128>;
using vvvpstr8=vector<vvpstr8>;
using vvva2bl=vector<vva2bl>;
using vvva2c8=vector<vva2c8>;
using vvva2uc8=vector<vva2uc8>;
using vvva2i8=vector<vva2i8>;
using vvva2i16=vector<vva2i16>;
using vvva2i32=vector<vva2i32>;
using vvva2i64=vector<vva2i64>;
using vvva2i128=vector<vva2i128>;
using vvva2u8=vector<vva2u8>;
using vvva2u16=vector<vva2u16>;
using vvva2u32=vector<vva2u32>;
using vvva2u64=vector<vva2u64>;
using vvva2u128=vector<vva2u128>;
using vvva2f32=vector<vva2f32>;
using vvva2f64=vector<vva2f64>;
using vvva2fld=vector<vva2fld>;
using vvva2f128=vector<vva2f128>;
using vvva2str8=vector<vva2str8>;

using vvvvbl=vector<vvvbl>;
using vvvvc8=vector<vvvc8>;
using vvvvuc8=vector<vvvuc8>;
using vvvvi8=vector<vvvi8>;
using vvvvi16=vector<vvvi16>;
using vvvvi32=vector<vvvi32>;
using vvvvi64=vector<vvvi64>;
using vvvvi128=vector<vvvi128>;
using vvvvu8=vector<vvvu8>;
using vvvvu16=vector<vvvu16>;
using vvvvu32=vector<vvvu32>;
using vvvvu64=vector<vvvu64>;
using vvvvu128=vector<vvvu128>;
using vvvvf32=vector<vvvf32>;
using vvvvf64=vector<vvvf64>;
using vvvvfld=vector<vvvfld>;
using vvvvf128=vector<vvvf128>;
using vvvvstr8=vector<vvvstr8>;
using vvvvpbl=vector<vvvpbl>;
using vvvvpc8=vector<vvvpc8>;
using vvvvpuc8=vector<vvvpuc8>;
using vvvvpi8=vector<vvvpi8>;
using vvvvpi16=vector<vvvpi16>;
using vvvvpi32=vector<vvvpi32>;
using vvvvpi64=vector<vvvpi64>;
using vvvvpi128=vector<vvvpi128>;
using vvvvpu8=vector<vvvpu8>;
using vvvvpu16=vector<vvvpu16>;
using vvvvpu32=vector<vvvpu32>;
using vvvvpu64=vector<vvvpu64>;
using vvvvpu128=vector<vvvpu128>;
using vvvvpf32=vector<vvvpf32>;
using vvvvpf64=vector<vvvpf64>;
using vvvvpfld=vector<vvvpfld>;
using vvvvpf128=vector<vvvpf128>;
using vvvvpstr8=vector<vvvpstr8>;
using vvvva2bl=vector<vvva2bl>;
using vvvva2c8=vector<vvva2c8>;
using vvvva2uc8=vector<vvva2uc8>;
using vvvva2i8=vector<vvva2i8>;
using vvvva2i16=vector<vvva2i16>;
using vvvva2i32=vector<vvva2i32>;
using vvvva2i64=vector<vvva2i64>;
using vvvva2i128=vector<vvva2i128>;
using vvvva2u8=vector<vvva2u8>;
using vvvva2u16=vector<vvva2u16>;
using vvvva2u32=vector<vvva2u32>;
using vvvva2u64=vector<vvva2u64>;
using vvvva2u128=vector<vvva2u128>;
using vvvva2f32=vector<vvva2f32>;
using vvvva2f64=vector<vvva2f64>;
using vvvva2fld=vector<vvva2fld>;
using vvvva2f128=vector<vvva2f128>;
using vvvva2str8=vector<vvva2str8>;

using lbl=list<bl>;
using lc8=list<c8>;
using luc8=list<uc8>;
using li8=list<i8>;
using li16=list<i16>;
using li32=list<i32>;
using li64=list<i64>;
using li128=list<i128>;
using lu8=list<u8>;
using lu16=list<u16>;
using lu32=list<u32>;
using lu64=list<u64>;
using lu128=list<u128>;
using lf32=list<f32>;
using lf64=list<f64>;
using lfld=list<fld>;
using lf128=list<f128>;
using lstr8=list<str8>;
using lpbl=list<pbl>;
using lpc8=list<pc8>;
using lpuc8=list<puc8>;
using lpi8=list<pi8>;
using lpi16=list<pi16>;
using lpi32=list<pi32>;
using lpi64=list<pi64>;
using lpi128=list<pi128>;
using lpu8=list<pu8>;
using lpu16=list<pu16>;
using lpu32=list<pu32>;
using lpu64=list<pu64>;
using lpu128=list<pu128>;
using lpf32=list<pf32>;
using lpf64=list<pf64>;
using lpfld=list<pfld>;
using lpf128=list<pf128>;
using lpstr8=list<pstr8>;
using la2bl=list<a2bl>;
using la2c8=list<a2c8>;
using la2uc8=list<a2uc8>;
using la2i8=list<a2i8>;
using la2i16=list<a2i16>;
using la2i32=list<a2i32>;
using la2i64=list<a2i64>;
using la2i128=list<a2i128>;
using la2u8=list<a2u8>;
using la2u16=list<a2u16>;
using la2u32=list<a2u32>;
using la2u64=list<a2u64>;
using la2u128=list<a2u128>;
using la2f32=list<a2f32>;
using la2f64=list<a2f64>;
using la2fld=list<a2fld>;
using la2f128=list<a2f128>;
using la2str8=list<a2str8>;

using vlbl=vector<lbl>;
using vlc8=vector<lc8>;
using vluc8=vector<luc8>;
using vli8=vector<li8>;
using vli16=vector<li16>;
using vli32=vector<li32>;
using vli64=vector<li64>;
using vli128=vector<li128>;
using vlu8=vector<lu8>;
using vlu16=vector<lu16>;
using vlu32=vector<lu32>;
using vlu64=vector<lu64>;
using vlu128=vector<lu128>;
using vlf32=vector<lf32>;
using vlf64=vector<lf64>;
using vlfld=vector<lfld>;
using vlf128=vector<lf128>;
using vlstr8=vector<lstr8>;
using vlpbl=vector<lpbl>;
using vlpc8=vector<lpc8>;
using vlpuc8=vector<lpuc8>;
using vlpi8=vector<lpi8>;
using vlpi16=vector<lpi16>;
using vlpi32=vector<lpi32>;
using vlpi64=vector<lpi64>;
using vlpi128=vector<lpi128>;
using vlpu8=vector<lpu8>;
using vlpu16=vector<lpu16>;
using vlpu32=vector<lpu32>;
using vlpu64=vector<lpu64>;
using vlpu128=vector<lpu128>;
using vlpf32=vector<lpf32>;
using vlpf64=vector<lpf64>;
using vlpfld=vector<lpfld>;
using vlpf128=vector<lpf128>;
using vlpstr8=vector<lpstr8>;
using vla2bl=vector<la2bl>;
using vla2c8=vector<la2c8>;
using vla2uc8=vector<la2uc8>;
using vla2i8=vector<la2i8>;
using vla2i16=vector<la2i16>;
using vla2i32=vector<la2i32>;
using vla2i64=vector<la2i64>;
using vla2i128=vector<la2i128>;
using vla2u8=vector<la2u8>;
using vla2u16=vector<la2u16>;
using vla2u32=vector<la2u32>;
using vla2u64=vector<la2u64>;
using vla2u128=vector<la2u128>;
using vla2f32=vector<la2f32>;
using vla2f64=vector<la2f64>;
using vla2fld=vector<la2fld>;
using vla2f128=vector<la2f128>;
using vla2str8=vector<la2str8>;

using sbl=set<bl>;
using sc8=set<c8>;
using suc8=set<uc8>;
using si8=set<i8>;
using si16=set<i16>;
using si32=set<i32>;
using si64=set<i64>;
using si128=set<i128>;
using su8=set<u8>;
using su16=set<u16>;
using su32=set<u32>;
using su64=set<u64>;
using su128=set<u128>;
using sf32=set<f32>;
using sf64=set<f64>;
using sfld=set<fld>;
using sf128=set<f128>;
using sstr8=set<str8>;
using spbl=set<pbl>;
using spc8=set<pc8>;
using spuc8=set<puc8>;
using spi8=set<pi8>;
using spi16=set<pi16>;
using spi32=set<pi32>;
using spi64=set<pi64>;
using spi128=set<pi128>;
using spu8=set<pu8>;
using spu16=set<pu16>;
using spu32=set<pu32>;
using spu64=set<pu64>;
using spu128=set<pu128>;
using spf32=set<pf32>;
using spf64=set<pf64>;
using spfld=set<pfld>;
using spf128=set<pf128>;
using spstr8=set<pstr8>;
using sa2bl=set<a2bl>;
using sa2c8=set<a2c8>;
using sa2uc8=set<a2uc8>;
using sa2i8=set<a2i8>;
using sa2i16=set<a2i16>;
using sa2i32=set<a2i32>;
using sa2i64=set<a2i64>;
using sa2i128=set<a2i128>;
using sa2u8=set<a2u8>;
using sa2u16=set<a2u16>;
using sa2u32=set<a2u32>;
using sa2u64=set<a2u64>;
using sa2u128=set<a2u128>;
using sa2f32=set<a2f32>;
using sa2f64=set<a2f64>;
using sa2fld=set<a2fld>;
using sa2f128=set<a2f128>;
using sa2str8=set<a2str8>;

using vsbl=vector<sbl>;
using vsc8=vector<sc8>;
using vsuc8=vector<suc8>;
using vsi8=vector<si8>;
using vsi16=vector<si16>;
using vsi32=vector<si32>;
using vsi64=vector<si64>;
using vsi128=vector<si128>;
using vsu8=vector<su8>;
using vsu16=vector<su16>;
using vsu32=vector<su32>;
using vsu64=vector<su64>;
using vsu128=vector<su128>;
using vsf32=vector<sf32>;
using vsf64=vector<sf64>;
using vsfld=vector<sfld>;
using vsf128=vector<sf128>;
using vsstr8=vector<sstr8>;
using vspbl=vector<spbl>;
using vspc8=vector<spc8>;
using vspuc8=vector<spuc8>;
using vspi8=vector<spi8>;
using vspi16=vector<spi16>;
using vspi32=vector<spi32>;
using vspi64=vector<spi64>;
using vspi128=vector<spi128>;
using vspu8=vector<spu8>;
using vspu16=vector<spu16>;
using vspu32=vector<spu32>;
using vspu64=vector<spu64>;
using vspu128=vector<spu128>;
using vspf32=vector<spf32>;
using vspf64=vector<spf64>;
using vspfld=vector<spfld>;
using vspf128=vector<spf128>;
using vspstr8=vector<spstr8>;
using vsa2bl=vector<sa2bl>;
using vsa2c8=vector<sa2c8>;
using vsa2uc8=vector<sa2uc8>;
using vsa2i8=vector<sa2i8>;
using vsa2i16=vector<sa2i16>;
using vsa2i32=vector<sa2i32>;
using vsa2i64=vector<sa2i64>;
using vsa2i128=vector<sa2i128>;
using vsa2u8=vector<sa2u8>;
using vsa2u16=vector<sa2u16>;
using vsa2u32=vector<sa2u32>;
using vsa2u64=vector<sa2u64>;
using vsa2u128=vector<sa2u128>;
using vsa2f32=vector<sa2f32>;
using vsa2f64=vector<sa2f64>;
using vsa2fld=vector<sa2fld>;
using vsa2f128=vector<sa2f128>;
using vsa2str8=vector<sa2str8>;

template<class Pr> using Sbl=set<bl, Pr>;
template<class Pr> using Sc8=set<c8, Pr>;
template<class Pr> using Suc8=set<uc8, Pr>;
template<class Pr> using Si8=set<i8, Pr>;
template<class Pr> using Si16=set<i16, Pr>;
template<class Pr> using Si32=set<i32, Pr>;
template<class Pr> using Si64=set<i64, Pr>;
template<class Pr> using Si128=set<i128, Pr>;
template<class Pr> using Su8=set<u8, Pr>;
template<class Pr> using Su16=set<u16, Pr>;
template<class Pr> using Su32=set<u32, Pr>;
template<class Pr> using Su64=set<u64, Pr>;
template<class Pr> using Su128=set<u128, Pr>;
template<class Pr> using Sf32=set<f32, Pr>;
template<class Pr> using Sf64=set<f64, Pr>;
template<class Pr> using Sfld=set<fld, Pr>;
template<class Pr> using Sf128=set<f128, Pr>;
template<class Pr> using Sstr8=set<str8, Pr>;
template<class Pr> using Spbl=set<pbl, Pr>;
template<class Pr> using Spc8=set<pc8, Pr>;
template<class Pr> using Spuc8=set<puc8, Pr>;
template<class Pr> using Spi8=set<pi8, Pr>;
template<class Pr> using Spi16=set<pi16, Pr>;
template<class Pr> using Spi32=set<pi32, Pr>;
template<class Pr> using Spi64=set<pi64, Pr>;
template<class Pr> using Spi128=set<pi128, Pr>;
template<class Pr> using Spu8=set<pu8, Pr>;
template<class Pr> using Spu16=set<pu16, Pr>;
template<class Pr> using Spu32=set<pu32, Pr>;
template<class Pr> using Spu64=set<pu64, Pr>;
template<class Pr> using Spu128=set<pu128, Pr>;
template<class Pr> using Spf32=set<pf32, Pr>;
template<class Pr> using Spf64=set<pf64, Pr>;
template<class Pr> using Spfld=set<pfld, Pr>;
template<class Pr> using Spf128=set<pf128, Pr>;
template<class Pr> using Spstr8=set<pstr8, Pr>;
template<class Pr> using Sa2bl=set<a2bl, Pr>;
template<class Pr> using Sa2c8=set<a2c8, Pr>;
template<class Pr> using Sa2uc8=set<a2uc8, Pr>;
template<class Pr> using Sa2i8=set<a2i8, Pr>;
template<class Pr> using Sa2i16=set<a2i16, Pr>;
template<class Pr> using Sa2i32=set<a2i32, Pr>;
template<class Pr> using Sa2i64=set<a2i64, Pr>;
template<class Pr> using Sa2i128=set<a2i128, Pr>;
template<class Pr> using Sa2u8=set<a2u8, Pr>;
template<class Pr> using Sa2u16=set<a2u16, Pr>;
template<class Pr> using Sa2u32=set<a2u32, Pr>;
template<class Pr> using Sa2u64=set<a2u64, Pr>;
template<class Pr> using Sa2u128=set<a2u128, Pr>;
template<class Pr> using Sa2f32=set<a2f32, Pr>;
template<class Pr> using Sa2f64=set<a2f64, Pr>;
template<class Pr> using Sa2fld=set<a2fld, Pr>;
template<class Pr> using Sa2f128=set<a2f128, Pr>;
template<class Pr> using Sa2str8=set<a2str8, Pr>;

template<class Pr> using vSbl=vector<Sbl<Pr>>;
template<class Pr> using vSc8=vector<Sc8<Pr>>;
template<class Pr> using vSuc8=vector<Suc8<Pr>>;
template<class Pr> using vSi8=vector<Si8<Pr>>;
template<class Pr> using vSi16=vector<Si16<Pr>>;
template<class Pr> using vSi32=vector<Si32<Pr>>;
template<class Pr> using vSi64=vector<Si64<Pr>>;
template<class Pr> using vSi128=vector<Si128<Pr>>;
template<class Pr> using vSu8=vector<Su8<Pr>>;
template<class Pr> using vSu16=vector<Su16<Pr>>;
template<class Pr> using vSu32=vector<Su32<Pr>>;
template<class Pr> using vSu64=vector<Su64<Pr>>;
template<class Pr> using vSu128=vector<Su128<Pr>>;
template<class Pr> using vSf32=vector<Sf32<Pr>>;
template<class Pr> using vSf64=vector<Sf64<Pr>>;
template<class Pr> using vSfld=vector<Sfld<Pr>>;
template<class Pr> using vSf128=vector<Sf128<Pr>>;
template<class Pr> using vSstr8=vector<Sstr8<Pr>>;
template<class Pr> using vSpbl=vector<Spbl<Pr>>;
template<class Pr> using vSpc8=vector<Spc8<Pr>>;
template<class Pr> using vSpuc8=vector<Spuc8<Pr>>;
template<class Pr> using vSpi8=vector<Spi8<Pr>>;
template<class Pr> using vSpi16=vector<Spi16<Pr>>;
template<class Pr> using vSpi32=vector<Spi32<Pr>>;
template<class Pr> using vSpi64=vector<Spi64<Pr>>;
template<class Pr> using vSpi128=vector<Spi128<Pr>>;
template<class Pr> using vSpu8=vector<Spu8<Pr>>;
template<class Pr> using vSpu16=vector<Spu16<Pr>>;
template<class Pr> using vSpu32=vector<Spu32<Pr>>;
template<class Pr> using vSpu64=vector<Spu64<Pr>>;
template<class Pr> using vSpu128=vector<Spu128<Pr>>;
template<class Pr> using vSpf32=vector<Spf32<Pr>>;
template<class Pr> using vSpf64=vector<Spf64<Pr>>;
template<class Pr> using vSpfld=vector<Spfld<Pr>>;
template<class Pr> using vSpf128=vector<Spf128<Pr>>;
template<class Pr> using vSpstr8=vector<Spstr8<Pr>>;
template<class Pr> using vSa2bl=vector<Sa2bl<Pr>>;
template<class Pr> using vSa2c8=vector<Sa2c8<Pr>>;
template<class Pr> using vSa2uc8=vector<Sa2uc8<Pr>>;
template<class Pr> using vSa2i8=vector<Sa2i8<Pr>>;
template<class Pr> using vSa2i16=vector<Sa2i16<Pr>>;
template<class Pr> using vSa2i32=vector<Sa2i32<Pr>>;
template<class Pr> using vSa2i64=vector<Sa2i64<Pr>>;
template<class Pr> using vSa2i128=vector<Sa2i128<Pr>>;
template<class Pr> using vSa2u8=vector<Sa2u8<Pr>>;
template<class Pr> using vSa2u16=vector<Sa2u16<Pr>>;
template<class Pr> using vSa2u32=vector<Sa2u32<Pr>>;
template<class Pr> using vSa2u64=vector<Sa2u64<Pr>>;
template<class Pr> using vSa2u128=vector<Sa2u128<Pr>>;
template<class Pr> using vSa2f32=vector<Sa2f32<Pr>>;
template<class Pr> using vSa2f64=vector<Sa2f64<Pr>>;
template<class Pr> using vSa2fld=vector<Sa2fld<Pr>>;
template<class Pr> using vSa2f128=vector<Sa2f128<Pr>>;
template<class Pr> using vSa2str8=vector<Sa2str8<Pr>>;

using usbl=unordered_set<bl>;
using usc8=unordered_set<c8>;
using usuc8=unordered_set<uc8>;
using usi8=unordered_set<i8>;
using usi16=unordered_set<i16>;
using usi32=unordered_set<i32>;
using usi64=unordered_set<i64>;
using usi128=unordered_set<i128>;
using usu8=unordered_set<u8>;
using usu16=unordered_set<u16>;
using usu32=unordered_set<u32>;
using usu64=unordered_set<u64>;
using usu128=unordered_set<u128>;
using usf32=unordered_set<f32>;
using usf64=unordered_set<f64>;
using usfld=unordered_set<fld>;
using usf128=unordered_set<f128>;
using usstr8=unordered_set<str8>;
using uspbl=unordered_set<pbl>;
using uspc8=unordered_set<pc8>;
using uspuc8=unordered_set<puc8>;
using uspi8=unordered_set<pi8>;
using uspi16=unordered_set<pi16>;
using uspi32=unordered_set<pi32>;
using uspi64=unordered_set<pi64>;
using uspi128=unordered_set<pi128>;
using uspu8=unordered_set<pu8>;
using uspu16=unordered_set<pu16>;
using uspu32=unordered_set<pu32>;
using uspu64=unordered_set<pu64>;
using uspu128=unordered_set<pu128>;
using uspf32=unordered_set<pf32>;
using uspf64=unordered_set<pf64>;
using uspfld=unordered_set<pfld>;
using uspf128=unordered_set<pf128>;
using uspstr8=unordered_set<pstr8>;
using usa2bl=unordered_set<a2bl>;
using usa2c8=unordered_set<a2c8>;
using usa2uc8=unordered_set<a2uc8>;
using usa2i8=unordered_set<a2i8>;
using usa2i16=unordered_set<a2i16>;
using usa2i32=unordered_set<a2i32>;
using usa2i64=unordered_set<a2i64>;
using usa2i128=unordered_set<a2i128>;
using usa2u8=unordered_set<a2u8>;
using usa2u16=unordered_set<a2u16>;
using usa2u32=unordered_set<a2u32>;
using usa2u64=unordered_set<a2u64>;
using usa2u128=unordered_set<a2u128>;
using usa2f32=unordered_set<a2f32>;
using usa2f64=unordered_set<a2f64>;
using usa2fld=unordered_set<a2fld>;
using usa2f128=unordered_set<a2f128>;
using usa2str8=unordered_set<a2str8>;

using vusbl=vector<usbl>;
using vusc8=vector<usc8>;
using vusuc8=vector<usuc8>;
using vusi8=vector<usi8>;
using vusi16=vector<usi16>;
using vusi32=vector<usi32>;
using vusi64=vector<usi64>;
using vusi128=vector<usi128>;
using vusu8=vector<usu8>;
using vusu16=vector<usu16>;
using vusu32=vector<usu32>;
using vusu64=vector<usu64>;
using vusu128=vector<usu128>;
using vusf32=vector<usf32>;
using vusf64=vector<usf64>;
using vusfld=vector<usfld>;
using vusf128=vector<usf128>;
using vusstr8=vector<usstr8>;
using vuspbl=vector<uspbl>;
using vuspc8=vector<uspc8>;
using vuspuc8=vector<uspuc8>;
using vuspi8=vector<uspi8>;
using vuspi16=vector<uspi16>;
using vuspi32=vector<uspi32>;
using vuspi64=vector<uspi64>;
using vuspi128=vector<uspi128>;
using vuspu8=vector<uspu8>;
using vuspu16=vector<uspu16>;
using vuspu32=vector<uspu32>;
using vuspu64=vector<uspu64>;
using vuspu128=vector<uspu128>;
using vuspf32=vector<uspf32>;
using vuspf64=vector<uspf64>;
using vuspfld=vector<uspfld>;
using vuspf128=vector<uspf128>;
using vuspstr8=vector<uspstr8>;
using vusa2bl=vector<usa2bl>;
using vusa2c8=vector<usa2c8>;
using vusa2uc8=vector<usa2uc8>;
using vusa2i8=vector<usa2i8>;
using vusa2i16=vector<usa2i16>;
using vusa2i32=vector<usa2i32>;
using vusa2i64=vector<usa2i64>;
using vusa2i128=vector<usa2i128>;
using vusa2u8=vector<usa2u8>;
using vusa2u16=vector<usa2u16>;
using vusa2u32=vector<usa2u32>;
using vusa2u64=vector<usa2u64>;
using vusa2u128=vector<usa2u128>;
using vusa2f32=vector<usa2f32>;
using vusa2f64=vector<usa2f64>;
using vusa2fld=vector<usa2fld>;
using vusa2f128=vector<usa2f128>;
using vusa2str8=vector<usa2str8>;

template<class H, class Eq> using USbl=unordered_set<bl, H, Eq>;
template<class H, class Eq> using USc8=unordered_set<c8, H, Eq>;
template<class H, class Eq> using USuc8=unordered_set<uc8, H, Eq>;
template<class H, class Eq> using USi8=unordered_set<i8, H, Eq>;
template<class H, class Eq> using USi16=unordered_set<i16, H, Eq>;
template<class H, class Eq> using USi32=unordered_set<i32, H, Eq>;
template<class H, class Eq> using USi64=unordered_set<i64, H, Eq>;
template<class H, class Eq> using USi128=unordered_set<i128, H, Eq>;
template<class H, class Eq> using USu8=unordered_set<u8, H, Eq>;
template<class H, class Eq> using USu16=unordered_set<u16, H, Eq>;
template<class H, class Eq> using USu32=unordered_set<u32, H, Eq>;
template<class H, class Eq> using USu64=unordered_set<u64, H, Eq>;
template<class H, class Eq> using USu128=unordered_set<u128, H, Eq>;
template<class H, class Eq> using USf32=unordered_set<f32, H, Eq>;
template<class H, class Eq> using USf64=unordered_set<f64, H, Eq>;
template<class H, class Eq> using USfld=unordered_set<fld, H, Eq>;
template<class H, class Eq> using USf128=unordered_set<f128, H, Eq>;
template<class H, class Eq> using USstr8=unordered_set<str8, H, Eq>;
template<class H, class Eq> using USpbl=unordered_set<pbl, H, Eq>;
template<class H, class Eq> using USpc8=unordered_set<pc8, H, Eq>;
template<class H, class Eq> using USpuc8=unordered_set<puc8, H, Eq>;
template<class H, class Eq> using USpi8=unordered_set<pi8, H, Eq>;
template<class H, class Eq> using USpi16=unordered_set<pi16, H, Eq>;
template<class H, class Eq> using USpi32=unordered_set<pi32, H, Eq>;
template<class H, class Eq> using USpi64=unordered_set<pi64, H, Eq>;
template<class H, class Eq> using USpi128=unordered_set<pi128, H, Eq>;
template<class H, class Eq> using USpu8=unordered_set<pu8, H, Eq>;
template<class H, class Eq> using USpu16=unordered_set<pu16, H, Eq>;
template<class H, class Eq> using USpu32=unordered_set<pu32, H, Eq>;
template<class H, class Eq> using USpu64=unordered_set<pu64, H, Eq>;
template<class H, class Eq> using USpu128=unordered_set<pu128, H, Eq>;
template<class H, class Eq> using USpf32=unordered_set<pf32, H, Eq>;
template<class H, class Eq> using USpf64=unordered_set<pf64, H, Eq>;
template<class H, class Eq> using USpfld=unordered_set<pfld, H, Eq>;
template<class H, class Eq> using USpf128=unordered_set<pf128, H, Eq>;
template<class H, class Eq> using USpstr8=unordered_set<pstr8, H, Eq>;
template<class H, class Eq> using USa2bl=unordered_set<a2bl, H, Eq>;
template<class H, class Eq> using USa2c8=unordered_set<a2c8, H, Eq>;
template<class H, class Eq> using USa2uc8=unordered_set<a2uc8, H, Eq>;
template<class H, class Eq> using USa2i8=unordered_set<a2i8, H, Eq>;
template<class H, class Eq> using USa2i16=unordered_set<a2i16, H, Eq>;
template<class H, class Eq> using USa2i32=unordered_set<a2i32, H, Eq>;
template<class H, class Eq> using USa2i64=unordered_set<a2i64, H, Eq>;
template<class H, class Eq> using USa2i128=unordered_set<a2i128, H, Eq>;
template<class H, class Eq> using USa2u8=unordered_set<a2u8, H, Eq>;
template<class H, class Eq> using USa2u16=unordered_set<a2u16, H, Eq>;
template<class H, class Eq> using USa2u32=unordered_set<a2u32, H, Eq>;
template<class H, class Eq> using USa2u64=unordered_set<a2u64, H, Eq>;
template<class H, class Eq> using USa2u128=unordered_set<a2u128, H, Eq>;
template<class H, class Eq> using USa2f32=unordered_set<a2f32, H, Eq>;
template<class H, class Eq> using USa2f64=unordered_set<a2f64, H, Eq>;
template<class H, class Eq> using USa2fld=unordered_set<a2fld, H, Eq>;
template<class H, class Eq> using USa2f128=unordered_set<a2f128, H, Eq>;
template<class H, class Eq> using USa2str8=unordered_set<a2str8, H, Eq>;

template<class H, class Eq> using vUSbl=vector<USbl<H, Eq>>;
template<class H, class Eq> using vUSc8=vector<USc8<H, Eq>>;
template<class H, class Eq> using vUSuc8=vector<USuc8<H, Eq>>;
template<class H, class Eq> using vUSi8=vector<USi8<H, Eq>>;
template<class H, class Eq> using vUSi16=vector<USi16<H, Eq>>;
template<class H, class Eq> using vUSi32=vector<USi32<H, Eq>>;
template<class H, class Eq> using vUSi64=vector<USi64<H, Eq>>;
template<class H, class Eq> using vUSi128=vector<USi128<H, Eq>>;
template<class H, class Eq> using vUSu8=vector<USu8<H, Eq>>;
template<class H, class Eq> using vUSu16=vector<USu16<H, Eq>>;
template<class H, class Eq> using vUSu32=vector<USu32<H, Eq>>;
template<class H, class Eq> using vUSu64=vector<USu64<H, Eq>>;
template<class H, class Eq> using vUSu128=vector<USu128<H, Eq>>;
template<class H, class Eq> using vUSf32=vector<USf32<H, Eq>>;
template<class H, class Eq> using vUSf64=vector<USf64<H, Eq>>;
template<class H, class Eq> using vUSfld=vector<USfld<H, Eq>>;
template<class H, class Eq> using vUSf128=vector<USf128<H, Eq>>;
template<class H, class Eq> using vUSstr8=vector<USstr8<H, Eq>>;
template<class H, class Eq> using vUSpbl=vector<USpbl<H, Eq>>;
template<class H, class Eq> using vUSpc8=vector<USpc8<H, Eq>>;
template<class H, class Eq> using vUSpuc8=vector<USpuc8<H, Eq>>;
template<class H, class Eq> using vUSpi8=vector<USpi8<H, Eq>>;
template<class H, class Eq> using vUSpi16=vector<USpi16<H, Eq>>;
template<class H, class Eq> using vUSpi32=vector<USpi32<H, Eq>>;
template<class H, class Eq> using vUSpi64=vector<USpi64<H, Eq>>;
template<class H, class Eq> using vUSpi128=vector<USpi128<H, Eq>>;
template<class H, class Eq> using vUSpu8=vector<USpu8<H, Eq>>;
template<class H, class Eq> using vUSpu16=vector<USpu16<H, Eq>>;
template<class H, class Eq> using vUSpu32=vector<USpu32<H, Eq>>;
template<class H, class Eq> using vUSpu64=vector<USpu64<H, Eq>>;
template<class H, class Eq> using vUSpu128=vector<USpu128<H, Eq>>;
template<class H, class Eq> using vUSpf32=vector<USpf32<H, Eq>>;
template<class H, class Eq> using vUSpf64=vector<USpf64<H, Eq>>;
template<class H, class Eq> using vUSpfld=vector<USpfld<H, Eq>>;
template<class H, class Eq> using vUSpf128=vector<USpf128<H, Eq>>;
template<class H, class Eq> using vUSpstr8=vector<USpstr8<H, Eq>>;
template<class H, class Eq> using vUSa2bl=vector<USa2bl<H, Eq>>;
template<class H, class Eq> using vUSa2c8=vector<USa2c8<H, Eq>>;
template<class H, class Eq> using vUSa2uc8=vector<USa2uc8<H, Eq>>;
template<class H, class Eq> using vUSa2i8=vector<USa2i8<H, Eq>>;
template<class H, class Eq> using vUSa2i16=vector<USa2i16<H, Eq>>;
template<class H, class Eq> using vUSa2i32=vector<USa2i32<H, Eq>>;
template<class H, class Eq> using vUSa2i64=vector<USa2i64<H, Eq>>;
template<class H, class Eq> using vUSa2i128=vector<USa2i128<H, Eq>>;
template<class H, class Eq> using vUSa2u8=vector<USa2u8<H, Eq>>;
template<class H, class Eq> using vUSa2u16=vector<USa2u16<H, Eq>>;
template<class H, class Eq> using vUSa2u32=vector<USa2u32<H, Eq>>;
template<class H, class Eq> using vUSa2u64=vector<USa2u64<H, Eq>>;
template<class H, class Eq> using vUSa2u128=vector<USa2u128<H, Eq>>;
template<class H, class Eq> using vUSa2f32=vector<USa2f32<H, Eq>>;
template<class H, class Eq> using vUSa2f64=vector<USa2f64<H, Eq>>;
template<class H, class Eq> using vUSa2fld=vector<USa2fld<H, Eq>>;
template<class H, class Eq> using vUSa2f128=vector<USa2f128<H, Eq>>;
template<class H, class Eq> using vUSa2str8=vector<USa2str8<H, Eq>>;

using qbl=queue<bl>;
using qc8=queue<c8>;
using quc8=queue<uc8>;
using qi8=queue<i8>;
using qi16=queue<i16>;
using qi32=queue<i32>;
using qi64=queue<i64>;
using qi128=queue<i128>;
using qu8=queue<u8>;
using qu16=queue<u16>;
using qu32=queue<u32>;
using qu64=queue<u64>;
using qu128=queue<u128>;
using qf32=queue<f32>;
using qf64=queue<f64>;
using qfld=queue<fld>;
using qf128=queue<f128>;
using qstr8=queue<str8>;
using qpbl=queue<pbl>;
using qpc8=queue<pc8>;
using qpuc8=queue<puc8>;
using qpi8=queue<pi8>;
using qpi16=queue<pi16>;
using qpi32=queue<pi32>;
using qpi64=queue<pi64>;
using qpi128=queue<pi128>;
using qpu8=queue<pu8>;
using qpu16=queue<pu16>;
using qpu32=queue<pu32>;
using qpu64=queue<pu64>;
using qpu128=queue<pu128>;
using qpf32=queue<pf32>;
using qpf64=queue<pf64>;
using qpfld=queue<pfld>;
using qpf128=queue<pf128>;
using qpstr8=queue<pstr8>;
using qa2bl=queue<a2bl>;
using qa2c8=queue<a2c8>;
using qa2uc8=queue<a2uc8>;
using qa2i8=queue<a2i8>;
using qa2i16=queue<a2i16>;
using qa2i32=queue<a2i32>;
using qa2i64=queue<a2i64>;
using qa2i128=queue<a2i128>;
using qa2u8=queue<a2u8>;
using qa2u16=queue<a2u16>;
using qa2u32=queue<a2u32>;
using qa2u64=queue<a2u64>;
using qa2u128=queue<a2u128>;
using qa2f32=queue<a2f32>;
using qa2f64=queue<a2f64>;
using qa2fld=queue<a2fld>;
using qa2f128=queue<a2f128>;
using qa2str8=queue<a2str8>;

using vqbl=vector<qbl>;
using vqc8=vector<qc8>;
using vquc8=vector<quc8>;
using vqi8=vector<qi8>;
using vqi16=vector<qi16>;
using vqi32=vector<qi32>;
using vqi64=vector<qi64>;
using vqi128=vector<qi128>;
using vqu8=vector<qu8>;
using vqu16=vector<qu16>;
using vqu32=vector<qu32>;
using vqu64=vector<qu64>;
using vqu128=vector<qu128>;
using vqf32=vector<qf32>;
using vqf64=vector<qf64>;
using vqfld=vector<qfld>;
using vqf128=vector<qf128>;
using vqstr8=vector<qstr8>;
using vqpbl=vector<qpbl>;
using vqpc8=vector<qpc8>;
using vqpuc8=vector<qpuc8>;
using vqpi8=vector<qpi8>;
using vqpi16=vector<qpi16>;
using vqpi32=vector<qpi32>;
using vqpi64=vector<qpi64>;
using vqpi128=vector<qpi128>;
using vqpu8=vector<qpu8>;
using vqpu16=vector<qpu16>;
using vqpu32=vector<qpu32>;
using vqpu64=vector<qpu64>;
using vqpu128=vector<qpu128>;
using vqpf32=vector<qpf32>;
using vqpf64=vector<qpf64>;
using vqpfld=vector<qpfld>;
using vqpf128=vector<qpf128>;
using vqpstr8=vector<qpstr8>;
using vqa2bl=vector<qa2bl>;
using vqa2c8=vector<qa2c8>;
using vqa2uc8=vector<qa2uc8>;
using vqa2i8=vector<qa2i8>;
using vqa2i16=vector<qa2i16>;
using vqa2i32=vector<qa2i32>;
using vqa2i64=vector<qa2i64>;
using vqa2i128=vector<qa2i128>;
using vqa2u8=vector<qa2u8>;
using vqa2u16=vector<qa2u16>;
using vqa2u32=vector<qa2u32>;
using vqa2u64=vector<qa2u64>;
using vqa2u128=vector<qa2u128>;
using vqa2f32=vector<qa2f32>;
using vqa2f64=vector<qa2f64>;
using vqa2fld=vector<qa2fld>;
using vqa2f128=vector<qa2f128>;
using vqa2str8=vector<qa2str8>;

using dbl=deque<bl>;
using dc8=deque<c8>;
using duc8=deque<uc8>;
using di8=deque<i8>;
using di16=deque<i16>;
using di32=deque<i32>;
using di64=deque<i64>;
using di128=deque<i128>;
using du8=deque<u8>;
using du16=deque<u16>;
using du32=deque<u32>;
using du64=deque<u64>;
using du128=deque<u128>;
using df32=deque<f32>;
using df64=deque<f64>;
using dfld=deque<fld>;
using df128=deque<f128>;
using dstr8=deque<str8>;
using dpbl=deque<pbl>;
using dpc8=deque<pc8>;
using dpuc8=deque<puc8>;
using dpi8=deque<pi8>;
using dpi16=deque<pi16>;
using dpi32=deque<pi32>;
using dpi64=deque<pi64>;
using dpi128=deque<pi128>;
using dpu8=deque<pu8>;
using dpu16=deque<pu16>;
using dpu32=deque<pu32>;
using dpu64=deque<pu64>;
using dpu128=deque<pu128>;
using dpf32=deque<pf32>;
using dpf64=deque<pf64>;
using dpfld=deque<pfld>;
using dpf128=deque<pf128>;
using dpstr8=deque<pstr8>;
using da2bl=deque<a2bl>;
using da2c8=deque<a2c8>;
using da2uc8=deque<a2uc8>;
using da2i8=deque<a2i8>;
using da2i16=deque<a2i16>;
using da2i32=deque<a2i32>;
using da2i64=deque<a2i64>;
using da2i128=deque<a2i128>;
using da2u8=deque<a2u8>;
using da2u16=deque<a2u16>;
using da2u32=deque<a2u32>;
using da2u64=deque<a2u64>;
using da2u128=deque<a2u128>;
using da2f32=deque<a2f32>;
using da2f64=deque<a2f64>;
using da2fld=deque<a2fld>;
using da2f128=deque<a2f128>;
using da2str8=deque<a2str8>;

using vdbl=vector<dbl>;
using vdc8=vector<dc8>;
using vduc8=vector<duc8>;
using vdi8=vector<di8>;
using vdi16=vector<di16>;
using vdi32=vector<di32>;
using vdi64=vector<di64>;
using vdi128=vector<di128>;
using vdu8=vector<du8>;
using vdu16=vector<du16>;
using vdu32=vector<du32>;
using vdu64=vector<du64>;
using vdu128=vector<du128>;
using vdf32=vector<df32>;
using vdf64=vector<df64>;
using vdfld=vector<dfld>;
using vdf128=vector<df128>;
using vdstr8=vector<dstr8>;
using vdpbl=vector<dpbl>;
using vdpc8=vector<dpc8>;
using vdpuc8=vector<dpuc8>;
using vdpi8=vector<dpi8>;
using vdpi16=vector<dpi16>;
using vdpi32=vector<dpi32>;
using vdpi64=vector<dpi64>;
using vdpi128=vector<dpi128>;
using vdpu8=vector<dpu8>;
using vdpu16=vector<dpu16>;
using vdpu32=vector<dpu32>;
using vdpu64=vector<dpu64>;
using vdpu128=vector<dpu128>;
using vdpf32=vector<dpf32>;
using vdpf64=vector<dpf64>;
using vdpfld=vector<dpfld>;
using vdpf128=vector<dpf128>;
using vdpstr8=vector<dpstr8>;
using vda2bl=vector<da2bl>;
using vda2c8=vector<da2c8>;
using vda2uc8=vector<da2uc8>;
using vda2i8=vector<da2i8>;
using vda2i16=vector<da2i16>;
using vda2i32=vector<da2i32>;
using vda2i64=vector<da2i64>;
using vda2i128=vector<da2i128>;
using vda2u8=vector<da2u8>;
using vda2u16=vector<da2u16>;
using vda2u32=vector<da2u32>;
using vda2u64=vector<da2u64>;
using vda2u128=vector<da2u128>;
using vda2f32=vector<da2f32>;
using vda2f64=vector<da2f64>;
using vda2fld=vector<da2fld>;
using vda2f128=vector<da2f128>;
using vda2str8=vector<da2str8>;

using pqbl=priority_queue<bl>;
using pqc8=priority_queue<c8>;
using pquc8=priority_queue<uc8>;
using pqi8=priority_queue<i8>;
using pqi16=priority_queue<i16>;
using pqi32=priority_queue<i32>;
using pqi64=priority_queue<i64>;
using pqi128=priority_queue<i128>;
using pqu8=priority_queue<u8>;
using pqu16=priority_queue<u16>;
using pqu32=priority_queue<u32>;
using pqu64=priority_queue<u64>;
using pqu128=priority_queue<u128>;
using pqf32=priority_queue<f32>;
using pqf64=priority_queue<f64>;
using pqfld=priority_queue<fld>;
using pqf128=priority_queue<f128>;
using pqstr8=priority_queue<str8>;
using pqpbl=priority_queue<pbl>;
using pqpc8=priority_queue<pc8>;
using pqpuc8=priority_queue<puc8>;
using pqpi8=priority_queue<pi8>;
using pqpi16=priority_queue<pi16>;
using pqpi32=priority_queue<pi32>;
using pqpi64=priority_queue<pi64>;
using pqpi128=priority_queue<pi128>;
using pqpu8=priority_queue<pu8>;
using pqpu16=priority_queue<pu16>;
using pqpu32=priority_queue<pu32>;
using pqpu64=priority_queue<pu64>;
using pqpu128=priority_queue<pu128>;
using pqpf32=priority_queue<pf32>;
using pqpf64=priority_queue<pf64>;
using pqpfld=priority_queue<pfld>;
using pqpf128=priority_queue<pf128>;
using pqpstr8=priority_queue<pstr8>;
using pqa2bl=priority_queue<a2bl>;
using pqa2c8=priority_queue<a2c8>;
using pqa2uc8=priority_queue<a2uc8>;
using pqa2i8=priority_queue<a2i8>;
using pqa2i16=priority_queue<a2i16>;
using pqa2i32=priority_queue<a2i32>;
using pqa2i64=priority_queue<a2i64>;
using pqa2i128=priority_queue<a2i128>;
using pqa2u8=priority_queue<a2u8>;
using pqa2u16=priority_queue<a2u16>;
using pqa2u32=priority_queue<a2u32>;
using pqa2u64=priority_queue<a2u64>;
using pqa2u128=priority_queue<a2u128>;
using pqa2f32=priority_queue<a2f32>;
using pqa2f64=priority_queue<a2f64>;
using pqa2fld=priority_queue<a2fld>;
using pqa2f128=priority_queue<a2f128>;
using pqa2str8=priority_queue<a2str8>;

using vpqbl=vector<pqbl>;
using vpqc8=vector<pqc8>;
using vpquc8=vector<pquc8>;
using vpqi8=vector<pqi8>;
using vpqi16=vector<pqi16>;
using vpqi32=vector<pqi32>;
using vpqi64=vector<pqi64>;
using vpqi128=vector<pqi128>;
using vpqu8=vector<pqu8>;
using vpqu16=vector<pqu16>;
using vpqu32=vector<pqu32>;
using vpqu64=vector<pqu64>;
using vpqu128=vector<pqu128>;
using vpqf32=vector<pqf32>;
using vpqf64=vector<pqf64>;
using vpqfld=vector<pqfld>;
using vpqf128=vector<pqf128>;
using vpqstr8=vector<pqstr8>;
using vpqpbl=vector<pqpbl>;
using vpqpc8=vector<pqpc8>;
using vpqpuc8=vector<pqpuc8>;
using vpqpi8=vector<pqpi8>;
using vpqpi16=vector<pqpi16>;
using vpqpi32=vector<pqpi32>;
using vpqpi64=vector<pqpi64>;
using vpqpi128=vector<pqpi128>;
using vpqpu8=vector<pqpu8>;
using vpqpu16=vector<pqpu16>;
using vpqpu32=vector<pqpu32>;
using vpqpu64=vector<pqpu64>;
using vpqpu128=vector<pqpu128>;
using vpqpf32=vector<pqpf32>;
using vpqpf64=vector<pqpf64>;
using vpqpfld=vector<pqpfld>;
using vpqpf128=vector<pqpf128>;
using vpqpstr8=vector<pqpstr8>;
using vpqa2bl=vector<pqa2bl>;
using vpqa2c8=vector<pqa2c8>;
using vpqa2uc8=vector<pqa2uc8>;
using vpqa2i8=vector<pqa2i8>;
using vpqa2i16=vector<pqa2i16>;
using vpqa2i32=vector<pqa2i32>;
using vpqa2i64=vector<pqa2i64>;
using vpqa2i128=vector<pqa2i128>;
using vpqa2u8=vector<pqa2u8>;
using vpqa2u16=vector<pqa2u16>;
using vpqa2u32=vector<pqa2u32>;
using vpqa2u64=vector<pqa2u64>;
using vpqa2u128=vector<pqa2u128>;
using vpqa2f32=vector<pqa2f32>;
using vpqa2f64=vector<pqa2f64>;
using vpqa2fld=vector<pqa2fld>;
using vpqa2f128=vector<pqa2f128>;
using vpqa2str8=vector<pqa2str8>;

template<class Pr> using PQbl=priority_queue<bl, vbl, Pr>;
template<class Pr> using PQc8=priority_queue<c8, vc8, Pr>;
template<class Pr> using PQuc8=priority_queue<uc8, vuc8, Pr>;
template<class Pr> using PQi8=priority_queue<i8, vi8, Pr>;
template<class Pr> using PQi16=priority_queue<i16, vi16, Pr>;
template<class Pr> using PQi32=priority_queue<i32, vi32, Pr>;
template<class Pr> using PQi64=priority_queue<i64, vi64, Pr>;
template<class Pr> using PQi128=priority_queue<i128, vi128, Pr>;
template<class Pr> using PQu8=priority_queue<u8, vu8, Pr>;
template<class Pr> using PQu16=priority_queue<u16, vu16, Pr>;
template<class Pr> using PQu32=priority_queue<u32, vu32, Pr>;
template<class Pr> using PQu64=priority_queue<u64, vu64, Pr>;
template<class Pr> using PQu128=priority_queue<u128, vu128, Pr>;
template<class Pr> using PQf32=priority_queue<f32, vf32, Pr>;
template<class Pr> using PQf64=priority_queue<f64, vf64, Pr>;
template<class Pr> using PQfld=priority_queue<fld, vfld, Pr>;
template<class Pr> using PQf128=priority_queue<f128, vf128, Pr>;
template<class Pr> using PQstr8=priority_queue<str8, vstr8, Pr>;
template<class Pr> using PQpbl=priority_queue<pbl, vpbl, Pr>;
template<class Pr> using PQpc8=priority_queue<pc8, vpc8, Pr>;
template<class Pr> using PQpuc8=priority_queue<puc8, vpuc8, Pr>;
template<class Pr> using PQpi8=priority_queue<pi8, vpi8, Pr>;
template<class Pr> using PQpi16=priority_queue<pi16, vpi16, Pr>;
template<class Pr> using PQpi32=priority_queue<pi32, vpi32, Pr>;
template<class Pr> using PQpi64=priority_queue<pi64, vpi64, Pr>;
template<class Pr> using PQpi128=priority_queue<pi128, vpi128, Pr>;
template<class Pr> using PQpu8=priority_queue<pu8, vpu8, Pr>;
template<class Pr> using PQpu16=priority_queue<pu16, vpu16, Pr>;
template<class Pr> using PQpu32=priority_queue<pu32, vpu32, Pr>;
template<class Pr> using PQpu64=priority_queue<pu64, vpu64, Pr>;
template<class Pr> using PQpu128=priority_queue<pu128, vpu128, Pr>;
template<class Pr> using PQpf32=priority_queue<pf32, vpf32, Pr>;
template<class Pr> using PQpf64=priority_queue<pf64, vpf64, Pr>;
template<class Pr> using PQpfld=priority_queue<pfld, vpfld, Pr>;
template<class Pr> using PQpf128=priority_queue<pf128, vpf128, Pr>;
template<class Pr> using PQpstr8=priority_queue<pstr8, vpstr8, Pr>;
template<class Pr> using PQa2bl=priority_queue<a2bl, va2bl, Pr>;
template<class Pr> using PQa2c8=priority_queue<a2c8, va2c8, Pr>;
template<class Pr> using PQa2uc8=priority_queue<a2uc8, va2uc8, Pr>;
template<class Pr> using PQa2i8=priority_queue<a2i8, va2i8, Pr>;
template<class Pr> using PQa2i16=priority_queue<a2i16, va2i16, Pr>;
template<class Pr> using PQa2i32=priority_queue<a2i32, va2i32, Pr>;
template<class Pr> using PQa2i64=priority_queue<a2i64, va2i64, Pr>;
template<class Pr> using PQa2i128=priority_queue<a2i128, va2i128, Pr>;
template<class Pr> using PQa2u8=priority_queue<a2u8, va2u8, Pr>;
template<class Pr> using PQa2u16=priority_queue<a2u16, va2u16, Pr>;
template<class Pr> using PQa2u32=priority_queue<a2u32, va2u32, Pr>;
template<class Pr> using PQa2u64=priority_queue<a2u64, va2u64, Pr>;
template<class Pr> using PQa2u128=priority_queue<a2u128, va2u128, Pr>;
template<class Pr> using PQa2f32=priority_queue<a2f32, va2f32, Pr>;
template<class Pr> using PQa2f64=priority_queue<a2f64, va2f64, Pr>;
template<class Pr> using PQa2fld=priority_queue<a2fld, va2fld, Pr>;
template<class Pr> using PQa2f128=priority_queue<a2f128, va2f128, Pr>;
template<class Pr> using PQa2str8=priority_queue<a2str8, va2str8, Pr>;

template<class Pr> using vPQbl=vector<PQbl<Pr>>;
template<class Pr> using vPQc8=vector<PQc8<Pr>>;
template<class Pr> using vPQuc8=vector<PQuc8<Pr>>;
template<class Pr> using vPQi8=vector<PQi8<Pr>>;
template<class Pr> using vPQi16=vector<PQi16<Pr>>;
template<class Pr> using vPQi32=vector<PQi32<Pr>>;
template<class Pr> using vPQi64=vector<PQi64<Pr>>;
template<class Pr> using vPQi128=vector<PQi128<Pr>>;
template<class Pr> using vPQu8=vector<PQu8<Pr>>;
template<class Pr> using vPQu16=vector<PQu16<Pr>>;
template<class Pr> using vPQu32=vector<PQu32<Pr>>;
template<class Pr> using vPQu64=vector<PQu64<Pr>>;
template<class Pr> using vPQu128=vector<PQu128<Pr>>;
template<class Pr> using vPQf32=vector<PQf32<Pr>>;
template<class Pr> using vPQf64=vector<PQf64<Pr>>;
template<class Pr> using vPQfld=vector<PQfld<Pr>>;
template<class Pr> using vPQf128=vector<PQf128<Pr>>;
template<class Pr> using vPQstr8=vector<PQstr8<Pr>>;
template<class Pr> using vPQpbl=vector<PQpbl<Pr>>;
template<class Pr> using vPQpc8=vector<PQpc8<Pr>>;
template<class Pr> using vPQpuc8=vector<PQpuc8<Pr>>;
template<class Pr> using vPQpi8=vector<PQpi8<Pr>>;
template<class Pr> using vPQpi16=vector<PQpi16<Pr>>;
template<class Pr> using vPQpi32=vector<PQpi32<Pr>>;
template<class Pr> using vPQpi64=vector<PQpi64<Pr>>;
template<class Pr> using vPQpi128=vector<PQpi128<Pr>>;
template<class Pr> using vPQpu8=vector<PQpu8<Pr>>;
template<class Pr> using vPQpu16=vector<PQpu16<Pr>>;
template<class Pr> using vPQpu32=vector<PQpu32<Pr>>;
template<class Pr> using vPQpu64=vector<PQpu64<Pr>>;
template<class Pr> using vPQpu128=vector<PQpu128<Pr>>;
template<class Pr> using vPQpf32=vector<PQpf32<Pr>>;
template<class Pr> using vPQpf64=vector<PQpf64<Pr>>;
template<class Pr> using vPQpfld=vector<PQpfld<Pr>>;
template<class Pr> using vPQpf128=vector<PQpf128<Pr>>;
template<class Pr> using vPQpstr8=vector<PQpstr8<Pr>>;
template<class Pr> using vPQa2bl=vector<PQa2bl<Pr>>;
template<class Pr> using vPQa2c8=vector<PQa2c8<Pr>>;
template<class Pr> using vPQa2uc8=vector<PQa2uc8<Pr>>;
template<class Pr> using vPQa2i8=vector<PQa2i8<Pr>>;
template<class Pr> using vPQa2i16=vector<PQa2i16<Pr>>;
template<class Pr> using vPQa2i32=vector<PQa2i32<Pr>>;
template<class Pr> using vPQa2i64=vector<PQa2i64<Pr>>;
template<class Pr> using vPQa2i128=vector<PQa2i128<Pr>>;
template<class Pr> using vPQa2u8=vector<PQa2u8<Pr>>;
template<class Pr> using vPQa2u16=vector<PQa2u16<Pr>>;
template<class Pr> using vPQa2u32=vector<PQa2u32<Pr>>;
template<class Pr> using vPQa2u64=vector<PQa2u64<Pr>>;
template<class Pr> using vPQa2u128=vector<PQa2u128<Pr>>;
template<class Pr> using vPQa2f32=vector<PQa2f32<Pr>>;
template<class Pr> using vPQa2f64=vector<PQa2f64<Pr>>;
template<class Pr> using vPQa2fld=vector<PQa2fld<Pr>>;
template<class Pr> using vPQa2f128=vector<PQa2f128<Pr>>;
template<class Pr> using vPQa2str8=vector<PQa2str8<Pr>>;

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
#define T_CASES
// #define PRECOMP
// #define PT_NUMS

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

#ifndef NUMBER_THEORY_H_INCLUDED
#define NUMBER_THEORY_H_INCLUDED

#ifndef TEMPLATE_H_INCLUDED
#include "template.h"
#endif // TEMPLATE_H_INCLUDED

template<typename T>
constexpr T bin_gcd(T l, T r) {
	if (!(l && r))
		return l | r;
	int s = __builtin_ctz(l | r);
	l >>= __builtin_ctz(l);
	do {
		r >>= __builtin_ctz(r);
		if (l > r)
			swap(l, r);
		r -= l;
	} while (r);
	return l << s;
}

template<typename T>
constexpr T gcd(const T& l, const T& r) {
	if constexpr (is_integral_v<T>)
		return bin_gcd(l, r);
	else {
		T a = abs(l), b = abs(r);
		while (b)
			tie(a, b) = make_pair(b, a % b);
		return a;
	}
}

template<typename T>
constexpr T gcd(initializer_list<T> args) {
	return accumulate(args.begin(), args.end(), (T)0, gcd<T>);
}

template<typename T>
constexpr T lcm(const T& l, const T& r) {
	return (l | r) ? l / gcd(l, r) * r : 0;
}

template<typename T>
constexpr T lcm(initializer_list<T> args) {
	return accumulate(args.begin(), args.end(), (T)1, lcm<T>);
}

template<typename T>
constexpr bool coprime(T l, T r) {
	return gcd(l, r) == 1;
}

template<typename T>
struct bezout {
	T gcd, x, y;
};

template<typename T>
constexpr bezout<T> eEuclid(const T& l, const T& r) {
	T a = abs(l), b = abs(r);
	vector<pair<T, T>> S;
	while (b != 0) {
		S.emplace_back(a, b);
		tie(a, b) = make_pair(b, a % b);
	}
	bezout<T> ans{a, 1, 0};
	for (; !S.empty(); S.pop_back()) {
		tie(a, b) = S.back();
		tie(ans.x, ans.y) = make_pair(ans.y, ans.x - a / b * ans.y);
	}
	return ans;
}

template<typename T, typename U>
constexpr T pos_mod(const T& n, const U& mod) {
	if (n >= 0)
		return n >= mod ? n % mod : n;
	else
		return (n % mod) + mod;
}

template<typename T>
constexpr T mod_inv(const T& n, const T& mod) {
	bezout<T> bz = eEuclid(n, mod);
	assert(bz.gcd == 1);
	return pos_mod(bz.x, mod);
}

template<typename T, uintmax_t M = 0>
struct mod_int {
	static constexpr T MOD = M;

	T value;

	inline mod_int() :
		value(0)
	{}

	template<typename U>
	constexpr mod_int(const U& value) :
		value(static_cast<T>(pos_mod(value, MOD)))
	{}

	template<typename U>
	inline mod_int& operator=(const U& value) {
		this->value = static_cast<T>(pos_mod(value, MOD));
		return value;
	}

	template<typename U>
	inline mod_int& operator=(U&& value) noexcept {
		this->value = static_cast<T>(pos_mod(value, MOD));
		return *this;
	}

	explicit constexpr operator const T&() const {
		return value;
	}

	template<typename U>
	explicit constexpr operator U() const {
		return static_cast<U>(value);
	}

	constexpr T mod() const {
		return MOD;
	}
};

template<typename T>
struct mod_int<T, 0> {
	const T MOD;
	T value;

	template<typename U>
	explicit inline mod_int(const U& mod) :
		MOD(static_cast<T>(mod)),
		value(0)
	{}

	template<typename U, typename V>
	constexpr mod_int(const U& mod, const V& value) :
		MOD(static_cast<T>(mod)),
		value(static_cast<T>(pos_mod(value, mod))) {
		assert(mod > 0);
	}

	explicit constexpr operator const T&() const {
		return value;
	}

	template<typename U>
	explicit constexpr operator U() const {
		return static_cast<U>(value);
	}

	constexpr T mod() const {
		return MOD;
	}
};

template<typename T, uintmax_t M>
constexpr mod_int<T, M> inv(mod_int<T, M> n) {
	n.value = mod_inv(n.value, n.mod());
	return n;
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M> operator+(mod_int<T, M> l) {
	return l;
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M> operator-(mod_int<T, M> l) {
	l.value = l.value ? l.mod() - l.value : 0;
	return l;
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M>& operator+=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	if (M == 0)
		assert(l.mod() == r.mod());
	l.value = l.value + r.value;
	if (l.value >= l.mod())
		l.value -= l.mod();
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M>& operator+=(mod_int<T, M>& l, const U& r) {
	if constexpr (M == 0)
		return l += mod_int<T, M>(l.mod(), r);
	else
		return l += mod_int<T, M>(r);
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M> operator+(mod_int<T, M> l, const mod_int<T, M>& r) {
	l += r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator+(mod_int<T, M> l, const U& r) {
	l += r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator+(const U& l, mod_int<T, M> r) {
	r += l;
	return r;
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M>& operator-=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	if (M == 0)
		assert(l.mod() == r.mod());
	l.value = l.value - r.value;
	if (is_unsigned_v<T> ? l.value >= l.mod() : l.value < 0)
		l.value += l.mod();
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M>& operator-=(mod_int<T, M>& l, const U& r) {
	if constexpr (M == 0)
		return l -= mod_int<T, M>(l.mod(), r);
	else
		return l -= mod_int<T, M>(r);
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M> operator-(mod_int<T, M> l, const mod_int<T, M>& r) {
	l -= r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator-(mod_int<T, M> l, const U& r) {
	l -= r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator-(const U& l, mod_int<T, M> r) {
	if constexpr (M == 0) {
		mod_int<T, M> ans(l.mod(), l);
		return ans -= r;
	} else {
		mod_int<T, M> ans(l);
		return ans -= r;
	}
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M>& operator*=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	if (M == 0)
		assert(l.mod() == r.mod());
	l.value = (l.value * r.value) % l.mod();
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M>& operator*=(mod_int<T, M>& l, const U& r) {
	if constexpr (M == 0)
		return l *= mod_int<T, M>(l.mod(), r);
	else
		return l *= mod_int<T, M>(r);
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M> operator*(mod_int<T, M> l, const mod_int<T, M>& r) {
	l *= r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator*(mod_int<T, M> l, const U& r) {
	l *= r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator*(const U& l, mod_int<T, M> r) {
	r *= l;
	return r;
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M>& operator/=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	return l *= inv(r);
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M>& operator/=(mod_int<T, M>& l, const U& r) {
	if constexpr (M == 0)
		return l /= mod_int<T, M>(l.mod(), r);
	else
		return l /= mod_int<T, M>(r);
}

template<typename T, uintmax_t M>
constexpr mod_int<T, M> operator/(mod_int<T, M> l, const mod_int<T, M>& r) {
	l /= r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator/(mod_int<T, M> l, const U r) {
	l /= r;
	return l;
}

template<typename T, uintmax_t M, typename U>
constexpr mod_int<T, M> operator/(const U& l, const mod_int<T, M>& r) {
	return l * inv(r);
}

template<typename T, uintmax_t M>
inline istream& operator>>(istream& strm, mod_int<T, M>& n) {
	strm >> n.value;
	n.value = pos_mod(n.value, n.mod());
	return strm;
}

template<typename T, uintmax_t M>
inline ostream& operator<<(ostream& strm, const mod_int<T, M>& n) {
	return strm << n.value;
}

// TODO multiple inverses

//template<typename InputIt, typename OutputIt>
//constexpr void mod_inv(InputIt first, InputIt last, OutputIt d_first, typename iterator_traits<InputIt>::value_type mod)
//{
//	typedef typename iterator_traits<InputIt>::value_type T;
//
//	size_t n = 0;
//}

#endif // NUMBER_THEORY_H_INCLUDED


constexpr i64 MOD = 1000000007;
typedef mod_int<i64, MOD> mod;
typedef vector<mod> vmod;

void go() {
	int n;
	cin >> n;
	//map<int, int> A, B;
	vpi32 A;
	vi32 C(n);
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		C[i] = a;
	}
	sort(ALL(C));
	for (int a : C)
		if (A.empty() || A.back().first != a)
			A.emplace_back(a, 1);
		else
			A.back().second++;

	while (A.size() > 1 || A.front().second > 1) {
		C.clear();
		int z = 0;
		int pr = -1;
		for (auto [a, ct] : A) {
			//cerr << a << ' ' << ct << ' ';
			z += ct - 1;
			if (pr >= 0)
				C.push_back(a - pr);
			pr = a;
		}
		//cerr << endl;
		A.clear();
		if (z)
			A.emplace_back(0, z);
		sort(ALL(C));
		for (int a : C)
			if (A.empty() || A.back().first != a)
				A.emplace_back(a, 1);
			else
				A.back().second++;
	}
	cout << A.front().first << endl;
}

/*
void go() {
	int n;
	cin >> n;
	vmod A(n);
	for (mod& a : A)
		cin >> a;
	vmod F(n);
	F[0] = 1;
	for (int i = 1; i < n; i++)
		F[i] = F[i - 1] * i;
	mod ans = 0;
	for (int i = 0; i < n; i++) {
		mod val = F[n - 1] / (F[i] * F[n - 1 - i]);
		if ((n - 1 + i) % 2)
			val = -val;
		cerr << val << ' ';
		ans += val * A[i];
	}
	cerr << endl;
	cout << ans << endl;
}*/
