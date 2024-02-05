#pragma GCC optimize("Ofast")

#include <unistd.h>

#define MAXN 200000u
// Offset to make q and everything in A nonnegative
#define OFF (1u << 31u)
#define RADIX (1u << 16u)
#define LO(x) ((x) & 0xffffu)
#define HI(x) ((x) >> 16u)
#define MAXN_DIG 6u  // i.e. 100000
#define MAXA_DIG 11u // i.e. -1000000000
//             n          ws            (A[i]       ws)...  q          ws
#define BUFS ((MAXN_DIG + 1u) + (MAXN * (MAXA_DIG + 1u)) + (MAXA_DIG + 1u))

// I/O buffer and pointers
char BUF[BUFS], *in = BUF, *out = BUF;
// Given array with each element increased by OFF
unsigned A[MAXN], *B;
// Counting sort aux array
unsigned C[RADIX], *const D = C + RADIX;
// I1[i] is the original index of the ith element in sorted order
unsigned I1[MAXN], *J1;
// I2[i] is the sorted index of the ith element in the original array
unsigned I2[MAXN], *J2;
// n and q from the input with q increased by OFF
unsigned n = 0, q = 0;
// Pointer to q's final position in A
unsigned *qq;
// Accumulator for counting sort
unsigned tot;
// Miscellaneous boolean variable used for I/O
unsigned bl;
// Temporary pointer/indices/value used in loopss
unsigned *a, i, j, temp;

int main()
{
	// Input
	read(STDIN_FILENO, BUF, BUFS);
	do
		n = n * 10u + *in - '0';
	while (*++in != '\n');
	B = A + n;
	J1 = I1 + n;
	J2 = I2 + n;
	// map q all values in a via x -> 2^31 + |x| for x >= 0 and 2^31 - |x| for x < 0
	for (a = A; a != B - 1u; ++a)
	{
		++in;
		in += bl = *in == '-';
		do
			*a = *a * 10u + *in - '0';
		while (*++in != ' ');
		if (bl) *a = OFF - *a;
		else *a = OFF + *a;
	}
	++in;
	in += bl = *in == '-';
	do
		*a = *a * 10u + *in - '0';
	while (*++in != '\n');
	if (bl) *a = OFF - *a;
	else *a = OFF + *a;
	++in;
	in += bl = *in == '-';
	do
		q = q * 10u + *in - '0';
	while (*++in != '\n');
	if (bl) q = OFF - q;
	else q = OFF + q;

	// Counting sort by low 16 bits
	for (a = A; a != B;) ++C[LO(*a++)];
	tot = C[0];
	for (a = C; ++a != D;) *a = tot += *a;
	for (i = n; i--;) I1[--C[LO(A[i])]] = i;
	// Reset C
	for (a = C; a != D;) *a++ = 0u;
	// Counting sort by high 16 bits
	for (a = A; a != B;) ++C[HI(*a++)];
	tot = C[0];
	for (a = C; ++a != D;) *a = tot += *a;
	for (a = J1; a-- != I1;) I2[*a] = --C[HI(A[*a])];
	// Calculate the pointer qq to the entry in A where q will end up
	for (i = 0; A[i] != q;) ++i;
	qq = A + I2[i];
	// Simulate the algorithm
	for (i = 0; *qq != q;)
	{
		// Skip positions which are already sorted
		while (i == (j = I2[i])) ++i;
		// Swap I2[i] with I2[j]
		I2[i] = I2[j];
		I2[j] = j;
		// Swap A[i] with A[j]
		temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	// Output
	for (a = A; a != B;)
	{
		// Map A[i] + OFF back to |A[i]| and print a negative sign if A[i] < 0
		if (*a & OFF)
			*a = *a - OFF;
		else
		{
			*out++ = '-';
			*a = OFF - *a;
		}

		if ((bl = *a >= 1000000000u))
		{
			*out++ = (char)(*a / 1000000000u + '0');
			*a %= 1000000000u;
		}
		if ((bl |= *a >= 100000000u))
		{
			*out++ = (char)(*a / 100000000u + '0');
			*a %= 100000000u;
		}
		if ((bl |= *a >= 10000000u))
		{
			*out++ = (char)(*a / 10000000u + '0');
			*a %= 10000000u;
		}
		if ((bl |= *a >= 1000000u))
		{
			*out++ = (char)(*a / 1000000u + '0');
			*a %= 1000000u;
		}
		if ((bl |= *a >= 100000u))
		{
			*out++ = (char)(*a / 100000u + '0');
			*a %= 100000u;
		}
		if ((bl |= *a >= 10000u))
		{
			*out++ = (char)(*a / 10000u + '0');
			*a %= 10000u;
		}
		if ((bl |= *a >= 1000u))
		{
			*out++ = (char)(*a / 1000u + '0');
			*a %= 1000u;
		}
		if ((bl |= *a >= 100u))
		{
			*out++ = (char)(*a / 100u + '0');
			*a %= 100u;
		}
		if ((bl |= *a >= 10u))
		{
			*out++ = (char)(*a / 10u + '0');
			*a %= 10u;
		}
		*out++ = (char)(*a++ + '0');
		*out++ = ' ';
	}
	write(STDOUT_FILENO, BUF, out - BUF);
}
