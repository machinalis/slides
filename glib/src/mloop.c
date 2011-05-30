#include <glib.h>
#include <stdio.h>

#define COUNT 100
#define STEPS 20

static char *progress_chars="-/|\\";
static int progress_cycle = 0;
static gsize progress_total = 0;

GMainLoop *loop = NULL;

void update_status(void) {
	int i = 0;

	g_print("\r%c |", progress_chars[progress_cycle]);
	for (i=0; i < STEPS; i ++) {
		g_print(i*COUNT < progress_total*STEPS?"=":" ");
	}
	g_print("|");
	fflush(stdout);
}

gboolean timer(gpointer data) {
	progress_cycle = (progress_cycle+1) % 4;
	update_status();
	return TRUE;
}

gboolean data_available(GIOChannel *s, GIOCondition c, gpointer data) {
	char buffer[4096];
	gsize total_read = 0;
	GIOStatus result = 0;
	
	g_assert(c == G_IO_IN);
	result = g_io_channel_read_chars(s, buffer, sizeof(buffer), &total_read, NULL);
	if (result != G_IO_STATUS_NORMAL || total_read == 0) {
		return FALSE;
	}
	
	progress_total = MIN(progress_total+total_read, COUNT);
	update_status();
	
	if (progress_total==COUNT) {
		g_main_loop_quit(loop);
	}
	return TRUE;
}

gint main(gint argc, gchar **argv) {

	loop = g_main_loop_new(NULL, FALSE);
	GIOChannel *io = g_io_channel_unix_new(0);
	g_io_channel_set_flags(io, G_IO_FLAG_NONBLOCK, NULL);
	
	update_status();
	g_timeout_add(500, timer, NULL);
	g_io_add_watch(io, G_IO_IN, data_available, NULL);
	g_main_loop_run(loop);
	g_print("\n");
	return 0;
}

