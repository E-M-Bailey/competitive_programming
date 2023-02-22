#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct node
{
	array<node*, 2> ch;
	node* p;
	T key;

	node(T key = T{}) :
		ch{},
		p{},
		key(key)
	{}

	bool dir()
	{
		return p->ch[1] == this;
	}

	void attach(bool d, node* n)
	{
		ch[d] = n;
		if (n)
			n->p = this;
	}

	void rotate()
	{
		if (!p)
			return;
		node* P = p;
		int d = dir();
		if (P->p)
			P->p->attach(P->dir(), this);
		P->attach(d, ch[!d]);
		attach(!d, this);
	}

	node* splay()
	{
		while (p && p->p)
		{
			if (p->dir() == dir())
				p->rotate();
			else
				rotate();
			rotate();
		}
		rotate();
		return this;
	}

	node* extremum(int d)
	{
		node* n = ch[d], p = this;
		while (n)
		{
			p = n;
			n = n->ch[d];
		}
		return n;
	}

	friend node* join(node* l, node* r)
	{
		if (!l)
			return r;
		node* e = l->extremum(1);
		e->splay()->attach(1, r);
		return e;
	}

	friend node* orphan(node* n)
	{
	    if (n)
            n->p = nullptr;
	}
};

template<typename T>
struct splay_tree
{
	node<T>* root;
	size_t s;

	bool empty()
	{
		return !s;
	}
	size_t size()
	{
		return s;
	}

	node* splay(node* n)
	{
		if (n)
			root = n->splay();
		return n;
	}

private:
	node* insert_point(T key)
	{
		node *n = root, *p = nullptr;
		while (n)
		{
			p = n;
			if (key < n->key)
				n = n->ch[0];
			else if (n->key < key)
				n = n->ch[1];
			else
				return n;
		}
		return p;
	}

public:
	node* find(T key)
	{
		node* ans = splay(insert_point(key));
		if (ans && ans->key == key)
			return ans;
		else
			return nullptr;
	}

	pair<node*, bool> insert(T key)
	{
		if (empty())
		{
			size++;
			return root = new node(key);
		}
		node* n = insert_point(key);
		if (n->key == key)
			return make_pair(splay(n), false);
		size++;
		node* c = new node(key);
		n->attach(n->key < key, c);
		return make_pair(splay(c), true);
	}

	bool erase(T key)
	{
		node* n = insert_point(key);
		if (n->key == key)
		{
			erase(n);
			return true;
		}
		else
		{
			splay(n);
			return false;
		}
	}

	void erase(node* n)
	{
		if (!n)
			return;
		splay(n);
		root = join(orphan(n->ch[0]), orphan(n->ch[1]));
		delete n;
		size--;
	}

    void join(splay_tree ST)
    {
        size += ST.size();
        root = join(root, ST.root);
    }
};

void go()
{

}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		freopen(argv[1],"r",stdin);
		freopen(argv[2],"w",stdout);
	}

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	go();
}
