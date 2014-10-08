#ifndef TREE_H
#define TREE_H

#include "list.h"
#include "list_alg.h"

class QAbstractItemModel;

//#include <QDebug>

template<class T>
class Tree
{
	friend class QAbstractItemModel;

	/*explicit Tree(const Tree<T> &t)
	: _value(t._value)
	, _siblings(t._siblings)
	, _parent(t._parent)
	, _row(t._row)
	{}*/

	explicit Tree(const Tree<T> &t, const Tree *parent, const int row)
	: _value(t._value)
	, _siblings(t._siblings)
	, _parent(parent)
	, _row(row)
	{}

	explicit Tree(const std::shared_ptr<const T> &value) : _value(value), _parent(0), _row(-1) {}

	explicit Tree(const std::shared_ptr<const T> &value, const List<const Tree<T>> &l)
	: _value(value)
	, _siblings(std::make_shared<const List<const Tree<T>>>(l))
	, _parent(0)
	, _row(-1)
	{
	}

	explicit Tree(const std::shared_ptr<const T> &value, const List<const Tree<T>> &l,
	              const Tree *parent, const int row)
	: _value(value)
	, _siblings(std::make_shared<const List<const Tree<T>>>(l))
	, _parent(parent)
	, _row(row)
	{
	}

	public:
		Tree() : _parent(0), _row(-1) {}
		Tree(const T &value) : _value(std::make_shared<const T>(value)), _parent(0), _row(-1) {}
		~Tree() { if (_value) std::cout << "destroyed" << value() << std::endl; }

		T value() const
		{
			return *_value;
		}

		const Tree* parent() const
		{
			return _parent;
		}

		int row() const
		{
			return _row;
		}

		bool isEmpty() const
		{
			return !_value;
		}

		Tree operator [](int i) const
		{
			assert( !isEmpty() );
			return Tree((*_siblings)[i]);
		}

		int size() const
		{
			return ( _siblings ) ? _siblings->size() : 0;
		}

		const Tree<T> append(const T &value) const
		{
			return append( Tree<T>(value) );
		}

		const Tree<T> append(const Tree<T> &t) const
		{
			Tree q = Tree(t, this, size() );

			if ( _siblings )
				return Tree( _value , _siblings->push_front(q), parent(), row() );
			else
				return Tree( _value, List<const Tree<T>>(q), parent(), row() );
		}

	private:
		std::shared_ptr<const T> _value;
		std::shared_ptr<const List<const Tree<T>>> _siblings;
		const Tree<T> *_parent;
		int _row;
};

#endif
