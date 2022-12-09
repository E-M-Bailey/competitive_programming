#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#ifndef TEMPLATE_H_INCLUDED
#include "template.h"
#endif // TEMPLATE_H_INCLUDED

template<typename T, size_t D>
struct vec
{
	array<T, D> data{};

	constexpr vec() = default;

	constexpr vec(const array<T, D>& data) :
		data(data)
	{}

	constexpr vec(initializer_list<T> data) :
		data(data)
	{}

	template<size_t D2>
	constexpr vec(const vec<T, D2>& v)
	{
		copy_n(v.data.begin(), v.data.begin() + min(D, D2), data.begin());
	}

	constexpr size_t size()
	{
	    return D;
	}

	constexpr T& x()
	{
		return data[0];
	}
	constexpr const T& x() const
	{
		return data[0];
	}
	constexpr T& y()
	{
		return data[1];
	}
	constexpr const T& y() const
	{
		return data[1];
	}
	constexpr T& z()
	{
		return data[2];
	}
	constexpr const T& z() const
	{
		return data[2];
	}
	constexpr T& w()
	{
		return data[3];
	}
	constexpr const T& w() const
	{
		return data[3];
	}
};

template<typename T>
using vec2<T> = vec<T, 2>;
template<typename T>
using vec3<T> = vec<T, 3>;
template<typename T>
using vec4<T> = vec<T, 4>;

template<typename T, size_t D>
constexpr vec<T, D> operator+(const vec<T, D>& l, const vec<T, D>& r)
{
    vec
}



#endif // GEOMETRY_H_INCLUDED
