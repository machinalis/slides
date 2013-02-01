# Django: vistas

----
# Vistas genéricas

----
# Vistas genéricas:

Muchos patrones comunes, DRY:

* detalle de un objeto
* Listado de objetos con algún criterio
* formulario GET/POST
* edición de un objeto
* mostrar un template fijo
* archivo de objetos por fecha
* ...

----
# CBGV

* Reemplazan un mecanismo anterior basado en funciones
* configuracion/extensión más legible
* jerarquía de clases algo compleja

Están todas en `django.views.generic`

Documentación en: <https://docs.djangoproject.com/en/1.4/topics/class-based-views/>

También es útil: <http://ccbv.co.uk/>

----
# Más de una forma de hacerlo:

El método `as_view` de clase fabrica y configura vistas.

    !python
    # 1) urls.py
        url(..., TemplateView.as_view(template_name='page.html'))

    # 2) views.py
        pagina = TemplateView.as_view(template_name='page.html')

    # 3) views.py
        class Paginita(TemplateView):
            viewfunc = 'page.html'
            ...
        pagina = Paginita.as_view()

----
# Un ejemplo

Nuestro índice de polls:

    !python
    from django.views.generic import ListView

    class LatestPolls(ListView):
        queryset = Poll.objects.order_by('-pub_date')[:5]
        context_object_name = 'latest_poll_list'
        template_name = 'polls/index.html'
    index = LatestPolls.as_view()

* defaults vs. valores customizados
* settings alternativos: `queryset` vs `model`
* valores de clase vs métodos

----
# Redefiniendo métodos

Supongamos que los polls tienen dueño:

    !python
    class LatestPolls(ListView):
        ...
        def get_queryset(self):
            return Polls.objects.filter(owner=request.user)

En el `self` hay:

* request
* args y kwargs (del router de urls)
* Otras cosas específicas de la vista (ej: `object_list`)

----
# Ejemplo 2

    !python
    url(r'^(?P<pk>\d+)/$',
        DetailView.as_view(
            model=Poll,
            template_name='polls/detail.html')),
            ...

El nombre del kwarg `pk` importa.

La página de resultados se puede hacer igual (con otro template)

----
# Uno con forms:

    !python
    class PollVote(FormView):
        form_class = VoteForm

        def post(self, request, *args, **kwargs):
            self.object = get_object_or_404(Poll, pk=self.kwargs['pk'])
            return super(PollVote, self).post(request, *args, **kwargs)

        def form_valid(self):
            self.object.votes += 1
            self.object.save()
            return redirect('polls:vote', self.object.pk)

* Cuándo usar o no `super()`

----
# El flujo normal

Cuando llega un request

* Se instancia una nueva instancia de la clase
* Se llama a `dispatch`. Este setea `request`, `args`, `kwargs`
* `dispatch` llama a `get`, a `post` o quien corresponda
* El metodo empieza seteando atributos específicos (`object` u `object_list`, por ej)
* Lo que se devuelve, es el resultado de la vista

----
# Algunas no tan genéricas:

* `View` y `TemplateView`
* redefinir `template_name` o `get_template`
* redefinir `get_context_data`

----
# Templates

----
# Variables

Lookup de variable `{{ var.lookup }}`:

* Diccionario: `var["lookup"]`
* Atributo: `var.lookup`
* Llamada a método: `var.lookup()`
* Acceso a índice (si lookup es entero): `var[lookup]`

----
# Filtros

* Sin argumentos: `{{ name|lower }}`
* Con argumentos: `{{ name|truncatewords:30 }}`
* Se puede componer: `{{ text|escape|linebreaks }}`
* Se pueden usar variables `{{ article.date|date:DATE_FORMAT }}`

----
# Tags

* Los más importantes:
    * for/empty/endfor
    * if/else/endif
    * debug
    * include
    * comment
    * load

Tambien se pueden poner commentarios con `{# comentario #}`. De una línea

----
# Herencia

* `extends`
* `block`

Cascada de herencia y anidado.

----
# Escaping

* orientado a html
* Filtro `|safe`
* Tag `autoescape`
* string literals y escaping


