#include "../../Reference/hungarian.h"

inline __float128 log(__float128 f)
{
    return logl(f);
}

typedef double F;

void go()
{
	int n;
	cin >> n;
	vector<vector<F>> P(n, vector<F>(n)), Q(n, vector<F>(n));
	for (int w = 0; w < n; w++)
		for (int j = 0; j < n; j++)
		{
			P[w][j] = read<int>() / (F)100;
			if (P[w][j] == 0)
				Q[w][j] = 100000;
			else
				Q[w][j] = -log(P[w][j]);
		}

	vi32 m = hungarian<F>(Q, 1e-13);
    F ans = 1;
    for (int w = 0; w < n; w++)
            ans *= P[w][m[w]];

    cout << fixed << setprecision(9) << f64(100 * ans);
}
