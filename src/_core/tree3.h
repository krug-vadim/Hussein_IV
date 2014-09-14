#ifndef TREE_H
#define TREE_H

#include <QtCore/QSharedPointer>
#include <QtCore/QScopedPointer>
#include <QtCore/QList>

template<class T>
class Tree
{
	explicit Tree(const QSharedPointer<T> &data) : _data(data) {}

	public:
		Tree(Tree *parent = 0) : _parent(parent) {}
		Tree(T &data, Tree *parent = 0) : _parent(parent), _data(QSharedPointer<T>(new T(data))) {}

		Tree *parent() const
		{
			return _parent;
		}

		T& value() const
		{
			return *_data;
		}

		void insert(int i, T data)
		{
			_siblings.insert(i, QScopedPointer< Tree<T> >(new Tree(data, this)));
		}

		int size() const
		{
			return _siblings.size();
		}

		Tree<T>& at(int i)
		{
			return *_siblings.at(i);
		}

		bool isEmpty() const
		{
			return !_data;
		}

		int row() const
		{
			return ( parent() ) ? parent()->_siblings.indexOf( QScopedPointer< Tree<T> >(this) ) : 0;
		}

	private:
		Tree *_parent;
		QSharedPointer<T> _data;
		QList< QScopedPointer< Tree<T> > > _siblings;
		QSharedPointer< Tree<T> > _prev;
};

#endif // TREE_H
