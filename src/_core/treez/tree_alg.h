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
		std::cout << "("
		          << tree.value()
		          << ", "
		          << tree.row()
		          << ", "
		          << tree.size()
		          << ") "
		          << std::endl;

		for(int i = 0; i < tree.size(); i++)
			printRaw(tree[i], level + 1);

	}
}


#endif