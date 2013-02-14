# Django: autenticacion

----
# django.contrib.auth

* Autenticación vs.
* Autorización

Hay más de una forma de hacerlo. La autenticación es configurable

----
# Lo básico

* Respaldado por base de datos
* Estado mantenido por sesión
* Autorización por tarea, no por objeto (más o menos)
* Permisos por usuario y por grupo

----
# Como habilitarlo

1. poner `django.contrib.auth` en `INSTALLED_APPS` (viene por default)
2. correr syncdb

Por defecto permite generar una cuenta de "superusuario".

----
# Me olvidé el password!

Si el developer necesita un superusuario:

    !sh
    ./manage.py createsuperuser
    ./manage.py createsuperuser --username=joe --email=joe@example.com

----
# Los “usuarios”

La clase `models.User` es un modelo de Django.

* `username`: 30 caracteres. A-Z, a-z, 0-9, _@+.-
* `first_name`/`last_name`
* `email` de longitud ridícula
* `password` o en realidad, su hash
* `is_active`
* `is_staff`
* `is_superuser`
* `last_login` y `date_joined`

----
# Algunos métodos

* `is_anonymous()`, `is_authenticated()`
* `get_full_name()`
* `set_password(unhashed)` (no graba)
* `check_password(unhashed)`
* `set_unusable_password()` y `has_usable_password` (no graba)
* `email_user()`

----
# A nivel clase:

Un par de métodos útiles:

    !python
    >>> from django.contrib.auth.models import User
    >>> user = User.objects.create_user('john', 'lennon@thebeatles.com',
                                        'johnpassword')
    >>> user = User.objects.make_random_password()
    'pEFy95ycub'

----
# Web requests y autenticación

Suponemos “bien” configurado `MIDDLEWARE_CLASSES` para que tenga sesión y autenticación.
Entonces

* Si hay un usuario autenticado, `request.user` tiene la instancia del usuario
* Si no, tiene un `AnonymousUser`

----
# Usuarios anónimos

* `id == None`
* `is_staff == is_superuser == False`
* `is_active == True`
* Los métodos que cambian algo levantan `NotImplementedError`

----
# Autenticando

Hay que usar `authenticate` y `login`

    !python
    from django.contrib.auth import authenticate, login

    def my_view(request):
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(username=username, password=password)
        if user is not None:
            if user.is_active:
                login(request, user)
                # Redirect to a success page.
            else:
                # Return a 'disabled account' error message
        else:
            # Return an 'invalid login' error message.

----
# Y el proceso inverso

    !python
    from django.contrib.auth import logout

    def logout_view(request):
        logout(request)
        # Redirect to a success page.

El logout limpia la sesión

----
# Usando la información de login

La forma obvia:

    !python
    from django.http import HttpResponseForbidden

    def my_view(request):
        if not request.user.is_authenticated():
            return HttpResponseForbidden('No esistí')

Aunque normalmente se usa:

    !python
    from django.contrib.auth.decorators import login_required

    @login_required(login_url='/accounts/login/')
    def my_view(request):
        ...

----
# Una vista de login

    !python
    from django.contrib.auth.views import login

* Sigue el patrón usual
* busca `registration/login.html` (no viene!)

Se puede customizar:

    !python
    (
        r'^accounts/login/$',
        'django.contrib.auth.views.login',
        {
            'template_name': 'myapp/login.html',
            'form': MiLoginForm
        }),

----
# Otras vistas predefinidas

* `logout`
* `logout_then_login`
* `password_change`
* `password_change_done`
* `password_reset`
* `password_done`
* `password_confirm`
* `password_complete`

Todas necesitan plantilla, `password_reset` necesita también una plantilla
para el email

----
# O si uno hace vistas a mano

En `django.contrib.auth.forms` hay:

* `AuthenticationForm`
* `PasswordchangeForm`
* `SetPasswordForm`
* etc, etc.

----
# Permisos

----
# Modelos involucrados

* `User.user_permissions`: m2m a `Permission`
* `User.groups`: m2m a `Group`

Dado que hay más de una forma de adquirir permisos, la API más comoda es

    !python
    if user.has_perm('polls.can_vote'): ...

O también

    !python
    @permission_required('polls.can_vote', raise_exception=True):
    def my_view(request):
        if user.has_perm('polls.can_vote'): ...

----
# En el template

El usuario pasa directo a los `RequestContext`

    !html
    {% if user.is_authenticated %}
        Welcome {{ user.get_full_name }}
    {% endif %}

Los permisos también, en una pseudovariable perms:

    !html
    {% if perms.polls.can_vote %} ... {% endif %}

----
# Y todos esos obj=...

* Muchas funciones de chequeo de permisos reciben un objeto
* No están implementados
* Sólo por compatibilidad futura
* o backends alternativos

----
# Profiles

Un profile es un modelo con un 1-to-1 a `User`:

    !python
    from django.contrib.auth.models import User

    class UserProfile(models.Model):
        # This field is required.
        user = models.OneToOneField(User)

        # Other fields here
        accepted_eula = models.BooleanField()
        favorite_animal = models.CharField(max_length=20, default="Dragons.")

Luego se define en el settings la app/modelo relevante:

    !python
    AUTH_PROFILE_MODULE = "miapp.UserProfile"

----
# Profiles (2)

* cada user tiene un `get_profile()` que da el objeto asociado
* puede haber usuarios sin profile, hay que manejar ese caso

----
# En el admin

    !python
    from django.contrib import admin
    from django.contrib.auth.admin import UserAdmin
    from django.contrib.auth.models import User

    from my_user_profile_app.models import UserProfile

    # Define an inline admin descriptor for UserProfile model
    # which acts a bit like a singleton
    class UserProfileInline(admin.StackedInline):
        model = UserProfile
        can_delete = False
        verbose_name_plural = 'profile'

    # Define a new User admin
    class UserAdmin(UserAdmin):
        inlines = (UserProfileInline, )

    # Re-register UserAdmin
    admin.site.unregister(User)
    admin.site.register(User, UserAdmin)

