#ifndef TREE_H
#define TREE_H

#include "list.h"
#include "list_alg.h"

template<class T>
class Tree
{
	struct Node
	{
		Node(T value) : _value(value) {}

		Node(T value, const List< std::shared_ptr<const Node> > &siblings)
		: _value(value)
		, _siblings(siblings)
		{}

		T _value;
		List< std::shared_ptr<const Node> > _siblings;
	};

	explicit Tree(std::shared_ptr<const Node> const &node) : _root(node) {}

	public:
		Tree() {}
		Tree(T value) : _root(std::make_shared<Node>(value)) {}
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

		List< const Tree > siblings() const
		{
			if ( isEmpty() )
				return List<const Tree>();
			else
				return fmap<const Tree>
				       ([](std::shared_ptr<const Node> t) { return Tree(t); }
				       , _root->_siblings);
		}

		Tree operator[](int i) const
		{
			assert( !isEmpty() );
			return Tree(_root->_siblings[i]);
		}

		Tree append(const Tree &r) const
		{
			assert( !isEmpty() );
			return Tree( value(), siblings().push_front(r) );
		}

		int headCount() const
		{
			return _root.use_count();
		}

	private:
		std::shared_ptr<const Node> _root;
};

#endif