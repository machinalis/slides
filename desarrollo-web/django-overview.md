# Django

----
# Aplicaciones web dinámicas

* Servidas por HTTP
* Los recursos están “generados”
* Las operaciones sobre recursos van más allá del servidor HTTP

----
# Patrón MVC

* Models, Views, Controllers
* En entornos tradicionales
* En la web
* Model/template/view

----
# Un ejemplo: encuestas

----
# Frameworks

* inversión de control
* comportamiento default
* extensible

----
# Django: el framework

* Componentizado
    * bajo acoplamiento / alta cohesión
* Poco código necesario (no al boilerplate)
    * Basado en convenciones
* DRY
* Explicit is better than implicit
    * Pero con defaults razonables y claros
* Foco en experiencia “consistente”

----
# Model layer

* Explicit is better than implicit: se incluye información de dominio (más rico que SQL)
* Orientado a BBDD relacionales

Se incluye un ORM:

* Sintaxis compacta, poderosa (cubre la mayoría de los casos comunes)
* SQL eficiente autogenerado
* Se puede pasar fácil a SQL a mano

----
# URL routing

## La mitad “superior” del controller

* bien desacoplado del resto
* muy flexible
* alienta buenas prácticas
* facil de generar URLs “definitivas”

----
# Vistas

* Simplicidad (función request -> response)
* El pedido es un objeto
* Bajo acomplamiento
* Se invocan por recurso(URL), no por método(get, post, ...)

----
# Plantillas

* Separa lógica de presentación
* Disminuye redundancia
* No sólo sirve para HTML
* Requiere comprensión de código
* pero no es un lenguaje de programación
* Seguro
* Extensible

----
# Crédito

This work is licensed under the Creative Commons Attribution-Noncommercial-Share Alike 2.5 Argentina License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/2.5/ar/ or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.

Basado en el curso de Django © 2008 Except S.A.


----
# Templates

