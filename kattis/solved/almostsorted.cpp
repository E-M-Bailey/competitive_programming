/*
BEGIN ANNOTATION:
PROBLEM URL: https://open.kattis.com/problems/almostsorted
TAGS: sorting, permutation, simulation
EXPLANATION:
To solve this problem, we will directly simulate the algorithm. In order to do this, we need to be able to efficiently
find where a given element will be moved to. To do this, first make a sorted copy of the array. Then, make a map from
the elements to their position in that array. That way, when processing an element, we know which index to swap it with
in O(1) (You could binary search the position in the sorted array instead.) Overall, this runs in Theta(n log n) time in
the worst case due to the sorting step, unless you use something like radix sort, in which case it runs in Theta(n).
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
	// Read input
	int n, q;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	cin >> q;

	// Create a sorted copy of A
	// This could be optimized to O(n) with radix sort
	vector<int> S = A;
	sort(begin(S), end(S));
	// Map each element to its index in sorted order
	unordered_map<int, int> I;
	for (int i = 0; i < n; i++)
		I[S[i]] = i;
	// Reference to q's final position in the sorted array
	int &aq = A[I[q]];

	// Swap index i with its element's sorted position until q is sorted
	for (int i = 0; aq != q;)
	{
		int &a = A[i];
		int &b = A[I[a]];
		swap(a, b);
		// If this index is now sorted, advance to the next one
		if (a == S[i])
			i++;
	}

	// Print the array
	for (int a : A)
		cout << a << ' ';
}
