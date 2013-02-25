# Apps surtidas

----
# Debug toolbar

* Performance (CPU, SQL)
* HTTP, routing
* Templates, contextos
* signals

----
# Debug toolbar

    !python
    DEBUG_TOOLBAR_PANELS = (
        'debug_toolbar.panels.version.VersionDebugPanel',
        'debug_toolbar.panels.timer.TimerDebugPanel',
        'debug_toolbar.panels.settings_vars.SettingsVarsDebugPanel',
        'debug_toolbar.panels.headers.HeaderDebugPanel',
        'debug_toolbar.panels.request_vars.RequestVarsDebugPanel',
        'debug_toolbar.panels.template.TemplateDebugPanel',
        'debug_toolbar.panels.sql.SQLDebugPanel',
        'debug_toolbar.panels.signals.SignalDebugPanel',
        'debug_toolbar.panels.logger.LoggingPanel',
    )

    DEBUG_TOOLBAR_CONFIG = {
        'INTERCEPT_REDIRECTS': False,
    }

----
# Django pagination

    !html
    {% load pagination_tags %}
    ...
    {% autopaginate object_list %}
    ... o bien ...
    {% autopaginate object_list 10 %}
    ...
    {% paginate %}

----
# Django filters

Se definen filtros declarativos

    !python
    import django_filters

    class ProductFilter(django_filters.FilterSet):
        price = django_filters.NumberFilter(lookup_type='lt')
        class Meta:
            model = Product
            fields = ['price', 'release_date']

Y la vista:

    !python
    def product_list(request):
        f = ProductFilter(request.GET, queryset=Product.objects.all())
        return render_to_response('my_app/template.html', {'filter': f})

----
# Django filters (2)

La plantilla

    !html
    <form action="" method="get">
        {{ filter.form.as_p }}
        <input type="submit" />
    </form>
    {% for obj in filter %}
        {{ obj.name }} - ${{ obj.price }}<br />
    {% endfor %}

También hay una vista genérica (`FilterView`)

----
# Django sorting

Similar a pagination:

    !html
    {% load sorting_tags %}
    ....
    {% autosort object_list %}
    ....
    <tr>
       <th>{% anchor first_name Name %}</th>
       <th>{% anchor creation_date Creation %}</th>
        ...
    </tr>

----
# South

* Los esquemas de BBDD cambian
* Problema similar a control de revisiones
    * Pero con datos a conservar

----
# Migraciones

Una migración describe:

* Un esquema de base de datos (restringido a una app)
* Como llegar a ese esquema, como revertir
* Dependencias

Cada uno tiene un identificador numérico, uno textual. La lógica es en python

----
# Instalando south

* pip install, agregar a `INSTALLED_APPS`
* pero no termina ahí...
    * south *modifica* el comando syncdb
    * south agrega un comando *migrate* (y otros)

Ahora para sincronizar la base de datos:

    !sh
    $ ./manage.py syncdb
    $ ./manage.py migrate

----
# Cual es la idea

* South mete tablas de datos en la misma base de datos para controlar cuales
  migraciones fueron aplicadas
* Si hay migraciones (archivos python) en una app, pero no estan en la base de
  datos, faltan aplicar
* `migrate` las aplica en orden
* `migrate --list` indica cuales estan aplicadas

----
# Arrancando

Para cada hay hay que crear una migración que describe el estado inicial (lo que
antes hacía el syncdb)

    !sh
    ./manage.py schemamigration polls --initial

Esto crea un `migrations/0001.initial`, que se puede aplicar. Si ya tenía la
base de datos, va a fallar. Se puede:

    !sh
    ./manage.py schemamigration polls --fake

----
# Cambiando el esquema

Después de editar el `models.py`,

    !sh
    $ ./manage.py schemamigration southtut --auto
    + Added field dances_whenever_able on southtut.Knight
    Created 0002_auto__add_field_knight_dances_whenever_able.py. You
     can now apply this migration with: ./manage.py migrate southtut

Esto crea el archivo que se puede aplicar

    !sh
    $ ./manage.py migrate
    - Migrating forwards to 0002_auto__add_field_knight_dances_whenever_able.
    > southtut:0002_auto__add_field_knight_dances_whenever_able
    - Loading initial data for southtut.

----
# En equipo

* Cada migración va a crear un archivo distinto
* No hay un conflicto del SCV, pero si algo para resolver
* A la hora del merge/rebase, prestar atención
* Guardar las migraciones para recrearlas
* Agregar la migración justo antes de commitear
* Comunicación

----
# Algunos casos raros

    !sh
    $ ./manage.py schemamigration southtut --auto
     ? The field 'Knight.shrubberies' does not have a default specified, yet is NOT NULL.
     ? Since you are adding or removing this field, you MUST specify a default
     ? value to use for existing rows. Would you like to:
     ?  1. Quit now, and add a default to the field in models.py
     ?  2. Specify a one-off value to use for existing columns now
     ? Please select a choice:

No todas las migraciones son reversibles:

    !python
    raise RuntimeError("Cannot reverse this migration.")

----
# Migraciones de datos

A veces cambia la semántica de los datos, no la estructura

    !sh
    $ ./manage.py datamigration southtut2 hash_passwords
    Created 0003_hash_passwords.py.

Hay que escribir el código a mano:

    !python
    def forwards(self, orm):
        import random, sha, string
        for user in orm.User.objects.all():
            user.password_salt = "".join([random.choice(string.letters) for i in range(8)])
            user.password_hash = sha.sha(user.password_salt + user.password).hexdigest()
            user.save()

No hay migraciones mixtas, se puede hacer en varios pasos

----
# Dependencias entre apps

Para campos de relación, es necesario que las clases relacionadas existan:

    !python
    class Migration:

        depends_on = (
            ("accounts", "0003_add_user_profile"),
        )

----
# Algunos tips

* Tener en mente “que les va a pasar a los demás cuando corran esto”
* eso incluye otros desarrolladores y producción
* Avisar al equipo cuando uno trabaja en migraciones (sincronizar y acordar)
* Cambiar las migraciones es como cambiar la historia (pero vale meter “fixes”)
* Tener cuidado con los “metadatos” de la migración (al mergear y tocar a mano)

