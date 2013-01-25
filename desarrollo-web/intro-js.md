# Javascript

----
# Javascript es

* Lenguaje para scripting
    * Sintáxis C-like
    * Semántica dinámica (Python, Ruby-like)
* Lo único que corre consistentemente en browsers
* Se puede usar para propósito general
    * No vamos a ver ese caso
    * En el caso de browsers es más limitado (por seguridad)


Material basdo en <http://javascript.info>

----
# Herramientas

* Editor de texto/código
* Firebug
    * consola interactiva
    * consola para debugging
* Hay features similares en Chrome (y algo en Safari e IE)

----
# Hello World

La mayoria de los tutoriales usan

    !js
    alert('Hello World!');

Aunque suele ser más práctico

    !js
    console.log('Hello world!');

----
# Tipos predefinidos

* `number`, `boolean`, `string` y `undefined`
* objetos (Similares a diccionarios)
* arreglos
* Los valores `null` 

----
# Quirks de sintáxis

* Los `;` son opcionales

Pero cuidado con:

    !js
    a = "Cadena
         larga";
    return
        1 + resultado;

Si se pueden:

    !js
    a = "Cadena \
         larga";
    return \
        resultado;
    a = "Cadena" +
        "larga";
    return 1 + (
        resultado)
----
# Declaraciones de variables

Lo básico

    !js
    var x;
    var saludo = "Hello World!";

* Porque usar siempre `var`
* variables no definidas

----
# Comentarios

Estilo C/C++:

    !js
    var x; // Un comentario
    var y; /* Otro comentario
    que sigue abajo */

----
# Bloques

Estilo C/C++

    !js
    {
        var x = 3;
        console.log("x = " + x);
    }

Los bloques **no** definen un scope. 

----
# Operadores:

* Strings: `+`. reglas de coerción
* Aritmética: `+`, `-`, `*`, `/`, `%`. Unarios
* In/decremento: `++`, `--`
* Bitwise: `&`, `|`, `^`, `~`, `<<`, `>>`
* Booleanos: `&&`, `||`, `!`. *Falsy* values
* Asignaciones: `=`, `+=`, `-=`, ...
* Relacionales: `==`, `!=`, `<`, ... `===`

----
# Control

Los mas o menos clásicos:

* `if`, `while`/`break`/`continue`
* `for` y `do`...`while` estilo C

Hay manejo de excepciones:

* `throw`
* `try`...`catch`...`finally`
* cualquier valor es una excepción

----
# Funciones

Las funciones son valores. declarr una funcion es declarar una variable

    !js
    function f(arg1, arg2, ...) {
       ... code ...
    }

* El valor se devuelve con `return`.
* Las variables tienen vida local
* Las declaraciones se ejecutan antes de todo

Comparar con

    !js
    f = function (arg1, arg2, ...) {
       ... code ...
    }

----
# Strings

* Single or double-quoted. escapado del modo usual
* Atributo `length`, método `charAt`
* Algunos métodos builtin (no tan rico como python)

----
# Objetos:

* `{}` es un objeto vacío
* se pueden acceder con `["key"]` o `.key`
* una clave desconocida se liga a `undefined`

Se puede iterar sobre claves

    !js
    obj = {ancho: 100, alto: 200};
    for (k in obj) {
        console.log(obj[k])
    }

----
# Arrays

* `[]`
* atributo `length`
* Los arreglos son objetos
* Pueden ser sparse

----
# Funciones (2)

* La cantidad de argumentos puede no coincidir con la definición
* Lo que falta se setea a `undefined`
* `arguments` contiene los argumentos reales

Dos técnicas para argumentos opcionales

    !js
    // 1
    function f(arg) {
        if (arg === undefined) arg = "valor por default";
        ...
    // 2
    function f(options) {
        if (options.arg === undefined) options.arg = "valor por default";
        ...

----
# Javascript en el browser

* Acceso al *DOM*
* objeto global `window` y `window.document`
* Otros elementos globales

----
# Caminando el DOM

* `document.documentElement` y `document.body`
* cada nodo tiene un `childNodes`
* También un `children` (con solo elementos)
* `firstChild` y `lastChild`
* `parentNode`, `previousSibling`, `nextSibling`

----
# Describiendo nodos

* `nodeType` (`ELEMENT_NODE`, `TEXT_NODE`)
* `tagName`
* `innerHTML` (es editable!)
* `getAttribute` y `setAttribute`
* `hasAttribute` y `removeAttribute`
* usando atributos custom en los nodos
* sincronizacion de atributos de DOM y JS. `class` y `className`

----
# Manipulando el DOM

* `document.createElement`
* `document.createTextNode`
* `elem.cloneNode` (deep y shallow)
* `elem.appendChild`, `removeChild`, `insertBefore`, ...

En tiempos ancestrales, se usaba `document.write`

----
# Buscando nodos

* `document.getElementById`
* `elem.getElementsByTagName`
* `elem.getElementsByName`
* `elem.getElementsByClassName`
* `elem.querySelector` y `querySelectorAll`

----
# Eventos

* `on...`
* Delegación de eventos, `event.target`
* Valor de retorno del event handler

----
# jQuery

Cargando:

    !html
    <script src="/js/jquery-1.9.0.min.js"></script>

Eso define una funcion/constructor global llamado `$`

----
# Construyendo jQuery objects

* `$(document)`
* `$(elem)`
* `$("div.news")`

A través de un objeto jQuery se puede:

* ligar eventos (múltiples handlers por evento)
* consultar datos
* modificar el elemento

----
# Ejemplos

    !js
    $(document).load(function() { ... })
    $(function() { ... })

    $("button#save").click(function () {... })

    var value = $("input[name='email']").val();
    $("input[name='email']").val(value+'@machinalis.com');

    $("div.header").html("Hello!")
    $("div.header").addClass("hidden")

----
# Ejercicios

1. Hacer un script que numere los hijos de una jerarquia de listas
2. implementar placeholder en JS puro
3. Hacer un tateti (de dos jugadores) en JS+jQuery


