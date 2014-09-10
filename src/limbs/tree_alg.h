#ifndef TREE_ALG_H
#define TREE_ALG_H

template<class T>
void printRaw(const Tree<T> &tree, const int level = 0)
{
	if (tree.isEmpty())
	{
		std::cout << std::endl;
	}
	else
	{
		for(int i=0;i<level;i++)
			std::cout << " ";
		std::cout  << "(" << tree.value() << ", " << tree.headCount() - 1 << ") " << std::endl;

		for(List<const Tree<T>> lst = tree.siblings(); !lst.isEmpty();lst = lst.pop_front())
			printRaw(lst.front(), level + 1);

	}
}


#endif