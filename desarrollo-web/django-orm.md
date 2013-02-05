# Django: el ORM

----
# Campos

A nivel clase, `nombre = models.***Field(...)`. Algunos tipos básicos:

* `CharField` y `TextField`; `max_length`
* `IntegerField`, `PositiveIntegerField`
* `BigIntegerField`, `SmallIntegerField`
* `FloatField` vs. `DecimalField`; `max_digits` y `decimal_places`
* `BooleanField` y `NullBooleanField`
* `DateField`, `DateTimeField` y `TimeField`
* `EmailField`, `IPAddressField`, `URLField`; `max_length`
* `SlugField`
* `AutoField`

----
# Argumentos generales

* `null` vs `blank`
* `default` (valor o *callable*)
* `choices`
* `help_text`
* `primary_key`
* `unique`
* `validators`
* `verbose_name`

----
# Meta-opciones

En el modelo se pueden definir algunas opciones generales:

    !python
    class Poll(models.Model):
        ...
        class Meta:
            ordering = ['campo1', 'campo2']
            unique_together = [('campo1', 'campo2')]
            managed = true
            order_with_respect_to = 'owner'
            permissions = [('can_vote', 'Can vote?')]
            verbose_name = 'poll'
            verbose_name_plural = 'polls'

Las más usuales son las de arriba

---
# Relaciones: Foreign Key

En el caso más simple:

    !python
    poll = models.ForeignKey(Poll)

Además de una clase, se puede usar `'Poll'` o `'polls.poll'`. Esto también
agrega un campo a la clase relacionada:

    !python
    p = Poll(...)
    p.choice_set.all()

Se puede renombrar `choice_set` cambiando el `related_name` de la FK.

El borrado se hace en cascada por defecto, se puede fijar `on_delete` para
customizar.

----
# Relaciones: Foreign Key

Se pueden fijar condiciones:

    !python
    poll = models.ForeignKey(Poll, limit_choices={'published': False})

Las claves del diccionario se pueden fijar a cualquier cosa que se use en un
filter. Los valores pueden ser callables.

    !python
    poll = models.ForeignKey(Poll,
        limit_choices={'publish_date__lte': datetime.now}
    )

----
# Relaciones: Foreign Key

Acceder a un campo FK busca en la BBDD la primera vez:

    !python
    c = Choice(...)
    print c.poll # Esto accede a la BBDD
    print c.poll # Esto NO accede a la BBDD, cache

Notar la performance de este patrón:

    !python
    cs = Choice.objects.filter(....)
    for c in cs:
        print c.poll.question # O(N) consultas!

Con lo cual usualmente se utiliza:

    cs = Choice.objects.filter(....).select_related('poll'):
    for c in cs:
        print c.poll.question # 1 consulta

----
# Relaciones: Many to Many

Se declaran similar a una FK:

    !python
    class Poll(models.Model):
        ...
        visitors = models.ManyToMany('auth.User')

* También soportan `limit_choices_to`, `related_name`
* Se pueden hacer a `'self'`, con `symmetrical=True` o a `False`.

----
# Relaciones: Many to Many

Se implementan con una tabla intermedia. Se puede controlar esa tabla
intermedia:

    !python
    class Poll(models.Model):
        ...
        visitors = models.ManyToMany('auth.User', through='Visit')

    class Visit(models.Model):
        visitor = models.ForeignKey('auth.User')
        poll = models.ForeignKey(Poll)
        last_visit = models.DateTimeField()

----
# Relaciones: Many to Many

El atributo de instancia da un *manager* parecido a *objects*:

    !python
    p = Poll(...)
    print p.visitors.all()
    print p.visitors.filter(email__endswith='@machinalis.com')

Pero tiene algunas operaciones extra:

    !python
    p.visitors.add(usuario1, usuario2)
    p.visitors.remove(usuario1)
    p.visitors.clear()
    p.visitors.create(username='pepe', ...)

Estas operaciones también están en el related de un FK

----
# Relaciones 1 a 1

    !python
    class Profile(models.Model):
        ...
        address = models.TextField()
        user = models.OneToOneField('auth.User')

* Se modela reusando claves primarias. Un lado siempre es 'nullable'
* Acepta las mismas opciones que `ForeignKey`
* Define el nombre reverso sin `_set`. Ojo con las colisiones

----
# Campos para archivos

Los campos `FileField`, `ImageField` guardan una ruta, mapeada a un archivo:

    !python
    class Profile(models.Model):
        picture = models.ImageField(upload_to='/users/profiles')

Se puede configurar el `storage` para mapear a otros archivos. Al acceder
al campo se obtiene un `FieldFile`, sobre el cual se puede operar:

    !python
    from django.core.files import File

    pic = user.profile.picture
    pic.open()
    ... # pic.read(), pic.write()
    pic.close()
    pic.save('prueba.txt', File(...), save=True)
    pic.delete(save=True)
    print pic.path, pic.url

----
# Realizando consultas

Sobre un manager, o un queryset:

* `filter` y `exclude`
* `order_by`
* `distinct`
* `none`, `all`
* `[...]` (slicing de querysets)
* `get`
* `count`, `exists`

Para condiciones más complicadas se pueden usar *Q objects*

----
# Q objects

    !python
    from django.db.models import Q

    m = Modelo.objects.filter(Q(x=0)|Q(y=0))

* Cada objeto Q representa una condición. Se arman como los filtros, y se pueden
operar con `&`, `|` y `~`.
* Las funciones que aceptan filtros, aceptan `Q`s

----
# Lookups

* `(i)exact`
* `gt(e)`, `lt(e)`
* `range`
* `(i)contains`, `(i)startswith`, `(i)endwith`, `(i)regex`
* `in`
* `isnull`

----
# Consultas entre campos:

Si quiero obtener los posts de blog que tienen la misma cantidad de comentarios
que de likes:

    !python
    from django.db.models import F

    m = Post.objects.filter(comentarios=F('likes'))

O más comentarios que el doble de likes:

    !python
    from django.db.models import F

    m = Post.objects.filter(comentarios__gt=F('likes') * 2)

En general los F soportan operaciones. notese que describen una operación, pero
no se calcula nada hasta evaluarse la consulta. Las operaciones tienen que ser
cosas que la BBDD sepa hacer

----
# Aggregation

    !python
    >>> from django.db.models import Avg, Max, Count
    # Total number of books with publisher=BaloneyPress
    >>> Book.objects.filter(publisher__name='BaloneyPress').count()
    73
    # Average price across all books.
    >>> Book.objects.all().aggregate(Avg('price'))
    {'price__avg': 34.35}
    # Max price across all books.
    >>> Book.objects.all().aggregate(m=Max('price'))
    {'m': Decimal('81.20')}
    # Each publisher, each with a count of books as a "num_books" attribute.
    >>> pubs = Publisher.objects.annotate(num_books=Count('book'))
    >>> pubs
    [<Publisher BaloneyPress>, <Publisher SalamiPress>, ...]
    >>> pubs[0].num_books
    73
    # The top 5 publishers, in order by number of books.
    >>> pubs = Publisher.objects.annotate(num_books=Count('book')).order_by('-num_books')[:5]
    >>> pubs[0].num_books
    1323

----
# Updates

Ademas de hacer `save` o `delete` de una instancia de un modelo:

    !python
    p, created = Poll.objects.get_or_create(question='Color favorito?')
    Poll.objects.filter(publish_date=d).update(published=False)
    Poll.objects.filter(published=False).delete()

A `get_or_create` ademas uno le peude pasara `defaults` (no son parte de
la búsqueda, pero si de el seteo de los campos)

En `update` se pueden usar `F` objects:

    !python
    Choice.objects.filter(poll=p).update(votes=F('votes')-1)

----
# Herencia: abstracta

    !python
    class BaseArticle(models.Model):
        name = models.CharField(...)
        description = models.TextField()

        class Meta:
            abstract = True
            
    class Article(BaseArticle): ...
    
    class BlogPost(BaseArticle): ...

En la abstracta:

* Se reusan elementos, cada clase tiene sus campos
* no hay forma de hacer consultas unificadas

----
# Herencia: concreta

    !python
    class Negocio(models.Model):
        direccion = models.CharField(...)
        telefono = models.TextField()

            
    class Rotiseria(Negocio):
        vende_doble_muzza = models.BooleanField()

    class Supermercado(Negocio):
        abre_24_hs = models.BooleanField()

* Se implementa con un OneToOne en cada hijo
* Los campos comunes estan en una tabla comun
* Se pueden hacer consultas globales...
* ...pero se obtienen objetos del tipo general, hay que bajar explícitamente

----
# Validación

La instancia de modelo tiene un `is_valid()` y un `full_clean()`. Además de
validators, se puede definir validación redefiniendo `clean()` 
(que genere `ValidationError`s)

    !python
    def clean(self):
        from django.core.exceptions import ValidationError
        # Don't allow draft entries to have a pub_date.
        if self.status == 'draft' and self.pub_date is not None:
            raise ValidationError('Draft entries may not have a publication date.')
        # Set the pub_date for published items if it hasn't been set already.
        if self.status == 'published' and self.pub_date is None:
            self.pub_date = datetime.datetime.now()

Normalmente uno no invoca esto directamente
