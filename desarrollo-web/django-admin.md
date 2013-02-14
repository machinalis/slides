# Django: el admin

----
# Instalación

1. Agregar `django.contrib.admin` y sus dependencias (`auth`, `sessions`,
   `contenttypes` y `messages`)
2. Generar un `AdminSite` (o usar `django.admin.site`)
3. Conectar el anterior al URLconf
4. Para cada modelo administrable, definir un `ModelAdmin` y registrarlo en
   el `AdminSite`

----
# AdminSite

* En el caso simple, uno usa la instancia de `django.admin.site`
* Permite registrar modelos con su `ModelAdmin

Genera un conjunto de urls que se puede usar:

    !python
    from django.contrib import admin
    urlpatterns = patterns('',
        (r'^admin/', include(admin.site.urls)),
    )

----
# Autodiscovery

Antes de generar URLs es necesario tener todo registrado.

    !python
    admin.autodiscover()

* Recorre todas las apps
* Hace import de app.admin
* convencionalmente el `admin.py` de una app registra lo que haga falta.

----
# ModelAdmins

* Muchas opciones declarativas. RTFM
* para muchas opciones esta la `get_xxx` correspondiente
* Hay mucho que se extiende con código

----
# Ajustando validación (1)

* El admin usa un `ModelForm`
* El form se puede overridear seteando `form`
* también se puede redefinir `get_form(self, request, obj=None, **kwargs)`


----
Por ejemplo:

    !python
    # forms.py
    class MyArticleAdminForm(forms.ModelForm):
        class Meta:
            model = Article

        def clean_name(self):
            # do something that validates your data
            return self.cleaned_data["name"].strip()

    # admin.py
    from cms.forms import MyArticleAdminForm
    class ArticleAdmin(admin.ModelAdmin):
        form = MyArticleAdminForm

----
# Ajustando validación (2)

* Los inlines son `ModelFormset`
* El formset se puede overridear seteando `formset` del `ModelInline`
* Cada form del formset se puede overridear seteando `form` del `ModelInline`
* también se puede redefinir `get_formsets(self, request, obj=None)`

Por ejemplo:

    !python
    def get_formsets(self, request, obj=None):
        for inline in self.get_inline_instances(request):
            # hide MyInline in the add view
            if isinstance(inline, MyInline) and obj is None:
                continue
            yield inline.get_formset(request, obj)

----
# Custom forms

Se puede customizar la generación de modelforms:

    !python
    class MyModelAdmin(admin.ModelAdmin):
        formfield_overrides = {
            models.TextField: {'widget': RichTextEditorWidget},
        }

O el field generado para una relación:

    !python
    class MyModelAdmin(admin.ModelAdmin):
        def formfield_for_foreignkey(self, db_field, request, **kwargs):
            if db_field.name == "car":
                kwargs["queryset"] = \
                    Car.objects.filter(owner=request.user)
            return super(MyModelAdmin, self).formfield_for_foreignkey(
                db_field, request, **kwargs)

Hay similares para un manytomany, y para choicefields

----
# Cambiando el conjunto

    !python
    class MyModelAdmin(admin.ModelAdmin):
        def queryset(self, request):
            qs = super(MyModelAdmin, self).queryset(request)
            if request.user.is_superuser:
                return qs
            return qs.filter(author=request.user)

----
# Agregando vistas:

    !python
    class MyModelAdmin(admin.ModelAdmin):
        def get_urls(self):
            urls = super(MyModelAdmin, self).get_urls()
            my_urls = patterns('',
                (r'^my_view/$', self.my_view)
            )
            return my_urls + urls

        def my_view(self, request):
            # custom view which should return an HttpResponse
            pass

Por defecto no hay chequeo de permisos. Posiblemente quieran

    !python
    (r'^my_view/$', self.admin_site.admin_view(self.my_view))

----
# Filtros

La opción para filtrar por campos

    !python
    list_filter = ('is_staff', 'company__name', MyFilter)

Acepta clases como la siguiente:

----
    !python
    from django.contrib.admin import SimpleListFilter

    class DecadeBornListFilter(SimpleListFilter):
        title = _('decade born')

        # Parameter for the filter that will be used in the URL query.
        parameter_name = 'decade'

        def lookups(self, request, model_admin):
            return (
                ('80s', _('in the eighties')),
                ('90s', _('in the nineties')),
            )

        def queryset(self, request, queryset):
            if self.value() == '80s':
                return queryset.filter(birthday__gte=date(1980, 1, 1),
                                        birthday__lte=date(1989, 12, 31))
            if self.value() == '90s':
                return queryset.filter(birthday__gte=date(1990, 1, 1),
                                        birthday__lte=date(1999, 12, 31))
----
# Redefiniendo comportamiento

* `save_model(self, rq, obj, form, change)`
* `delete_model(self, rq, obj)`
* `save_formset(self, rq, form, formset, change)`

Por ejemplo:

    !python
    class ArticleAdmin(admin.ModelAdmin):
        def save_model(self, request, obj, form, change):
            obj.user = request.user
            obj.save()

----
# Redefiniendo vistas

* `add_view()`
* `change_view()`
* `changelist_view()`
* `delete_view()`
* `history_view()`

----
# Agregando acciones

Las “acciones” figuran en el listado y se aplican sobre un conjunto de objetos:

    !python
    def make_published(modeladmin, request, queryset):
        queryset.update(status='p')
    make_published.short_description = "Mark selected stories as published"

    ...
    class ArticleAdmin(admin.ModelAdmin):
        actions = [make_published]
        ...

Si la acción devuelve None, se redirige al listado. También puede devolver
un response. Es también comun llamar a `modeladmin.message_user`

