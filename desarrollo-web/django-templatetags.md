# Django: templates avanzados

----
# Customizando el lenguaje

Lo puede hacer cualquier app instalada agregando un paquete:

    polls/
        templatetags/
            __init__.py
            poll_tags.py
        ...

El template lo carga con:

    !html
    {% load poll_tags %}

La biblioteca puede proveer *tags* o *filtros*

    !html
    {{ var|mi_tag }}
    {% mi_filtro var var %}
    {% if var|mi_tag %} ...

----
# Definiendo bibliotecas

En todas, uno necesita algo como:

    !python
    from django import template

    register = template.Library()

La biblioteca provee métodos `register.filter` y `register.tag` que se
pueden usar de forma directa o como decoradores

----
# Filtros simples

Un filtro es una función que toma un argumento o dos.

    !python
    @register.filter
    def gritar(value, arg=0):
        return value.upper() + "!"*arg

Entonces si nuestro contexto tiene `saludo="hola"`, podemos hacer

    !html
    {{ saludo|gritar }}    {# HOLA #}
    {{ saludo|gritar:10 }} {# HOLA!!!!!!!!!! #}

----
# Filtros: procesado de string

Si lo que filtramos no es un string, nuestro filtro va a fallar.
Como muchos filtros trabajan sobre strigns, hay un shortcut para esto

    !python
    from django.template.defaultfilters import stringfilter

    @register.filter
    @stringfilter
    def gritar(value, arg=0):
        return value.upper() + "!"*arg

    !html
    {{ persona|gritar }}         {# JUAN PEREZ #}
    {{ persona.edad|gritar:10 }} {# 42!!!!!!!!!! #}

----
# Escapado en filtros

Un filtro que devuelve un string es por defecto escapado (en un template que
tiene prendido el autoescape). si sabems que estamos generando contenido listo
para consumir podemos marcar la salida como *safe*:

    !python
    from django.utils.safestring import mark_safe

    @register.filter
    @stringfilter
    def gritar_html(value):
        return mark_safe("<strong>%s</strong>" % value.upper)

Entonces ahora:

    !html
    {{ persona|gritar_html }}        {# <strong>JUAN PEREZ</strong> #}
    {{ dibujo_animado|gritar_html }} {# <strong>TOM & JERRY</strong> #}

El segundo ejemplo rompió el HTML. Hay que ser más cuidadoso:

----
# Escapado en filtros

Un filtro que devuelve un string es por defecto escapado (en un template que
tiene prendido el autoescape). si sabems que estamos generando contenido listo
para consumir podemos marcar la salida como *safe*:

    !python
    from django.utils.html import conditional_escape

    @register.filter(needs_autoescape=True)
    @stringfilter
    def gritar_html(value, autoescape=None):
        if autoescape:
            esc = conditional_escape
        else:
            esc = lambda x: x
        return mark_safe("<strong>%s</strong>" % esc(value.upper()))

----
# Templatetags

* El mecanismo de definición de tags es muy flexible.
* Es bastante tedioso construir un tag de 0: hace falta un función de 
  parseo/compilación, y un nodo, con una funcion de render
* Mismas consideraciones sobre escaping

Por suerte los casos simples estan “prearmados”:

* un tag que evalua una función, con argumentos
* un tag que incluye otro template
* un tag que setea una variable de contexto

----
# `simple_tag`

Soporta sintaxis compleja

    !html
    {% my_tag 123 "abcd" book.title warning=message|lower profile=user.profile %}

Para definirlo:

    !python
    @register.simple_tag
    def my_tag(arg1, arg2, arg3, **kwargs):
        return "salida"

Se puede acceder al contexto:

    !python
    @register.simple_tag(takes_context=True)
    def otro_tag(context, arg1, arg2, arg3, **kwargs):
        return "salida"

----
# `assignment_tag`

Modifica el contexto sin salida:

    !html
    {% recomendados request.user producto as rs %}
    {% for p in rs %} ...

Se usa similar a simple_tag, pero se devuelve el valor a asignar

    !python
    @register.assignment_tag
    def recomendados(usuario, producto):
        return ...

----
# `inclusion_tags`

Son customizaciones ligeras de `{% include %}`:

    !python
    @register.inclusion_tag('polls/results.html`)
    def show_results(poll):
        choices = poll.choice_set.all()
        return {'choices': choices}

Acepta argumentos similares a los anteriores

