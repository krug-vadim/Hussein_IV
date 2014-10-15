#include "testtreemodel.h"

TestTreeModel::TestTreeModel(QObject *root, QObject *parent) :
    TreeModel(parent)
{
	_root = new QObject(parent);
	_root->setObjectName(QString("(root)"));

	for(int i = 0; i < childCount(0); i++)
	{
		_nodes.append(new QObject(_root));
		_nodes.last()->setObjectName(QString("%1").arg(i));
	}
}

QObject *TestTreeModel::root()
{
	return _root;
}

QObject *TestTreeModel::parent(const QObject *obj)
{
	return (obj == _root) ? 0 : _root;
}

QObject *TestTreeModel::nextSibling(const QObject *obj)
{
	int n = getNum(obj);

	if ( n == -1 )
		return 0;
	else if ( n < _nodes.size() - 1 )
		return _nodes.at(n + 1);
	else
		return 0;
}

QObject *TestTreeModel::previousSibling(const QObject *obj)
{
	int n = getNum(obj);

	if ( n == -1 )
		return 0;
	else if ( n > 1 )
		return _nodes.at(n - 1);
	else
		return 0;
}

QObject *TestTreeModel::firstChild(const QObject *obj)
{
	return ( getNum(obj) == -1 ) ? _nodes.first() : 0;
}

QObject *TestTreeModel::lastChild(const QObject *obj)
{
	return ( getNum(obj) == -1 ) ? _nodes.last() : 0;
}

quint64 TestTreeModel::childCount(const QObject *obj)
{
	return (1000*1000);
}

quint64 TestTreeModel::columnCount(const QObject *obj)
{
	return 3;
}

quint64 TestTreeModel::flags(const QObject *obj)
{
	return 0;
}

int TestTreeModel::getNum(const QObject *obj)
{
	if ( obj->objectName() == QString("(root)") )
		return -1;
	else
		return obj->objectName().toInt();
}
