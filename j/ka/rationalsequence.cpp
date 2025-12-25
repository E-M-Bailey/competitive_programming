// The idea is to go up the tree until you reach a left child, go up one more time, go down and right once, and descend left back
// to the same level you started at.
//
//         *
//      /     \ 
//    *         *
//     \       /
//      *     *
//       \   /
//        x y
//
// Notice that a node p/q is a left child iff p < q, so you could just ascend (subtract q from p) until p < q. However, this
// takes far too long with a fraction like 1/2000000000, so instead notice the number of steps upwards is just the number of times
// you can subtract q from p without resulting in a negative number, d = floor(p / q). The steps are:
// - p -= d * q:	go up d times
// - q -= p:		go up once
// - p += q:		go right once
// - q += d * p:	go left d times
//
// This still works when you start on the right spine of the tree, i.e. with a fraction of the form p/1. In that case, d = p, so:
// - p -= d * q:	go to 0/1
// - q -= p:		do nothing
// - p += q:		go to 1/1
// - q += d * p:	go to 1/(d + 1)
// The resulting fraction is 1/(p + 1), which is on the left spine one level lower than the node we started with.
// Note that in this case, since p can be up to 2^31-1, we need either 64-bit integers or 32-bit unsigned integers.
//
// Exercise: prove that gcd(p, q) stays the same after each step, so you don't have to simplify the resulting fraction.

#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n;
		string s;
		cin >> n >> s;
		s[s.find('/')] = ' ';
		istringstream strm(s);
		unsigned p, q;
		strm >> p >> q;

		unsigned d = p / q;
		p -= d * q;
		q -= p;
		p += q;
		q += d * p;
		cout << n << ' ' << p << '/' << q << '\n';
	}
}
