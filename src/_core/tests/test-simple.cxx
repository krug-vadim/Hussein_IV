#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tree.H>

#include <string>

void TreeCallback(Fl_Widget *w, void *data) {
    Fl_Tree *tree = (Fl_Tree*)w;
    //fprintf(stderr, "TreeCallback: data=%d, ", (int)data);
    // Find item that was clicked
    Fl_Tree_Item *item = (Fl_Tree_Item*)tree->item_clicked();
    if ( item ) {
        fprintf(stderr, "item='%s'\n", item->label());	// print item's label
        tree->deselect_all();		// deselect all items
        tree->select(item);		// select this one
	// tree->redraw();
    } else {
        fprintf(stderr, "(NO ITEM?)\n");
    }
}

int main(int argc, const char *argv[]) {
    Fl_Double_Window win(250, 400, "Simple Tree");

    // Create tree, add items
    Fl_Tree tree(10, 10, win.w()-20, win.h()-20);

    for(int i = 0; i < (1000); i++)
    {

        tree.add(std::to_string(i).c_str());

        // tree.add("Flintstones/Fred");
        // tree.add("Flintstones/Wilma");
        // tree.add("Flintstones/Pebbles");
        // tree.add("Simpsons/Homer");
        // tree.add("Simpsons/Marge");
        // tree.add("Simpsons/Bart");
        // tree.add("Simpsons/Lisa");
    }

    //tree.close("/Simpsons");
    //tree.callback(TreeCallback, (void*)1234);

    win.end();
    win.resizable(win);
    win.show();
    return(Fl::run());
}
