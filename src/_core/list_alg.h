#ifndef LIST_ALG_H
#define LIST_ALG_H

template<class T>
List<T> concat(List<T> const & a, List<T> const & b)
{
	if (a.isEmpty())
		return b;
	return List<T>(a.front(), concat(a.pop_front(), b));
}

template<class U, class T, class F>
List<U> fmap(F f, List<T> lst)
{
	static_assert(std::is_convertible<F, std::function<U(T)>>::value,
				 "fmap requires a function type U(T)");
	if (lst.isEmpty())
		return List<U>();
	else
		return List<U>(f(lst.front()), fmap<U>(f, lst.pop_front()));
}

template<class T, class P>
List<T> filter(P p, List<T> lst)
{
	static_assert(std::is_convertible<P, std::function<bool(T)>>::value,
				 "filter requires a function type bool(T)");
	if (lst.isEmpty())
		return List<T>();
	if (p(lst.front()))
		return List<T>(lst.front(), filter(p, lst.pop_front()));
	else
		return filter(p, lst.pop_front());
}

template<class T, class U, class F>
U foldr(F f, U acc, List<T> lst)
{
	static_assert(std::is_convertible<F, std::function<U(T, U)>>::value,
				 "foldr requires a function type U(T, U)");
	if (lst.isEmpty())
		return acc;
	else
		return f(lst.front(), foldr(f, acc, lst.pop_front()));
}

template<class T, class U, class F>
U foldl(F f, U acc, List<T> lst)
{
	static_assert(std::is_convertible<F, std::function<U(U, T)>>::value,
				 "foldl requires a function type U(U, T)");
	if (lst.isEmpty())
		return acc;
	else
		return foldl(f, f(acc, lst.front()), lst.pop_front());
}

// Set difference a \ b
template<class T>
List<T> diff(List<T> const & as, List<T> const & bs)
{
	return foldl([](List<T> const & acc, T x) {
		return acc.remove(x);
	}, as, bs);
}

// Set union of two lists, xs u ys
// Assume no duplicates inside either list
template<class T>
List<T> unionize(List<T> const & xs, List<T> const & ys)
{
	// xs u ys = (ys \ xs) ++ xs
	// remove all xs from ys
	auto trimmed = foldl([](List<T> const & acc, T x) {
		return acc.remove(x);
	}, ys, xs);
	return concat(trimmed, xs);
}

template<class T>
List<T> concatAll(List<List<T>> const & xss)
{
	if (xss.isEmpty()) return List<T>();
	return concat(xss.front(), concatAll(xss.pop_front()));
}

// consumes the list when called:
// forEach(std::move(lst), f);

template<class T, class F>
void forEach(List<T> lst, F f)
{
	static_assert(std::is_convertible<F, std::function<void(T)>>::value,
				 "forEach requires a function type void(T)");
	while (!lst.isEmpty()) {
		f(lst.front());
		lst = lst.pop_front();
	}
}

template<class Beg, class End>
auto fromIt(Beg it, End end) -> List<typename Beg::value_type>
{
	typedef typename Beg::value_type T;
	if (it == end)
		return List<T>();
	T item = *it;
	return List<T>(item, fromIt(++it, end));
}

template<class T, class F>
List<T> iterateN(F f, T init, int count)
{
	if (count <= 0) return List<T>();
	return iterateN(f, f(init), count - 1).push_front(init);
}

// Pass lst by value not reference!
template<class T>
void printRaw(List<T> lst)
{
	if (lst.isEmpty()) {
		std::cout << std::endl;
	}
	else {
		std::cout << "(" << lst.front() << ", " << lst.headCount() - 1 << ") ";
		printRaw(lst.pop_front());
	}
}

template<class T>
std::ostream& operator<<(std::ostream& os, List<T> const & lst)
{
	os << "[";
	forEach(lst, [&os](T v) {
		os << v << " ";
	});
	os << "]";
	return os;
}

template<class T>
List<T> reverse(List<T> const & lst)
{
	return foldl([](List<T> const & acc, T v)
	{
		return List<T>(v, acc);
	}, List<T>(), lst);
}

#endif