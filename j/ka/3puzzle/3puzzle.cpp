#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;

static constexpr string_view P[]{
	"12\n3-\n",
	"12\n-3\n",
	"-2\n13\n",
	"2-\n13\n",
	"23\n1-\n",
	"23\n-1\n",
	"-3\n21\n",
	"3-\n21\n",
	"31\n2-\n",
	"31\n-2\n",
	"-1\n32\n",
	"1-\n32\n",
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	char buf[6];
	ignore = ::read(STDIN_FILENO, buf, 6);
	auto pos = rng::find(P, string_view(buf, 6)) - begin(P);
	cout << min(pos, 12 - pos);
}
