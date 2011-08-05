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

Es útil analizar un poco nuestra industria y definir terminología para
comprender porque hacemos o dejamos de hacer nuestras distintas actividades.

La producción de Software es una actividad productiva. Algunas teorías
económicas analizan las actividades productivas separando los *factores de 
producción* involucrados. En nuestra área, se pueden identificar 3 factores
clave: Procesos, Personas, y Tecnología.

Los **procesos** son descripciones de actividades a realizar, normalmente por
personas, donde las actividades producen alguna transformación con el propósito
de generar valor, directa o indirectamente. Hay mucha variación respecto a cuan
precisos y auto-contenidos pueden ser los procesos. Algunos procesos son de
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

### Contra-propuesta: Modelos ágiles

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
The New New Product Development Game*,
<http://www.sao.corvallis.or.us/drupal/files/The%20New%20New%20Product%20Development%20Game.pdf>)

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

Durante el estudio mencionado, realizado en 1986 se observó que este modelo
teórico muchas veces se desviaba de la práctica real. La diferencia se hacía más
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
allá de donde podemos predecir es una inversión poco efectiva de esfuerzos,
mientras que además indican que no podemos dejar de planificar para poder
tener los cambios en cuenta.

El objetivo deja de ser cumplir una lista de requerimientos, para poder ser
cumplir con una visión.

En este nuevo entorno en las organizaciones hay varios elementos comunes:

 * Incertidumbre
 * Auto-organización
 * Superposición de las fases de desarrollo
 * Control sutil
 * Difusión del conocimiento

En un entorno de este tipo, denominado “campo de scrum” por Takeuchi y Nonaka,
las fases como tales no existen; se disuelven en actividades realizadas a
demanda. El orden de ejecución de esas tareas y la asignación se hace de forma
flexible por el mismo equipo que las va a realizar. Esto se hace en un entorno
de comunicación, no solo entre el equipo de trabajo sino también entre algún
representante del cliente o usuario, que provee retroalimentación continua
sobre la visión

## Los principios de la gestión ágil

### El manifiesto ágil

En el encuentro de Utah de 2001, el documento de cabecera producido es el llamado
*Manifiesto Ágil*, disponible en <http://agilemanifesto.org/>.

El texto (© 2001 los firmantes) es el siguiente:

> **Manifiesto por el Desarrollo Ágil de Software**
> 
> Estamos descubriendo formas mejores de desarrollar
> software tanto por nuestra propia experiencia como
> ayudando a terceros. A través de este trabajo hemos
> aprendido a valorar:
> 
> **Individuos e interacciones** sobre procesos y herramientas
> 
> **Software funcionando** sobre documentación extensiva
> 
> **Colaboración con el cliente** sobre negociación contractual
> 
> **Respuesta ante el cambio** sobre seguir un plan
> 
> Esto es, aunque valoramos los elementos de la derecha,
> valoramos más los de la izquierda.
> 
> Kent Beck, Mike Beedle, Arie van Bennekum, Alistair Cockburn, Ward Cunningham
> Martin Fowler, James Grenning, Jim Highsmith, Andrew Hunt, Ron Jeffries
> Jon Kern, Brian Marick, Robert C. Martin, Steve Mellor, Ken Schwaber
> Jeff Sutherland y Dave Thomas

El primer punto es un reconocimiento de que en el campo del desarrollo de
Software, el trabajo es esencialmente creativo y de conocimiento tácito, y
por lo tanto, los procesos y la tecnología deben servir a la gente y no al
revés. Es una contraposición a los procesos predictivos donde, en pro de la
repetibilidad, se ponen procesos rígidos y estrictos, que al no ser
funcionales a la creatividad requerida obstaculizan la producción de valor.

Los procesos son efectivos en tareas mecánicas y repetibles, pero defenderlos
a rajatabla en condiciones donde es necesaria resolución de problemas tiene
un resultado negativo

El segundo punto indica que el objetivo de un proyecto de desarrollo de
software es producir un producto de software, y la documentación interna no
tiene valor intrínseco. No quiere decir que siempre sea inútil, simplemente que
debe restringirse a aquellos casos donde es capaz de dar valor por que será
consultada para poder producir software (o por tener valor intrínseco cuando
es documentación externa).

El tercer punto se alinea con la forma de plantear objetivos en gestión ágil
En vez de prenegociar un contrato con una lista de requerimientos con la
meticulosidad suficiente para decidir cuando están cumplidos o no, la gestión
ágil busca maximizar valor para lo cual se colabora con el cliente en medir
los cambios que aumentaran más el valor del producto en las circunstancias
del momento.

El último punto hace explícito que el cambio deja de ser un aspecto a “evitar”
y controlar, para reconocerse como una fuerza intrínseca del proceso, y que
tiene que estar integrada plenamente en él.

### Objetivos de la gestión ágil

En un contexto donde el producto se desarrolla en un mercado y con
requerimientos cambiantes, el objetivo clásico de cumplimiento de una lista
de requerimientos para un producto final no mide con precisión las metas
reales de los que desarrollan proyectos.

En el nuevo contexto es frecuente que ni siquiera exista tal cosa como un
“producto final”, sino incrementos de valor sobre un producto que ya está
en el mercado

En vez, la gestión ágil propone mecanismos para lograr como meta:

**Incrementos de valor** donde cada aspecto del producto es evaluado por el
cliente, y en cada momento se agregan al producto aquellos que producen
los mayores beneficios.

**Menor tiempo de llegada al mercado**, lo que es crucial en un mercado
altamente competitivo. Para lograr esto los métodos ágiles solapan fases del
desarrollo, y hacen entregas tempranas que ya tienen valor en vez de esperar
alcanzar un estado "ideal".

**Flexibilidad** a través de establecer múltiples puntos donde puede ajustarse
el curso del proyecto de acuerdo a la evolución de los requerimientos

### El rol de la información

(Material basado en *Daniel Cook, 
Rockets, Cars and Gardens: Visualizing waterfall, agile and stage gate*
<http://www.lostgarden.com/2007/02/rockets-cars-and-gardens-visualizing.html>)

Hay dos premisas en la gestión ágil relacionadas al rol del conocimiento:

**El conocimiento es un componente crítico del éxito**: La razón principal
de la falla de muchos proyectos es enfocarse en aspectos poco relevantes o no
comprender lo que el cliente necesitaba. Esto concluye en la construcción de
productos de poco valor, lo que extiende los ciclos de desarrollo y pérdida
de credibilidad. No se puede brindar valor al cliente si no se conoce lo que
éste necesita.

**La mayoría de los equipos tienen poco conocimiento al comenzar**: 
Normalmente, sin importar cuantas reuniones o discusiones haya habido con el
cliente es muy limitado el conocimiento que tenemos de si el producto va a
resolver de forma efectiva las necesidades del cliente, de si el diseño va
a sobrevivir el encuentro con el mundo real. Podemos tener algunas ideas si
somos expertos en el área, pero aún así no podemos prever las restricciones
que van a encontrarse ni las oportunidades que podrían surgir

Por lo tanto es crucial que a lo largo del proyecto se vaya recolectando nueva
información, y además integrar esta información a nuestro proceso para que
tenga valor.

Cook hace una analogía del modelo predictivo con el lanzamiento de un cohete:
se establece una meta inicial, y se sigue el plan hasta su conclusión, sin
posibilidad de ajuste hasta que se llega a la meta

![Modelo predictivo](Iteration-Diagrams-Waterfall1-756439.jpg)

(Imagen © 2007 Daniel Cook)

Al llegar a la meta se hace un lanzamiento, en el cual puede obtenerse
información de si el producto generado era lo que el cliente o el mercado
necesitaba. En un mercado donde el ritmo de cambio es mas grande que el tiempo
de desarrollo del proyecto, esto tiene como consecuencia que suele no
llegarse a la meta deseada, a un costo importante. Si todavía queda recursos
puede intentarse nuevamente

![Modelo predictivo](Iteration-Diagrams-Waterfall3-715206.jpg)

(Imagen © 2007 Daniel Cook)

En este intento hay más chances de obtener buenos resultados porque el equipo
tiene mejor información (si bien sigue existiendo el riesgo de que esa
información vaya volviéndose obsoleta con el paso del tiempo). Fred Brooks, en
su clásico de la ingeniería de Software *“The Mythical Man-Month”* recomendaba
“Planea como si tuvieras que hacerlo dos veces, por que es lo que vas a hacer
de todos modos”

La metáfora para los procesos iterativos usados en metodologías ágiles son
similares a manejar en auto. No se fija en detalle de antemano cada maniobra,
sino que se van haciendo ligeros ajustes durante el camino

![Modelo iterativo](Iteration-Diagrams-Agile1-782053.jpg)

(Imagen © 2007 Daniel Cook)

Con este nuevo modelo, reconocemos que podemos equivocarnos, pero a su vez cada
uno de los errores que cometemos es de menor impacto por el reajuste constante.
A la larga, obtenemos un camino más eficiente y de menor riesgo.

![Modelo iterativo](Iteration-Diagrams-Agile3-765636.jpg)

(Imagen © 2007 Daniel Cook)

Para que la re-evaluación pueda hacerse, se generan versiones del producto cada
periodos cortos de tiempo (típicamente 2 a 4 semanas). La interacción con el
cliente y participación en todas las actividades del desarrollo transforma al
equipo en expertos. Los productos resultantes tienen muchas mejores chances de
servir a las necesidades reales del cliente.

### Modelos de trabajo cíclico

Los procesos ágiles usualmente contienen ciclos que se repiten. A veces estos
ciclos están anidados (es decir, ciclos grandes contienen muchos ciclos
pequeños). Si bien hay variantes entre los diferentes procesos, algunos elementos
son comunes.

Todos los ciclos parten de una *visión* general que delimita en que dirección se
desea avanzar y cuales son las restricciones. 

A partir de esa visión el equipo discute formas de avanzar hacia ella, fijando
*metas* para el ciclo, y ya teniendo en cuenta las restricciones del entorno
(costos, agenda).

Teniendo la meta el equipo colabora para la *producción* un incremento del producto
que satisfaga las metas.

Al terminar el ciclo se integra el trabajo realizado con el del resto del
equipo, y se hace una *inspección* donde se verifica que se hayan cumplido las
metas. Si hubo alguna desviación, se toman medidas de *adaptación* para el 
siguiente ciclo.

El primer aspecto clave de esto es que el cierre de cada ciclo no es el final
del proyecto, sino que en la mayoría de los casos se sigue del inicio de otro
ciclo.

El segundo aspecto clave es que cada ciclo termina lo que en metodologías
ágiles es normalmente llamado *Inspect and Adapt*, que es el elemento clave
que hecho periódicamente permitirá que el proceso sea flexible y responda a los
cambios. 

### Condiciones de aplicabilidad de modelos ágiles vs predictivos

Bajo nuestra premisa inicial de no seguir ciegamente procesos sino preguntarse
si el contexto en que los seguimos nos ayuda a alcanzar las metas que
necesitamos, es valioso preguntarse en cuales contextos es apropiado aplicar a
cada uno de los modelos.

El “contexto” en el que aplicamos el método involucra no sólo las 
características del producto que se construye, sino también las características
de la organización que lo construye. Veremos varias características de ambos
que inclinan la balanza hacia modelos ágiles o predictivos; es muy probable
que cualquier situación concreta tenga elementos de ambos lados de la balanza
y haya que hacer una ponderación para elegir la metodología.

El criterio principal para elección es el *objetivo del proyecto*. Si 
“maximizar el valor hacia una visión” describe mejor la situación que 
“satisfacer esta meta estricta de tiempos y costes para satisfacer esta lista
fija de requerimientos”, entonces probablemente queramos trabajar con un
modelo ágil. Este punto es clave, en el sentido de que elegir el modelo
no apropiado hará que lleguemos correctamente a la meta incorrecta.

La *variabilidad de los requerimientos* es otro punto a tener en cuenta. Aunque
cada vez es menos común, en algunos proyectos es posible obtener una lista de
requerimientos detallada y fija al inicio, y saber que eso sin cambios es lo
que va a satisfacer al cliente. En esos casos es perfectamente razonable
considerar modelos predictivos. Para entornos más variables, las metodologías
ágiles dan mejores respuestas.

El *costo de prototipado* es la contrapartida del valor que da prototipar
para obtener más información. Algunos productos (sobre todo si extendemos
las metodologías fuera del campo de software) son mucho más rígidos que 
otros, con lo cual pensar en hacer varias versiones para probar el efecto
se hace más costoso que los beneficios que provee. A medida de que el costo
de prototipado crece, se va haciendo más importante llegar a un resultado
correcto en pocos intentos; si sabemos cual resultado es correcto, eso se logra
con planificación. Si los prototipos son baratos el costo de esa planificación
puede invertirse en prototipos y disminuir costos y riesgos.

La *criticidad* del sistema normalmente influye en la importancia de 
“satisfacción de requisitos” contra “maximizar el valor”.

El *tamaño* del producto suele tener un impacto directo en el tamaño del equipo
involucrado. Los procesos ágiles tienen un foco fuerte en la comunicación
directa, pero el costo de esta comunicación crece con el tamaño del equipo.
La mayoría de las prácticas ágiles operan bien para equipos de hasta 10 a 15
personas. Para más de eso, hay que por lo menos pensar en algunos modelos que
proponen separar el producto en varios equipos ágiles que se comunican entre
sí siguiendo un esquema más tradicional

Organizacionalmente, los factores más importantes de la decisión están ligados
a la prioridad que los métodos ágiles dan a las personas frente a procesos
y tecnologías.

En el área de software, el *nivel de seniority* produce una variación muy grande
en la capacidad creativa de resolución de problemas y adaptación, que es una
habilidad importante para aplicar procesos ágiles. Un equipo con menor nivel de
experiencia va a tener problemas de adaptarse a métodos ágiles, sobre todo si
la poca experiencia que tienen se ha focalizado en otros métodos.

No sólo importa el equipo de trabajo en si sino la *cultura de la organización*
en donde se realiza el proyecto. Si el equipo trabaja con un método ágil, pero
la gestión no esta familiarizada y trata de evaluar el avance con objetivos
y métodos predictivos, la incongruencia dará lugar a roces que van a afectar
negativamente el desempeño de las personas, lo que en un proceso basado en
personas tiene un impacto negativo también en el proyecto

## Los 12 principios del Manifiesto Ágil

Es difícil hacer un mejor resumen de cierre sobre la gestión ágil que el
realizado por los autores del manifiesto ágil. Luego del manifiesto redactaron
una lista de principios sobre las prácticas, basadas en el manifiesto y en
su experiencia. Transcribo a continuación

> Nuestra mayor prioridad es satisfacer al cliente
> mediante la entrega temprana y continua de software
> con valor.
> 
> Aceptamos que los requisitos cambien, incluso en etapas
> tardías del desarrollo. Los procesos Ágiles aprovechan
> el cambio para proporcionar ventaja competitiva al
> cliente.
> 
> Entregamos software funcional frecuentemente, entre dos
> semanas y dos meses, con preferencia al periodo de
> tiempo más corto posible.
> 
> Los responsables de negocio y los desarrolladores
> trabajamos juntos de forma cotidiana durante todo
> el proyecto.
> 
> Los proyectos se desarrollan en torno a individuos
> motivados. Hay que darles el entorno y el apoyo que
> necesitan, y confiarles la ejecución del trabajo.
> 
> El método más eficiente y efectivo de comunicar
> información al equipo de desarrollo y entre sus
> miembros es la conversación cara a cara.
> 
> El software funcionando es la medida principal de
> progreso.
> 
> Los procesos Ágiles promueven el desarrollo
> sostenible. Los promotores, desarrolladores y usuarios
> debemos ser capaces de mantener un ritmo constante
> de forma indefinida.
> 
> La atención continua a la excelencia técnica y al
> buen diseño mejora la Agilidad.
> 
> La simplicidad, o el arte de maximizar la cantidad de
> trabajo no realizado, es esencial.
> 
> Las mejores arquitecturas, requisitos y diseños
> emergen de equipos auto-organizados.
> 
> A intervalos regulares el equipo reflexiona sobre
> cómo ser más efectivo para a continuación ajustar y
> perfeccionar su comportamiento en consecuencia. 
> 
> Fuente: <http://agilemanifesto.org/iso/es/principles.html>
> 


