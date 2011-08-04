# Gestión de proyectos con Scrum

Daniel F. Moisset - dmoisset@machinalis.com

© 2011 Machinalis

## Los objetivos de la gestión de proyectos de Software

Nadie se cuestiona hoy en día sobre la necesidad de usar técnicas de gestión
al momento de encarar un nuevo proyecto de desarrollo de Software. Sería una
locura esperar que, luego de encerrar a un conjunto de desarrolladores sueltos
con un “cliente”, al cabo de un período de tiempo saliera un producto de
software para ese cliente.

En vez de tomar esto como una verdad dada, es importante realizar algunas
preguntas importantes. Estas preguntas no van a ser importantes solamente
para entender puntualmente la gestión de proyectos de software, sino que son
preguntas que en el día a día de proyectos scrum nos vamos a estar haciendo
permanentemente

### El origen de los procesos

Una historia interesante que circula en la Internet, es interesante para la
situación:

> **Monos y Plátanos**
> 
> Un grupo de científicos encerró a cinco monos en una jaula, en cuyo centro colocaron una escalera y, sobre ella, un montón de plátanos.
> Cuando uno de los monos subía la escalera para agarrar los plátanos los científicos lanzaban un chorro de agua fría sobre los que se quedaban en el suelo.
> Pasado algún tiempo, los monos aprendieron la relación entre la escalera y el agua, de modo que cuando un mono iba a subir la escalera, los otros lo molían a palos.
> 
> Después de haberse repetido varias veces la experiencia, ningún mono osaba subir la escalera, a pesar de la tentación de los plátanos.
> 
> Entonces, los científicos sustituyeron a uno de los monos por otro nuevo.
> Lo primero que hizo el mono novato nada más ver los plátanos fue subir la escalera. Los otros, rápidamente, le bajaron y le pegaron antes de que saliera el agua fría sobre ellos.
> Después de algunas palizas, el nuevo integrante del grupo nunca más subió por la escalera.
> 
> Un segundo mono fue sustituido, y ocurrió lo mismo con el que entró en su lugar.
> El primer sustituido participó con especial entusiasmo en la paliza al nuevo.
> Un tercero fue cambiado, y se repitió el suceso.
> El cuarto, y finalmente el quinto de los monos originales fueron sustituidos también por otros nuevos.
> 
> Los científicos se quedaron con un grupo de cinco monos que, a pesar de no haber recibido nunca una ducha de agua fría, continuaban golpeando a aquél que intentaba llegar hasta los plátanos.
> Si fuera posible preguntar a alguno de ellos por qué pegaban con tanto ímpetu al que subía a por los plátanos, con certeza ésta sería la respuesta: «No lo sé. Aquí, las cosas siempre se han hecho así».
> 
> *Fuente*: <http://akin.blogalia.com/historias/3260>

Esta fábula tiene más moralejas de las que se pueden llegar a ver a primera
vista. La primera y obvia es que vale la pena cuestionarse el motivo por el
cual hacemos las cosas, aún si son cosas que siempre vimos que “se hacen
así”. Y aplicar gestión de proyectos es una cosa que hacemos porque siempre “se
hizo así”.

Muchos de los procesos de gestión que hoy en día, se basan en premisas falsas o
suposiciones sobre el contexto que han cambiado en las décadas que han
transcurrido entre el desarrollo de esos métodos y la actualidad.

Pero antes de tirar los procesos de gestión por la borda y empezar de cero,
también es interesante ver una segunda moraleja en la fábula: los monos no son
tan estúpidos como parecen al final: desarrollaron un procedimiento para seguir
que de forma efectiva les evita un problema. Si bien los 5 monos finales no
saben por que lo hacen, probablemente están haciendo algo que los beneficia.

Entonces, queremos ser como los monos, o diferentes? Lo ideal es tener procesos
que nos permitan evitar situaciones desventajosas (chorros de agua fría), pero
a la vez entender en que contexto el *motivo* de esas reglas, para no estar
ciegamente atado a ellas cuando las premisas sobre las cuales trabajamos
cambian.

Para cualquier práctica es útil preguntarse ¿Vale la pena hacer esto? y en caso
de que valga la pena, también tenemos que preguntarnos ¿por qué? y ¿En que caso
estas causas siguen siendo válidas y lo que hacemos resuelve el problema? 

En desarrollo de software uno puede hacer estas preguntas respecto a cualquiera
de las prácticas. En algunos casos las respuestas se encuentran fácil. ¿Vale
la pena que los desarrolladores programen? Sí. ¿por qué? por que si no lo hacen
no existe el software que queremos construir. Entonces hoy poner programadores
a trabajar en un proyecto de software es muy justificable, pero eso podría
dejar de ser válido en un contexto donde el software pueda crearse sin que los
programadores lo construyan. Hoy eso es un escenario bastante ficticio, pero
si alguien llega a ese escenario bien debería rehacerse esas preguntas en vez
de programar porque “siempre pusimos programadores a programar para escribir
software”

Otras actividades en el desarrollo toman más trabajo de justificar. Eso no
quiere decir que importen menos, sólo que el impacto de estas tareas sobre la
calidad del producto es indirecto, y por ello dependen de más variables. Por
ejemplo realizar QA no mejora por si solo el producto final, pero hay formas
de hacerlo donde se puede observar que resulta en un producto con menos
defectos.

### El rol de los modelos, procesos, personas, y tecnología.

Es útil analizar un poco nuetra industria y definir terminología para
comprender porque hacemos odejamos de hacer nuestras distintas actividades.

La producción de Software es una actividad productiva. Algunas teorías
económicas analizan las actividades productivas separando los *factores de 
producción* involucrados. En nuestra área, se pueden identificar 3 factores
clave: Procesos, Personas, y Tecnología.

Los **procesos** son descripciones de actividades a realizar, normalmente por
personas, donde las actividades producen alguna transformación con el propósito
de generar valor, directa o indirectamente. Hay mucha variación respecto a cuan
precisos y autocontenidos pueden ser los procesos. Algunos procesos son de
conocimiento explícito, y el rol de la persona (si es que lo hay) es proveer
una fuerza de trabajo siguiendo literalmente el proceso. Otros procesos son
de conocimiento tácito, donde sirve como herramienta guía apara la persona
pero es la persona la que aplica su conocimiento para generar valor.

Las **personas** actúan proveyendo una combinación de *trabajo* (especialmente
en procesos con conocimiento explícito) y de *conocimiento* (en procesos con
conocimiento tácito). El valor de cada uno de estos en el producto es esencial
para decidir que tipo de procesos aportaran más valor.

La **tecnología** provee herramientas y mecanismos de transformación e
inspección que auxilian a los dos elementos anteriores. Si bien somos parte
de una industria íntimamente ligada a la tecnología, en este curso tomamos
la decisión de relegarla a un papel secundario. Esto se debe a que la
tecnología no debería guiar nuestros objetivos, sino que debería ser elegida y
utilizada de forma que sirva a ellos.

Para que nuestra organización sea productiva, estos 3 factores deben estar
funcionando bien y colaborando mutuamente. Ningún proceso puede compensar la
falta de capacidad de trabajo o conocimiento en las personas, ni puede
resolver la carencia de tecnología apropiada. Aún suponiendo que disponemos
de suficientes personas bien capacitadas y con el equipamiento correcto, un 
proceso que las personas no están convencidas de seguir tampoco acaba siendo
útil.

En este curso, se hará foco esencial en procesos, pero de una forma en que las
personas estén incentivadas a ver su valor y seguirlo.

Los procesos usualmente no vienen sueltos, sino agrupados en *modelos* o 
*prácticas* que brindan un marco de trabajo coherente. Los primeros normalmente
dan formas de mejora y evaluación sobre objetivos sin prescribir una forma
de trabajo, mientras que los segundos son más específicos, y a la vez menos
intrusivos organizacionalmente

## Motivación histórica/contextual

### El origen del problema

Una de las mejores formas de evaluar si una actividad tiene valor es preguntarse
que pasaría si dejamos de hacerla. Si nada cambia, conviene no hacer la tarea.
Normalmente la decisión no es tan obvia porque dejar de hacer una tarea trae
beneficios (típicamente ahorro de tiempo, esfuerzo y dinero) y simultáneamente
trae desventajas.

A nadie le gusta inventarse trabajo por que sí. La mayoría de las tareas que
“se hacen” están ahí porque al menos en algún momento fueron o parecieron
beneficiosas.

La gestión de proyectos de software como disciplina nace de ese modo. Hasta
mediados o fines de los '60 la programación era “artesanal” y normalmente sin
gestión. Un “experto” se arremangaba delante de la computadora y producía lo
que a su juicio era el producto de software necesario. En muchos casos este
procedimiento era efectivo.

A medida que el hardware se fue volviendo más complejo y poderoso, y la
ubicuidad de las computadoras creció, los requerimientos de los sistemas fueron
creciendo y la complejidad del software necesario también. Esta complejidad
se tradujo en complejidad para construir el software, que frecuentemente
terminaba en:

 * Proyectos pasados en costo.
 * Proyectos fuera de sus plazos.
 * Software ineficiente.
 * Software de poca calidad.
 * Software que no satisfacía requerimientos.
 * Proyectos complicados de continuar y mantener.
 * Software que jamás era entregado.

En una conferencia de la OTAN en 1968 se discutieron estos problemas y se
acuñaron los términos *crisis del software* e *Ingeniería de Software*.

### La primer solución: Modelos predictivos

Ante el chorro de agua fría que resultó ser la crisis del Software, comenzaron
a buscarse mecanismos de prevenir los problemas detectados. Los primeros
intentos, se basaron en adoptar modelos y prácticas de la ingeniería y gestión
de proyectos existentes (en ámbitos militares, automotrices).

Los mecanismos de gestión existentes en el momento eran principalmente modelos
de *gestión predictiva*, donde la gestión es una disciplina formal, basada en 
planificación seguida de ejecución seguida de seguimiento, usando procesos
sistemáticos y repetibles.

La gestión predictiva establece como medida de éxito mantenerse en los límites
de tiempo y coste, obteniendo un producto que satisfaga los requerimientos. En
base a ese objetivo establece mecanismos para mantener el cronograma,
presupuesto y recursos. Para ello se basa en una serie de suposiciones de que
el proyecto se desarrolla en un ámbito predecible y sin cambios, y por lo tanto
puede seguir una secuencia preestablecida de pasos de concepto, requisitos,
diseño, planificación, cierre.

Los mecanismos de la gestión predictiva proponen que el trabajo basado en
procesos garantiza repetibilidad, escalabilidad y mejora continua

### Crítica a los modelos predictivos

Durante la década de los 1990, distintos grupos de estudiosos y practicantes
de la Ingeniería de Software empezaron a cuestionar la efectividad de la
solución propuesta. Algunos estudios[1] indicaron que solo entre el 15% y el 25%
de los proyectos de software (dependiendo el año) resultaban "exitosos", y
entre el 30% y 40% de los proyectos resultaba en fracaso completo.

Entre los '70 y los '90, la explicación usual de por que los modelos fallaban
era “No estás haciendo o suficiente”. El cambio en los '90 fue que mucha gente
empezó a preguntarse si no tenían que en vez hacer algo diferente, si la falla
no era por aplicar técnicas inapropiadas en vez de falta de aplicación de 
éstas.

Hubo varios a aspectos a cuestionar, desde la forma de medir el éxito, hasta los
objetivos del proceso y la gestión en sí.

[1] http://spinroot.com/spin/Doc/course/Standish_Survey.htm

### Contrapropuesta: Modelos ágiles

El cuestionamento de los '90s llevo a varios grupos a desarrollar diferentes
nuevos modelos y prácticas que trataban de evitar los problemas de los modelos
predictivos. Si bien muchos de estos desarrollos fueron independientes,
empezaron a notarse muchos aspectos comunes entre estos modelos (como Scrum, XP,
TDD, etc.)

En febrero de 2001, 17 impulsores de estos nuevos modelos se reunieron para
aunar esfuerzos y encontrar formas de colaboración en base a los puntos
comunes. De esa reunión salió el nombre de *metodologías ágiles*, y un documento
describiendo los principios y valores compartidos entre ellos.

Los modelos proponen formas de trabajo adaptivas y flexibles, y descartan el
estilo preplanificado y rígido de otras metodologías formales que se estaban
desarrollando simultáneamente como CMMI e ISO 15504.

### Nuevo contexto en las organizaciones

(El contenido de esta sección se basa en *Hirotaka Takeuchi y Ikujiro Nonaka: 
The New New Product Development Game*, <http://www.sao.corvallis.or.us/drupal/files/The%20New%20New%20Product%20Development%20Game.pdf>)

Hasta los '80s la forma típica en que se planteaban los proyectos en una
organización era una secuencia de pasos, donde las tareas a realizar en cada
paso eran diferentes:

 * Requerimientos
 * Diseño
 * Codificación
 * QA
 * Integración
 * Operación y Mantenimiento
 
En este contexto, cada uno de estos pasos era llevado a cabo por un equipo
especializado diferente, mientras que la gestión de proyectos se encargaba de
comunicar y sincronizar cada uno de los departamentos involucrados. Cada
departamento tenía su propio sistema de procesos.

Durante estudios realizados durante los '80 se observo que este modelo teórico
muchas veces se desviaba de la práctica real. La diferencia se hacía más
marcada en aquellos equipos que estaban desarrollando tecnología más novedosa
y recorriendo espacios inexplorados. En esos casos, tendían a tener más éxito
aquellas empresas que, en vez de tener distintos departamentos especializados, 
tenían un equipo interdisciplinario que colaboraba a lo largo de todo el proceso
de desarrollo de los productos.

Este nuevo escenario es cada vez mas frecuente a medida que los avances
tecnológicos hacen que los ciclos de obsolescencia de productos sean cada vez
menores. En este contexto, los productos necesitan:

 * Producir valor lo antes posible en el proceso
 * Mantenerse activos y en renovación, con cambios y actualizaciones constantes
 * Adaptarse a cambios en el mercado

Estas circunstancias invalidad muchas de las premisas de los modelos
predictivos. Los modelos ágiles incorporan como premisa que el cambio es una
parte intrínseca del desarrollo del producto, y por lo tanto planear más
allá de donde podemos predecir es una inversión inefectiva de esfuerzos,
mientras que además indican que no podemos dejar de planificar para poder
tener los cambios en cuenta.

El objetivo deja de ser cumplir una lista de requerimientos, para poder ser
cumplir con una visión

En este nuevo entorno en las organizaciones hay varios elementos comunes:

 * Incertidumbre
 * Auto-organización
 * Superposición de las fases de desarrollo
 * Control sútil
 * Difusión del conocimiento

http://www.lostgarden.com/2007/02/rockets-cars-and-gardens-visualizing.html

----

1. Los objetivos de la gestión de proyectos de Software
       * Analisis de la problemática
       * El rol de los modelos, procesos, personas, y tecnología.
2. Motivacion historica/contectual
       * Crisis del software
       * Modelos predictivos vs
       * Modelos agiles
       * Nuevos entornos organizacionales
3. Los principios de la gestion agil

       * El manifiesto agil
       * Objetivos de la gestion agil
       * Modelos de trabajo ciclico
       * Condiciones de aplicabilidad de modelos agiles vs predictivos
