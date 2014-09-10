#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <memory>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <iostream> // print
#include <vector>

template<class T>
class List
{
	struct Item
	{
		Item(T value, std::shared_ptr<const Item> const &tail) : _value(value), _next(tail) {}

		explicit Item(T value) : _value(value) {}

		T _value;
		std::shared_ptr<const Item> _next;
	};

	explicit List(std::shared_ptr<const Item> const &items) : _head(items) {}

	public:
		List() {}
		List(T v, List const &tail) : _head(std::make_shared<Item>(v, tail._head)) {}
		explicit List(T v) : _head(std::make_shared<Item>(v)) {}

		// From initializer list
		List(std::initializer_list<T> init)
		{
			/* need rewrite when std::rbegin std::rend availiable */
			const std::vector<T> v(init);
			for (auto it = v.rbegin(); it != v.rend(); ++it)
				_head = std::make_shared<Item>(*it, _head);
		}

		bool isEmpty() const
		{
			return !_head;
		}

		T front() const
		{
			assert( !isEmpty() );
			return _head->_value;
		}

		List pop_front() const
		{
			assert( !isEmpty() );
			return List(_head->_next);
		}

		// Additional utilities
		List push_front(T v) const
		{
			return List(v, *this);
		}

		List take(int n)
		{
			if ( n <= 0 || isEmpty() )
				return List();

			return pop_front().take(n - 1).push_front(front());
		}

		List insert(int i, T v) const
		{
			if (i == 0)
				return push_front(v);
			else
			{
				assert( !isEmpty() );
				return List<T>(front(), pop_front().insert(i - 1, v));
			}
		}

		List remove(int i) const
		{
			assert( !isEmpty() );
			if (i == 0)
				return pop_front();
			else
				return pop_front().remove(i - 1).push_front(front());
		}

		T operator[](int i)
		{
			assert( !isEmpty() );
			if (i == 0)
				return front();
			else
				return pop_front()[i-1];
		}

		int headCount() const
		{
			return _head.use_count();
		}

	private:
		std::shared_ptr<const Item> _head;
};

#endif