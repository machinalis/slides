#GLib

----
# GLib NO es

## Glibc (GNU C Standard Library)
## Nada que ver con GL / OpenGL

----
# GLib es

## Una bolsa de “utilidades”

----
# GLib: genealogía

 * En los principios existía GIMP
 * Los componentes reusables de GIMP se volvieron GTK+
 * Los componentes no gráficos de GTK+ se volvieron GLib

----
# Entonces GLib puede usarse...

## Para casi cualquier cosa, con UI o no 
## (puede verse como una extensión de la biblioteca estándar)

## *“GLib provides the core application building blocks for libraries and applications written in C.”*

----
# Algunas características

 * Puro C (nada de C++!)
 * Portable (OS/plataforma)
 * Bien mantenido (último release estable 2.28.6, el 14 de abril de 2011)
 * Licencia: LGPL
 * Ubicua en sistemas GNU/Linux

----
# Bueno... pero ¿qué hay en GLib?

 * Tipos y estructuras de datos simples y complejos (desde enteros hasta hash tables)
 * Herramientas portables para threading (threads, semáforos, mutexes, colas sincronizadas...)
 * Infraestructura para aplicaciones basadas en eventos (main loop y señales)
 * Un sistema de tipos y orientación a objetos 

----
# Bueno... pero ¿qué hay en GLib?

Y también:  logging, timers, unit-testing, I/O asíncrono, conversión de endian, reporte de errores, constantes matemáticas, conversiones de charset, operaciones de fecha y hora, cargado de módulos en runtime, parsers, manejo de URIs, manejo de línea de comandos, expresiones regulares, internacionalización, ...

----
# Alternativas

 * C++ con STL
 * Apache Portable Runtime
    * Menos estructuras, más IPC
 * WxBase
    * Pegado a WxWidgets
 * QtCore
    * En C++
    * Pegado a Qt

----
# No voy a hablar de 

 * Como compilar GLib
    * Instalen el paquete de desarrollo
 * Estructuras de datos complejas
    * Si usan C++, usen la STL o Boost
 * Las infinitas funciones auxiliares
    * Lean el manual: http://developer.gnome.org/glib/ 
    * Instalen devhelp

----

# GLib: A los bifes

----

# Hello World

Un programa que usa una función de GLib

    !c
    /* hello-glib.c */

    #include <glib.h>

    gint main(gint argc, gchar **argv) {
	    if (!GLIB_CHECK_VERSION (2, 2, 0))
		    g_error ("GLib version 2.2.0 or above is needed");
	    g_print("%s\n", "Hello World!");
	    return 0;
    }

Compilando:

    !sh
    $ gcc $(pkg-config --cflags glib-2.0) -c hello-glib.c
    $ gcc $(pkg-config --libs glib-2.0) hello-glib.o -o hello-glib
    $ ./hello-glib 
    Hello World!

----

# `pkg-config`

Se originó en GTK, pero se independizó. Ahora se usa para muchas bibliotecas
(en Linux)

    !sh
    $ pkg-config --cflags glib-2.0
    -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include  
    $ pkg-config --libs glib-2.0
    -lglib-2.0  

Las ventajas:

 * El mantenimiento de flags lo hace el programador/empaquetador de la biblioteca, no el usuario
 * Mensajes de error más sensatos si nos hace falta algo
 * `Makefile`s más entendibles

----
 
# `pkg-config` para GLib

Hay varios módulos

 * `glib-2.0`: dónde está casi todo
 * `gthread-2.0 gobject2.0`: El sistema de tipos de GObject
 * `gmodule-2.0` ó `gmodule-no-export-2.0`: Carga de módulos en runtime
 
Algunos hints:

 * Se pueden pasar muchos paquetes a `pkg-config`
 * Se puede usar `--libs` y `--cflags` a la vez para programas autocontenidos. 

---- 
# Tipos básicos

 * GLib define `gint`, `gchar`, `gdouble`, ... “por completitud”
 * Y para escribir “más fácil”, `gpointer`, `gconstpointer`, `gushort`
 * Y para unificar varios tipos de distintos estándares, `gboolean`, `gsize`, ...
 * Un poco más útil, GLib define tipos con tamaño definido
    * `gint8`, `guint8`, ... `guint64`


Mucho de esto está cubierto por C99

---- 
# Tipos básicos

También se definen constantes asociadas:

 * `G_MAX****`, `G_MIN****`
 * Para impresión, `G_***MODIFIER` y `G_****FORMAT`

Ejemplo:
 
    !c
    gint16 value = G_MAXUINT16;
    g_print ("%" G_GINT16_FORMAT, value);
    g_print ("%#" G_GINT16_MODIFIER "x", value);
 
----
# C “orientado a objetos”

----
# Anatomía de una “clase” de GLib

Las reglas de nombres son muy consistentes y vale la pena aprenderlas:

 * Para cada tipo, hay un `typedef` asociado (ej: `GHashTable`)
   * Al usarlo uno declara punteros (ej: `GHashTable *usuarios;`)
 * Cada tipo define un constructor (ej: `g_hash_table_new`)
   * A veces hay constructores alternativos (`g_hash_table_new_full`)
 * Y un destructor (`g_hash_table_destroy`)
 * Y operaciones (`g_hash_table_insert`, ...)

----
# Ejercicio

Hacer un programa que

 * Al principio levante una hash table que mapee usuarios a contraseñas
 * Luego pregunte en un loop pares usuario/contraseña y los verifique
 * Y que al terminar libere toda la memoria
 
Ejemplo:

    usuarios.txt:
    alejandro AAAAA
    beatriz betty
    carlos password
    diana 123456

----
# Una solución

    !c
    #include <glib.h>
    #include <stdio.h>
    #include <string.h>

    GHashTable *usuarios = NULL;

    void cargar_usuarios(gchar *archivo) {
	    FILE *f = fopen(archivo, "r");
	    gchar usuario[50], clave[50]; 
	    /* Esto es susceptible a buffer overflow. Solo para simplificar el ejemplo */
	
	    usuarios = g_hash_table_new_full(
		    g_str_hash,
		    g_str_equal,
		    g_free,
		    g_free);
	
	    g_warn_if_fail(f!= NULL); /* No habra usuarios disponibles*/

	    while (fscanf(f, "%s %s", usuario, clave) == 2) {
		    g_hash_table_insert(usuarios, g_strdup(usuario), g_strdup(clave));
	    }
	    fclose(f);
    }

----
# Una solución(2)

    !c
    gint main(gint argc, gchar **argv) {
	    cargar_usuarios("usuarios.txt");
	    while (TRUE) {
		    gchar nombre[50];
		    gchar clave[50];
		    gchar *clave_real = NULL;

		    /* Preguntar al usuario */
		    g_print("Usuario: ");
		    fgets(nombre, G_N_ELEMENTS(nombre), stdin);
		    g_print("Clave: ");
		    fgets(clave, G_N_ELEMENTS(clave), stdin);

		    /* Sacar el \n final */
		    nombre[strlen(nombre)-1] = clave[strlen(clave)-1] = '\0';

		    /* Validar */
		    clave_real = g_hash_table_lookup(usuarios, nombre);
		    if (g_strcmp0(clave, clave_real) == 0) {
			    g_print("Usuario %s aceptado!\n", nombre);
		    } else {
			    g_print("Usuario(%s)/clave(%s); inexistente o no coinciden!\n", nombre, clave);
		    }
		
	    }
	    g_hash_table_destroy(usuarios);
	    return 0;
    }

----
# Notas sobre debugging de memoria

 * GLib tiene su propio manejador de memoria que usa `malloc()` por detrás
    * Es más eficiente, práctico, sin sodio, y no daña la capa de ozono
 * Se llama GSlice, y lo van a ver a veces en tracebacks
 * Pero confunde a los debuggers de memoria
 
En el ejemplo anterior, con valgrind

    !sh
    $ valgrind --leak-check=full --show-reachable=yes ./passwords
    ...
    ==28649== LEAK SUMMARY:
    ==28649==    definitely lost: 0 bytes in 0 blocks
    ==28649==    indirectly lost: 0 bytes in 0 blocks
    ==28649==      possibly lost: 1,744 bytes in 6 blocks
    ==28649==    still reachable: 5,418 bytes in 13 blocks
    ==28649==         suppressed: 0 bytes in 0 blocks

----
# Apagando GSlice

    !sh
    $ export G_SLICE=always-malloc
    $ valgrind --leak-check=full --show-reachable=yes ./passwords
    ...
    ==28652== LEAK SUMMARY:
    ==28652==    definitely lost: 0 bytes in 0 blocks
    ==28652==    indirectly lost: 0 bytes in 0 blocks
    ==28652==      possibly lost: 0 bytes in 0 blocks
    ==28652==    still reachable: 1,642 bytes in 9 blocks
    ==28652==         suppressed: 0 bytes in 0 blocks

No todos los pools se liberan! Pero está bien hecho, y no crece con el tiempo.

----

# *Quarks* e *interned strings*

Dos formas de tener representaciones *canónicas*

    !c
    #include <glib.h>

    typedef       GQuark;
    GQuark        g_quark_from_string          (const gchar *string);
    GQuark        g_quark_from_static_string   (const gchar *string);
    const gchar * g_quark_to_string            (GQuark quark);
    GQuark        g_quark_try_string           (const gchar *string);

Los *quarks* se usan en varios contextos en GLib, menos frecuentemente se
usan interned strings:

    !c
    const gchar * g_intern_string              (const gchar *string);
    const gchar * g_intern_static_string       (const gchar *string);

----

# Errores

 * Un canal alternativo para informar errores *recuperables*.
 * Algunas funciones toman un `GError **` como último argumento
    * Puede pasarse `NULL`
    * Seteado a `!= NULL` en caso de error.
 * Varias reglas respecto a como usarlo, principalmente relevantes para el
   *productor* (no para el consumidor) de errores.

La información del error es:

    !c
    struct GError {
      GQuark       domain;
      gint         code;
      gchar       *message;
    };

----

# Errores(2)

Las reglas para el consumidor son:

 * No usar si no nos interesa la información del error; en general las funciones
   informan éxito/fallo de formas alternativas
 * Siempre inicializar los `GError *` a `NULL`
 * Cuando uno pasa un `GError`, hacer algo al respecto:
     * Hacer `g_error_free` y retornar
     * Manejar el problema, usar `g_clear_error()` si uno planea seguir.
 * Acordarse del `g_error_free()` después

----

# Ejemplo: Process spawning

Esta es la API de una de las varias funciones de process spawning:

    !c
    gboolean g_spawn_async_with_pipes (const gchar          *working_directory,
                                       gchar               **argv,
                                       gchar               **envp,
                                       GSpawnFlags           flags,
                                       GSpawnChildSetupFunc  child_setup,
                                       gpointer              user_data,
                                       GPid                 *child_pid,
                                       gint                 *standard_input,
                                       gint                 *standard_output,
                                       gint                 *standard_error,
                                       GError              **error);
 
Ejercicio:

  * Usar esto en un programa que genere los numeros del 1 al 100...
  * ...los filtre por 'grep [37]'
  * Y los muestre en la pantalla
 
----

# GObject

 * Herencia simple, interfaces, y carga de tipos en run-time
 * Propiedades introspectables
 * Tipos base
 * Señales
 * Introspección suficiente para automatizar creado de `bindings`
 
Vamos a ver como usar, no como hacer

----

# Reference Counting

 * `g_object_ref()` y `g_object_unref()`
 * El constructor deja el conteo en 1
 * Thread-safe
 * También hay weak references
 
Esto es importante en contextos donde se comparten los objetos:

 * Olvidarse un `unref` produce leaks
 * Olvidarse un `leak` produce fallas y segfaults

----
# Tipos

El sistema de `GType` permite, con una API, definir tipos dados lo siguiente:

 * Tamaño
 * “constructor” / “destructor” de instancia
 * “constructor” / “destructor” de clase (opcional)
 * Funciones de inicialización, liberado, copia, manejo de varargs
 * Algunos flags
 
Uno normalmente nunca define un tipo (aún armando GObjects).
 
----
# Valores encapsulados

Un `GValue` es un contenedor que puede contener un type `GType` y un valor. Son
uno de los pocos tipo diseñados para ser usados sin alocación dinámica:

    !c
    GValue a = {0};
    g_type_init();

    g_value_init (&a, G_TYPE_STRING);
    g_value_set_static_string (&a, "Hello, world!");
    g_print ("%s\n", g_value_get_string (&a));

    g_value_unset (&a);
    g_value_init (&a, G_TYPE_INT);
    g_value_set_int (&a, 42);

Soporta todos los tipos que puede especificar `GType`: básicos, arreglos,
“objetos”, etc.

----
# Properties

El seteo es a través de `GValue`s

    !c
    GObject *bar;
    GValue val = { 0, };

    ...
 
    g_value_init (&val, G_TYPE_CHAR);
    g_value_set_char (&val, '*');

    g_object_set_property (G_OBJECT (bar), "nombre-propiedad", &val);

    g_value_unset (&val);

Notar el “cast” a `G_OBJECT`. En realidad suele hacerse:

    !c
    g_object_set (G_OBJECT (bar), "nombre-propiedad", '*');

----
# Boxed objects

Como definir objetos es engorroso y uno a veces nomás quiere pasar una estructura,
una opcion intermedia es usar `GBoxed`

    !c
    GType g_boxed_type_register_static (const gchar *name,
                                        GBoxedCopyFunc boxed_copy,
                                        GBoxedFreeFunc boxed_free);

Se puede meter cualquier cosa manejada via punteros (ej: objetos de C++)

Ejercicio: Hacer un box para `list<int>`

----

# Signals

El uso es fácil:

    !c
    g_signal_connect(G_OBJECT(objeto), "señal", func, NULL);
 
    ...
 
    tipo func(int arg1, float arg2, gpointer user_data) {
        ....
        return x;
    }

Se puede filtrar un poco:

    !c
    g_signal_connect(G_OBJECT(objeto), "notify::propiedad", func, NULL);

----

# Emisión de señales...

 * El handler puede ser de clase, o de instancia, sin contar “emission hooks”
 * Se pueden bloquear handlers con `g_signal_handler_block()`

Las 5 etapas de emisión se dan secuencialmente, a menos que la emisión se detenga o reinicie:

 1. `RUN_FIRST`: handler de clase (según flags)
 2. `EMISSION_HOOK`: en el orden que se agregaron
 3. `HANDLER_RUN_FIRST`: de primero a último
 4. `RUN_LAST`: handler de clase (según flags) 
 5. `HANDLER_RUN_LAST`: de primero a último. Sin duplicados.
 6. `RUN_CLEANUP`:  handler de clase (según flags) 
 
----

# El main loop

----
# Conceptos

 * El contexto: `GMainContext`
    * Solo uno activo por thread
 * Fuentes: `GSource`
    * Asociados a un contexto
 * Ciclos: `GMainLoop`
    * Asociados a un contexto
    * Anidables

Todos ellos son reference counted, pero no “objetos”

----
# Contextos

 * Usualmente se obtiene con `_default()` o `_get_thread_default()`
 * Y con `_iteration()` se lo hace dar UNA vuelta.
 * Normalmente no se manipulan mucho directamente
 * Para saber si hay eventos, usar `_pending()`

----
# Fuentes

 * Se crean con `_new`, pero recien creadas no hacen nada
 * Hay que hacerle `_attach(contexto)`
 * Se le puede asociar:
    * File descriptors
    * Procesos hijos
    * timeout
    * idle
    * Sources hijos
    * Otra fuente!

----
# Fuentes(2)

 * Rara vez uno define tipos nuevos de fuentes.
 * Para muchos casos iguales ni siquiera hay que instanciar:
    * `g_timeout_add`    
    * `g_idle_add`

----
# Main Loop

 * No hace falta tocarlo mucho:
 * `_run()` y `_quit()` son las cosas mas interesantes que tiene

----
# IO Channels

 * Wrapper de fds / socket
 * La API no tiene nada muy sorprendente
 * se les puede pedir un `GSource` con sus eventos

----
# Ejercicio:

 * Hacer un main loop
   * Leer stdin con un `IOChannel`
   * Mostrar una barra de progreso que cuente hasta 100 bytes
   * Salir a los 100 bytes
   * Mientras mostrar un icono de actividad

