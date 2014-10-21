#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QtCore/QObject>

class TreeModel : public QObject
{
	Q_OBJECT

	public:
		enum Flag
		{
			NoItemFlags      = 0x0000,
			ItemIsSelected   = 0x0001,
			ItemIsSelectable = 0x0002,
			ItemIsEdited     = 0x0004,
			ItemIsEditable   = 0x0008
		};
		Q_DECLARE_FLAGS(Flags, Flag)

		explicit TreeModel(QObject *parent = 0);
		virtual ~TreeModel();

		virtual QObject *root() =0;
		virtual QObject *parent(const QObject *obj) =0;

		virtual QObject *nextSibling(const QObject *obj) =0;
		virtual QObject *previousSibling(const QObject *obj) =0;

		virtual QObject *firstChild(const QObject *obj) =0;
		virtual QObject *lastChild(const QObject *obj) =0;

		virtual quint64 childCount(const QObject *obj) =0;
		virtual quint64 columnCount(const QObject *obj) =0;

		virtual Flags flags(const QObject *obj) =0;
		virtual void setFlags(Flags flags, QObject *obj) =0;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TreeModel::Flags)

#endif // TREEMODEL_H
