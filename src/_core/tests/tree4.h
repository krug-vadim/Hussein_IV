template<class T>
struct TreeNode
{
	TreeNode *parent;

	TreeNode *firstChild;
	TreeNode *lastChild;
	TreeNode *prevSibling;
	TreeNode *nextSibling;

	int index;
	int childCount;
	int flags;

	T data;
};

template<class T>
struct TreeInterface
{
	TreeInterface *parent() =0;

	TreeInterface *firstChild() =0;
	TreeInterface *lastChild() =0;
	TreeInterface *prevSibling() =0;
	TreeInterface *nextSibling() =0;

	int index;
	int childCount;
	int flags;

	T data;
};

class TreeModel : public AbstractTreeModel
{
	void *parent(void *node)
	{
	}

	rowCount();
	columnCount();

};

class TreeView
{
	protected:
		void drawCell(int row, int col, Tree &t); // -> model ???
		void drawRow(int row, Tree &t);
		void drawTree(Tree &t)
		{
			for(int row = 0; t; t = t->nextSibling, row++)
				drawRow(row, t);
		}

		void renderTree(Tree t);

	public:
		setModel(AbstractTreeModel &model)
		{
			// ???
		}

	private:
		AbstractModel *t;
};