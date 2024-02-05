#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct Hungarian
{
	static_assert(is_floating_point_v<T>);

private:
	vector<vector<T>> C;
	int				  n;
	vector<T>		  lw, lj, slj;
	vector<int>		  slwj, mw, mj, p;
	vector<bool>	  cw;
	const T			  EPS;

public:
	inline Hungarian(const vector<vector<T>> &costs, T epsilon) :
		C(costs), n((int)C.size()), lw(n), lj(n), slj(n), slwj(n), mw(n, -1), mj(n, -1), p(n), cw(n), EPS(epsilon)
	{}

private:
	inline void reduce()
	{
		for (int w = 0; w < n; w++)
		{
			T m = numeric_limits<double>::infinity();
			for (int j = 0; j < n; j++)
				m = min(C[w][j], m);
			for (int j = 0; j < n; j++)
				C[w][j] -= m;
		}
		for (int j = 0; j < n; j++)
		{
			T m = numeric_limits<double>::infinity();
			for (int w = 0; w < n; w++)
				m = min(m, C[w][j]);
			for (int w = 0; w < n; w++)
				C[w][j] -= m;
		}
	}

	inline void init()
	{
		for (int j = 0; j < n; j++)
			lj[j] = numeric_limits<double>::infinity();
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
		fill(begin(cw), end(cw), false);
		fill(begin(p), end(p), -1);
		cw[w] = true;
		for (int j = 0; j < n; j++)
		{
			slj[j]	= C[w][j] - lw[w] - lj[j];
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
			T	s = numeric_limits<double>::infinity();
			for (int j = 0; j < n; j++)
				if (p[j] < 0 && slj[j] < s)
				{
					s  = slj[j];
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
						slj[j]	= sl;
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

template<typename T>
inline vector<int> hungarian(const vector<vector<T>> &costs, T epsilon)
{
	return Hungarian<T>(costs, epsilon)();
}

vector<int> perm_inv(const vector<int> &X)
{
	int n = (int)X.size();

	vector<int> Y(n);
	for (int i = 0; i < n; i++)
		Y[X[i]] = i;
	return Y;
}

struct result
{
	int			n, k;
	vector<int> IA, IB;
	int			c;

	result(int N, int K, const vector<vector<pair<int, int>>> &A, const vector<vector<pair<int, int>>> &B) :
		n(N), k(K), c(0)
	{
		vector<vector<double>> WA(n, vector<double>(n)), WB(n, vector<double>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				WA[i][j] = j < k ? A[i][j].first : A[i][j].second;
				WB[i][j] = j < k ? B[i][j].first : B[i][j].second;
			}
		IA = hungarian<double>(WA, 1e-13);
		IB = perm_inv(hungarian<double>(WB, 1e-13));
		for (int i = 0; i < n; i++)
		{
			c += (int)WA[i][IA[i]];
			c += (int)WB[IB[i]][i];
		}
	}

	friend bool operator<(const result &l, const result &r)
	{
		return l.c < r.c;
	}

	friend ostream &operator<<(ostream &strm, const result &r)
	{
		stringstream buf;
		buf << r.c << '\n';
		for (int i = 0; i < r.n; i++)
		{
			int j = r.IA[i];
			int k = r.IB[j];
			buf << i + 1 << ' ' << j + 1 << (j < r.k ? 'A' : 'B') << ' ' << k + 1 << '\n';
		}
		strm << buf.str();
		return strm;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<vector<pair<int, int>>> A(n, vector<pair<int, int>>(n)), B(n, vector<pair<int, int>>(n));
	for (vector<pair<int, int>> &AA : A)
		for (pair<int, int> &a : AA)
			cin >> a.first >> a.second;
	for (vector<pair<int, int>> &BB : B)
		for (pair<int, int> &b : BB)
			cin >> b.first >> b.second;

	result best(n, n, A, B);
	for (int k = 0; k < n; k++)
	{
		result r(n, k, A, B);
		if (r.c < best.c)
			best = move(r);
	}

	cout << best;
}
