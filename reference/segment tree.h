#ifndef SEGMENT_TREE_H_INCLUDED
#define SEGMENT_TREE_H_INCLUDED

#ifndef TEMPLATE_H_INCLUDED
#include "template.h"
#endif // TEMPLATE_H_INCLUDED

template<typename T, typename Op = plus<T>>
class segtree
{
private:
	size_t _size;
	vector<vector<T>> _data;
	Op _op;
	T _id;

public:
	segtree(vector<T>&& leaves, const Op& op = Op{}, const T& id = T{}) :
		_size(rup2(leaves.size())),
		_data{leaves},
		_op(op),
		_id(id)
	{
		_data.back().resize(_size, _id);
		while (_data.back().size() > 1)
		{
		    _data.reserve(_data.size() + 1);
			vector<T>& prev = _data.back();
			size_t n = prev.size() / 2;
			_data.emplace_back(n);
			for (size_t i = 0; i < n; i++)
				_data.back()[i] = _op(prev[2 * i], prev[2 * i + 1]);
		}
		reverse(_data.begin(), _data.end());
	}

	segtree(const vector<T>& leaves, const Op& op = Op{}, const T& id = T{}) :
		segtree(vector<T>(leaves), op, id)
	{}

	template<typename It>
	segtree(It first, It last, const Op& op = Op{}, const T& id = T{}) :
		segtree(vector<T>(first, last), op, id)
	{}

	segtree(size_t size, const Op& op = Op{}, const T& id = T{}) :
		segtree(vector<T>(size, id), op, id)
	{}

	segtree(const Op& op = Op{}, const T& id = T{}) :
		segtree(vector<T>(1, id), op, id)
	{}

	size_t size() const
	{
	    return size;
	}

	vector<vector<T>>& data()
	{
	    return _data;
	}

	const vector<vector<T>>& data() const
	{
	    return _data;
	}

	const vector<vector<T>>& leaves() const
	{
	    return _data.back();
	}

	const Op& op() const
	{
	    return _op;
	}

	const T& id() const
	{
	    return _id;
	}

	const T& operator[](size_t idx) const
	{
	    return _data.back()[idx];
	}

private:
	T query(size_t l, size_t r, size_t nl, size_t nr, size_t i, size_t j) const
	{
		l = max(l, nl);
		r = min(r, nr);
		if (l >= r)
			return _id;
		else if (l == nl && r == nr)
			return _data[i][j];
		else
		{
			size_t mid = (nl + nr) / 2;
			return _op(query(l, r, nl, mid, i + 1, j * 2), query(l, r, mid, nr, i + 1, j * 2 + 1));
		}
	}

public:
	T query(size_t l, size_t r) const
	{
	    return query(l, r, 0, _size, 0, 0);
	}

private:
    void update(size_t idx, size_t i, const T& val)
    {
        if (i == _data.size() - 1)
            _data.back()[idx] = val;
        else
        {
            update(idx, i + 1, val);
            size_t j = idx >> _data.size() - 1 - i;
            _data[i][j] = _op(_data[i + 1][j * 2], _data[i + 1][j * 2 + 1]);
        }
    }

public:
    void update(size_t idx, const T& val)
    {
        update(idx, 0, val);
    }
};

/*
struct l_segtree
{
	int n;
	vvnode data;

	l_segtree(const vim& X) :
		n(rup2(X.size()))
	{
		data.emplace_back();
		for (im x : X)
			data.back().emplace_back(x);
		data.back().resize(n);

		while (data.back().size() > 1)
		{
			vnode next;
			for (int i = 0; i < data.back().size(); i += 2)
				next.emplace_back(data.back()[i].x + data.back()[i + 1].x);
			data.push_back(move(next));
		}

		reverse(ALL(data));
	}

private:
	void push_down(int i, int j)
	{
		node& c = data[i][j];
		c.x = c.val();
		if (i < data.size() - 1)
		{
			node &l = data[i + 1][j * 2], &r = data[i + 1][j * 2 + 1];
			l.f = c.f(l.f);
			r.f = c.f(r.f);
		}
		c.f = func();
	}

	void update(int l, int r, int nl, int nr, int i, int j, func f)
	{
		l = max(l, nl);
		r = min(r, nr);
		node& c = data[i][j];
		if (l > r)
			return;
		if (l == nl && r == nr)
		{
			c.f = f(c.f);
			return;
		}

		int nm = (nl + nr) / 2;
		node &L = data[i + 1][j * 2], &R = data[i + 1][j * 2 + 1];

		push_down(i, j);
		update(l, r, nl, nm, i + 1, j * 2, f);
		update(l, r, nm + 1, nr, i + 1, j * 2 + 1, f);
		c.x = L.val() + R.val();
	}

	im query(int l, int r, int nl, int nr, int i, int j)
	{
		l = max(l, nl);
		r = min(r, nr);
		node& c = data[i][j];
		if (l > r)
			return 0;
		if (l == nl && r == nr)
			return c.val();

		int nm = (nl + nr) / 2;

		push_down(i, j);
		im lq = query(l, r, nl, nm, i + 1, j * 2);
		im rq = query(l, r, nm + 1, nr, i + 1, j * 2 + 1);
		return lq + rq;
	}

public:
	void update(int l, int r, func f)
	{
		update(l, r, 0, n - 1, 0, 0, f);
	}

	im query(int l, int r)
	{
		return query(l, r, 0, n - 1, 0, 0);
	}
};
*/

#endif // SEGMENT_TREE_H_INCLUDED
