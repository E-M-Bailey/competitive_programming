/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/learningtocode
TAGS: recursion, recursive descent, parsing, string, string parsing, ast, abstract syntax tree, pruning
EXPLANATION:
Let n <= 10000 be the size of the input and m = 10000 be the bound on size of the output excluding new lines in both cases.
One solution is to eagerly evaluate every string when reading the input.

However, there is a problem with this approach: it is possible to create a variable consisting of two copies of another
variable, so the length of the variables can grow exponentially.

However, notice that if a variable has length > m, it cannot be relevant for the output, so we don't need
to compute it. Thus, we can optimize the above algorithm by not parsing any strings which contain more than m characters.

A expression for a variable can be evaluated in time proportional to that variable's length. By additionally stopping early
if and when that length exceeds m, the time complexity of evaluating a variable's expression is proportional to the minimum
of its length and m, which is O(m). Thus, the complexity of evaluating all m variables is O(m n), which is fast enough.
*/

#include <bits/stdc++.h>

using namespace std;

unordered_map<string, string> D;

// Parse the expression starting at it and ending at last and append the value onto val.
// it is placed after the end of the parsed expression (at the closing "}" or ";").
// If the value's length would exceed m, returns false instead.
bool parse_expr(string &val, string::const_iterator &it, string::const_iterator last)
{
	if (*it == '"') // string literal
	{
		it++; // skip the opening quote
		while (*it != '"') // until the closing quote:
		{
			if (val.size() >= 10000) // if the new lenght would exceed m, return false.
				return false;
			val += *it; // append the current character
			it++; // skip the added character
		}
		it++; // skip the closing quote
	}
	else if (*it == '`') // template literal
	{
		it++; // skip the opening backtick
		while (*it != '`') // until the closing backtick:
		{
			if (it + 1 != last && *(it + 1) == '{') // if a sub-expression starts here:
			{
				it += 2; // skip "${"
				// parse the sub-expression or return false if the value's length would exceed m
				if (!parse_expr(val, it, last))
					return false;
			}
			else
			{
				if (val.size() >= 10000) // return false if the value's length would exceed m
					return false;
				val += *it; // add the current character
			}
			it++; // skip "}" or the added character
		}
		it++; // skip the closing backtick
	}
	else // variable name
	{
		auto jt = it; // find the end of the variable name
		while (jt != last && (('a' <= *jt && *jt <= 'z') || *jt == '_'))
			jt++;
		auto it_val = D.find(string(it, jt)); // find the variable's value
		// if the variable's value is longer than m, or the length of the new combined value is longer than m, return false
		if (it_val == D.end() || val.size() + it_val->second.size() > 10000)
			return false;
		// append the variable's value
		val += it_val->second;
		// skip the variable name
		it = jt;
	}
	// parsing succeeded, so return true
	return true;
}

int main()
{
	for (string line, val; getline(cin, line), line[0] != 'e';)
	{
		val.clear();
		if (line[0] == 'v') // var
		{
			auto it = cbegin(line) + line.find(' ', 4); // skip "var " and the variable name
			string name(cbegin(line) + 4, it); // variable name
			it += 3; // skip " = "
			if (parse_expr(val, it, cend(line) - 1)) // if the expression's value is sufficiently short:
				D.emplace(move(name), move(val)); // assign the variable to that value
		}
		else // print
		{
			auto it = cbegin(line) + 6; // skip "print "
			parse_expr(val, it, cend(line) - 1); // parse the expression, which is guaranteed to be short enough
			cout << val << '\n'; // print its value
		}
	}
}
