#include <bits/stdc++.h>

using namespace std;
namespace rg = ranges;
namespace vw= views;
using namespace std::placeholders;

int main()
{
	cout << map<int, const char*>{ { -1, "Nekad" }, { 0, "Lagom" }, { INT_MAX, "Usch, vinst" } }.lower_bound(rg::fold_left(vw::istream<string>(cin) | vw::stride(2) | vw::drop(1) | vw::transform(bind((int(*)(const string&, size_t*, int))&stoi, _1, nullptr, 10)), 0, plus<>{}))->second;
}
