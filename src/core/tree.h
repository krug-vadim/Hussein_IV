#ifndef TREE_H
#define TREE_H

#include "list.h"
#include "list_alg.h"

//#include <QDebug>

template<class T>
class Tree
{
	explicit Tree(const std::shared_ptr<const Tree<T>> &t)
	: _value(t->_value)
	, _siblings(t->_siblings)
	, _parent(t->_parent)
	, _row(t->_row)
	{}

	explicit Tree(const std::shared_ptr<const T> &value) : _value(value) {}

	explicit Tree(const std::shared_ptr<const T> &value, const List<const Tree<T>> &l)
	: _value(value)
	, _siblings(std::make_shared<const List<const Tree<T>>>(l))
	{
	}

	public:
		Tree() : _parent(0), _row(-1) {}
		Tree(T value) : _value(std::make_shared<const T>(value)), _parent(0), _row(-1) {}
		~Tree() { if (_value) std::cout << "destroyed" << value() << std::endl; }

		T value() const
		{
			return *_value;
		}

		bool isEmpty() const
		{
			return !_value;
		}

		const Tree<T> operator [](int i) const
		{
			assert( !isEmpty() );
			return Tree(_siblings[i]);
		}

		const Tree<T> append(const T &value) const
		{
			return append(Tree<T>(value));
		}

		const Tree<T> append(const Tree<T> &t) const
		{
			if ( _siblings )
				return Tree( _value , _siblings->push_front(t) );
			else
				return Tree( _value, List<const Tree<T>>(t));
		}

	private:
		std::shared_ptr<const T> _value;
		std::shared_ptr<const List<const Tree<T>>> _siblings;
		const Tree<T> *_parent;
		int _row;
};

#endif
