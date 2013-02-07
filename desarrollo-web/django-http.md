# Django: HTTP

----
# Request objects

Cada request tiene varios atributos: `request.`

* `method`
* `GET` y `POST`. No usen `REQUEST`
* `path`: sin dominio. Su primo `path_info`
* `body`
* `COOKIES`

----
# QueryDicts

El contenido de GET y POST no es exactamente un diccionario:

* Los que vienen no son mutables (se puede hacer `copy`)
* `.getlist(key [, default])`
* `.iterlists()`
* `.setlist(key, list)`
* `.urlencode()`

----
# Usuarios

* `request.user` se setea al usuario identificado por django.contrib.auth:
* `is_anonymous()` / `is_authenticated()`
* `has_perm(permission)`
* `username`, `first_name`, `last_name`

Más adelante vemos máß autenticación

----
# Sesiones

Se porta como un diccionario, pero persiste entre requests. Tiene además:

* `flush()`
* `set_test_cookie()` / `test_cookie_worked()` / `delete_test_cookie()`
* `set_expiry()` / `get_expire_...`

A veces no es ideal (¿cuándo?). Pensar en el caso "muchos tabs"

* `./manage.py cleanup`

----
# Construyendo URLs

* `get_host()`
* `get_full_path()`
* `build_absolute_uri_location()`

----
# Otros metadatos

* `META`
    * `HTTP_...`
* `is_secure()`
* `is_ajax()`

----
# Stream de contenido

El contenido de un request se puede manejar como un archivo. Es iterable y
tiene métodos `read()`, `readline()`, etc.

Esto es útil para APIs:

 * implementaciones de PUT
 * interacción con AJAX que postea JSON o XML

----
# Manejando archivos

El atributo `FILES` contiene archivos subidos

* Cuándo hay `<input>`s con `type="file"`
* Cuándo el `enctype="multipart/form-data"`
* Los claves corresponden a los `name` del input
* Los valores son `UploadedFile` (con `read` y `chunks`)

----
# Response

Los instancia uno (directa o indirectamente). Lo que hace falta es:

* Contenido (obligatorio)
* `content_type` (`text/html` por default)
* `status_code` (200 por default)

----
# Headers y Cookies

Varios headers se setean solos. El response se porta como un diccionario

    !python
    response['X-Cuchuflito'] = 'yes'

Los campos de cookie se pueden controlar con:

* `set_cookie(key, value, max_age, expires, path)`
* `delete_cookie`

----
# Contenido

Se puede generar contenido como un file-like

* `write()`
* `flush()`

Alternativamente, se puede pasar como contenido un file-like

----
# Subclases

Nada que no se peuda hacer con `HttpRequest`, pero es mas simple:

* `HttpResponseRedirect` y la version permanent.
* `HttpResponseNotFound` / `Http404`
* `HttpResponseServerError`
* y otros para 304, 400, 403, 405, 410

