# Django: messages

----
# Generando mensajes

* Basado en cookie o sesión
* Varios niveles (DEBUG, INFO, SUCCESS, WARNING, ERROR)

En la vista:


    !python
    from django.contrib import messages
    ...
    messages.success(request, 'Profile details updated.')

----
# Mostrando mensajes

    !html
    {% if messages %}
    <ul class="messages">
        {% for message in messages %}
        <li{% if message.tags %} class="{{ message.tags }}"{% endif %}>
            {{ message }}
        </li>
        {% endfor %}
    </ul>
    {% endif %}

Acceder a los mensajes los consume

