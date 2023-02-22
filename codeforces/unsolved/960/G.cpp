#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <math.h>
#include <numeric>
#include <queue>
#include <ranges>
#include <vector>

// Floor of square root
constexpr unsigned isqrt(unsigned x)
{
	unsigned y = 0;
	while (y * y <= x)
		y++;
	return y - 1;
}

// Note that (MOD - 1)'s prime factorization only has primes up to 17.
constexpr unsigned MOD = 998244353;
constexpr unsigned SQRTP = isqrt(MOD);
constexpr unsigned MAXN = 1e5;

// Computes a^b mod MOD using binary exponentiation
constexpr unsigned modpow(unsigned a, unsigned b)
{
	unsigned ans = 1;
	for (; b; b /= 2, a = (uint64_t)a * a % MOD)
		if (b % 2)
			ans = (uint64_t)a * ans % MOD;
	return ans;
}

// Computes a^-1 mod MOD using binary exponentiation and Fermat's Little Theorem
constexpr unsigned modinv(unsigned a)
{
	return modpow(a, MOD - 2);
}

// Generate primes up to sqrt(MOD) using the Sieve of Eratosthenes. This is run at compile time.
// The return value indicates whether each number up to SQRT(MOD) is composite.
constexpr std::array<bool, SQRTP + 1> sieve()
{
	std::array<bool, SQRTP + 1> C{};
	for (unsigned p = 2; p <= SQRTP; p++)
	{
		if (C[p])
			continue;
		for (unsigned j = p * 2; j <= SQRTP; j += p)
			C[j] = true;
	}
	return C;
}

// For x <= sqrt(MOD), SIEVE[x] is true iff x is composite.
constexpr std::array<bool, SQRTP + 1> SIEVE = sieve();

// Number of primes up to sqrt(MOD)
constexpr unsigned PRIME_CT = size(SIEVE) - std::accumulate(begin(SIEVE), end(SIEVE), 0u);

// Generate array of primes up to sqrt(MOD) from SIEVE.
constexpr std::array<unsigned, PRIME_CT> primes()
{
	std::array<unsigned, PRIME_CT> P{};
	std::ranges::copy_if(std::ranges::iota_view(0u, SQRTP + 1), begin(P), [](int p) { return !SIEVE[p]; });
	return P;
}

// Primes up to sqrt(MOD)
std::array<unsigned, PRIME_CT> PRIMES = primes();

//int main() {}



/*

// The prime factorization of MOD-1 in (prime, multiplicity) pairs
vector<pair<int, int>> PFAC;
// All divisors of MOD-1
vector<int> DIV;
// Maps divisors x to numbers of order x in the multiplicative group mod MOD (or 0 for non-divisors)
unordered_map<int, int> ROOT1;

// The smallest prime factor of every number up to MAXN * 2 + 1
vector<int64_t> MINP;

// Factorials modulo MOD
vector<int64_t> FAC;


constexpr void precomp()
{


	// Factorize MOD-1 into primes with multiplicity by trial division using the list of primes computed earlier.
	int64_t n = MOD - 1;
	for (int64_t i : PRIMES)
	{
		if (i * i > n)
			break;
		if (n % i == 0)
		{
			PFAC.emplace_back(i, 1);
			n /= i;
			while (n % i == 0)
			{
				PFAC.back().second++;
				n /= i;
			}
		}
	}
	if (n > 1)
	{
		if (PFAC.back().first == n)
			PFAC.back().second++;
		else
			PFAC.emplace_back(n, 1);
	}

	vector<int> idx(PFAC.size(), 0);
	// Increments the multiindex idx representing one combination of prime factors.
	const auto inc = [&]()
	{
		bool ans = false;
		for (int i = 0; i < PFAC.size(); i++)
		{
			if (++idx[i] > PFAC[i].second)
				idx[i] = 0;
			else
			{
				ans = true;
				break;
			}
		}
		return ans;
	};

	// Iterate over all combinations of prime factors of MOD-1 to compute MOD-1's divisors
	do
	{
		int64_t div = 1;
		for (int i = 0; i < PFAC.size(); i++)
			div *= modpow(PFAC[i].first, idx[i]);
		DIV.push_back(div);
	} while (inc());

	// Sort the list of divisors
	sort(DIV.begin(), DIV.end());

	// Find a primitive root mod MOD, i.e. a number p such that p^n is congruent to 1 mod MOD only when MOD-1 divides n.
	// (When MOD-1 does divide n, p^n must be congruent to 1 by Fermat's Little Theorem.)
	// This is done by checking all primes until one is a primitive root; this usually only takes a few tries.
	int64_t proot = 0;
	for (int64_t p : PRIMES)
	{
		bool isPRoot = true;
		// p's order (the smallest positive n such that p^n is congruent to 1 mod MOD) must be a divisor of MOD-1. This follows from Lagrange's theorem.
		// If p is not a primitive root, then its order must be a proper divisor of MOD-1; equivalently, it must be a divisor of (MOD-1)/q for some prime factor q of MOD-1.
		// This is because a proper divisor must be missing at least one prime factor of MOD-1; otherwise, it would equal MOD-1.
		// Thus, p is a primitive root iff, for each prime factor q of MOD-1, p^((MOD-1)/q) is not congruent to 1 mod MOD.
		for (int i = 0; i < PFAC.size(); i++)
			if (modpow(p, (MOD - 1) / PFAC[i].first) == 1)
			{
				isPRoot = false;
				break;
			}
		if (isPRoot)
		{
			proot = p;
			break;
		}
	}
	assert(proot != 0);

	// Let p be a primitive root (computed earlier) and let a, b be a pair of corresponding divisors of MOD-1, so a*b = MOD-1.
	// Then, p^(MOD-1) = p^(a*b) = (p^a)^b is congruent to 1 mod MOD, but for 0 < c < b, 0 < a*c < a*b = MOD-1, so (p^a)^c = p^(a*c) is not congruent to 1.
	// This means p^a has order b = (MOD - 1) in the multiplicative group mod MOD.
	// Here, numbers of order div are computed for every divisor div of MOD-1.
	for (int64_t div : DIV)
		ROOT1[(MOD - 1) / div] = modpow(proot, div);

	// For each prime p, find all numbers up to MAXN * 2 + 1 having p as their smallest prime factor using a modified Sieve of Eratosthenes
	MINP.resize(MAXN * 2 + 1, 0);
	for (int64_t p : PRIMES)
		for (int64_t i = p; i <= MAXN * 2; i += p)
			if (MINP[i] == 0)
				MINP[i] = p;

	// Compute all factorials as modular prefix products
	FAC.resize(MAXN * 2 + 1);
	FAC[0] = 1;
	for (int64_t i = 1; i <= MAXN * 2; i++)
		FAC[i] = FAC[i - 1] * i % MOD;
}

// Rounds n up to a divisor of MOD-1.
// The vector DIV is sorted, so this function uses binary search.
inline int64_t ruDiv(int64_t n)
{
	int64_t lo = 0, hi = DIV.size() - 1;
	while (lo < hi)
	{
		int64_t mid = (lo + hi) / 2;
		int64_t div = DIV[mid];
		if (div < n)
			lo = mid + 1;
		else
			hi = mid;
	}
	return DIV[(lo + hi) / 2];
}

// Computes the Number-Theoretic Transform (the rough equivalent of the Discrete Fourier Transform for finite fields) of X, which has size n dividing MOD-1.
// Here, a variant of the Cooley-Turkey algorithm is used that operates on the finite field of size MOD instead of the field of complex numbers.
// The Discrete Fourier Transform computes the values of an n-th degree polynomial at the n complex n-th roots of unity (conventionally powers of e^(2*pi*i/n)).
// Analogously, the Number-Theoretic Transform computes the values of an n-th degree polynomial mod MOD at n modular n-th roots of unity (given a primitive root r mod MOD, powers of r^((MOD-1)/n)).
// Note that these roots of unity are unique. As shown earlier, r^((MOD-1)/n) has order n, so the cyclic subgroup it generates has n distinct elements, which are all n-th roots of unity.
// For n = 1, this is trivial; the polynomial has one term, which is constant, so its value is just that constant and we can simply return the input.
// For larger n, let a be some prime dividing n (here, the smallest such prime) and let b = n / a.
// Then, let w be the selected primitive root to the (MOD-1)/n-th power, which has order n, so w_i := w^i is a distinct n-th root of unity for all integer i from 0 to n-1.
// The problem is then to evaluate the polynomial with coefficients given by X at w_i, Y[i] := X[0]*w_i^0 + X[1]*w_i^1 + ... + X[n-1]^w_i^(n-1), for all integer i from 0 to n-1.
// Grouping terms by their exponents mod a, and factoring out w_i to those exponents mod a, Y[i] becomes
// w_i^0*(X[0]*w_i^0 + X[a]*w_i^a + ... + X[n-a]*w_i^(n-a)) + w_i^1*(X[1]*w_i^0 + X[a+1]*w_i^a + ... + X[n-a+1]*w_i^(n-a)) + ... + w_i^(a-1)*(X[a-1]*w_i^0 + X[2*a-1]*w_i^a + ... + X[n-1]*w_i^(n-a)).
// Besides the factored-out powers of w_i, each of the a collections of b terms is a polynomial in w_i^a = ((w^((MOD-1)/n))^i)^a = (w^((MOD-1)*a/n))^i = (w^((MOD-1)/b))^i.
// This is the i-th of the b-th roots of unity, so each collection of terms can be computed for all values of i from 0 to n with a recursive Number-Theoretic Transforms of size b.
// The results can then added for each resulting term in O(n*a) = O(b*a^2) time. Since a is always a prime in this implementation, and MOD-1 is only divisible by small primes, this is okay.
// Note that, for the same reason as in the Discrete Fourier Transform, the Inverse Number-Theoretic Transform may be computed by nearly the same algorithm.
// The only necessary changes are choosing a primitive root equal to the multiplicative inverse of the primitive root used in the normal Number-Theoretic Transform and dividing by n at the end.
template<bool inverse = false, bool top = true>
inline vector<int64_t> ntt(const vector<int64_t>& X)
{
	if (X.size() <= 1)
		return X;
	int64_t n = X.size();
	int64_t a = MINP[n];
	int64_t b = n / a;
	// Split the input polynomial into collections of terms by the index mod a.
	vector<vector<int64_t>> XX(a, vector<int64_t>(b));
	for (int64_t i = 0; i < a; i++)
		for (int64_t j = 0; j < b; j++)
			XX[i][j] = X[i + j * a];
	// Compute the NTT of each collection of terms recursively.
	vector<vector<int64_t>> YY(a);
	if (b == 1)
		YY = XX;
	else
		for (int64_t i = 0; i < a; i++)
			YY[i] = ntt<inverse, false>(XX[i]);
	vector<int64_t> Y(n, 0);
	int64_t wn = ROOT1[n];
	// Use the multiplicative inverse of the root of unity for the inverse transform
	if (inverse)
		wn = modinv(wn);
	// Combine recursively computed terms into the final answer
	// The outer loop iterates over which polynomial is being computed
	for (int64_t i = 0, wni = 1; i < n; i++, wni = wni * wn % MOD)
		// The inner loop iterates over which collection of terms is being added to the result
		for (int64_t j = 0, wnij = 1; j < a; j++, wnij = wnij * wni % MOD)
			// The j-th collection of terms is computed in the recursive NTT on coefficients with an index of j mod a using the (i%b)-th of the b-th roots of unity.
			// This is because, if i%b=p and i/b=q, all terms within the collection are some power of w_i^a = w^((MOD-1)*i*a/n) = w^((MOD-1)/b*i) = w^((MOD-1)/b*(p+b*q)) = ((MOD-1)*p/b + (MOD-1)*q).
			// For multiplication mod MOD, exponents operate mod MOD-1 by Fermat's Little Theorem, so the MOD-1*q term in the exponent can be ignored and only p=i%b is relevant.
			Y[i] = (Y[i] + YY[j][i % b] * wnij) % MOD;
	// For the top recursive level of the inverse transform, divide by n.
	if (inverse && top)
	{
		int64_t inv = modinv(n);
		for (int64_t& y : Y)
			y = y * inv % MOD;
	}

	return Y;
}

// Inverse transform convenience method
inline vector<int64_t> intt(const vector<int64_t>& X)
{
	return ntt<true>(X);
}

// Convolution mod MOD using multiplication of NTT's
inline vector<int64_t> conv(vector<int64_t> A, vector<int64_t> B)
{
	int64_t a = A.size(), b = B.size();
	// The result can have up to a+b-1 values, and the NTT must operate on arrays with size dividing MOD-1, so the size is rounded up to the next divisor.
	// MOD-1 is divisible by many small primes, so this will not be too much larger than a+b-1.
	int64_t n = ruDiv(a + b - 1);
	// 0-pad A and B
	A.resize(n, 0);
	B.resize(n, 0);
	// Compute NTT's
	A = ntt(A);
	B = ntt(B);
	// Elementwise multiplication of NTT's corresponds with convolution of the original arrays (just like DFT's)
	vector<int64_t> C(n);
	for (int64_t i = 0; i < n; i++)
		C[i] = A[i] * B[i] % MOD;
	// Compute the convolution from its NTT
	C = intt(C);
	// Remove extra space needed to ensure a size dividing MOD-1.
	C.resize(a + b - 1);
	return C;
}

// Unsigned Stirling numbers of the first kind.
inline int64_t S1(int64_t n, int64_t k)
{
	// Base cases: if 0<k<=n is not true, S1 returns 0, unless k = n = 0, where S1 returns 1.
	if (k == 0)
		return n == 0;
	if (k < 0 || k > n)
		return 0;

	// The unsigned Stirling numbers of the first kind are the coefficients of x's n-th rising factorial.
	// Specifically, the x^k term of the polynomial x * (x+1) * ... * (x+n-1) has coefficient S1(n, k).
	// We can compute this polynomial's coefficients by starting with these linear factors and multiplying them using NTT-based convolution, as rounding errors from DFT-based convolution are large.
	// Using a queue, this can be done so polynomials being convolved are of similar degrees, preventing inefficiency that would be caused by computing large NTT's on polynomials with few terms.
	deque<vector<int64_t>> Q;
	// Add all factors to the queue.
	for (int i = 0; i < n; i++)
	{
		// Add a new factor of degree 1.
		Q.push_back(vector<int64_t>(2));
		// Set its constant term to i and its linear term to x.
		Q.back()[0] = i;
		Q.back()[1] = 1;
	}
	// Repeatedly multiply the two smallest elements on the queue and put the result back on the queue until only one polynomial remains.
	while (Q.size() > 1)
	{
		const vector<int64_t>& A = Q[0];
		const vector<int64_t>& B = Q[1];
		vector<int64_t> C = conv(A, B);
		Q.push_back(move(C));
		Q.pop_front();
		Q.pop_front();
	}
	return Q.front()[k];
}

// Binomial coefficients mod MOD computed directly from factorials.
inline int64_t modncr(int64_t n, int64_t r)
{
	if (n < 0 || r < 0 || r > n)
		return 0;
	int64_t num = FAC[n], den = FAC[n - r] * FAC[r] % MOD;
	return num * modinv(den) % MOD;
}

// The solution can be computed as S1(N-1, (A-1) + (B-1)) * nCr((A-1) + (B-1), A-1).
// I do not have a full proof for this formula, as I found it by trying lots of examples, but it does make some intuitive sense.
// The maximum-weight bag will be picked up in both directions. Additionally, no bags beyond it will be picked up.
// This means the other bags picked up from the left and right are to the left and right of this maximum, respectively.
// Consider the bags with the maximum weight bag removed. Then, of the N-1 bags, choose a permutation with (A-1) + (B-1) records from left to right.
// There are S1(N-1, (A-1) + (B-1)) ways to do this, as unsigned Stirling numbers of the first kind can be interpreted as counting permutations with a given number of records, not just cycles.
// (Source: https://oeis.org/A008275)
// A vague, hand-wavey way to get the correct formula is to then choose (B-1) of those records to be from the right instead of the left (the details of how to do this are unspecified).
// This gives a total of S1(N-1, (A-1) + (B-1)) * nCr((A-1) + (B-1), A-1) possible permutations of the bags.
// An inductive proof for this identity should also be fairly straightforward, but I did not use it to find the answer.
int main()
{
	precomp();
	int N, A, B;
	cin >> N >> A >> B;
	N--;
	A--;
	B--;
	int64_t s = S1(N, A + B);
	int64_t ncr = modncr(A + B, A);
	cout << s * ncr % MOD;
}*/