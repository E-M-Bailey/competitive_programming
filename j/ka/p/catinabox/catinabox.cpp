#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int h, w, l, c;
	cin >> h >> w >> l >> c;
	int a = h * w * l;
	cout << (c < a ? "SO MUCH SPACE" : c == a ? "COZY" : "TOO TIGHT");
}
