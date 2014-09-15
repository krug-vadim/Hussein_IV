#ifndef TREE_H
#define TREE_H

#include "list.h"
#include "list_alg.h"

#include <QDebug>

template<class T>
class Tree
{
	struct ParentInfo
	{
		ParentInfo() : _parent(0), _row(-1) {}

		ParentInfo(const Tree *parent, int row) : _parent(parent), _row(row) {}

		const Tree *_parent;
		int _row;
	};

	struct Node
	{
		Node(T value) : _value(value) {}
		Node(T value, const ParentInfo &info) : _value(value), _info(info) {}
		Node(T value, const List< std::shared_ptr<const Node> > &siblings)
		: _value(value)
		, _siblings(siblings)
		{}

		Node(T value, const ParentInfo &info, const List< std::shared_ptr<const Node> > &siblings)
		: _value(value)
		, _info(info)
		, _siblings(siblings)
		{}

		Node(std::shared_ptr<const Node> &prev)
		: _value(prev->_value)
		, _info(prev->_info)
		, _siblings(prev->_siblings)
		{}

		T _value;
		ParentInfo _info;

		std::shared_ptr<const Node> _prev;
		List< std::shared_ptr<const Node> > _siblings;
	};

	explicit Tree(std::shared_ptr<const Node> const &node) : _root(node) {}
	explicit Tree(T value, const ParentInfo &info) : _root(std::make_shared<Node>(value, info)) {}
	explicit Tree(T value, const List< const Tree > &siblings, const ParentInfo &info)
	{
		List< std::shared_ptr<const Node> > nodes;

		nodes = fmap<std::shared_ptr<const Node>>([](const Tree &t) { return t._root; }, siblings);

		_root = std::make_shared<const Node>(value, info, nodes);
	}

	public:
		Tree() {}
		Tree(T value) : _root(std::make_shared<Node>(value)) {}
		~Tree() { qDebug() << "destoing value" << value(); }

		Tree(T value, const List< const Tree > &siblings)
		{
			List< std::shared_ptr<const Node> > nodes;

			nodes = fmap<std::shared_ptr<const Node>>([](const Tree &t) { return t._root; }, siblings);

			_root = std::make_shared<const Node>(value, nodes);
		}

		bool isEmpty() const
		{
			return !_root;
		}

		T value() const
		{
			assert( !isEmpty() );
			return _root->_value;
		}

		const Tree *parent() const
		{
			assert( !isEmpty() );
			return _root->_info._parent;
		}

		int row() const
		{
			assert( !isEmpty() );
			return _root->_info._row;
		}

		Tree operator[](int i) const
		{
			assert( !isEmpty() );
			return Tree(_root->_siblings[i]);
		}

		Tree append(T &data) const
		{
			return append(Tree(data));
		}

		Tree append(const Tree &r) const
		{
			assert( !isEmpty() );
			return Tree( Node(value(), ParentInfo(this, size()), _root->_siblings.push_front(r._root)) );
		}

//		Tree remove(int i) const
//		{
//			assert( !isEmpty() );
//			return Tree( value(), siblings().remove(i) );
//		}

		int size() const
		{
			auto l = _root->_siblings;
			int size = 0;

			while ( !l.isEmpty() )
			{
				size++;
				l = l.pop_front();
			}

			return size;
		}

		int headCount() const
		{
			return _root.use_count();
		}

	private:
		std::shared_ptr<const Node> _root;
};

#endif
