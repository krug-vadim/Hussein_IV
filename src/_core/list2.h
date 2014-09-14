#include <cassert>
#include <memory>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <iostream> // print
#include <vector>

template<class T> class List2;

template<class T> using list_ptr = std::shared_ptr<List2<T>>;

template<class T>
class List2: public std::enable_shared_from_this<List2<T>>
{
	public:
		List2() {}
		List2(T v) : _value(v) {}
		List2(T v, std::shared_ptr<List2<T>> tail) : _value(v), _next(tail) {}
		//~List() { cout << "destroyed " << _value << endl; }

		std::shared_ptr<List2<T>> push_front(T v)
		{
			return std::make_shared<List2>(v, this->shared_from_this());
		}

		std::shared_ptr<List2<T>> pop_front()
		{
			return _next;
		}

		T value() const
		{
			return _value;
		}

	private:
		T _value;
		std::shared_ptr<List2<T>> _next;
};
