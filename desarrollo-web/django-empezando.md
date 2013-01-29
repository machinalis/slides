# Django

----
# Empezando

Típicamente trabajamos en un virtualenv donde instalamos `django` y lo
que vayamos a necesitar para base de datos (nada para sqlite, `psycopg2` para
postgres, etc). Después se crea un proyecto:

    !sh
    $ django-admin.py startproject cuchuflito_com
    $ cd cuchuflito_com/
    $ ls
    cuchuflito_com  manage.py
    $ ls cuchuflito_com/
    __init__.py  settings.py  urls.py  wsgi.py


`manage.py` es lo mismo, pero local, que `django-admin.py`:

    !sh
    $ python /ruta/a/django-admin.py help
    $ python /ruta/a/django-admin.py help startproject # u otro cmd
    $ python manage.py help
    $ python manage.py help startproject # u otro cmd


----
# Listo!

Bueno, al menos tenemos un servidor de desarrollo

    !sh
    $ ./manage.py runserver
    Validating models...

    0 errors found
    Django version 1.4.3, using settings 'cuchuflito_com.settings'
    Development server is running at http://127.0.0.1:8000/
    Quit the server with CONTROL-C.

Empezamos con algo de config básica:

    !sh
    $ edit cuchuflito_com/settings.py

----
# settings.py 

El archivo de settings es python:

    !python
    ...
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.sqlite3',
            'NAME': 'cuchuflito.db',
    ...
    TIME_ZONE = 'America/Cordoba'
    LANGUAGE_CODE = 'es-ar'

* Los settings son “globales”

----
# Aplicaciones

* ¿Que es una aplicación? (en Django)
* `INSTALLED_APPS`

Por ejemplo:

    !python
    INSTALLED_APPS = (
        'django.contrib.auth',
        'django.contrib.contenttypes',
        'django.contrib.sessions',
        'django.contrib.sites',
        'django.contrib.messages',
        'django.contrib.staticfiles',
    )

* ¿Qué es contrib?

----
# Actualizando la BBDD:

Cada aplicación define sus modelos que se mapean a la base:

    !sh
    $ ./manage.py syncdb 
    Creating tables ...
    Creating table auth_permission
    Creating table auth_group_permissions
    Creating table auth_group
    Creating table auth_user_user_permissions
    Creating table auth_user_groups
    Creating table auth_user
    Creating table django_content_type
    Creating table django_session
    Creating table django_site

    You just installed Django's auth system, which means you don't have any superusers defined.
    Would you like to create one now? (yes/no): yes
    Username (leave blank to use 'dmoisset'): 
    E-mail address: dmoisset@machinalis.com
    Password: 
    Password (again): 
    Superuser created successfully.
    Installing custom SQL ...
    Installing indexes ...
    Installed 0 object(s) from 0 fixture(s)

----
# Creando una aplicación

Una aplicación es un “paquete python” cualquiera. Hay algunas convenciones de
donde ponerlas. Por ahora no nos preocupamos.

    !sh
    $ ./manage.py startapp polls
    $ ls polls/
    __init__.py  models.py  tests.py  views.py

En `models.py` definimos modelos:

    !python
    from django.db import models

    class Poll(models.Model):
        question = models.CharField(max_length=200)
        pub_date = models.DateTimeField('date published')

    class Choice(models.Model):
        poll = models.ForeignKey(Poll)
        choice = models.CharField(max_length=200)
        votes = models.PositiveIntegerField()

----
# “Instalando” la aplicación

En el settings file:

    !python
    INSTALLED_APPS = (...
        'django.contrib.staticfiles',
        'polls',
    )

Antes de hacer el sync, exploremos:

    !sql
    $ ./manage.py sql polls
    BEGIN;
    CREATE TABLE "polls_poll" (
        "id" integer NOT NULL PRIMARY KEY,
        "question" varchar(200) NOT NULL,
        "pub_date" datetime NOT NULL
    );
    CREATE TABLE "polls_choice" (
        "id" integer NOT NULL PRIMARY KEY,
        "poll_id" integer NOT NULL REFERENCES "polls_poll" ("id"),
        "choice" varchar(200) NOT NULL,
        "votes" integer unsigned NOT NULL
    );
    COMMIT;

----
# Sincronizando la BBDD, de nuevo

Podemos (opcionalmente) ver que este todo OK:

    !sh
    $ ./manage.py validate
    0 errors found

OK, la hora de la verdad

    !sh
    $ ./manage.py syncdb
    Creating tables ...
    Creating table polls_poll
    Creating table polls_choice
    Installing custom SQL ...
    Installing indexes ...
    Installed 0 object(s) from 0 fixture(s)

Sólo se agregaron las tablas nuevas. Las otras no se tocan

----
# Manejando la base de datos

Para borrar, podemos pedir el SQL y correrlo a mano

    !sql
    $ ./manage.py sqlclear polls
    BEGIN;
    DROP TABLE "polls_choice";
    DROP TABLE "polls_poll";
    COMMIT;

* Django nunca borra tablas
* Django nunca modifica tablas
* Si cambiamos el modelo, hay que actualizar a mano
    * Borrar las tablas y volver a correr syncdb
    * Usar una herramienta como south

----
# Explorando la BBDD

El comando shell levanta un interprete con el entorno del proyecto configurado:

    !sh
    $ python manage.py shell
    Python 2.5.2 (r252:60911, Sep 29 2008, 21:15:13) 
    [GCC 4.3.2] on linux2
    Type "help", "copyright", "credits" or "license" for more information.
    (InteractiveConsole)
    >>> █

Si tienen ipython (recomendado) usa eso

----
# Explorando la BBDD (2)

Podemos importar los modelos y explorar la API:

    !python
    >>> from polls.models import Poll, Choice

    # Esto es un comentario -- No hay encuestas, todavía.
    >>> Poll.objects.all()
    []

    # Creamos una nueva encuesta.
    >>> import datetime
    >>> p = Poll(question=u"Cómo vá?", pub_date=datetime.datetime.now())

    # Grabamos el objeto Poll en la BD
    >>> p.save()
    # Ahora ya tiene un identificador (ID)
    >>> p.id
    1

    # Accedemos a columnas a través de atributos del objeto, con Python.
    >>> p.question
    u'Cómo vá?' # posiblemente codificado (acentos)
    >>> p.pub_date
    datetime.datetime(2008, 10, 28, 18, 40, 21)

----
# Explorando la BBDD (3)

Ahora que hay datos en la BBDD se pone más interesante:

    !python
    # Cambiamos valores modificando dichos atributos y
    # llamando a save().
    >>> p.pub_date = datetime.datetime(2008, 10, 31, 0, 0)
    >>> p.save()

    # objects.all() muestra todas las encuestas que hay e la BD.
    >>> Poll.objects.all()
    [<Poll: Poll object>]

* `objects` expone las operaciones sobre conjuntos. Es llamado el *manager*.
* La representación de los objetos por default es un poco aburrida, pero redefinible

----
# Ajustando representación

Y ya que estamos, metemos métodos de instancia:

    !python
    ...
    import datetime

    class Poll(models.Model):
        ...
	    def __unicode__(self):
		    return self.question

	    def was_published_today(self):
		    return self.pub_date.date() == datetime.date.today()

    class Choice(models.Model):
        ...
	    def __unicode__(self):
		    return self.choice

----
# Explorando la BBDD (4)

    !python
    $ python manage.py shell
    [...]
    >>> from polls.models import Poll, Choice

    # Buscamos el objeto que ya hemos agregado usando un atajo provisto
    # idéntico a usar Poll.objects.get(id=1).
    >>> Poll.objects.get(pk=1)
    <Poll: Cómo vá?>
    # (notar que la representación cambió)

    # Probamos nuestro método was_published_today().
    >>> p = Poll.objects.get(pk=1)
    >>> p.was_published_today()
    False # No estamos en Halloween

    >>> Poll.objects.all()
    [<Poll: Cómo vá?>]

    # Django provee una API para consultas a la BD basada en argumentos 
    # 'keyword'.
    >>> Poll.objects.filter(id=1)
    [<Poll: Cómo vá?>]
    >>> Poll.objects.filter(question__startswith=u'Cómo')
    [<Poll: Cómo vá?>]

----
# Más consultas

    !python
    # Buscamos la encuesta del año 2008:
    >>> Poll.objects.get(pub_date__year=2008)
    <Poll: Cómo vá?>

    >>> Poll.objects.get(id=2)
    Traceback (most recent call last):
        ...
    DoesNotExist: Poll matching query does not exist

    # Creamos un par de objetos Choice relacionados a la encuesta:
    >>> p = Poll.objects.get(pk=1)
    >>> p.choice_set.create(choice='Todo bien', votes=0)
    <Choice: Todo bien>
    >>> p.choice_set.create(choice='Bastante mal', votes=0)
    <Choice: Bastante mal>
    >>> c = p.choice_set.create(choice='Preocupado', votes=0)

----

    !python
    # Los objetos Choice tiene disponible una API para acceder a sus
    # objetos Poll relacionados.
    >>> c.poll
    <Poll: Cómo vá?>

    # y viceversa: objetos Poll pueden acceder a objetos Choice.
    >>> p.choice_set.all()
    [<Choice: Todo bien>, <Choice: Bastante mal>, <Choice: Preocupado>]
    >>> p.choice_set.count()
    3

    # La API sigue automáticamente las relaciones tanto como sea
    # necesario sin que existan limitaciones arbitrarias.
    # Usamos doble guión bajo para separar relaciones.
    # Encontrar todos los Choices para cquier. Encuesta cuya fecha
    # de publicación sea durante el año 2008.
    >>> Choice.objects.filter(poll__pub_date__year=2008)
    [<Choice: Todo bien>, <Choice: Bastante mal>, <Choice: Preocupado>]

    # Por último veamos como borrar una de las opciones de la
    # encuesta con el método .delete().
    >>> c = p.choice_set.filter(choice__startswith='Preocupado')
    >>> c.delete()

----
# Ejercicios

1. Poner a funcionar esto,
2. Agregarle interfaz administrativa, según: <https://docs.djangoproject.com/en/1.4/intro/tutorial02/>

