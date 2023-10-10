#include <bits/stdc++.h>
using namespace std;
typedef bitset<1 << 20> state;
vector<string> tokens;
int k = 0;
char vars[20];
int ids[128];
state var_st[20];
state parse_and(char const *&ptr);
state parse_not(char const *&ptr);
state parse_atom(char const *&ptr);
state parse_or(char const *&ptr)
{
	state ans = parse_and(ptr);
	while (*ptr == '|')
	{
		ptr++;
		ans |= parse_and(ptr);
	}
	return ans;
}
state parse_and(char const *&ptr)
{
	state ans = parse_not(ptr);
	while (*ptr == '&')
	{
		ptr++;
		ans &= parse_not(ptr);
	}
	return ans;
}
state parse_not(char const *&ptr)
{
	return *ptr == '~' ? ~parse_not(++ptr) : parse_atom(ptr);
}
state parse_atom(char const *&ptr)
{
	state ans = *ptr == '(' ? parse_or(++ptr) : var_st[ids[(int)*ptr]];
	ptr++;
	return ans;
}

void run(vector<string>::const_iterator &it, state st)
{
	for (;; it++)
	{
		if (*it == "if")
		{
			char const *ptr = (++it)->c_str();
			auto cond = parse_or(ptr);
			run(it += 2, st & cond);
			if (*it == "else")
				run(++it, st & ~cond);
		}
		else if (*it == "checkpoint")
		{
			cout << '>';
			if (st.none())
				cout << "unreachable\n";
			else
			{
				for (int i = 0; i < k; i++)
				{
					auto filt = var_st[i] & st;
					if (filt == st)
						cout << vars[i];
					else if (filt.none())
						cout << char(vars[i] | 32);
				}
				cout << '\n';
			}
		}
		else
			break;
	}
}

int main()
{
	{
		stringstream strm;
		strm << cin.rdbuf();
		string token;
		while (strm >> token)
			tokens.push_back(move(token));
		tokens.push_back("end");
	}

	for (string const &token : tokens)
		for (char c : token)
			if (isupper(c) && find(vars, vars + k, c) == vars + k)
				vars[k++] = c;
	sort(vars, vars + k);
	for (int i = 0; i < k; i++)
		ids[(int)vars[i]] = i;

	for (int i = 0; i < k; i++)
		for (int j = 0; j < (1 << k); j++)
			var_st[i][j] = (1 << i) & j;

	state st{};
	st.set();
	st >>= (1 << 20) - (1 << k);
	auto it = cbegin(tokens);
	run(it, st);
}