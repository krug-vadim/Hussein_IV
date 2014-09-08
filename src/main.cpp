#include <iostream>

using namespace std;

#include "tree.h"
#include "list.h"
#include "list2.h"
#include "list_alg.h"
#include "tree_alg.h"

#define LONG 10

void test_list()
{
	List<int> t;
	List<int> q(2);

	for(int i = 0; i < LONG; i++)
		t = t.push_front(i);

	printRaw(t);
	printRaw(q);

	cout << "pushed " << LONG << endl;
	cout << "pushed " << t[4] << endl;

	/*for(int i = 0; i < LONG; i++)
		t = t.remove(LONG-i-1);*/

	for(;!t.isEmpty();t=t.pop_front())
		;

	cout << "removed" << endl;
}

void test_list2()
{
	cout << "test2" << endl;
	list_ptr<int> t = std::make_shared<List2<int>>();

	t=t->push_front(0);
	t=t->push_front(1);
	t=t->push_front(2);

	for(list_ptr<int> q = t; q; q=q->pop_front())
		cout << "q: (" << q->value() << ", " << q.use_count() << ")"<< endl;

	for(int i = 0; i < LONG; i++)
		t = t->push_front(i);

	cout << "pushed " << LONG << endl;

	for(;t;t=t->pop_front())
		;

	cout << "removed" << endl;
}

void test_tree()
{
	cout << "test_tree" << endl;

	Tree<int> root(2);

	printRaw(root);

	Tree<int> dwa(69);

	for(int i =0; i<8;i++)
		dwa = dwa.append( Tree<int>(i) );

	printRaw(dwa);

	dwa = dwa.remove(3);

	for(int j = 0; j<8; j++)
	{
		root = root.append( dwa );
		printRaw(dwa);
	}

	printRaw(root);

	cout << "end_tree" << endl;
}

int main(int argc, char *argv[])
{
	//Tree<int> root;
	/*List<int> lst = { 1, 2, 3 };
	List<int> lst1 = lst.take(2);
	List<int> lst2 = lst.removeAt(0);

	auto lst3 = fmap<int>([](int i) { return i + 2; }
	                , lst
	                );

	printRaw(lst);
	printRaw(lst1);
	printRaw(lst2);
	printRaw(lst3);*/



	/*cout << lst.front() << endl;*/

	test_list();
	test_list2();
	test_tree();

	return 0;
}
