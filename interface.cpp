//
// Created by joaquin on 04/09/18.
//
#include "interface.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

#include "state.h"

void VisualInterface::init_list(GtkWidget *list) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes("List Items",
                                                      renderer, "text", LIST_ITEM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list),
                            GTK_TREE_MODEL(store));

    g_object_unref(store);
}

void VisualInterface::add_to_list(GtkWidget *list, const gchar *str) {
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model
                                   (GTK_TREE_VIEW(list)));

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}


void VisualInterface::on_changed(GtkWidget *widget, gpointer label) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *value;

    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(widget), &model, &iter)) {

        gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
        gtk_label_set_text(GTK_LABEL(label), value);
        g_free(value);
        
    }

}

void VisualInterface::player() {
    GtkWidget *window;
    GtkWidget *list;

    GtkWidget *vbox;
    GtkWidget *label;
    GtkTreeSelection *selection;

    gtk_init(NULL,NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    list = gtk_tree_view_new();

    gtk_window_set_title(GTK_WINDOW(window), "List view");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

    vbox = gtk_vbox_new(FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

    label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    init_list(list);
    add_to_list(list, "Dummy Item");
    add_to_list(list, "Dummy Item");
    add_to_list(list, "Create Gesture");
    add_to_list(list, "North Face");
    add_to_list(list, "Der Untergang");
    add_to_list(list, "oneko");

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    
    g_signal_connect(window, "key-release-event", G_CALLBACK(key_event), label);
    
    g_signal_connect(selection, "changed", G_CALLBACK(on_changed), label);
    

    g_signal_connect(G_OBJECT (window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();
}

void VisualInterface::startDisplay() {
    GtkWidget *window;
    GtkWidget *myImage;
    GtkWidget *myButton;
    GtkWidget *myPaned;

    gtk_init(NULL,NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 500);

    gtk_window_set_title(GTK_WINDOW(window), "Shortcut LeapMotion");

    myPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);


    myImage = gtk_image_new_from_file ("/home/joaquin/Repos/LeapMotion/thanos.gif");//poner imagen XDDDD

//
//    myButton = gtk_button_new_with_label("Start");

    g_signal_connect (window, "destroy",
                      G_CALLBACK(gtk_main_quit), NULL);

    gtk_paned_add1 (GTK_PANED(myPaned), myImage);
//    gtk_paned_add2 (GTK_PANED(myPaned), myButton);

    gtk_container_add(GTK_CONTAINER (window), myPaned);
    gtk_widget_show_all (window);

    gtk_main();
}

bool flag = 1;
bool VisualInterface::key_event(GtkWidget *widget, GdkEventKey *event, gpointer label)
{
    char ch[50];
    const gchar *word=gtk_label_get_text(GTK_LABEL(label));
    sprintf(ch,word);

    if (!g_strcmp0(gdk_keyval_name(event->keyval),"Return")){
        if(strcmp(ch,"Create Gesture")==0) {
//        std::cout << "Entre aca wtf\n" << ch << "\n";
            system("xdotool key super+w");
            currentState = Free;
//            sleep(1000);
        }
        else if(strcmp(ch,"Proceed to bind with command!")==0) {
//            bindWithCommand();
        }
//        g_printerr("value %s\n", gtk_label_get_text(GTK_LABEL(label)));
//        system(ch);
    }
    return FALSE;
}


void VisualInterface::createGesture(const gchar *gestureDetected) {
    GtkWidget *window;
    GtkWidget *list;

    GtkWidget *vbox;
    GtkWidget *label;
    GtkTreeSelection *selection;

    gtk_init(NULL,NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    list = gtk_tree_view_new();

    gtk_window_set_title(GTK_WINDOW(window), "List view");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

    vbox = gtk_vbox_new(FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

    label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    init_list(list);
    add_to_list(list, "Gesture Detected");
    add_to_list(list, gestureDetected);
    add_to_list(list, "Bad Recognition!, repeat grab");
    add_to_list(list, "google-chrome-stable");
    add_to_list(list, "termite");
    add_to_list(list, "oneko");
    add_to_list(list, "chromium");


    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(window, "key-release-event", G_CALLBACK(key_event), label);

    g_signal_connect(selection, "changed", G_CALLBACK(on_changed), label);


    g_signal_connect(G_OBJECT (window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

}
