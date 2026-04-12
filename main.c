#include <geanyplugin.h>
#define RESPONSE_START 1

static void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    if (response_id == RESPONSE_START) {
        msgwin_msg_add(COLOR_RED, -1, NULL, "Start button clicked!");
    }
}

static void item_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget *window, *button;
    window = gtk_dialog_new();

    gtk_window_set_keep_above ( (GtkWindow *) window, TRUE);
    gtk_window_set_type_hint (GTK_WINDOW (window), GDK_WINDOW_TYPE_HINT_DIALOG);
    gtk_window_set_title(GTK_WINDOW(window), "Stopwatch -by Anxhul10");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 100);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_show(window);

    
    gtk_dialog_add_buttons(GTK_DIALOG(window),
        "_Start", RESPONSE_START,
    NULL);
    
    g_signal_connect(window, "response", G_CALLBACK(on_dialog_response), NULL);
}
 
 
static gboolean stopwatch_init(GeanyPlugin *plugin, gpointer pdata)
{
    GtkWidget *main_menu_item;
 
    // Create a new menu item and show it
    main_menu_item = gtk_menu_item_new_with_mnemonic("Stopwatch");
    gtk_widget_show(main_menu_item);
    gtk_container_add(GTK_CONTAINER(plugin->geany_data->main_widgets->tools_menu),
            main_menu_item);
    g_signal_connect(main_menu_item, "activate",
            G_CALLBACK(item_activate_cb), NULL);
 
    geany_plugin_set_data(plugin, main_menu_item, NULL);
    return TRUE;
}
 
 
static void stopwatch_cleanup(GeanyPlugin *plugin, gpointer pdata)
{
    GtkWidget *main_menu_item = (GtkWidget *) pdata;
 
    gtk_widget_destroy(main_menu_item);
}

G_MODULE_EXPORT
void geany_load_module(GeanyPlugin *plugin)
{
    plugin->info->name = "Stopwatch";
    plugin->info->description = "A watch which can be started and stopped by pressing a button, so that you can measure exactly how long something takes";
    plugin->info->version = "0.0.1";
    plugin->info->author = "Anshul Ekka <anxhul10@gmail.com>";
 
    plugin->funcs->init = stopwatch_init;
    plugin->funcs->cleanup = stopwatch_cleanup;
 
    GEANY_PLUGIN_REGISTER(plugin, 225);
}