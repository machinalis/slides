# Django: forms

----
# Un form puede

* Generar HTML total o parcial en base a una descripción de campos
* Comprobar un conjunto de datos contra reglas de validación
* Generar HTML con mensajes de error para devolver al usuario
* Convertir strings validados en los datos a tipos python

----
# Ejemplo

    !python
    from django import forms

    class ContactForm(forms.Form):
        subject = forms.CharField(max_length=100)
        message = forms.CharField()
        sender = forms.EmailField()
        cc_myself = forms.BooleanField(required=False)

    >>> ContactForm(data) # ligado
    >>> ContactForm(initial=data) # no ligado

----
# Atributos

La instancia de form **NO** tiene un atributo para cada campo

* Sí tiene un `f["campo"]` (ligado o no ligado)
    * También accesible por iteración
* y un `f.fields["campo"]`
* y un `f.cleaned_data["campo"]`

----
# Campos

El campo ligado/no ligado sabe principalemnte representarse en HTML:

* `{{ field }}`
* `{{ field.label }}`
* `{{ field.label_tag }}`
* `{{ field.html_name }}`
* `{{ field.help_text }}`
* `{{ field.errors }}`
* `{{ field.is_hidden }}`

----
# Forms ligados

Sólo los forms ligados pueden validar

* Atributo `is_bound`
* `is_valid()`
* `errors` (invoca validación)
* `cleaned_data` (existe solo después de validar)
    * Tiene valores python para todos los campos

----
# Custom HTML

Se pueden definir las clases usadas

    !python
    class ContactForm(Form):
        error_css_class = 'error'
        required_css_class = 'required'

    >>> f['message'].css_classes()
    'required'
    >>> f['message'].css_classes('foo bar')
    'foo bar required'

* Parámetro `auto_id` (`True`, `False`, `"id_%s"`)
* Parámetro `prefix`

----
# Forms y herencia

Se pueden heredar forms; los campos se heredan “normalmente”

    !python
    class PersonForm(Form):
        first_name = CharField()
        last_name = CharField()
    class InstrumentForm(Form):
        instrument = CharField()
    class BeatleForm(PersonForm, InstrumentForm):
        haircut_type = CharField()

----
# Campos base

Heredan de `django.forms.Field`. Su característica más importante es el
método `clean()`

    !python
    >>> from django import forms
    >>> f = forms.EmailField()
    >>> f.clean('foo@example.com')
    u'foo@example.com'
    >>> f.clean(u'foo@example.com')
    u'foo@example.com'
    >>> f.clean('invalid e-mail address')
    Traceback (most recent call last):
    ...
    ValidationError: [u'Enter a valid e-mail address.']

----
# Opciones universales

* `required`
* `label`
* `initial` (menos precedencia que el constructor de forms)
* `widget`
* `help_text`
* `error_messages`
* `validators`

----
# Campos específicos

En base a tipo de datos+representación. Las características que definen a un
field son:

* Widget por default
* Valor “vacío”
* Tipo python al que normaliza
* Reglas de validación
* Nombres de mensajes de error

<https://docs.djangoproject.com/en/1.4/ref/forms/fields/>

----
# Widgets

* Son los que “saben HTML”
* Operan a nivel string
* Sin validación
* argumento `attrs`
* `render(name, value)`, `value_from_datadict(data, files, name)`

----
# Validación

1. El método `to_python` de cada `Field`
1. El método `validate` de cada `Field`
1. El método `run_validators` de cada `Field`
1. El método `clean` de cada `Field`
1. El método `clean_campo` del form
1. El método `clean` del form

el último puede generar un `ValidationError` o modificar `form._errors`

----
# Un campo custom

Este es el que viene con Django:

    !python
    class EmailField(CharField):
        default_error_messages = {
            'invalid': _(u'Enter a valid e-mail address.'),
        }
        default_validators = [validators.validate_email]

----
# Un campo más custom

    !python
    from django import forms
    from django.core.validators import validate_email

    class MultiEmailField(forms.Field):
        def to_python(self, value):
            "Normalize data to a list of strings."
            if not value:
                return []
            return value.split(',')

        def validate(self, value):
            "Check if value consists only of valid emails."
            super(MultiEmailField, self).validate(value)

            for email in value:
                validate_email(email)

----
# Desde el form

    !python
    class ContactForm(forms.Form):
        ...

        def clean_recipients(self):
            data = self.cleaned_data['recipients']
            if "fred@example.com" not in data:
                raise forms.ValidationError("You have forgotten about Fred!")

            # IMPORTANTE:
            return data

----
# Validación “cross-field”

    !python
    class ContactForm(forms.Form):

        def clean(self):
            cleaned_data = super(ContactForm, self).clean()
            cc_myself = cleaned_data.get("cc_myself")
            subject = cleaned_data.get("subject")

            if cc_myself and subject:
                # Only do something if both fields are valid so far.
                if "help" not in subject:
                    raise forms.ValidationError("Did not send for 'help' in "
                            "the subject despite CC'ing yourself.")

            # Always return the full collection of cleaned data.
            return cleaned_data

----
# Modelforms

----
# DRY

    !python
    class ArticleForm(ModelForm):
        class Meta:
            model = Article

    >>> a = Article.objects.get(pk=123)
    >>> f = ArticleForm(instance=a)

Se generan campos automáticamente, siguiendo un mapeo estándar. La validación
integra validación de modelo.

----
# Guardado automático

    !python
    a = Article.objects.get(pk=1)
    f = ArticleForm(request.POST, instance=a)
    f.save()

* `save()` falla con `ValueError` si hay problemas de validación
* `save(commit=False)`
* `save_m2m()`

Esto permite:

    !python
    f = ArticleForm(request.POST, instance=a)
    new_a = f.save(commit=false)
    new_a.campo = ...
    new_a.save()
    f.save_m2m()

----
# Eligiendo campos:

* `editable=False` en el modelo
* Meta-opción `fields`
* Meta-opción `exclude`

Los campos que no aparecen, no son modificados por `save()`

----
# Modificando widgets

    !python
    from django.forms import ModelForm, Textarea

    class AuthorForm(ModelForm):
        class Meta:
            model = Author
            fields = ('name', 'title', 'birth_date')
            widgets = {
                'name': Textarea(attrs={'cols': 80, 'rows': 20}),
            }

----
# Modificando fields

Los campos que uno define, pisan/agregan a los autogenerados:

    !python
    class ArticleForm(ModelForm):
        pub_date = DateField(label='Publication date')

        class Meta:
            model = Article

Ahora hay que encargarse de poner a mano todo (label, required, etc.)

Para cambiar el orden, alcanza con redefinir `Meta.fields`

----
# Validación

* Igual que en forms normales
* Importante llamar a super si se quiere la validación de modelo
    * Incluyendo validación de campos unique, unique_together.

----
# Herencia

* Igual que en forms normales
* No se puede heredar de un ModelForm y de un Form a la vez
* Ojo con herencia múltiple y `Meta`

----
# Formsets

----
# Formsets

* Una colección de forms similares
* Puede verse conceptualmente como una “grilla”
* Para hacer submit de todo junto

Es lo que se usa en los inlines del admin

----
# Ejemplo

Supongamos que `ArticleForm` es un form normal

    !python
    from django.forms.formsets import formset_factory
    ArticleFormSet = formset_factory(ArticleForm)

`ArticleFormSet` es una **clase**:

    !python
    formset = ArticleFormSet() # no ligado
    for form in formset:
        ...

----
# Instanciando formsets

* ligados y no ligados
* argumento `extra`
* argumento `initial`
* argumento `max_num`

----
# Validación

* El formset agrega algunos campos internos (el “management form”)
* Tiene `is_valid()`, `errors`, `clean()` para usar igual que un form

el patrón para extender es:

    !python
    class BaseArticleFormSet(BaseFormSet):
        def clean(self):
            if any(self.errors):
                return
            titles = set()
            for form in self.forms[:self.total_form_count()]:
                title = form.cleaned_data['title']
                if title in titles:
                    raise forms.ValidationError("Articles in a set must have distinct titles.")
                titles.add(title)

    ArticleFormSet = formset_factory(ArticleForm, formset=BaseArticleFormSet)

----
# Otros features

Si pasamos a la factory `can_order=True`

* Cada form tendrá un campo extra llamado `ORDER` de tipo `IntegerField`
* Al limpiar los datos, se reordenan
* Probablemente queda mejor con algo de JS

----
# Otros features

Si pasamos a la factory `can_delete=True`

* Cada form tendrá un campo extra llamado `DELETE` de tipo `BooleanField`
* Se agrega un atributo `deleted_forms` con los forms que tienen esa opción

----
# Integrando con templates

Más alla de poner `{{ formset }}` se puede:

    !html
    <form method="post" action="">
        {{ formset.management_form }}
        <table>
            {% for form in formset %}
            {{ form }}
            {% endfor %}
        </table>
    </form>

Si se renderizan los campos a mano, recordar `form.ORDER` y `form.DELETE`

----
# Model Formsets

Combinando los dos anteriores. Notar que la factory recibe un modelo en vez
de un form:

    !python
    from django.forms.models import modelformset_factory
    AuthorFormSet = modelformset_factory(Author)

Los datos iniciales se sacan de `Author.objects.all()`. En vez, se puede
pasar un argumento `queryset` para ser más específico. O setearlo en el
`__init__` (heredando de `BaseModelFormSet`)

Si se pasa initial se usan esos datos *para los forms vacíos*

----
# Eligiendo campos

La factory acepta `fields` y `exclude`, que se comportan como en el `Meta`
del modelform.

----
# Guardando

* El formset tiene un `save()`
* Devuelve una *lista* de instancias
* Sólo aparecen las instancias modificadas
* Se puede usar `commit=False`

----
# Un ejemplo

El patrón es similar que el de forms

    !python
    def manage_authors(request):
        AuthorFormSet = modelformset_factory(Author)
        if request.method == 'POST':
            formset = AuthorFormSet(request.POST, request.FILES)
            if formset.is_valid():
                formset.save()
                # do something.
        else:
            formset = AuthorFormSet()
        return render_to_response("manage_authors.html", {
            "formset": formset,
        })

Los formsets no de modelo son casi igual (cambia la llamada a la factory y
hay código propio en vez de `save`)

----
# Inline formsets:

Caso particular de modelform, para objetos ligados a una instancia via FK

    !python
    class Author(models.Model):
        name = models.CharField(max_length=100)

    class Book(models.Model):
        author = models.ForeignKey(Author)
        title = models.CharField(max_length=100)

    >>> from django.forms.models import inlineformset_factory
    >>> BookFormSet = inlineformset_factory(Author, Book)
    >>> author = Author.objects.get(name=u'Mike Royko')
    >>> formset = BookFormSet(instance=author)

----
# Ejemplo

    !python
    def manage_books(request, author_id):
        author = get_object_or_404(Author, pk=author_id)
        BookInlineFormSet = inlineformset_factory(Author, Book)
        if request.method == "POST":
            formset = BookInlineFormSet(request.POST, request.FILES, instance=author)
            if formset.is_valid():
                formset.save()
                # Do something.
        else:
            formset = BookInlineFormSet(instance=author)
        return render_to_response("manage_books.html", {
            "formset": formset,
        })

