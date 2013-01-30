# Django

----
# Creando una vista simple

Podemos poner en views.py

    !python
    from django.http import HttpResponse

    def index(request):
        return HttpResponse("Hello, world. You're at the poll index.")

Si bien esa vista es correcta, tenemos que explicarle a Django a que
URL corresponde. Para eso definimos un "URLConf". Un URLConf es un módulo con
un atributo `urlpatterns`, que contiene tuplas (*patrón*, *funcion*, *argumentos*, *nombre*). Los
dos últimos son opcionales.

----
# Un URLConf básico

Creamos `polls/urls.py`:

    !python
    from django.conf.urls import patterns, url

    from polls import views

    urlpatterns = patterns('',
        url(r'^$', views.index, name='index')
    )

Todavía Django no sabe que existe este URLConf hasta que no este conectado con
el URLConf “raíz”

----
# El root de los URLConfs

En settings.py dice:

    !python
    ROOT_URLCONF = 'cuchuflito_com.urls'

En `cuchuflito_com/urls.py` agregamos:

    !python
    from django.conf.urls import patterns, include, url
    import admin.site

    urlpatterns = patterns('',
        url(r'^admin/', include(admin.site.urls)),
        url(r'^polls/', include('polls.urls')),
    )

Ahora podemos ver una vista, y también un 404.

----
# La función `url`

* una regex
    * con posible captura de parametros: `(?P<nombre>regex)`
    * NO matchean *query strings*
* la vista
    * por nombre
    * o la función
* kwargs: argumentos adicionales
* name: un identificador (para poder construir URLs)
* namespace: para agrupar names

El primer arguemnto de `patterns` se combina con los nombres de views, cuando
se pasan como strings

----
# Más vistas

Estás son ligeramente distintas: tienen un argumento

    !python
    def detail(request, poll_id):
        return HttpResponse("You're looking at poll %s." % poll_id)

    def results(request, poll_id):
        return HttpResponse("You're looking at the results of poll %s." % poll_id)

    def vote(request, poll_id):
        return HttpResponse("You're voting on poll %s." % poll_id)

Las conectamos:

    !python
    url(r'^(?P<poll_id>\d+)/$', views.detail, name='detail'),
    url(r'^(?P<poll_id>\d+)/results/$', views.results, name='results'),
    url(r'^(?P<poll_id>\d+)/vote/$', views.vote, name='vote'),

----
# Repasando el proceso

1. El browser manda un request, llega al server
2. El server construye el `HttpRequest`, identifica la URL `/polls/42/vote/?x=3`
3. Se busca en el `ROOT_URLCONF` cual URL coincide con `polls/42/vote/`
4. Se encuentra `^polls/` que envía a `polls.urls`. Se recorta la parte que coincide (`polls/`)
5. Se busca en `polls.urls` cual URL coincide con `polls/42/vote/`
6. Se encuentra `^(?P<poll_id>\d+)/vote/$` que asocia a la vista `polls.views.vote`. Se captura `poll_id=42`
7. Se invoca `response = polls.views.vote(request, poll_id=42)`
8. Se decodifica `response` como una respuesta HTTP y se contesta al browser

----
# Vistas que hagan algo útil

La vista tiene que devolver un `HttpResponse` o levantar una excepción como `Http404`.
Sin restricciones de como lo logra. Usemos el ORM de django:

    !python
    from polls.models import Poll

    def index(request):
        latest_poll_list = Poll.objects.order_by('-pub_date')[:5]
        output = ', '.join([p.question for p in latest_poll_list])
        return HttpResponse(output)

Las 5 encuestas mas recientes, por fecha de publicación

Modificar la visualización requiere tocar código. Podemos mejorar?

----
# Plantillas

Creamos `polls/templates/polls/index.html`

    !html
    <html>
    <head><title>Lo último en encuestas!</title></head>
    <body>
        {% if latest_poll_list %}
            <ul>
            {% for poll in latest_poll_list %}
                <li><a href="/polls/{{ poll.id }}/">{{ poll.question }}</a></li>
            {% endfor %}
            </ul>
        {% else %}
            <p>No hay encuestas.</p>
        {% endif %}
    </body>
    </html>

Para que esto tenga sentido necesitamos hacerle *render* con un *contexto*

----
# Usando plantillas

Modificamos...

    !python
    from django.template import Context, loader

    def index(request):
        latest_poll_list = Poll.objects.order_by('-pub_date')[:5]
        template = loader.get_template('polls/index.html')
        context = Context({
            'latest_poll_list': latest_poll_list,
        })
        return HttpResponse(template.render(context))

* Dónde busca los templates el loader

----
# Shortcuts

El módulo `django.shortcuts` tiene varios atajos que cruzan varias capas pero
dan features comunes. Por ejemplo “cargar un template, crear un contexto, renderizar,
generar un `HttpResponse`”.

    !python
    from django.shortcuts import render

    def index(request):
        latest_poll_list = Poll.objects.all().order_by('-pub_date')[:5]
        context = {'latest_poll_list': latest_poll_list}
        return render(request, 'polls/index.html', context)

* Ya no necesitamos HttpResponse
* Notar que `render` también toma el `request` para que?

----
# 404s

Una vista puede devolver un 404, cuando no todos los valores del patrón son
un recurso existente

    !python
    from django.http import Http404

    def detail(request, poll_id):
        try:
            poll = Poll.objects.get(pk=poll_id)
        except Poll.DoesNotExist:
            raise Http404
        return render(request, 'polls/detail.html', {'poll': poll})

Por ahora el `detail.html` es básico:

    !html
    {{ poll }}

----
# Otro shortcut

Otro patrón muy común: obtener un objeto de la DB, y si no existe generar
un 404

    !python
    from django.shortcuts import render, get_object_or_404
    # ...
    def detail(request, poll_id):
        poll = get_object_or_404(Poll, pk=poll_id)
        return render(request, 'polls/detail.html', {'poll': poll})

También hay un `get_list_or_404` más infrecuente.

----
# Más sobre manejo de errores

Se produce un 404 cuando:

* No hay un URLConf que matchee
* La vista levanta la excepción `Http404`
* La vista devuelve un `HttpResponse` con status = 404

Se produce un 500 en caso de excepción

* En modo debug, hay páginas prehechas para 404 y 500
* Sino, entrar a lo que diga `handler404` (o 500) en el URLConf raíz.
* El default es `django.views.defaults.page_not_found()`
* Trata de renderizar un `404.html` o `500.html`

----
# Un poco más de templates:

Podemos completar un poco nuestro `detail.html`

    !html
    <h1>{{ poll.question }}</h1>
    <ul>
    {% for choice in poll.choice_set.all %}
        <li>{{ choice.choice_text }}</li>
    {% endfor %}
    </ul>

Además, podemos eliminar hardcoding en `index.html`:

    !html
    ...
    <li><a href="{% url 'detail' poll_id=poll.id %}">{{ poll.question }}</a></li>

----
# Evitando colisiones de nombres

Los nombres de URLs se pueden agrupar en namespaces. Podemos cambiar el urlconf raíz

    !python
    ...
    url(r'^polls/', include('polls.urls', namespace="polls")),
    ...

Y luego actualizar el link anterior a 

    !html
    ...
    <li><a href="{% url 'polls:detail' poll_id=poll.id %}">{{ poll.question }}</a></li>

----
# Ejercicios

1. Hacer una pantalla para resultados, que diga cuantos votos tenga cada opción

----
# Como no manejar POSTs

----
# Un formulario para votar

Esto en `detail.html`

    !html
    <h1>{{ poll.question }}</h1>

    {% if error_message %}
        <p><strong>{{ error_message }}</strong></p>
    {% endif %}

    <form action="{% url 'polls:vote' poll_id=poll.id %}"
          method="post">
    {% csrf_token %}
    {% for choice in poll.choice_set.all %}
        <input type="radio" name="choice"
               id="choice{{ forloop.counter }}" value="{{ choice.id }}" />
        <label for="choice{{ forloop.counter }}">{{ choice.choice }}</label>
        <br />
    {% endfor %}
    <input type="submit" value="Vote" />
    </form>

----
# Algunas cosas para mirar

* Protección contra pedidos externos: `csrf_token`
* Cadenas de llamadas en templaets
* Variables mágicas como `forloop.counter`
* Usamos POST (para cambiar etado)

Hace falta un cambio menor en la vista para que renderice:

    !python
    def detail(request, poll_id):
        p = get_object_or_404(Poll, pk=poll_id)
        return render(request, 'polls/detail.html', {'poll': p})

----
# Una implementación

    !python
    from django.http import HttpResponseRedirect
    from django.core.urlresolvers import reverse
    # ...
    def vote(request, poll_id):
        p = get_object_or_404(Poll, pk=poll_id)
        try:
            selected_choice = p.choice_set.get(pk=request.POST['choice'])
        except (KeyError, Choice.DoesNotExist):
            # Redisplay the poll voting form.
            return render(request, 'polls/detail.html', {
                'poll': p,
                'error_message': "You didn't select a choice.",
            })
        else:
            selected_choice.votes += 1
            selected_choice.save()
            # El patrón usual POST/redirect/get:
            return HttpResponseRedirect(
                reverse('polls:results', args=(p.id,)))
            # shortcut: return redirect('polls:results', p.id)

----
# Es horrible!

----
# Forms

Django implementa una clase form donde definimos de forma abstracta un form
de HTML y su mapeo a python. resuelve conversion de datos, validación, rendering,
y más. Creamos un `polls/forms.py`

    !python
    from django import forms
    from polls.models import Choice

    class VoteForm(forms.Form):
        choice = forms.ModelChoiceField(queryset=Choice.objects.all())

        def __init__(self, *args, **kwargs):
            poll = kwargs.pop('poll')
            super(VoteForm, self).__init__(*args, **kwargs)
            self.fields['choice'].queryset = poll.choice_set.all()

----
# Forms (en la vista)

Lo usamos en la vista:

    !python
    def vote(request, poll_id):
        if request.method != 'POST':
            return HttpResponse("Solo para POST", status=405)
        poll = get_object_or_404(Poll, pk=poll_id)
        form = VoteForm(request.POST, poll=poll)
        if form.is_valid():
            choice = form.cleaned_data['choice']
            choice.votes += 1
            choice.save()
            return redirect('polls:results', poll_id=poll.id)
        else:
            return render(request, 'polls/detail.html', {'poll': poll, 'form': form})

----
# Renderizando en templates

    !html
    <form action="{% url 'polls:vote' poll_id=poll.id %}"
          method="post">
        {% csrf_token %}
        {{ form.as_p }}
        <input type="submit" value="Vote" />
    </form>

Para que esto ande hay que ajustar un poquito la vista de detail:

    !python
    def detail(request, poll_id):
        poll = get_object_or_404(Poll, pk=poll_id)
        form = VoteForm(poll=poll)
        return render(request, 'polls/detail.html',
            {'poll': poll, 'form': form})

----
# Customizando look

Queremos radio buttons, no un selector:

    !python
    class VoteForm(forms.Form):
        choice = forms.ModelChoiceField(
            queryset=Choice.objects.all(),
            widget=forms.RadioSelect,
            empty_label=None,
        )

Hay varios widgets y se pueden agregar.

----
# El patrón usual

    !python
    def vista(request):
        if request.method == 'POST':
            form = FormClass(request.POST)
            if form.is_valid():
                lanzar_misiles()
                return redirect('otra_vista')
        else:
            form = FormClass()
        context = {'form': form, ... }
        return render(request, 'plantilla.html', context)


