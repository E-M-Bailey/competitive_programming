#include <bits/stdc++.h>

using namespace std;

struct node;

int				 q;
int64_t			 m, S[2], s;
unique_ptr<node> ed;
int64_t			 steps(node const *a, node const *b);

pair<int64_t, int64_t> repr(bool side, int64_t pos)
{
	pos += side * S[0];
	return {pos % s, pos / s * 2 - side};
}
pair<bool, int64_t> rpos(int64_t bck, int64_t bpos)
{
	bool side = bpos % 2;
	return {side, (bpos + side) / 2 * s + bck - side * S[0]};
}

size_t constexpr ARENA_SIZE = 1 << 20;
node extern *PTR;
node		*FR[ARENA_SIZE];
node	   **FPTR = FR;

struct node
{
	node   *p = 0, *pp = 0, *c[2]{}, *par = 0;
	bool	flip = 0;
	int64_t val = 0, sum = 0;
	int64_t bck, bpos;
	int64_t haz = 0;
	node(int64_t b = 0, int64_t bp = 0) : bck(b), bpos(bp)
	{
		fix();
	}
	void fix()
	{
		val = sum = par ? steps(this, par) : 0;
		if (c[0])
		{
			c[0]->p = this;
			sum += c[0]->sum;
		}
		if (c[1])
		{
			c[1]->p = this;
			sum += c[1]->sum;
		}
	}
	void push()
	{
		if (flip)
		{
			flip = 0;
			swap(c[0], c[1]);
			if (c[0])
				c[0]->flip ^= 1;
			if (c[1])
				c[1]->flip ^= 1;
		}
	}
	int up()
	{
		return p ? p->c[1] == this : -1;
	}
	void rot(int i, int b)
	{
		int	  h = i ^ b;
		node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
		if ((y->p = p))
			p->c[up()] = y;
		c[i] = z->c[i ^ 1];
		if (b < 2)
		{
			x->c[h]		= y->c[h ^ 1];
			z->c[h ^ 1] = b ? x : this;
		}
		y->c[i ^ 1] = b ? this : x;
		fix();
		x->fix();
		y->fix();
		if (p)
			p->fix();
		swap(pp, y->pp);
	}
	void splay()
	{
		for (push(); p;)
		{
			if (p->p)
				p->p->push();
			p->push();
			push();
			int c1 = up(), c2 = p->up();
			if (c2 < 0)
				p->rot(c1, 2);
			else
				p->p->rot(c2, c1 != c2);
		}
	}
	node *first()
	{
		push();
		return c[0] ? c[0]->first() : (splay(), this);
	}

	static void *operator new(size_t)
	{
		return FPTR == FR ? PTR++ : *--FPTR;
	}
	static void operator delete(void *ptr)
	{
		*FPTR++ = (node *)ptr;
	}
};
char  BUF[ARENA_SIZE * sizeof(node)];
node *PTR = (node *)BUF;

node *access(node *u)
{
	u->splay();
	while (node *pp = u->pp)
	{
		pp->splay();
		u->pp = 0;
		if (pp->c[1])
			pp->c[1]->p = 0, pp->c[1]->pp = pp;
		pp->c[1] = u;
		pp->fix();
		u = pp;
	}
	return u;
}
bool connected(node *u, node *v)
{
	u = access(u)->first();
	return u == access(v)->first();
}
void make_root(node *u)
{
	access(u);
	u->splay();
	if (node *&l = u->c[0])
	{
		l->p = 0;
		l->flip ^= 1;
		l->pp = u;
		l	  = 0;
		u->fix();
	}
}
int64_t steps(node const *a, node const *b)
{
	auto [as, ap] = rpos(a->bck, a->bpos);
	auto [bs, bp] = rpos(b->bck, b->bpos);
	if (b == ed.get())
		bp = m;
	int64_t pcur = ap + a->haz, popp = pcur + S[!as];
	if (popp >= bp)
		return 1;
	int64_t scur = (bp - pcur + s - 1) / s * 2, sopp = (bp - popp + s - 1) / s * 2 + 1;
	return min(scur, sopp);
}
void link(node *u, node *v)
{
	make_root(u);
	u->pp  = v;
	u->par = v;
	u->fix();
}
void cut(node *u, node *v)
{
	make_root(v);
	u->splay();
	u->par = 0;
	if (u->pp)
		u->pp = 0;
	else
	{
		u->c[0] = v->p = 0;
		u->fix();
	}
}
void cut(node *u)
{
	if (u->par)
		cut(u, u->par);
}
void relink(node *u, node *v)
{
	cut(u);
	link(u, v);
}

unordered_map<int64_t, map<int64_t, unique_ptr<node>>> E;

// Add cloudless node if no node already present
node *node_at(bool side, int64_t pos)
{
	auto [bck, bpos] = repr(side, pos);
	if (pos >= m) // Off the end
		return ed.get();
	auto &EE = E[bck];
	auto  it = EE.find(bpos);
	if (it != end(EE)) // Already exists
		return it->second.get();

	node *nd = new node(bck, bpos);

	// Connect Forwards
	auto  itnxt = EE.upper_bound(bpos);
	node *nxt	= (itnxt == end(EE) ? ed : itnxt->second).get();
	link(nd, nxt);

	// Connect Backwards
	node *prv = itnxt == begin(EE) ? nullptr : prev(itnxt)->second.get();
	if (prv && prv->haz == 0)
		relink(prv, nd);

	// Add to E
	EE.emplace_hint(itnxt, bpos, nd);

	return nd;
}

void add_cloud(bool side, int64_t pos, int64_t haz)
{
	node *cur = node_at(side, pos), *nxt = node_at(!side, pos + haz + S[!side]);
	cur->haz = haz;

	relink(cur, nxt);
}
void del_cloud(bool side, int64_t pos)
{
	auto [bck, bpos] = repr(side, pos);
	auto &EE		 = E[bck];
	auto  itnxt		 = EE.upper_bound(bpos);
	node *nd = EE[bpos].get(), *nxt = (itnxt == end(EE) ? ed : itnxt->second).get();
	nd->haz = 0;
	relink(nd, nxt);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> q >> m >> S[0] >> S[1];
	s = S[0] + S[1];

	ed.reset(new node);
	node *st = node_at(0, 0);

	while (q--)
	{
		int		t;
		int64_t p, h;
		cin >> t;
		if (t == 1)
		{
			cin >> p >> h;
			add_cloud(0, p, h);
			add_cloud(1, p, h);
		}
		else
		{
			cin >> p;
			del_cloud(0, p);
			del_cloud(1, p);
		}
		make_root(ed.get());
		access(st);
		st->splay();
		cout << st->sum << '\n' << flush;
	}
}
