# Javascript...
# ...para programadores python


## PyCon.ar 2012 - Daniel F. Moisset
## dmoisset@machinalis.com - @dmoisset

----
# Disclaimers

.notes: Supongo que sabés Python. Voy a hablar del Core de javascript, no de DOM, bibliotecas. Voy a hablar del último ECMAscript estándar 3, a menos que indique lo contrario; muchos detalles son distintos/mejores en nuevos drafts del estándar de javascript, o versiones "custom".

Producto sólo para propósitos educativos. Cualquier parecido a personas reales,
vivas o no, es completamente accidental. Puede requerir ensamblaje. No incluye
baterías. Use sólo siguiendo las instrucciones. No hay otras garantías
expresas o implícitas. No utilizar mientras conduce u opera maquinaria
pesada. Sujeto a aprobación. Aplíquese solo en el área afectada. No apto para
uso comercial. Consumir preferentemente antes de la fecha en el envase. No
contiene componentes reparables por el usuario. Sujeto a cambios sin previo
aviso. Si la condición persiste, consulte a su médico. Imágenes solo a modo
ilustrativo. Las fotos de personas han sido retocadas digitalmente. Los colores
pueden deteriorarse con el paso del tiempo. Resbaloso al mojarse. Romper la faja
de seguridad invalida la garantía. El listado estaba actualizado al momento
de impresión. No escriba por debajo de la línea de puntos. Evite el contacto
con la piel. Utilícese como cualquier otro jabón. Empleados y sus familiares
directos no son elegibles. Oferta por tiempo limitado. Úsese solo en espacios
bien ventilados. El precio no incluye impuestos. Puede contener trazas de maní
y de lácteos. Sin estéreo. La decisión del jurado es inapelable. Talle único.
As seen on TV.

----
# ¿¡Javascript?! ¡que asco!

## ¿Por qué?

* Por que es la única opción
* Comodidad
* Portabilidad (o algo así)
* Eficiencia

----
# Dijeron “extrema”. A los bifes

----
# JS y Python son parecidos!

* Tipado dinámico
    * Duck typing
    * introspección y mutabilidad
* Orientado a objetos
    * Todo es un objeto! casi!
* Funcional
    * Las funciones son valores
    * Y se portan de forma bastante objetosa
* Estructuras de datos de alto nivel: listas, “diccionarios”

----
# Algunas cosas 99% iguales

* Tipos base y sus literales:
    * listas (arreglos)
    * “diccionarios” (objetos)
    * números (aunque no tiene precisión arbitraria)
    * strings (unicode)
    * booleanos
    * `null` (cómo `None`)
* Control: `if`, `while`, `break`, `return`, `for (... in ...) ...`
* Excepciones: `throw`, `try ... catch ... finally ...`

----
# Otras también (mod sintaxis)

* Bloques con `{}` en vez de indentación
    * Pero igual el scoping es por función
* Operadores más a lo C: `&&` en vez de `and`
* Lambdas:

        !python
        square = lambda x: x*x
  vs

        !js
        square = function (x) {return x*x;}

----
# Esto está sólo en Javascript

Pero no le vamos a dedicar mucho tiempo:

* break con label
* switch/case
* do/while
* `for (init; cond; incr)`
* Sintaxis para regexes
* Operadores `++`, `--`

----
# Para extrañar... por ahora

* generadores (1.7)
    * Tomados de Python!
* listas^W arrays por comprensión (1.7)
    * Tomados de Python!
* asignación multiple (1.7): `[a,b] = [b,a]`
* generator expressions (1.8)
    * Tomados de Python!
* "function closures" (estilo `lambda`)
* `super`

----
# Para extrañar

## import foo

* No hay una noción de módulo
* Para hacer singletons se usan globales
* Es tan distinto? un módulo es un objeto
* Soluciones a nivel biblioteca (require.js), 3rd party
* ... que no es tan diferente a importlib (Python3)

        !js
        requirejs(['jquery', 'canvas', 'app/sub'],
        function   (jquery,   canvas,   sub) {
            // aquí están cargados los módulos y
            // mapeados a los argumentos
        });

----
# Para extrañar (2)

## Protocolos!

* El mejor amigo del duck typing
* En todos lados en Python: operadores, iterable, hashable, callable,
  equality, descriptor, context-manager, ...
* En JS, los operadores, statements de control, etc. se comportan de una forma
  fija:
    * Más predecible / Menos flexible
* Hay dos métodos que pueden alterar un poco el comportamiento de operadores:
    * `valueOf` / `toString`

----
# Modelo de datos:

## Tipos primitivos (como los indica `typeof`):

* `"number"`
* `"string"`
* `"boolean"`
* `"undefined"`

Pero se portan como objetos

----
# Modelo de datos(2)

Tipos no primitivos:

* `"object"`
    * `null` es de estos
    * y todos los arrays
    * y todas las regexes
    * instancias de `Number()`, `String()`, ...
* `"function"`

----
# Coerciones, coerciones

## Contextos de string

1. Primero se usa `toString`
2. sino se usa `valueOf`, (seguido de `toString`)
3. sino, excepción

        !js
        console.log( {key: 'value'} ) // "[object Object]"
        console.log( [1,2] )          // "1,2" 

----
# Coerciones, coerciones

## Contextos de string

La usan algunas funciones, implícitamente el “`+`”:

    !js
    >>> x = {
        toString: function () {return "123";}
    }
    >>> console.log(x)
    "123"
    >>> "Testing "+x
    "Testing 123"

.notes: aquí hay un objeto sin clase, tiene el método directamente adentro

----
# Coerciones, coerciones

## Contextos numéricos:

1. Primero se usa `valueOf`
2. sino se usa `toString`, (seguido de `valueOf`)
3. sino, excepción

        !js
        console.log( +x ) // 123
        console.log( +x+1 ) // 124
        console.log( x+1 ) // "1231" (??)
        console.log( +[1,2,3] ) // NaN
        console.log(+'') // 0
        console.log(+'python') // NaN

----
# Coerciones, coerciones

## Contextos numéricos - implícitamente en muchos lados: 

* operadores aritméticos (`+` y `-` unario, `*`, `%`, ...)
* Comparaciones: `<`, `>`, `==`
* `Math.sin()`, `isNan()`

        !js
        console.log(x == 123) // true
        console.log(x == "123") // true

¿Qué devuelve?

    !js
    console.log(['xy'] == 'xy')
    console.log([] == 0)
    console.log([0] == 0)

----
# Sí, `==` es difícil:

* Para tipos iguales
    1. `NaN` no es igual a si mismo
    3. Un objeto es sólo idéntico a si mismo (`is` de python)
    4. En general, lo obvio
* Para tipos distintos
    1. `null` == `undefined`
    2. Para número == string, se convierte todo a número
    3. Para booleano == X, se convierte el booleano a número
    4. Para número/string == objeto, se convierte el objeto a valor
* El operador `===` es más estricto

----
# Coerciones, coerciones

## Contextos booleanos:

 * `false` es falso.
 * `null` es falso
 * `undefined` es falso
 * `0` y `NaN` son falsos
 * `""` es falso
 * todos lo demás son verdaderos

----
# Coerciones, coerciones

## Contextos booleanos:

    !js
    x = 0
    y = "0"
    if (x==y) {
        if (x)
            ...
        if (y)
            ...
    }

O también:

    !js
    x = []
    if (x == true) ...
    if (!!x == true) ...

----
# El infierno de las coerciones

## gracias @garybernhardt

    !js
    >>> [] + []
    >>> [] + {}
    >>> {} + []
    >>> {} + {}
    >>> x = {} + []
    >>> x = {} + {}

----
# El infierno de las coerciones

## gracias @garybernhardt

    !js
    >>> [] + [] // ""
    >>> [] + {} // "[object Object]"
    >>> {} + [] // {}; +[]; -> 0
    >>> {} + {} // {}; +{}; -> NaN
    >>> x = {} + [] // "[object Object]"
    >>> x = {} + {} // ""

----
# El infierno de las coerciones

## gracias @garybernhardt

    !js
    >>> Array(16)
    ,,,,,,,,,,,,,,,
    >>> Array16.join("wat")
    "watwatwatwatwatwatwatwatwatwatwatwatwatwatwat"
    >>> Array16.join("wat"+1)

?

    !js
    >>> Array16.join("wat"-1) + " Batman!"

?

----
# El infierno de las coerciones

## gracias @garybernhardt

    !js
    >>> Array16.join("wat"-1) + " Batman!"
    "NaNNaNNaNNaNNaNNaNNaNNaNNaNNaNNaNNaNNaNNaNNaN Batman!"

    >>> []==![]
    true

----
# Reglas que muerden

* La suma concatena si cualquiera es string, suma caso contrario
* Pero el `+` unario, resta, multiplicación y división van a número.
* No es lo mismo `==` que `===`.
* No existe `is`, aunque `==` se porta así en objetos

Por lo tanto:

    !js
    >>> [1,2,3]+[4,5,6]
    "1,2,34,5,6"
    >>> [1,2,3]==[1,2,3]
    false

----
# El Zen:

## “Errors should never pass silently.”

----
# ¡JA!

----
# Object Model

* No hay distinción entre objetos y diccionarios
* Todas las claves son strings (ojo! coerciones!)
* Y de hecho “`.`” es syntax sugar:

        !js
        >>> x.attr
        >>> x['attr']
        >>> x[2]
        >>> x["2"]

* No hay muchos métodos builtin (como si hay en `dict`)
* Acceder a algo que no existe da `undefined`

----
# Object Model

Por supuesto, es completamente mutable

    !js
    >>> x = {attr1: 10, attr2: 20}
    >>> x.attr3 = 30;
    >>> delete x.attr1

e introspectable

    !js
    >>> for (k in x) console.log([k,x[k]])

las keys de arrays... son keys!

    !js
    >>> a = [10,20,30,40]
    >>> delete a[1]
    >>> a[2]
    30
    >>> a[1]
    undefined

----
# Object Model: arrays

Los arrays son más que una bolsa de key numéricos:

    !js
    >>> a.length
    4

Pero si itero sobre un array entonces...

    !js
    >>> for (k in a) console.log(k)
    0
    2
    3

y `length`?

    !js
    >>> a.propertyIsEnumerable(1)
    false
    >>> a.propertyIsEnumerable(2)
    true
    >>> a.propertyIsEnumerable('length')
    false

----
# ¡Iterar con `for ... in` no garantiza orden!

----
# OK... pero y los métodos?

En Python, los métodos son por abajo funciones:

    !python
    class Decimal(object):
        ...
        def is_nan(self):
            ...
    >>> Decimal.is_nan
    <function decimal.is_nan>
    >>> d = Decimal(0)
    >>> m = d.is_nan
    >>> m
    <bound method Decimal.is_nan of Decimal('0')>
    >>> m()
    False

Hay un poquito de “magia negra” (descriptor protocol) en el
“.”, al hacer lookup en la clase.

----
# OK... pero y los métodos?

En Python, los métodos van en una *clase*:

    !python
    >>> class C(object): pass
    >>> obj = C()
    >>> def fun(self, v): self.x = v
    >>> obj.fun=fun
    >>> obj.fun(3)
    Traceback (most recent call last):
    TypeError: fun() takes exactly 2 arguments (1 given)
    >>> obj.fun(obj, 3)
    >>> obj.x
    3

Las líneas 8 a 10 “funcionan”, pero son trampa (el `obj.` de la izquierda
es de adorno)

----
# OK... pero y los métodos?

En Javascript, los métodos van en un *objeto*:

    !js
    >>> obj = {}
    >>> function fun(v) { this.x = v }
    >>> obj.fun = fun
    >>> obj.fun(3)
    >>> obj.x
    3

Aunque no hay una idea de método ligado

    !js
    >>> obj.fun
    fun(v) // en algunas consolas esto se ve diferente
    >>> obj.fun === fun
    true
    >>> f = obj.fun
    >>> f("PyCon.ar 2012")
    >>> obj.x
    3

----
# OK... pero y los métodos?

    !js
    >>> window.x
    "PyCon.ar 2012" // SORPRESA!
    >>> x
    "PyCon.ar 2012" // SORPRESA 2.0!

En Javascript, las funciones son por abajo métodos!

* Por eso siempre el `this` implícito
    * En **todas** las funciones.
* `this` se pasa al hacer *obj*.*attr*(*args*)
* O se pasa el *“objeto global”* al hacer *f*(*args*)

----
# Para los incrédulos

    !js
    >>> fun = function (v) {this.x = v}
    >>> list = [10, 20, 30, 40, fun]
    >>> list[4]("hola!")

Y entonces quien es `this`?

    !js
    >>> x
    ReferenceError: x is not defined

Ok... no es el objeto global...

----
# Para los incrédulos

    !js
    >>> fun = function (v) {this.x = v}
    >>> list = [10, 20, 30, 40, fun]
    >>> list[4]("hola!")
    >>> list.x
    "hola!"

Recordatorio: La notación *obj*.*attr* es un atajo para *obj*`["`*attr*`"]`

Por lo tanto *obj*`[`*key*`](`*args*`)` es una llamada a método, con *obj* haciendo de `this`

----
# Alindando nuestros objetos

    !js
    // esta no es la versión final. no programen así
    function Cuenta(obj, inicial) {
        obj.balance = inicial
        obj.depositar = function (cantidad) {
            this.balance += cantidad;
        }
        obj.enRojo = function () {
            return (this.balance < 0);
        }
    }
    c1 = {}; Cuenta(c1, 10)
    c2 = {}; Cuenta(c2, 20)
    c1.depositar(20);
    if (c2.enRojo())

Mejora un poco. Todavía tenemos algunos problemas:

* no hay sharing de valores/métodos
* no hay forma de saber si algo es una `Cuenta` o no
* Repetición, y algo manual lo de `{}`

----
# Alindando nuestros objetos

    !js
    // todavía no es la versión final. no programen así
    function Cuenta(inicial) {
        this.balance = inicial
        this.depositar = function (cantidad) {
            this.balance += cantidad;
        }
        this.enRojo = function () {
            return (this.balance < 0);
        }
    }
    c1 = new Cuenta(10)
    c2 = new Cuenta(20)
    c1.depositar(20);
    if (c2.enRojo())

* Ahora podemos hacer `c1 instanceof Cuenta`
* Dejamos que el runtime cree objetos.

----
# Alindando nuestros objetos

    !js
    function Cuenta(inicial) {
        this.balance = inicial
    }
    Cuenta.prototype = {
        depositar: function (cantidad) {
            this.balance += cantidad;
        }
        enRojo: function () {
            return (this.balance < 0);
        }
    }

* `prototype` es un atributo que `new` lee
* Ahora las funciones están en un solo lugar

----
# Comparación: creación

Python:

    !python
    obj = Clase(x, y, z)

1. Llama a `Clase.__new__(Clase, x,y,z)`
2. Lo que normalmente acaba en `type.__new__(Clase, x,y,z)` que crea un objeto nuevo *o*
3. Al objeto se setea un atributo *o*`.__class__ = Clase`
4. se inicializa el objeto con `Clase.__init__(`*o*`, x, y, z)`
5. Liga `obj` a *o*

----
# Comparación: creación

Javascript:

    !js
    obj = new Clase(x, y, z)

1. `new` fabrica un objeto nuevo *o*
2. Al objeto se setea un atributo `obj.__proto__ = Clase.prototype`
3. se inicializa el objeto llamando a `Clase(x, y, z)` con `this`=*o*
4. Liga `obj` a *o*

El atributo `__proto__` no es visible en JS estándar

----
# Comparación: Lookup `obj.x`

Python:

1. Si `"x"` está en `obj.__dict__`, el resultado es `obj.__dict__["x"]`
2. Sino, en cada clase `C` de `obj.``__``class__.__mro__`
    1. si no está `"x"` en `C.__dict__`, pasar a la siguiente
    2. sea *x*=`C.__dict__["x"]`. Si *x* no tiene un `__get__`, el resultado es *x*
    3. sino, el resultado es *x*`.__get__(obj, obj.__class__)`
3. Si llegamos hasta acá, levantar `AttributeError`

----
# Comparación: Lookup `obj.x`

Javascript:

1. Sea *o*=`obj`
2. Si *o* es `null` el resultado es `undefined`
3. Si `"x"` está en *o*, el resultado es *o*`["x"]`
4. Sino, sea *o*=*o*`.prototype`, y volver a 2

----
# Comparacion: chequeo de tipos

Python:

    !python
    isinstance(obj, C)

Revisa si `obj.__class__` está en `C.__mro__`

    !js
    obj instanceof C

revisá si `obj.__proto__` esta en la cadena de prototipos de `C`

----
# Prototipos en Python?

## Sí!

* <http://tobyho.com/2009/05/23/prototype-inheritence-in/>
* <https://github.com/airportyh/misc/tree/86d360ef5b449f4d2ceb795fbf6015341a82d491/prototype.py>

----
# Repasando

* Son similares a nivel datos
* Muchos features están “convergiendo”
* algunos aspectos a nivel filosofía son distintos

----
# Bibliografía

* Mozilla Developer Network, <https://developer.mozilla.org/en-US/docs/JavaScript/Reference>
* <http://javascript.info/tutorial/object-conversion>
* <http://tobyho.com/2009/05/23/prototype-inheritence-in/>
* Guha, Saftoiu, Krishnamurthi: “The Essence of JavaScript”, 2011
* <http://saladwithsteve.com/2008/02/javascript-undefined-vs-null.html>
* Wikipedia, <http://en.wikipedia.org/wiki/Javascript>
* Wikipedia, <http://en.wikipedia.org/wiki/ECMAScript>
* <http://javascript.info/tutorial/constructor>

----
# Preguntas

## dmoisset@machinalis.com
## @dmoisset
## <https://github.com/machinalis/slides>


