# Django: staticfiles

----
# Archivos estáticos

* Generados por el desarrollador
* No cambian (en cantidad ni en contenido) durante el funcionamiento de la
  aplicación.
* Se sirve directamente su contenido por GET
* No tienen reglas lógicas (autenticación, acciones en POST  u otro tipo de
  ejecución de código)
  
Típicamente:

* imágenes
* css / javascript
* a veces, HTMLs no dinámicos

----
# El problema

Se puede hacer fácil una vista que los devuelva, pero:

* es tedioso de mantener
* o propenso a problemas de seguridad
* y es poco eficiente

----
# django.contrib.staticfiles

1. Poner el contenido estático en el lugar estándar
    * *app*`/static/`
    * o donde diga `settings.STATICFILES_DIRS`
2. Poner `django.contrib.staticfiles` en `INSTALLED_APPS`
3. Hacer que las URLs relevantes apunten correctamente
    * donde indica `settings.STATIC_URL`

----
# Desde templates

Supongamos el default `settings.STATIC_URL == "/static/"`

No es buena idea hardcodear urls `/static/imagenes/foto.jpg`

Conviene:

    !html
    {% load staticfiles %}
    <img src="{% static 'imagenes/foto.jpg' %}" />

Notar que también funciona con variables. En código viejo pueden encontrar el
arcaíco

    !html
    {% load staticfiles %}
    <img src="{{ STATIC_URL }}imagenes/foto.jpg" />


----
# Para servir esto

Queremos que efectivamente se mapeen las urls `/static/...` a los archivos,
donde sea que estén

* Con `runserver`... listo. Los sirve el servidor de desarrollo
    * *grossly inefficient*
    * *probably insecure*
    * *should never be used in production*

Si usamos otro server local, en `urls.py`, solo con `DEBUG=True`:

    !python
    from django.contrib.staticfiles.urls import staticfiles_urlpatterns
    ...
    urlpatterns += staticfiles_urlpatterns()

----
# En producción

1. Definir un directorio donde van a estar los elementos estáticos
2. Configurar en `setttings.py` `STATIC_ROOT` al directorio anterior
3. Correr `./manage.py collectstatic`
4. Mapear en el webserver `/static/*` (o lo que diga `STATIC_URL`) al
   directorio anterior

El último paso es bien dependiente de cual server usarmos; hay que asegurar
que sea consistente con `STATIC_URL`

----
# Sirviendo “media”

* Generados por el usuario (a través de la aplicación)
* Cambian (en cantidad y/o en contenido) durante el funcionamiento de la
  aplicación
* Se sirve directamente su contenido por GET
* No tienen reglas lógicas (autenticación, acciones en POST  u otro tipo de
  ejecución de código)

Típicamente:

* uploads de usuario (imágenes, documentos)
* documentos generados persistentes

----
# No hay receta mágica

* Hay `MEDIA_ROOT` y `MEDIA_URL`
* Los `FileField` los saben usar para guardar y generar URLs
* Pero no hay nada que los sirva (ni siquiera runserver)

Para desarrollo esta la receta:

    !python
    if settings.DEBUG:
        urlpatterns += patterns('',
            url(r'^media/(?P<path>.*)$', 'django.views.static.serve', {
                'document_root': settings.MEDIA_ROOT,
            }),
       )

----
# En producción

Lo anterior tiene los problemas de siempre, por eso `if settings.DEBUG`. En
realidad

1. Se define `MEDIA_ROOT`
2. Se apunta el webserver para que mapee apropiadamente `/media/` a lo que diga
   `MEDIA_ROOT`

En un entorno multiserver, hay que ver bien quien guarda los datos, quien los
sirve, y como se comunican


