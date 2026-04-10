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
    plugin->info->name = "HelloPlugin";
    plugin->info->description = "My first Geany plugin";
    plugin->info->version = "1.0";
    plugin->info->author = "Anshul";

    plugin->funcs->init = hello_init;
    plugin->funcs->cleanup = hello_cleanup;

    GEANY_PLUGIN_REGISTER(plugin, 225);
}