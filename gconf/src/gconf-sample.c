#include <glib.h>
#include <gconf/gconf-client.h>
#include <stdio.h>


void value_changed(GConfClient *c, const gchar *key, GConfValue *value, gpointer user_data) {

	g_print("changed: %s\n", key);
}

gboolean timer(gpointer data) {
	gboolean state = gconf_client_get_bool((GConfClient *)data, "/apps/gedit-2/preferences/editor/line_numbers/display_line_numbers", NULL);
	gconf_client_set_bool((GConfClient *)data, "/apps/gedit-2/preferences/editor/line_numbers/display_line_numbers", !state, NULL);
	return TRUE;
}

gint main(gint argc, gchar **argv) {
    GMainLoop *loop = NULL;
    GConfClient *client = NULL;

	loop = g_main_loop_new(NULL, FALSE);
	client = gconf_client_get_default();
	gconf_client_add_dir (client,
		"/apps/gedit-2",
		GCONF_CLIENT_PRELOAD_NONE,
		NULL);

	g_signal_connect(G_OBJECT(client), "value_changed", (GCallback)value_changed, NULL);

	g_timeout_add(1000, timer, (gpointer)client);

	g_main_loop_run(loop);
	return 0;
}

