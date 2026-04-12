#include <geanyplugin.h>
#include <gtk/gtk.h>

static GtkWidget *label;
static GtkWidget *start_btn;
static GtkWidget *stop_btn;
static GtkWidget *reset_btn;

static guint timer_id = 0;
static int seconds = 0;
static gboolean running = FALSE;

static gboolean update_timer(gpointer data)
{
    if (!running)
        return FALSE;

    seconds++;

    int hrs = seconds / 3600;
    int mins = (seconds % 3600) / 60;
    int secs = seconds % 60;

    char buf[64];
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hrs, mins, secs);

    gtk_label_set_text(GTK_LABEL(label), buf);

    return TRUE;
}


static void on_start_clicked(GtkButton *btn, gpointer user_data)
{
    if (!running) {
        running = TRUE;
        timer_id = g_timeout_add(1000, update_timer, NULL);

        gtk_widget_set_sensitive(start_btn, FALSE);
        gtk_widget_set_sensitive(stop_btn, TRUE);

        msgwin_msg_add(COLOR_RED, -1, NULL, "Started");
    }
}

static void on_stop_clicked(GtkButton *btn, gpointer user_data)
{
    if (running) {
        running = FALSE;

        if (timer_id) {
            g_source_remove(timer_id);
            timer_id = 0;
        }

        gtk_widget_set_sensitive(start_btn, TRUE);
        gtk_widget_set_sensitive(stop_btn, FALSE);

        msgwin_msg_add(COLOR_RED, -1, NULL, "Stopped");
    }
}

static void on_reset_clicked(GtkButton *btn, gpointer user_data)
{
    seconds = 0;
    gtk_label_set_text(GTK_LABEL(label), "00:00:00");

    msgwin_msg_add(COLOR_RED, -1, NULL, "Reset");
}

static void item_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget *window = gtk_dialog_new();

    gtk_window_set_title(GTK_WINDOW(window), "Stopwatch - by Anxhul10");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 100);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(window));

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(content), vbox);

    // Label
    label = gtk_label_new("00:00:00");

    // Increase font size
    PangoAttrList *attrs = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_scale_new(2.0);
    pango_attr_list_insert(attrs, attr);

    gtk_label_set_attributes(GTK_LABEL(label), attrs);
    pango_attr_list_unref(attrs);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 5);

    // Button container
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);

    // Buttons
    start_btn = gtk_button_new_with_label("Start");
    stop_btn  = gtk_button_new_with_label("Stop");
    reset_btn = gtk_button_new_with_label("Reset");

    gtk_box_pack_start(GTK_BOX(hbox), start_btn, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), stop_btn, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), reset_btn, TRUE, TRUE, 5);

    // Signals
    g_signal_connect(start_btn, "clicked", G_CALLBACK(on_start_clicked), NULL);
    g_signal_connect(stop_btn, "clicked", G_CALLBACK(on_stop_clicked), NULL);
    g_signal_connect(reset_btn, "clicked", G_CALLBACK(on_reset_clicked), NULL);

    // Initial state
    gtk_widget_set_sensitive(start_btn, TRUE);
    gtk_widget_set_sensitive(stop_btn, FALSE);

    gtk_widget_show_all(window);
}

static gboolean stopwatch_init(GeanyPlugin *plugin, gpointer pdata)
{
    GtkWidget *main_menu_item;

    main_menu_item = gtk_menu_item_new_with_mnemonic("Stopwatch");
    gtk_widget_show(main_menu_item);

    gtk_container_add(
        GTK_CONTAINER(plugin->geany_data->main_widgets->tools_menu),
        main_menu_item
    );

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
    plugin->info->description = "Simple stopwatch plugin";
    plugin->info->version = "0.1";
    plugin->info->author = "Anshul Ekka";

    plugin->funcs->init = stopwatch_init;
    plugin->funcs->cleanup = stopwatch_cleanup;

    GEANY_PLUGIN_REGISTER(plugin, 225);
}