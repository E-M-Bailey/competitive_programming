#ifndef HUNGARIAN_H_INCLUDED
#define HUNGARIAN_H_INCLUDED

#ifndef TEMPLATE_H_INCLUDED
#include "template.h"
#endif // TEMPLATE_H_INCLUDED

namespace Impl
{
template<typename T>
struct Hungarian
{
    static_assert(is_floating_point_v<T>);

private:
	vector<vector<T>> C;
	int n;
	vector<T> lw, lj, slj;
	vector<int> slwj, mw, mj, p;
	vbl cw;
	const T EPS;

public:
	inline Hungarian(const vector<vector<T>>& costs, T epsilon) :
		C(costs),
		n(C.size()),
		lw(n),
		lj(n),
		slj(n),
		slwj(n),
		mw(n, -1),
		mj(n, -1),
		p(n),
		cw(n),
		EPS(epsilon)
	{}

	private:
	inline void reduce()
	{
		for (int w = 0; w < n; w++)
		{
			T m = INF<f64>;
			for (int j = 0; j < n; j++)
				m = min(C[w][j], m);
			for (int j = 0; j < n; j++)
				C[w][j] -= m;
		}
		for (int j = 0; j < n; j++)
		{
			T m = INF<f64>;
			for (int w = 0; w < n; w++)
				m = min(m, C[w][j]);
			for (int w = 0; w < n; w++)
				C[w][j] -= m;
		}
	}

	inline void init()
	{
		for (int j = 0; j < n; j++)
			lj[j] = INF<f64>;
		for (int w = 0; w < n; w++)
			for (int j = 0; j < n; j++)
				lj[j] = min(lj[j], C[w][j]);
	}

	inline void match()
	{
		for (int w = 0; w < n; w++)
			for (int j = 0; j < n; j++)
				if (mw[w] < 0 && mj[j] < 0 && abs(C[w][j] - lw[w] - lj[j]) <= EPS)
				{
					mw[w] = j;
					mj[j] = w;
				}
	}

	inline int next()
	{
		for (int w = 0; w < n; w++)
			if (mw[w] < 0)
				return w;
		return -1;
	}

	inline void init_phase(int w)
	{
		fill(ALL(cw), false);
		fill(ALL(p), -1);
		cw[w] = true;
		for (int j = 0; j < n; j++)
		{
			slj[j] = C[w][j] - lw[w] - lj[j];
			slwj[j] = w;
		}
	}

	inline void upd(T s)
	{
		for (int w = 0; w < n; w++)
			if (cw[w])
				lw[w] += s;
		for (int j = 0; j < n; j++)
		{
			if (p[j] >= 0)
				lj[j] -= s;
			else
				slj[j] -= s;
		}
	}

	inline void phase()
	{
		for (;;)
		{
			int sw = -1, sj = -1;
			T s = INF<f64>;
			for (int j = 0; j < n; j++)
				if (p[j] < 0 && slj[j] < s)
				{
					s = slj[j];
					sw = slwj[j];
					sj = j;
				}
			if (abs(s) > EPS)
				upd(s);

			p[sj] = sw;
			if (mj[sj] < 0)
			{
				int j = sj, w = p[sj];
				for (;;)
				{
					mj[j] = w;
					swap(mw[w], j);
					if (j < 0)
						break;
					w = p[j];
				}
				return;
			}
			int w = mj[sj];
			cw[w] = true;
			for (int j = 0; j < n; j++)
				if (p[j] < 0)
				{
					T sl = C[w][j] - lw[w] - lj[j];
					if (slj[j] > sl)
					{
						slj[j] = sl;
						slwj[j] = w;
					}
				}
		}
	}

public:
	inline vector<int> operator()()
	{
		reduce();
		init();
		match();
		for (int w = next(); w >= 0; w = next())
		{
			init_phase(w);
			phase();
		}
		return mw;
	}

};
}

template<typename T>
inline vector<int> hungarian(const vector<vector<T>>& costs, T epsilon)
{
    return Impl::Hungarian<T>(costs, epsilon)();
}

#endif // HUNGARIAN_H_INCLUDED
