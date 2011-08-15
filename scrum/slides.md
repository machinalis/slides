# Gestión de proyectos con Scrum

----

## Daniel F. Moisset

## dmoisset@machinalis.com

© 2011 Machinalis

----

## Plan de curso

1. Gestión de proyectos de Software
2. El modelo básico en Scrum
3. Otros elementos, buenas prácticas
4. Proyecto práctico

----

# Los objetivos de la gestión de proyectos de Software

----

## “Gestión de proyectos (software)”

Obvio!

----

## “El origen...”

(en forma de fábula)

----

## ¿Esto es lo que queremos?

 * ¿Son los monos inteligentes por tener un proceso?
 * ¿Son los monos tontos por no entender lo que hacen?

----

## Idealmente

 * Tenemos procesos que capturan nuestro aprendizaje
 * Entendemos el motivo por el cual tenemos tales procesos
 * Entendemos el contexto en el cual esos procesos valen
 * Evaluamos si el contexto sigue siendo válido
    * Y si no lo es, adaptamos!

----

## Ejemplo: desarrollo

 * Agrega valor directamente a lo que queremos obtener
 * ¿Bajo que premisas?

----

## Ejemplo: QA

 * Agrega valor indirectamente a lo que queremos obtener
 * ¿Bajo que premisas?

----

## Factores de producción

 * Procesos 
 * Personas
 * Tecnología

----

## Factores de producción: procesos

 * Procesos 
    * Conocimiento implícito
    * Conocimiento tácito
 * Personas
 * Tecnología

----

## Factores de producción: personas

 * Procesos 
 * Personas
    * Conocimiento
    * Trabajo
 * Tecnología

----

## Factores de producción: tecnología

 * Procesos 
 * Personas
 * Tecnología
    * Al servicio de procesos y personas

----
## Procesos:

 * Modelos
    * ¿Qué ...?
    * Ej: Lean, PMBOK, CMMI
 * Prácticas
    * ¿Como ...?
    * Ej: Scrum, XP, Test Driven Development

----
# ¿Y si no hacemos nada de gestión?

----

## La “crisis del software”

 * Proyectos pasados en costo.
 * Proyectos fuera de sus plazos.
 * Software ineficiente.
 * Software de poca calidad.
 * Software que no satisfacía requerimientos.
 * Proyectos complicados de continuar y mantener.
 * Software que jamás era entregado.

----
## Solución: gestión predictiva

 * Basada en otras disciplinas
    * Con sus propios supuestos
 * Disciplina formal
 * Ciclo de planificación/ejecución/seguimiento
 * Tiene como objetivos cumplimiento de tiempo, costo y requerimientos
 * Presupone un entorno predecible
 * Basada en procesos
    * Repetibilidad, escalabilidad, mejora contínua

----
## Crítica: gestión predictiva

 * ¿Está aplicada en el contexto apropiado?
 * ¿Sus objetivos y métricas son relevantes?
 * ¿Existen otros modelos?
 * ¿Es su valor agregado superior al costo?

----
## Modelos ágiles

 * Iterativos e incrementales
 * Equipos autoorganizados
 * Foco en las personas y el producto, no en el proceso y las tecnología
 * Basados en la suposición de un entorno cambiante
 
----
# The New New Product Development Game

----
## Campos de scrum

 * Incertidumbre
 * Auto-organización
 * Superposición de las fases de desarrollo
 * Control sútil
 * Difusión del conocimiento

----
## Incertidumbre

 * Visión compartida
 * Responsabilidad compartida
 * Autonomía y libertad compartida
 
----
## Auto-organización

 * No hay roles de gestión
 * No hay pautas de organización de tareas

El equipo debe tener:

 * Autonomía
 * Voluntad de superación
 * Voluntad de enriquecimiento

----
## Superposición de las fases

 * *Sashimi* o *rugby*
 * Los involucrados se hacen responsables por el resultado final
 * Comunicación directa por sobre documentación
 * Eliminación de cuellos de botella

----
## Control sutil

 * Fomento de creatividad
 * Control entre pares
 * Interacción entre ingenieros y clientes
 * Tolerancia con errores
 * Implicación del cilente en el proceso
 
----
## Transferencia de conocimiento

 * A nivel proyecto
 * A nivel organización 
 
---- 

# Modelos ágiles

----
## El manifiesto ágil

 * Personas > Procesos
 * Software > Documentación
 * Colaboración > Contrato
 * Adaptabilidad > Precisión
 
----
## Personas > Procesos

 * El software es un área de conocimiento tácito
 * El talento no es sustituible por procesos
 * Los procesos tienen su lugar
 
----
## Software > Documentación 

 * La documentación interna es un auxiliar
 * No garantiza calidad
    * Solo se hace la que sirve
 * Al escribir documentación:
    * ¿Cómo se mantiene?
    * ¿Cuando se usa?
    * Se puede transmitir la misma información de modo más eficiente?

----
## Colaboración > Contrato

 * Contrato implica:
    * Prenegociar
    * Un momento de comunicación alcanza
 * Colaboración implica:
    * Comunicación continua
    * Involucramiento en el proyecto

----
## Adaptabilidad > Precisión

 * El cambio no es “mala suerte”
    * *Embrace change*
    * La variabilidad del contexto se presupone
    * Planear en base al cambio
 * Seguimiento de un plan no sirve si el contexto cambia
    * No quiere decir que no haya planes
    * El plazo del plan debe ajustarse a la variabilidad del contexto

----
## Objetivos ágiles:

 * Producir incrementos de valor
 * Minimizar tiempo de salida al mercado
 * Responder al cambio

----
## Respondiendo al cambio

 * Necesitamos recolectar permanentemente conocimiento
    * Para garantizar valor
 * El conocimiento inicial es bajo
 * La forma de recolectar conocimiento es haciendo y revisando
 
----
## Modelo predictivo 

 * Se supone el conocimiento inicial. Se fija la meta y se lanza un cohete.
 
<img src="waterfall1.png">

 * Si las cosas cambian, nos enteramos al llegar
 
----

## Modelo predictivo 

 * Si quedan recursos, se puede reintentar.
 
<img src="waterfall2.png">

----
## Modelo iterativo

 * Se avanza hasta un incremento
 
<img src="iterative1.png">

 * *Dado que las cosas cambian*, medimos y ajustamos
 
----

## Modelo iterativo 

 * Como esta planeado, reintentamos
 
<img src="iterative2.png">

 * El esfuerzo total es menor
 
----
## Ciclos

 * Visión compartida
    * Se planean metas para el ciclo
 * Se produce un incremento
    * Se integra
 * Se evalúa contra las metas (*Inspect*)
 * Se ajusta el plan y proceso (*Adapt*)
 
----
# Cuando aplicar?

Aspectos del proyecto:

 * Objetivo
 * Variabilidad
 * Costo de prototipado
 * Criticidad
 * Tamaño
 
----
# Cuando aplicar?

Aspectos de la organización:

 * Seniority
 * Cultura
