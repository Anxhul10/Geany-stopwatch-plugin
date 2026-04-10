#include <geanyplugin.h>

static gboolean hello_init(GeanyPlugin *plugin, gpointer pdata) {
    g_print("Hello from Geany Plugin!\n");
    return TRUE;
}

static void hello_cleanup(GeanyPlugin *plugin, gpointer pdata) {
    g_print("Goodbye!\n");
}

G_MODULE_EXPORT
void geany_load_module(GeanyPlugin *plugin) {
    plugin->info->name = "Stopwatch";
    plugin->info->description = "A watch which can be started and stopped by pressing a button, so that you can measure exactly how long something takes";
    plugin->info->version = "0.0.1";
    plugin->info->author = "Anshul Ekka <anxhul10@gmail.com>";

    // init and cleanup are mandatory
    plugin->funcs->init = hello_init;
    plugin->funcs->cleanup = hello_cleanup;

    GEANY_PLUGIN_REGISTER(plugin, 225);
}