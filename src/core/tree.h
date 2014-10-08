#ifndef TREE_H
#define TREE_H

template<class T>
class Tree
{
	public:
		Tree(const T &data)
		: _parent(0)
		, _nextSibling(0)
		, _previousSibling(0)
		, _firstChild(0)
		, _lastChild(0)
		, _data(data)
		{}

		~Tree()
		{
		}

		Tree *parent() const
		{
			return _parent;
		}

		void setParent(Tree *parent) const
		{
			_parent = parent;
		}

		Tree *nextSibling() const
		{
			return _nextSibling;
		}

		void setNextSibling(Tree *nextSibling) const
		{
			_nextSibling = nextSibling;
		}

		Tree *previousSibling() const
		{
			return _previousSibling;
		}

		void setPreviousSibling(Tree *previousSibling) const
		{
			_previousSibling = previousSibling;
		}

		Tree *firstChild() const
		{
			return _firstChild;
		}

		void setFirstChild(Tree *firstChild) const
		{
			_firstChild = firstChild;
		}

		Tree *lastChild() const
		{
			return _lastChild;
		}

		void setLastChild(Tree *lastChild) const
		{
			_lastChild = lastChild;
		}

	private:
		Tree *_parent;

		Tree *_nextSibling;
		Tree *_previousSibling;

		Tree *_firstChild;
		Tree *_lastChild;

		T _data;
};

#endif // TREE_H
