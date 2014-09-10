#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include "../limbs/tree.h"

template<class T>
class TreeModel : public wxDataViewModel
{
	public:
		TreeModel(const Tree<T> &root): wxDataViewModel(), _root(root) {}
		~TreeModel() {}

		unsigned int GetColumnCount() const
		{
			return 1;
		}

		wxString GetColumnType(unsigned int column) const
		{
			return "string";
		}

		void GetValue(wxVariant& val, const wxDataViewItem& item, unsigned int column) const
		{
			/*wxVariant v(_asString(item));*/
			val = "test";
		}

		bool SetValue(const wxVariant& val, const wxDataViewItem& item, unsigned int column)
		{
			return true;
		}

		wxDataViewItem GetParent(const wxDataViewItem& item) const
		{
			/*wxString par = _asString(item);
			if (par.length() != 1) {
				return wxDataViewItem(asPointer(par.Left(par.length() - 1)));
			}*/
			return wxDataViewItem((void *)1);
			return wxDataViewItem(NULL);
		}

		bool IsContainer(const wxDataViewItem& item) const
		{
			/*return (1 < 3);*/
			return false;
		}

		unsigned GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const
		{
			/*children.Add(wxDataViewItem((void *)1));
			children.Add(wxDataViewItem((void *)2));
			children.Add(wxDataViewItem((void *)3));*/
			return 0;
		}

	private:
		Tree<T> _root;
};

#endif