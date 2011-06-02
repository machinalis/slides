# GConf

----
# The GNOME configuration database

----
# The GNOME configuration database API

----
# Qué es?

## Un sistema para que el desktop y las aplicaciones en GNOME almacenen *opciones de configuración*
  
----
# Motivación(1)

## Antes de GConf...

Cada aplicación usaba su formato propio:

    !ini
    [Config]
    auto_hide_step_size=18
    use_large_icons=false
    menu_flags=26634

 * Inconsistencia
 * Duplicacion de codigo (parsers)
 * La pesadilla del sysadmin

---
# Motivación(2)

## GConf es

 * Amigable para el sysadmin
    * Interfaz unificada
    * Soporte de defaults de sistema
    * Soporte de *lockdown*
 * Instant-apply
    * Arquitectura MVC
 * Soporte para multiproceso

----
# ¿Cómo lo logra?

 * API para almacenar pares clave/valor
 * Servicio de notificación para poder compartir configuración
 * Arquitectura de  almacen via Plugins
 * Configuración autodocumentable
 * Layering de fuentes de configuración

----
# Cosas que GConf NO es

 * Un almacen para datos arbitrarios
    * La aplicación no puede suponer acceso de escritura
 * Un almacen para configuración de sistema
    * Con los defaults la aplicación debería funcionar

----
# Arquitectura

 * API de GConf
 * GConf daemon
 * Storage
    * XML
    * LDAP
    * Berkeley DB
    * ...

----
# El demonio de GConf

 * Detalle de implementación
    * Actualmente funciona por CORBA
    * Posiblemente el sistema pase a usar DBUS
 * La activación por CORBA lo levanta automáticamente
    * comunicacion por pipes/sockets
    * soporta transparencia en red
 * Hace posible la process transparency
 * Sabe irse solo
   
----
# Contenido del storage

 * Los datos se guardan en una jerarquía
    * Ej: `/apps/gedit-2/preferences/editor/` 
 * Cada valor tiene un key (una cadena)
 * Los valores son tipados:
    * Tipos primitivos: int, bool, string, float
    * Listas: de tipos primitivos
    * Pares: de dos tipos primitivos, iguales o distintos

----
# Donde está el storage

 * Dónde *yo* quiera: `/etc/gconf/2/path`

Ejemplo:

    !sh
    xml:readonly:/etc/gconf/gconf.xml.mandatory
    include "$(HOME)/.gconf.path"
    xml:readwrite:$(HOME)/.gconf
    xml:readonly:/etc/gconf/gconf.xml.defaults

 * La búsqueda se hace en orden, de arriba hacia abajo

----
# Formato del storage

 * Depende del backend que usemos
 * El "estándar" es el llamado `xml`
 * La jerarquía usa directorios de filesystem

Por ejemplo:
 
    !sh
    $ cd .gconf
    $ ls apps/gedit-2/preferences/editor/
    auto_indent       colors        %gconf.xml    right_margin  wrap_mode
    bracket_matching  current_line  line_numbers  tabs

Y en `apps/gedit-2/preferences/editor/tabs/%gconf.xml`

    !xml
    <?xml version="1.0"?>
    <gconf>
	    <entry name="insert_spaces" mtime="1283015506" type="bool" value="false"/>
	    <entry name="tabs_size" mtime="1278448272" type="int" value="4"/>
    </gconf>

----
# Formato del storage(2)

Para tipos más complicados

    !xml
    <?xml version="1.0"?>
    <gconf>
	    <entry name="active-plugins" mtime="1301630776" type="list" ltype="string">
		    <li type="string">
			    <stringvalue>markdownpreview</stringvalue>
		    </li>
		    <li type="string">
			    <stringvalue>indent</stringvalue>
		    </li>
		    ...
		    <li type="string">
			    <stringvalue>spell</stringvalue>
		    </li>
	    </entry>
    </gconf>

También se puede armar jerarquía en el XML:

    !xml
    <dir name="apps">
        <dir name="empathy">
            ...
        </dir>
    </dir>
----
# Schemas

 * Un *schema* describe un conjunto de opciones de configuración
 * También se guardan en el store! Debajo de `/schemas`

Ejemplo:
 
    !xml
    <entry name="autoconnect" mtime="1269733493" 
           schema="/schemas/apps/empathy/autoconnect"/>
    ...
    <entry name="autoconnect" mtime="1269733493" type="schema" 
           stype="bool" owner="empathy" gettext_domain="empathy">
        <local_schema locale="C" 
                      short_desc="Empathy should auto-connect on startup">
            <default type="bool" value="true"/>
            <longdesc>
                Whether or not Empathy should automatically log in to
                your accounts on startup.
            </longdesc>
        </local_schema>
    </entry>

----
# Convenciones del store

 * Cada apliación pone sus cosas en `apps/`nombre
    * Es buena idea categorizar
 * Se reserva `desktop`, `system`, y `schemas`
    * `schemas` tiene un espejo del árbol
 * Los nombres de claves son minúsculas, con guíones bajos.
 * Los colores se guardan como en HTML
 * Las enumeraciones se guardan como strings
 * Los atajos de teclado van en `keybindings`
 
----
# Herramientas útiles: gconftool-2

    !sh
    $ gconftool-2 -R /desktop/gnome
    $ gconftool-2 --get /schemas/apps/gcalctool/mode

 * Puede leer, escribir, borrar
 * Puede generar schemas
 * Puede instalar archivos con esquemas en el directorio apropiado
 * Stress-tests
 
----
# Herramientas útiles: gconfeditor

----
# API

El caso simple:

    !c
    GConfClient *client = NULL;
    gchar *s = NULL;

    client = gconf_client_get_default();
    string = gconf_client_get_string(client,
                                     "apps/gcalctool/mode",
                                     NULL
                                    );

Para compilar: `pkg-config gconf-2.0.pc`

----
# API

La escritura es igual de fácil:

    !c
    gconf_client_set_string(client,
                            "apps/gcalctool/mode", "SCIENTIFIC"
                            NULL
                           );

Lo interesante es la notificación:

    !c
    void notificacion (GConfClient *client,
                       guint cnxn_id,
                       GConfEntry *entry,
                       gpointer user_data);

----
# Notificación

Tenemos que indicar que partes nos interesan:

    !c
    gconf_client_add_dir(client, "apps/gcalctool", 
                         GCONF_CLIENT_PRELOAD_NONE, NULL);

Con eso podemos anotarnos a la señal `value_changed` del cliente. Pero
normalmente es más práctico usar:

    !c
    gconf_client_notify_add(client, "apps/gcalctool/mode",
                            notification, NULL,
                            NULL, NULL);

Esto además devuelve un `guint` que identifica la asociación, y puede usarse
luego.

----
# Notificación(2)

En la función notificadora, recibimos un GConfEntry

    !c
    GConfValue *v = NULL;
    g_print("key=%s", gconf_entry_get_key(entry));

    v = gconf_entry_get_value(value);
    g_assert(v->type == GCONF_VALUE_STRING);
    g_print("key=%s", gconf_value_get_string(v));

Mas detalles de la API en <http://developer.gnome.org/gconf/stable/>

----
# GConfEngine

En genral no hace falta/no hay que usarlo. Pero los siguientes son
útiles:

    !c
    GConfEngine *gconf_engine_get_for_address   (const gchar *address,
                                                 GError **err);
    GConfEngine *gconf_engine_get_for_addresses (GSList *addresses,
                                                 GError **err);

----
# Recomendaciones

 * Solo guardar *preferencias*.
 * Usar MVC
 * Chequear `gconf_client_key_is_writable()` en la UI
    * Se puede testear sacando la linea de `readwrite`
 * Los valores leídos son *untrusted*.
 * Nunca modificar una clave de GConf al recibir una notificación

----
# Compatibilidad

 * Las configuración debe ser compatible hacia atrás y **hacia adelante**
 * Si me logueo en dos lugares, usando dos versiones, debería funcionar
 * Concesión: puede que para configurar dos versiones haya que hacerlo 2 veces. 
   no es ideal pero es aceptable
   
Lograr esto implica:

 * Al cambiar el conjunto de valores válidos, o sus interpretaciones, renombrar la clave
 * Si no se renombra, no se pueden agregar valores
 * Al renombrar, se puede hacer que se copie/convierta el valor viejo. No borrar la anterior
 
----
# Lo que se viene

## GSettings

 * Por ahora, solo dos backends
    * dconf en UNIX
    * El registry del sistema en Windows
 * Interoperables
 * Conceptualmente similares
    * Algo de soporte transaccional

