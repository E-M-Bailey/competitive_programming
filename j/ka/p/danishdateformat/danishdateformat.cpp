#include "template.hpp"

using namespace std;
using namespace abbrev;

static constexpr string_view M[]{ "januar", "februar", "marts", "april", "maj", "juni", "juli", "august", "september", "oktober", "november", "december" };

int main()
{
	str s;
	cin >> s;
	cout << stoi(s.substr(3, 2)) << ". " << M[stoi(s.substr(0, 2)) - 1] << ' ' << s.substr(6);
}
