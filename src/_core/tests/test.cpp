#include <iostream>

#include "core/tree.h"
#include "core/tree_alg.h"

int main(void)
{
	Tree<int> t(2);

	for(int i = 0; i < 10; i++)
	{
		std::cout << "adding " << i << std::endl;
		t = t.append( i );
		std::cout << "added " << i << std::endl;
	}

	//t = t.append( t );

	printRaw(t);

	std::cout << "exiting" << std::endl;

	return 0;
}
