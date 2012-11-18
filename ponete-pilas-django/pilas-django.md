# Ponete las pilas con Django

----
# De que se trata esto?

 * Sos desarrollador Django
 * Estás resolviendo problemas y decís “me suena que alguien ya pasó por esto”
 * Estás a punto de enredarte en un problema que alguien más previó
 
----
# Encuesta

* Cuántos desarrolladores Django?
* Cuántos usan más de 5 ó 6 aplicaciones extra en sus proyectos

----
# Disclaimers

* Voy a hacer un paseo superficial por muchas herramientas
* Al final de esta charla no vas a saber usar ninguna de ellas
* Al final de esta charla vas a tener una idea de cuando te sirve cada una
* No todas las herramientas son 100% django, pero al menos se combinan
* No cubro todas las opciones. No se puede

----
# Antes de empezar

## virtualenv + pip

* Más fácil instalar y probar cosas
* Los paquetes de django evolucionan más que cualquier distro
* Permiten tener en sync entornos de desarrollo/producción otros
    * Recomendación: tener un `requirements.txt` en tu VCS
* Para cualquier cosa en python, pero en Django todavía más

----
# Antes de empezar

## ipython

* Como el shell, pero más
* Django lo integra si esta presente

----
# Donde encuentro paquetes

* PyPI
* Google
* djangopackages.com
    * mirar que estén activos

----
# Para el desarrollador

----
# Command extensions

Una bolsa de gatos:

* Graficar modelos
* pre-import de modelos
* runserver concurrente
* ...

----
# Debug toolbar

* Navaja suiza de django
* Información sobre uso de la DB
* Información sobre rendering
* Información de HTTP
* Información de ruteo de URLs

----
# Para el desarrollador: testing

----
# Un runner más lindo

## nose+django-nose

* Plugins fáciles
* Muchos plugins
    * progressive
    * cobertura
* Incluye opciones frecuentemente usadas

----
# Tests indepenientes

## mock

* Próximamente en la stdlib
* Relativamente fácil de usar
* permite desacoplar las capaz al testear con el test client.

----
# Creando casos de test

## factory_boy

* definiciones simples
* mucho más legible que fixtures
* y más eficiente!
* y más robusto!

----
# Para mantener arriba mi sitio

----
# Sobreviviendo a cambios de modelo

## South

* Los cambios de esquema son inevitables
* Escribir los comandos de SQL a mano duele
* Trabajar en equipo es un problema
* Trabajar con múltiples entornos es otro parecido

----
# Monitoreo

## Sentry + raven

* Muy fácil de poner a andar 
* Mucho más cómodo que leer emails con tracebacks
* Puede capturar logs custom
* Hecho en Django!

----
# Herramientas para construir el sitio

----
# Modelando jerarquías

## mptt

* Eficiente para acceso (buscar hijos, cadenas de hijos)
* Las actualizaciones no son caras, pero no son un update de uan fila
* Hay que entender el algoritmo para sacarle el jugo
* No vale la pena en jerarquías fijas

----
# Modelando cambios

## django-reversion

* Muy bueno y “mágico” para seguir modelos simples:
* seguir relaciones es un poc más complicado

----
# Apps prearmadas frecuentemente útiles

* smart-selects
* pagination
* django_filter

----
# La gran bolsa de apps prearmadas

## Pinax

* Mi relación de amor-odio con Pinax

----
# Interactuando con otros servicios web

## requests

* Acceso a HTTP pythonico
* Soporta autenticación surtida (basic auth, oauth)
* integra bien con servicios JSON
* se puede wrappear con slumber

----
# Interactuando con otros servicios web

## pyquery

* interfaz basada en jQuery
* maneja bien HTML y XML
* sabe parsear HTML "real" (más formado)
* Le da vueltas a BeautifulSoup

----
# Ofreciendo servicios web

## tastypie

* nocion de recurso, facil de pegar a modelos
* relativamente facil de hacer separado a modelos
* permite integrar autenticación, autorización

----
# Servicios asíncronos

## celery, django-celery

* Reemplaza a cron
* Ofrece servicios de cola además de periódicos
* Se integra bien

----
# Cerrando

* Hay de todo, y más
* Hay mucho abandonado
* Hay mucho poco documentado
* Hay muchos tesoros

----
# Preguntas?

## dmoisset@machinalis.com

## @dmoisset

----
# Para agregar a la charla

 - model utils?
 - pagination, django_filter
