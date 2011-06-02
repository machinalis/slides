#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-bindings.h>
#include <stdio.h>

GMainLoop *loop = NULL;

GType server_object_get_type (void);

/* Standard GObject class structures, etc */
typedef struct {
    GObject parent;
} ServerObject;

typedef struct
{
    GObjectClass parent;
	DBusGConnection *connection;
}ServerObjectClass;

#define TYPE_SERVER_OBJECT (server_object_get_type ())
#define SERVER_OBJECT(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SERVER_OBJECT, ServerObject))
#define SERVER_OBJECT_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SERVER_OBJECT, ServerObjectClass))
#define IS_SERVER_OBJECT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SERVER_OBJECT))
#define IS_SERVER_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SERVER_OBJECT))
#define SERVER_OBJECT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SERVER_OBJECT, ServerObjectClass))

gboolean
server_echo_string (ServerObject *server, gchar *original, gchar **echo, GError **error)
{
	*echo = g_strdup (original);

	if (*echo == NULL)
	{
		/* We have an error, set the gerror */
		g_set_error (error, g_quark_from_static_string ("echo"),
					0xdeadbeef,
					"Some random problem occured, you're screwed");
		return FALSE;
	}

	return TRUE;
}

#include "echo-server.h"
void class_init(ServerObjectClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
	if (klass->connection == NULL)
	{
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	/* &dbus_glib__object_info is provided in the server-bindings.h file */
	/* OBJECT_TYPE_SERVER is the GType of your server object */
	dbus_g_object_type_install_info (TYPE_SERVER_OBJECT, &dbus_glib_echo_object_info);
}

ServerObject *server_object_new(void) {
    return SERVER_OBJECT(g_object_new (TYPE_SERVER_OBJECT, NULL));
}

GType 
server_object_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (ServerObjectClass),
      NULL,           /* base_init */
      NULL,           /* base_finalize */
      (GClassInitFunc) class_init,
      NULL,           /* class_finalize */
      NULL,           /* class_data */
      sizeof (ServerObject),
      0,              /* n_preallocs */
      (GInstanceInitFunc) NULL /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
                                   "ServerObjectType",
                                   &info, 0);
  }
  return type;
}


void init (ServerObject *server) {
	GError *error = NULL;
	DBusGProxy *driver_proxy;
	ServerObjectClass *klass = SERVER_OBJECT_GET_CLASS (server);
	unsigned int request_ret;

	/* Register DBUS path */
	dbus_g_connection_register_g_object (klass->connection,
			"/org/gnome/ServiceName",
			G_OBJECT (server));

	/* Register the service name, the constant here are defined in dbus-glib-bindings.h */
	driver_proxy = dbus_g_proxy_new_for_name (klass->connection,
			DBUS_SERVICE_DBUS,
			DBUS_PATH_DBUS,
			DBUS_INTERFACE_DBUS);

	if(!org_freedesktop_DBus_request_name (driver_proxy,
			"org.gnome.ServiceName",
			0, &request_ret,    /* See tutorial for more infos about these */
			&error))
	{
		g_warning("Unable to register service: %s", error->message);
		g_error_free (error);
	}
	g_object_unref (driver_proxy);

}

gint main(gint argc, gchar **argv) {

    ServerObject *s = NULL;
    
    g_type_init();
    
    s = server_object_new();    
    

	loop = g_main_loop_new(NULL, FALSE);
    init(s);

	g_main_loop_run(loop);
	g_print("\n");
	return 0;
}

