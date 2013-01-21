# Introducción al desarrollo web

----
# ¿Qué es la web?

* Un **servicio**
* **distribuido**
* funcionando sobre **internet**
* que ofrece acceso a **documentos** (o *recursos* de **multimedia**)
* conectados entre si por **enlaces**

----
# Es un servicio

* Hay una distinción fuerte entre:
    * El **cliente** (consumidor del servicio)
    * El **servidor** (proveedor del servicio)
* El diseño de protocolos y aplicaciones refleja esta asimetría

----
# Es distribuido

* No hay una entidad que organice centralmente el servicio...
* ...para que funcione, se basa en convenciones
* Hay una entidad central que estandariza convenciones: W3C
    * rol de los "vendors"
* No se pueden dar ciertas garantías
    * estabilidad de links
    * sincronización entre recursos de distintas organizaciones

----
# Funciona sobre internet

* Internet ≠ WWW
* WWW depende de otros servicios de Internet (en especial DNS)
* WWW puede referirse a otros recursos de Internet (por ej ftp, email, telnet, ...)
    * Una de las metas era que sirviera de un índice de internet
* Es de donde viene lo de *world-wide*
* Pero de todos modos, se puede usar de forma bastante "local"
* Consecuencias: Construido sobre servicio confiable, punto a punto, sin
  autenticación ni seguridad

----
# Provee acceso a documentos

* El término usado es **recurso**
* Un recurso es cualquier cosa que puede representarse como un stream de bytes
* Pero además está “tipado” y acompañado por metadatos
    * Se usa el estándar MIME para identificar tipos
* No sólo se ofrece *lectura*, sino también otras operaciones

----
# Conectado por enlaces

* Cada recurso tiene una dirección: una *URL*
* La *URL* es universal: permite acceder al recurso desde otro lado
* Todas las referencias entre recursos se hacen a través de URLs
    * Los enlaces son unidireccionales

----
# La fundación: HTTP

* No, no es HTML. Es HTTP
* HTTP es un protocolo de Internet a nivel aplicación
* Es client/server
* Es request/response
* stateless

----
# Anatomía de una URL

`http://<host>/<path>/<path>/...`

Elementos ocpionales:

* `:<puerto>` (default 80)
* `<usuario>@` o `<usuario>:<password>@`
* `?<key>=<value>&<key>=<value>...`
* `#<fragment>`

Dada una URL, se pueden armar URLs “relativas”

----
# Solicitudes HTTP

* Verbo + ruta (y versión)
* Encabezados
* Opcionalmente, contenido

Ejemplo:

    GET /wiki/World_wide_web HTTP/1.1
    Host: en.wikipedia.org
    User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:18.0) Gecko/20100101 Firefox/18.0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    Accept-Language: en-us,en;q=0.7,es-ar;q=0.3
    Accept-Encoding: gzip, deflate
    Cookie: userbuckets=%7B%22lastModified%22%3A%5B%22expr1%22%2C1%5D%7D; mediaWiki.user.id=OIDHyu0NoxyNg2k6nkAKdaNlNdDC2uLt; mediaWiki.user.bucket%3Aext.articleFeedback-tracking=10%3Atrack; mediaWiki.user.bucket%3Aext.articleFeedbackv5%406-form=6%3A6; mediaWiki.user.bucket%3Aext.articleFeedbackv5%405-links=5%3AX; centralnotice_bucket=0-4.2; mediaWiki.user.bucket%3Aext.articleFeedback-options=8%3Ashow; clicktracking-session=Mp4jNY3HVBXSstdoH0Fo5QBSnNs5uEusE; mediaWiki.user.bucket%3Aext.articleFeedbackv5%4011-tracking=11%3Aignore
    Connection: keep-alive
    If-Modified-Since: Thu, 17 Jan 2013 10:45:02 GMT
    Cache-Control: max-age=0

----
# Respuestas HTTP

* Status code (y versión, y descripción del status)
* Encabezados
* Opcionalmente, contenido

Ejemplo:

    HTTP/1.0 200 OK
    Content-Language: en
    Last-Modified: Thu, 17 Jan 2013 10:45:02 GMT
    Content-Encoding: gzip
    Content-Length: 51331
    Content-Type: text/html; charset=UTF-8
    Date: Thu, 17 Jan 2013 17:18:50 GMT
    Server: Apache
    Cache-Control: private, s-maxage=0, max-age=0, must-revalidate
    X-Cache: HIT from cp1019.eqiad.wmnet, MISS from cp1018.eqiad.wmnet
    Connection: keep-alive

    <!DOCTYPE html>
    <html lang="en" dir="ltr" class="client-nojs">
    ...

----
# Status codes:

El servidor le dice al cliente...

* 2xx: Todo OK
* 3xx: Bueno, pero vas a tener que hacer algo más
* 4xx: No puedo hacer lo que pedís. Es tu culpa
* 5xx: No puedo hacer lo que pedís. Es mi culpa

Ejemplos usuales:

* 200, 204
* 301, 302, 304
* 401, 403, 404
* 500, 502

----
# Verbo `GET`

* Obtener un recurso
* El request va sin contenido
* La respuesta tiene el contenido del recurso
* Se puede pasar algo de info en el query string

La semántica está bien definida:

* Debe ser *safe* (mandarlo 0 ó 1 vez da lo mismo para el servidor)
* Debe ser *idempotent* (mandarlo 1 o muchas veces es lo mismo)

Otro verbo muy parecido: `HEAD`

----
# Algunos encabezados usuales

## En el request:

* `Host` (obligatorio en HTTP/1.1)
* `User-Agent`
* `Accept`, `Accept-Language`, `Accept-Encoding`
* `Connection: keep-alive`
* `If-Modified-Since`
* `Cache-Control`
* `Range`
* `Referer`

----
# Algunos encabezados usuales

## En el response:

* `Content-Type`, `Content-Length`
* `Last-Modified`
* `Server`
* `Date`
* `Cache-Control`
* `Content-Range`

Para las respuestas 30x:

* `Location`

----
# Verbo `POST`

* Técnicamente es para “enviar una entidad subordinada a un recurso”
* En la práctica, eso quiere decir: mandar forms y operaciones que cambian el estado
* El **request** lleva un `Content-Type`, normalmente `application/x-www-form-urlencoded` o sino `multipart/form-data`
* Generalmente no es *safe* ni *idempotent*
* A veces se usa de todos modos para operaciones que lo son

----
# Patrón usual para POST

Cuando un usuario tiene que hacer un `POST`:

1. `GET` de un recurso con un formulario para llenar
2. El usuario llena el formulario, hace click en “submit”, lo que genera un `POST` sobre el mismo recurso
3. El servidor procesa el pedido, contesta con un `302` apuntando a posiblemente *otro* recurso.
4. El cliente hace un `GET` del nuevo recurso, donde se ven los resultados.

En caso de error de procesamiento del paso 2., el servidor en vez contesta `200`,
presentando de nuevo el formulario (típicamente con mensajes de error)

----
# Los otros verbos

* `PATCH`: ni *idempotent*, ni *safe*
* `PUT`: *idempotent*, pero no *safe*
* `DELETE`: *idempotent*, pero no *safe*
* `OPTIONS`:*idempotent* + *safe*

----
# Autenticación

El modelo básico: HTTP-Auth

* El primer request retorna un `401` con un `WWW-Authenticate`
* El cliente pide credenciales al usuario
* El pedido se reenvía con un `Authorization`

Desventajas:

* El pedido se manda dos veces, la info de autorización siempre
* No hay forma de desloguearse
* La UI para loguearse es "estándar"
* Todo viaja en visible
* Vulnerable a man-in-the middle

----
# HTTPS

* Resuelve verificación de identidad *en ambos sentidos*
* Encripta
* Autenticacion de servidor requiere un *trusted third party*
* Para que funcione bien debe cubrir a recursos relacionados
* basado en criptografía de clave pública

----
# Sesiones

Basado en tokens de estado

* Headers `Set-Cookie` y `Cookie`
* Limitaciones de dominio, tamaño
* Uso para autenticación, comparación con HTTP auth

----
# Un rato de práctica: Firebug

----
# Y el resto?

Preview de lo que viene

 * HTML
 * CSS
 * Javascript

----

Ejercicio:

1. Armar un webserver simple con SImpleHTTPServer
2. Armar un formulario de 3 preguntas usando el patron get/redirect/post, con validacion, que guarde el resultado en un archivo
3. Hacer el archivo anterior accesible por GET, con implementación correcta de caching


