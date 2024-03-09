#include <bits/stdc++.h>
using namespace std;

vector<int> P;
vector<vector<int>> C;

int DD;

struct offset_pq
{
	priority_queue<int, vector<int>, greater<>> data;
	int off;
	void push(int x)
	{
		data.push(x - off);
	}
	void pop()
	{
		data.pop();
	}
	bool empty() const
	{
		return data.empty();
	}
	size_t size() const
	{
		return data.size();
	}
	int top() const
	{
		return data.top() + off;
	}
	void add(int x)
	{
		off += x;
	}
	void swap(offset_pq& s)
	{
		data.swap(s.data);
		::swap(off, s.off);
	}
	/*void dbg()
	{
		for (int d : data)
			cerr << ' ' << d + off;
	}*/
};

vector<offset_pq> S;

void dfs(int v)
{
	vector<offset_pq> o;
	for (int w : C[v])
	{
		dfs(w);
		o.push_back(move(S[w]));
		o.back().add(1);
		if (o.back().size() > S[v].size())
			o.back().swap(S[v]);
	}

	for (offset_pq& s : o)
	{
		while (!S[v].empty() && !s.empty() && S[v].top() + s.top() < DD)
			(s.top() < S[v].top() ? s : S[v]).pop();
		while (!s.empty())
		{
			S[v].push(s.top());
			s.pop();
		}
	}
	//cerr << v << ' ' << S[v].size() << ' ' << (S[v].empty() ? -1 : S[v].top()) << endl;
	//cerr << ' ';
	//cerr << endl;
	if (S[v].empty() || S[v].top() >= DD)
		S[v].push(0);

}

/*
7 2
0 0 1 2 3 4

*/

int main()
{
	int n;
	cin >> n >> DD;

	P.resize(n);
	C.resize(n);
	S.resize(n);

	for (int i = 1; i < n; i++)
	{
		int x;
		cin >> x;
		P[i] = x;
		C[x].push_back(i);
	}

	dfs(0);

	cout << S[0].size();
}