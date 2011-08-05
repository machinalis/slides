# Gestión de proyectos con Scrum

# Ejercicios - Parte I

Daniel F. Moisset - <dmoisset@machinalis.com>

© 2011 Machinalis

1. Discutir grupalmente que valor aportan las siguientes actividades:

    * Análisis de requerimientos
    * Diseño
    * Desarrollo
    * Testing Automático
    * Testing Manual
    * Documentacion externa
    * Documentación interna
    * Mantenimiento

    Discutir si el valor agregado es directo o indirecto.
 
2. Para cada par de *factores de producción* (procesos, personas, tecnología),
   dar un ejemplo de un tipo de organización con foco en ellos dos pero no el
   otro.
   
    * Procesos y Tecnología:
    * Procesos y Personas:
    * Personas y Tecnología:

3. Para cada una de los siguientes actividades, evaluar del 1 al 10 cuánto
   participa las personas, y cuánto participa el proceso + tecnología
   
    * Un artista haciendo pintura al óleo
    * Una imprenta
    * Cocinero en cocina de un restaurant de comida rápida
    * Cocinero en cocina de un restaurant gourmet francés
    * Operario en una fábrica de alimentos
    * Conductor de trenes
    * Piloto de rally

4. Para cada una de las siguientes tareas evaluar del 1 al 10 la confianza que
le darían a una máquina realizando la tarea, vs la confianza que le darían a
persona idónea realizando la tarea.

    * Realizar una entrevista a candidatos políticos
    * Tornear piezas de motores
    * Jugar al ajedrez
    * Componer jazz
    * Coser ropa industrial
    * Defender a un acusado en un juicio
    * Detectar infractores de límites de velocidad

5. Discutir en grupo: construir una línea de tiempo de cuando fueron
   incorporados distintos accesorios al tablero de los autos. Incluir por
   ejemplo:
   
    * Radio
    * Stereo con cassette
    * Integración con teléfono
    * GPS
    * Reproductor de DVD
    etc.

## Modelo de Gestión predictiva

En los siguientes ejercicios realizaremos y ejecutaremos un plan con una
simulación de modelos predictivos.

Vamos a definir un proyecto como una lista de tareas a realizar secuencialmente,
junto con restricciones de tiempo y costo.
La descripción de cada tarea será simplemente una medida de “esfuerzo” en una
unidad arbitraria. Por ejemplo, una descripción de proyecto simple podría ser

<table border="1">
    <tr><th>Tarea</th><th>Esfuerzo</th></tr>
    <tr><td>I</td><td>50</td></tr>
    <tr><td>II</td><td>80</td></tr>
</table>

**Tiempo máximo**: 5; **Costo máximo**: 5800

Para planificar un proyecto, vamos a dar una secuencia de actividades
y asociarlas a cada tarea. La lista de actividades posibles está dada, y cada
una de ellas va a producir un *avance* (en esfuerzo), y va a tener un *costo*,
consumiendo una unidad de tiempo. Por ejemplo, podríamos tener las siguientes
actividades:

<table border="1">
    <tr><th>Actividad</th><th>Avance</th><th>Costo</th></tr>
    <tr><td>A</td><td>30</td><td>1000</td></tr>
    <tr><td>B</td><td>60</td><td>2500</td></tr>
</table>

Con esas restricciones, podríamos dar un plan:
    
> I:AA; II: AB (tiempo=4, costo=5500)
    
o bien:
    
> I:AA; II: AAA (tiempo=5, costo=5000)
    
Por supuesto, también existen planificaciones que se pasan del costo:

> I:B; II: AB (tiempo=3, costo=6000)
    
O del tiempo (en este caso no es posible, porque el tiempo máximo permitido
es cómodo), o planificaciones que no cumplen los requerimientos:
    
> I:B; II: B (tiempo=2, costo=5000)
    
1. Planificar el siguiente proyecto

    <table border="1">
    <tr><th>Tarea</th><th>Esfuerzo</th></tr>
    <tr><td>I</td><td>130</td></tr>
    <tr><td>II</td><td>90</td></tr>
    <tr><td>III</td><td>20</td></tr>
    <tr><td>IV</td><td>130</td></tr>
    <tr><td>V</td><td>30</td></tr>
    <tr><td>VI</td><td>70</td></tr>
    <tr><td>VII</td><td>160</td></tr>
    <tr><td>VIII</td><td>120</td></tr>
</table>

    **Tiempo máximo**: 30;

    <table border="1">
    <tr><th>Actividad</th><th>Avance</th><th>Costo</th></tr>
    <tr><td>A</td><td>20</td><td>1000</td></tr>
    <tr><td>B</td><td>30</td><td>1800</td></tr>
    <tr><td>C</td><td>50</td><td>3000</td></tr>
</table>

2. Planificar el proyecto anterior, pero ahora con la restricción de que el
tiempo máximo es 24, y el costo máximo es 48000

3. Introducimos la siguiente variante en el modelo, para simular variabilidad
durante la ejecución: Al llevar al cabo el plan, el avance real de las
tareas nos era un valor fijo, sino que variará según una tirada de dado 
(simulando así elementos imprevistos). El símbolo "?" indica tal tirada:

    <table border="1">
    <tr><th>Actividad</th><th>Avance</th><th>Costo</th></tr>
    <tr><td>A</td><td>17+?</td><td>1000</td></tr>
    <tr><td>B</td><td>27+?</td><td>1800</td></tr>
    <tr><td>C</td><td>43+?+?</td><td>3000</td></tr>
</table>

    * Reajustar el último plan si se lo desea para considerar esta variación
    * “Ejectuar” el plan (tirando los dados y midiendo cuanto se avanzó en cada
      tarea).
    * Evaluar: ¿Fue el plan un éxito o fracaso?
        * En caso de éxito: cuanta desviación hubo del plan? que significa?
          (Discutir)
        * En caso de fracaso: queda margen para reajustes? En ese caso,
          realizarlos y reevaluar

## Aplicabilidad del modelo ágil

Para cada uno de los siguientes aspectos, de dos ejemplos de proyectos (no
necesariamente de Software), uno donde el aspecto lo haga más apto para gestión
ágil, y el otro donde lo haga más apto para gestión predictiva

 * Objetivo del proyecto
 * Variabilidad de los requerimientos
 * Costo de prototipado
 * Criticidad
 * Tamaño
 
