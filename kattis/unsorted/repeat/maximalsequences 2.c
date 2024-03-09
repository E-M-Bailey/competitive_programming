#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

unsigned A[MAXN], I[MAXN], M[MAXN], *B[MAXN], C[MAXN], S[MAXN], Y[MAXN];

unsigned arena[MAXN];
unsigned *nxt = arena;
unsigned *balloc(unsigned sz)
{
	unsigned *ptr = nxt;
	nxt += sz;
	return ptr;
}

uint64_t BS[(1 << (31 - 6)) + 1];

#define test(i) (BS[(i) >> 6] & ((uint64_t)1 << (i)))
#define toggle(i) (BS[(i) >> 6] ^= (uint64_t)1 << ((i) & 0x3f))

#define P 300007

struct ent
{
	unsigned k, v;
	struct ent *p, *n;
};

struct ent H[P];
struct ent *front;

struct ent *get(unsigned k)
{
	unsigned i = k % P, d = 0;
	while (H[i].k && H[i].k != k)
		i = (i + ++d) % P;
	H[i].k = k;
	return H + i;
}

void pull_front(struct ent *e)
{
	if (front == e)
		return;
	if (e->p)
		e->p->n = e->n;
	if (e->n)
		e->n->p = e->p;
	e->p = NULL;
	e->n = front;
	if (front)
		front->p = e;
	front = e;
}

int SP[256];

#define BUFS (1u << 22)

char BUF[BUFS];
char *pos = BUF;

void init()
{
	SP['\0'] = SP[' '] = SP['\n'] = 1;
	fread(BUF, 1, BUFS, stdin);
}

void term()
{
	fwrite(BUF, 1, pos - BUF, stdout);
}

unsigned in()
{
	while (SP[*pos])
		pos++;
	unsigned ans = 0;
	do
		ans = 10 * ans + *pos - '0';
	while (!SP[*++pos]);
	return ans;
}

void out(unsigned x)
{
	char *st = pos;
	do
		*pos++ = x % 10 + '0';
	while (x /= 10);
	for (char *a = st, *b = pos; a < b;)
	{
		char temp = *a;
		*a++ = *--b;
		*b = temp;
	}
	*pos++ = '\n';
}

int main()
{
	init();

	unsigned n = in();
	for (unsigned i = 0; i < n; i++)
		A[i] = in();
	unsigned q = in();
	for (unsigned i = 0; i < q; i++)
	{
		I[i] = in();
		M[i] = in();
		I[i]--;
		C[I[i]]++;
		B[i] = balloc(M[i]);
		for (unsigned j = 0; j < M[i]; j++)
			B[i][j] = in();
	}
	(front = get(1u << 31))->v = n + 1;

	for (unsigned i = 1; i < n; i++)
		C[i] += C[i - 1];
	for (unsigned i = q; i-- > 0;)
		S[--C[I[i]]] = i;

	unsigned qi = q;
	for (unsigned i = n; i-- > 0;)
	{
		struct ent *e = get(A[i] + 1);
		e->v = i + 1;
		pull_front(e);
		unsigned qs;
		while (qi > 0 && I[(qs = S[qi - 1])] == i)
		{
			qi--;
			unsigned m = M[qs];
			for (unsigned bi = 0; bi < m; bi++)
				toggle(B[qs][bi]);
			unsigned lim = i;
			for (struct ent *f = front;; f = f->n)
			{
				lim = f->v - 1;
				if (!test(f->k - 1))
					break;
			}
			for (unsigned bi = 0; bi < m; bi++)
				toggle(B[qs][bi]);
			Y[qs] = lim - i;
		}
	}

	pos = BUF;

	for (unsigned i = 0; i < q; i++)
		out(Y[i]);
	term();
}