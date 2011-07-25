/* hello-glib.c */

#include <glib.h>

gint main(gint argc, gchar **argv) {
	if (!GLIB_CHECK_VERSION (2, 2, 0))
		g_error ("GLib version 2.2.0 or above is needed");
	g_print("%s\n", "Hello World!");
	return 0;
}

