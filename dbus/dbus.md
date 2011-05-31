# D-Bus

----

# "The desktop bus"

----

# ¿Qué es D-Bus?

 * Un sistema de IPC para aplicaciones de escritorio
    * Reemplaza a DCOP
    * Reemplaza a Bonobo
* Estandarizado  por freedesktop
* Soporte para comunicación con el sistema

----
# Origen

 * GNOME usaba Bonobo
    * Basado en CORBA
    * demasiada complejidad
 * KDE usaba DCOP
    * Más apropiado a escritorio
    * Atado a la plataforma
    * espacio de nombres muy plano
 * D-Bus es el acuerdo entre ambos
    * "DCOP", la nueva generación

----
# Comunicación en D-Bus

 * Mensajes asíncronos
    * Mensajes tipados
 * Señales
    * Publish/subscribe
 * Sobre un stream
    * Típicamente UNIX sockets
    * Típicamente cliente/servidor
    * Puede hablarse punto a punto

----
# Arquitectura

 * Los mensajes viajan por un **canal**
    * El canal **de sistema** para alertas de sistema
    * El canal **de sesión** para comunicación entre aplicaciones
 * Los canales tienen **direcciones de conexión**
    * No con fundir con la dirección de canal
 * Las conexiones tienen  un **nombre de bus**
    * Nombre estándar (`:01-234`)
    * Nombre legible `org.freedesktop.Notifications`
 * Las conexiones las recibe un **objeto** en el receptor
 * La acción solicitada por el mensaje es el **método**
 * Un mensaje enviado por una aplicación es una **señal**

----
# Algunas características

 * Pensado para uso asíncrono
 * Agnóstico de escritorio/plataforma
 * Pocas dependencias
 * Independiente de UI
    * Permite implementación por system tools
 * Baja latencia/overhead
 * Codificación binaria
 * API bien establecida
 
----
# Algunas características(2)

 * No transaccional
 * Con estado
 * Basado en conexión
 * Por paso de mensajes

----
# Casos de uso

 * Casos de uso (system bus)
    * PolicyKit
    * DeviceKit
    * NetworkManager
    * PackageKit
 * Casos de uso (desktop bus)
    * Tracker
    * Screen Saver
    * Settings Daemon

----
# Ejemplo

`dbus-send` permite armar ejemplos "a mano"

    !sh
    $ dbus-send --print-reply 
                --type=method_call
                --dest=org.gnome.Rhythmbox
                /org/gnome/Rhythmbox/Player
                org.gnome.Rhythmbox.Player.setVolume
                double:0.5
    method return sender=:1.40 -> dest=:1.400 reply_serial=2
    $ dbus-send --print-reply 
                --type=method_call
                --dest=org.gnome.Rhythmbox
                /org/gnome/Rhythmbox/Player
                org.gnome.Rhythmbox.Player.getVolume
    method return sender=:1.40 -> dest=:1.401 reply_serial=2
       double 0.5

----
# D-feet

----
# Para el programador

 * Un biblioteca `libdbus` permite que dos aplicaciones hablen el protocolo
 * Hay un daemon de canal basado en `libdbus` que lo habla, y rutea mensajes
 * Hay *wrappers* para distintos frameworks de aplicaciones (Glib, Qt, ...)
    * La implementación de referencia es la basada en GLib

----
# Canales y conexiones

 * Uno normalmente se conecta a alguno de los buses estándar
 * Adentro hay conexiones
    * Los nombres de conexiones son únicos (empiezan con `:`), *unique connection name*
    * Una aplicación puede pedir nombres adicionales, *well-known name*
 * Los nombres no se pueden compartir entre conexions

----
# Del lado de la aplicación

 * Cada aplicacion conectada contiene "objetos"
    * Objetos C++
    * Objetos Python
    * GObject
    * QObject
 * Un objeto es una identidad, no un tipo
 * Similar a sistemas de componentes
 * Cada objeto tiene su dirección, el *object path*
 * Las otras aplicaciones suelen usar un "proxy"

----
# Object path

 * Similar a una ruta en el filesystem
    * No son archivos!
 * Jerarquía idealmente basada en DNS para los niveles externos
 * Jerarquía definida para aplicación para niveles internos

----
# Interfaces

 * Cada objeto puede tener *varias* interfaces
    * Una interfaz describe signatura de varios métodos
    * Los nombres de métodos pueden ser distintos
 * La interfaz tiene un nombre jerárquico:
    * ej: `org.gnome.Rhythmbox.Player`
    * Se suele usar la misma jerarquía que el objeto, cuando es una interfaz específica para ese objeto

----
# Mensajes:

 * method call
 * method return
 * signal
 * error

----
# Métodos

 * Nombre simple
 * Múltiples entradas, multiples salidas
 * Tipadas
 * Pueden producir errores
    * Incluyen un nombre y un mensaje
 * Puede usarse de forma asíncrona
 * Se garantiza entrega secuencial de las llamadas
 * Pero las respuestas pueden llegar fuera de orden!
 * El proxy/binding nomralmente se encarga del marshalling

----
# Llamada a métodos, por dentro

 * La aplicación llama al proxy, que genera un mensaje
    * O la aplicación genera un mensaje "a mano"
 * El mensaje contiene una dirección de conexión, path, interfaz, método, argumentos
 * El mensaje es enviado al daemon de canal
 * El daemon mira la dirección de conexión. Si hay un proceso dueño de ese nombre, 
   se le envía el mensaje. Sino, el daemon genera un mensaje de error y lo devuelve.
 * El receptor desempaqueta el mensaje. El mensaje uede convertirse directamente
   o transformarse en una llamada a función de un objeto nativo, y una conversión del
   resultado
 * El demonio de bus recibe la respuesta y la devuelve a su origen
 * El proxy en el origen transforma la respuesta en un valor de retorno o excepción.

----
# Señales

 * Nombre simple
 * Multiples parámetros
 * Sin valores de retorno
 * Sin destinatario explícito
 * El receptor registra "matchers"

----
# Matchers

 * Describen los mensajes que se reciben
    * Basados en interfaces, paths, métodos
 * Esto sirve para:
    * Las aplicaciones se enfocan en manejar lo que les interesa
    * Poder rutear mensajes eficientemente
    * Evitar degradación de performance
 
----
# Servicios   

 * Una aplicación puede ser "dueña" de una dirección
 * Se puede definir una activación
 
Esto permite crear instancias nuevas la primera vez, y reusar las siguientes. 

    !ini
    # bank.service
    [D-BUS Service]
    Names=com.bigmoneybank.Deposits;com.bigmoneybank.Withdrawals
    Exec=/usr/local/bin/bankcounter

----

# El bus de sistema

 * Incluye seguridad
    * Usuarios de sistema
    * Autenticación por UNIX sockets
    * Autorización por archivos de configuración
 
----
# Setup

 * Se pueden lanzar canales con `dbus-launch`
    * Que por dentro corre `dbus-daemon`
 * Los dos toman `--config-file ...`
 * Los dos canales estándar usan:
    * `/etc/dbus-1/system.conf`
    * `/etc/dbus-1/session.conf`

----
# Seguridad

 * Del lado del servidor
 * Para el que hace una aplicación de sistema, conviene hacer un archivo de
   configuración

Ejemplo: `NetworkManager`

----
# Tipos en dbus

 * Tipos básicos:
    * Byte, Boolean
    * Enteros de 16, 32, 64 bits
    * double
    * string
    * object path
 * Arrays
 * Dictionary entry
 * Variant
 
----
# Ejemplo: dbus-glib.c

---
# Definiendo interfaces

!xml
<?xml version="1.0" encoding="UTF-8"?>
<node name="/org/gnome/ServiceName">
	<interface name="org.gnome.ServiceName">
		<annotation name="org.freedesktop.DBus.GLib.CSymbol" value="server"/>
		<method name="EchoString">
			<arg type="s" name="original" direction="in" />
			<arg type="s" name="echo" direction="out" />
		</method>
		<!-- Add more methods/signals if you want -->
	</interface>
</node>

Lo "traducimos con: `dbus-binding-tool --prefix=server_object --mode=glib-client interface.xml`


