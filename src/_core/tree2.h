#ifndef TREE_H
#define TREE_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream> // print

template<class T>
class Tree : std::enable_shared_from_this<Tree<T>>
{
	explicit Tree(const std::shared_ptr<T> &data) : _data(data) {}

	public:
		Tree(Tree *parent = 0) : _parent(parent) {}
		Tree(T data, Tree *parent = 0) : _parent(parent), _data(std::make_shared<T>(data)) {}
//		Tree2(Tree2 *parent, T data, std::list<T> &siblings);

		Tree *parent() const
		{
			return _parent;
		}

		T value() const
		{
			return *_data;
		}

		void insert(int i, T data)
		{
			/*_siblings.emplace( std::make_pair(i, new Tree(data, this)) );*/
			_siblings.push_back(std::unique_ptr<Tree<T>>(new Tree(data, this)));
		}

		int size() const
		{
			return _siblings.size();
		}

		Tree<T>& at(int i)
		{
			return *_siblings[i];
		}

		bool isEmpty() const
		{
			return !_data;
		}

	private:
		Tree *_parent;
		std::shared_ptr<T>    _data;

		/*std::unordered_map<int, std::unique_ptr<Tree> > _siblings;*/
		std::vector<std::unique_ptr<Tree<T>>> _siblings;

		std::shared_ptr<Tree<T>>              _prev;
};

#endif // TREE2_H
