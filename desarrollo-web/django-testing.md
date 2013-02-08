# Django: testing
----

# Escribiendo tests

* Los tests van en cada app
* `tests.py` o `tests/...`
* `from django.utils import unittest`
* Y de ahí en mas, similar a testing en python
* doctests vs unit tests

Se pueden correr los tests con

    !sh
    $ ./manage.py test [app ...]

----
# Corriendo tests

* `test app.TestCase`
* `test app.TestCase.method`
* `--failfast`
* nose y django-nose

Los tests corren en una db aparte

----
# El cliente de test

Permite testear vistas com si las accedieramos por HTTP:

    !python
    >>> from django.test.client import Client
    >>> c = Client()
    >>> response = c.post('/login/', {'username': 'john', 'password': 'smith'})
    >>> response.status_code
    200
    >>> response = c.get('/customer/details/')
    >>> response.content
    '<!DOCTYPE html...'

Usa rutas, no URLs completas

----
# Métodos importantes:

* `get(path, data={}, follow=False)`
* `post(path, data={}, content_type=MULTIPART_CONTENT, follow=False)`
* `head`, `options`, `put`, `delete`

Por ejemplo:

    !python
    >>> response = c.get('/redirect_me/', follow=True)
    >>> response.redirect_chain
    [(u'http://testserver/next/', 302), (u'http://testserver/final/', 302)]
    >>> c = Client()
    >>> c.post('/login/', {'name': 'fred', 'passwd': 'secret'})

----
# Testing y autenticación:

* `login(**credentials)`
* `logout()`

Por ejemplo, con contrib.auth:

    !python
    >>> c = Client()
    >>> c.login(username='fred', password='secret')
    >>> ...
    >>> c.logout()

----
# Resultado de un pedido

El resultado es un `Response`, no un `HttpResponse`. Tiene más datos:

* `client` y `request`
    * `client.cookies`, `client.session`
* `status_code` y `content`
* `context` y `templates`

----
# `TestCase` de django

Extiende el test case de django

* Incluye un `self.client`
* carga de fixtures (no lo hagan!)
* Aserciones
    * `assertTemplateUsed(response, template_name)` y `NotUsed`
    * `assertRedirects(response, expected_url)`
    * `assertContains(response, text, status_code=200, html=False)` y `NotCointains`
    * `assertFormError(response, form, field, errors)`

----
# Evitando interferencia

* Los tests deberían ser independientes
* Pero la base de dato compartida puede interferir
* Se pueden usar `cleanUp()` con mucha prolijidad...
* O usar `TransactionTestCase`

----
# Hay más en la documentación

<https://docs.djangoproject.com/en/1.4/topics/testing/>

Pero esto es lo que importa

----
# Prácticas de testing

----
# Para que testeamos

## gracias Javi

* asegurar propiedades de lo que estamos codeando
* ayudarnos a que esas propiedades persistan cuando nuevos cambios aparezcan
* ayudarnos a explorar algunos casos raros mientras codeamos
* debuggear
* documentar

----
# Propiedades deseables de los tests

1. que sean fáciles de entender, corregir, mantener
2. que sean fáciles/rápidos de correr
3. que sea natural entender qué parte del sistema hay que mirar cuando un test falla
4. que no estén acoplados
5. reproducibles
6. otros?

----
# fáciles de entender

* tiene que quedar claro que se quiere testear
* tiene que querer demostrarse UNA sola cosa por test
* documentacion explicando cosas raras (cuidado con los docstring, porque los
  test runners usan eso en vez del nombre del test y es imposible de seguir)

----
# Asserts

* la menor cantidad de self.assert... posibles

usa el assert que corresponda, o construi el propio:

    !python
    assertEqual / assertNotEqual / assertIs / assertIsNot
    assertIsNone / assertIsNotNone
    assertIsInstance / assertIsNotInstance
    assertTrue / assertFalse
    assertIn / assertNotIn
    assertRaises / assertRaisesRegexp
    assertRedirects / assertContains / assertQuerysetEqual

Además:

* para revisar precondiciones usar assert (no self.assert)
* nunca nunca `self.assert_`
* no repitas asserts de otros tests

----
# Contraejemplo:

    !python
    class Sample(TestCase):
        def test_validation_1(self):
            item = create_item(args_config_1)
            self.assertSomething(item)
                ...
        def test_validation_15(self):
            item = create_item(args_config_15)
            self.assertSomething(item)

----
# Contraejemplo:

    !python
    class Sample(TestCase):
        def test_works_with_A(self):
            # stuff, stuff, stuff
            self.assertEqual('A', 'A')

        def test_works_with_B(self):
            """same than previous one but with B"""
            self.assertEqual('A', 'B')

Falla así

    !sh
	FAIL: same than previous one but with B

	Traceback (most recent call last):
	File "/home/javier/sample/tests/test_sample.py", line 12, in test_works_with_B
	self.assertEqual('A', 'B')
	AssertionError: 'A' != 'B'

----
# Los tests son código!

Los mismos criterios que se pueden usar para evaluar la lindura o no del código de una aplicación también la podés aplicar a los test.

* pep8 / pyflakes / pylint
* no hardcodees cosas, intentá definir constantes
* no te repitas, creá métodos, utilities, etc.
* nombrá bien tus variables
* test_methods de más de 20 o 25 lineas son serios sospechosos de necesitar un refactor
* Separá en Cases, nadie obliga a agregar tests a los existentes
    * Cuanto mejor separadas, más sentido: setUps con más utilidad, fixtures con más coherencia

----
# Fixtures

* Datos iniciales en la DB para darle contexto a nuestros tests
* El mecanismo que provee Django
* problemas:
    * falta de “explicitud”
    * difícil de mantener
    * difícil de generar
    * mezclan datos relevantes al test con datos de consistencia

----
# Factory Boy

Aplicación 3rd party al rescate

    !python
    class AuthorFactory(factory.Factory):
       FACTORY_FOR = MaterialKind
       name = factory.Sequence(lambda n: 'Autor {0}'.format(n))
       slug = factory.LazyAttribute(lambda o: o.name.lower().replace(' ', '-'))
    class BookFactory(factory.Factory):
       FACTORY_FOR = MaterialType
       name = factory.Sequence(lambda n: 'Libro {0}'.format(n))
       slug = factory.LazyAttribute(lambda o: o.name.lower().replace(' ', '-'))
       author = factory.SubFactory(AuthorFactory)
    ...
    class MyTestCase(unittest.TestCase):
       def test_something(self):
          b = BookFactory()
----
# Un poquito de mock:

Nos ayuda a testear *nuestro* código

    !python
    with mock.patch('django.contrib.messages.warning') as warning_mock:
        warning_mock.return_value = 8
        warning_mock.side_effects = django.contrib.messages.warning
        # do stuff
        self.assertIn("doesn't have a sequence", warning_mock.call_args[0][1])
        warning_mock.assert_called_once_with(1)

----
# Otros tips

Testear la vista entera con el `Client` es “último recurso”

* podés revisar validaciones de un formulario sin hacer POSTS
* podés usar mock para revisar que al entrar al view X se llama la funcion Z, y luego testear Z solito

Revisar HTML es “último recurso”:

* es lento
* es frágil
* acopla lógica con presentación


