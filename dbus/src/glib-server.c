#include <dbus/dbus-glib-bindings.h>

/* Standard GObject class structures, etc */
typedef struct
{
	DBusGConnection *connection;
}ServerObjectClass;

class_init(ServerObjectClass *klass)
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
	dbus_g_object_type_install_info (OBJECT_TYPE_SERVER, &dbus_glib__object_info);
}

init(ServerObject *server)
{
	GError *error = NULL;
	DBusGProxy *driver_proxy;
	ServerObjectClass *klass = SERVER_OBJET_GET_CLASS (server);
	int request_ret;

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
