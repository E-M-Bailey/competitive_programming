#include <bits/stdc++.h>
using namespace std;

/*
typedef float T;
typedef complex<T> cp;

const T TAU = 8 * atanf(1);

void ffth(vector<cp>& X, cp w)
{
	int n = size(X);
	if (n <= 1)
		return;
	vector<cp> A(n / 2), B(n / 2);
	for (int i = 0; i < n; i++)
		(i % 2 ? B : A)[i / 2] = X[i];
	cp w2 = w * w;
	ffth(A, w2);
	ffth(B, w2);
	cp wi = 1;
	for (int i = 0; i < n / 2; i++)
	{
		X[i] = A[i] + wi * B[i];
		X[i + n / 2] = A[i] - wi * B[i];
		wi *= w;
	}
}

void fft(vector<cp>& X)
{
	int n = size(X);
	ffth(X, cp{ cosf(TAU / n), -sinf(TAU / n) });
}

void ifft(vector<cp>& X)
{
	int n = size(X);
	ffth(X, cp{ cosf(TAU / n), sinf(TAU / n) });
	for (auto& x : X)
		x /= n;
}*/

queue<int> Q;
struct graph
{
	int n;
	vector<vector<int>> G;
	vector<vector<bool>> D;
	graph(int N, int m): n(N), G(N), D(N, vector<bool>(N))
	{
		while (m--)
		{
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			G[u].push_back(v);
		}
		D[0][0] = true;
	}
	const vector<bool>& cmp()
	{
		vector<int> I(n);
		for (int v = 0; v < n; v++)
			for (int w : G[v])
				I[w]++;
		Q.push(0);
		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (int w : G[v])
			{
				for (int i = 0; i + 1 < n; i++)
					if (D[v][i])
						D[w][i + 1] = true;
				if (--I[w] == 0)
					Q.push(w);
			}
		}
		return D[n - 1];
	}
};

int main(int argc, const char* argv[])
{
	if (argc > 1)
		(ignore = freopen(argv[1], "r", stdin)) = freopen(argv[2], "w", stdout);

	int n1, n2, m1, m2;
	cin >> n1 >> n2 >> m1 >> m2;
	graph G1(n1, m1), G2(n2, m2);
	auto D1 = G1.cmp(), D2 = G2.cmp();
	int k;
	cin >> k;
	while (k--)
	{
		int q;
		cin >> q;
		bool f = false;
		for (int i = 0, j = q; i <= q; i++, j--)
			if (i < n1 && j < n2 && D1[i] && D2[j])
			{
				f = true;
				break;
			}
		cout << (f ? "Yes\n" : "No\n");
	}
}