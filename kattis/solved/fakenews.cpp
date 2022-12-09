#include <bits/stdc++.h>
using namespace std;
enum TYPE : int
{
	T, F, C
};
const array<string, 3> NAMES = {"truther", "fabulist", "charlatan"};
enum OP : int
{
	TYP, NOT, AND, XOR
};
struct node
{
	OP op;
	int a, b;
};
vector<node> E;
vector<vector<int>> A;
int n, k;

int parse()
{
	static string op;
	cin >> op;
	int i = E.size();
	E.push_back({});
	switch (op[0])
	{
	case 't':
		E[i].op = TYP;
		E[i].a = T;
		cin >> E[i].b;
		E[i].b--;
		break;
	case 'f':
		E[i].op = TYP;
		E[i].a = F;
		cin >> E[i].b;
		E[i].b--;
		break;
	case 'c':
		E[i].op = TYP;
		E[i].a = C;
		cin >> E[i].b;
		E[i].b--;
		break;
	case 'n':
		E[i].op = NOT;
		E[i].a = parse();
		E[i].b = -1;
		break;
	case 'a':
		E[i].op = AND;
		E[i].a = parse();
		E[i].b = parse();
		break;
	case 'x':
		E[i].op = XOR;
		E[i].a = parse();
		E[i].b = parse();
		break;
	}
	return i;
}

bool eval(int i, const vector<int>& t)
{
	const node& e = E[i];
	switch (e.op)
	{
	case TYP:
		return t[e.b] == e.a;
	case NOT:
		return !eval(e.a, t);
	case AND:
		return eval(e.a, t) && eval(e.b, t);
	case XOR:
		return eval(e.a, t) ^ eval(e.b, t);
	}
}

int main()
{
	cin >> n >> k;
	A.resize(n);
	for (int i = 0; i < k; i++)
	{
		int c;
		cin >> c;
		c--;
		A[c].push_back(parse());
	}
	vector<int> t(n, 0);
	const auto inc = [&]() -> bool
	{
		for (int i = 0; i < n; i++)
		{
			if (++t[i] < 3)
				return true;
			t[i] = 0;
		}
		return false;
	};
	do
	{
		//for (int tt : t)
		//	cerr << tt << ' ';
		bool good = true;
		for (int i = 0; good && i < n; i++)
		{
			switch (t[i])
			{
			case T:
				for (int a : A[i])
					if (!eval(a, t))
					{
						good = false;
						break;
					}
				break;
			case F:
				for (int a : A[i])
					if (eval(a, t))
					{
						good = false;
						break;
					}
				break;
			case C:
				bool prev = true;
				bool tr = false, fa = false;
				for (int a : A[i])
				{
					bool cur = eval(a, t);
					if (cur && !prev) {
						good = false;
						break;
					}
					(cur ? tr : fa) = true;
					prev = cur;
				}
				good &= tr && fa;
				break;
			}
		}
		//cerr << good << endl;
		if (good) {
			for (int typ : t)
				cout << NAMES[typ] << endl;
			return 0;
		}
	} while (inc());
	//cerr << "fail?" << endl;
}