# Prácticas PSyD

Aquí se recogen todas las prácticas de la asignatura PSyD. 

## [Práctica 0](practica0/practica0.pdf) - Configuración del entorno de programación

El entorno de prácticas consiste en una máquina virtual previamente configurada con la suite oficial de herramientas de **STMicroelectronics**, necesarias para la programación y desarrollo en placas y microcontroladores **STM32**.

Todas las herramientas se pueden instalar igualmente de manera nativa en un ordenador Linux, Windows o Mac.

En cualquiera de los dos casos, las instrucciones, herramientas y paquetes necesarios se describen en esta práctica.

---

## [Práctica 1](practica1/practica1.pdf) - Acceso elemental a dispositivos mapeados en memoria - Registros y depuración

En esta práctica se presenta la estructura de control del procesador, mediante accesos mapeados en memoria. También se introducen las nociones básicas de creación y depuración de proyectos.

---

## [Práctica 2](practica2/practica2.pdf) - Creación de BSP

En esta práctica se introduce la idea de BSP, un paquete que permite trabajar de manera cómoda con los elementos del procesador y placa. Se realizará la creación de un BSP personalizado para el proyecto.

---

## [Práctica 3](practica3/practica3.pdf) - Entrada / Salida programada - UART TX

La UART es uno de los periféricos más extendidos para intercomunicación de dispositivos empotrados por su sencillez de implementación. No es lo más rápido, pero sí uno de los protocolos más interoperativos. En esta práctica se programa una UART para comunicación directa con el ordenador.

---

## [Práctica 4](practica4/practica4.pdf) - Entrada / Salida por interrupciones - UART RX y botones

Las interrupciones permiten que el procesador ejecute cierta funcionalidad únicamente cuando ocurran eventos preprogramados. Su gestión requiere de una configuración concreta que se explora en esta práctica, mediante interrupciones para la recepción de información por UART y la detección de pulsaciones de botones.

---

## [Práctica 5](practica5/practica5.pdf) - Temporizadores

Determinados eventos en el procesador requieren de una ejecución temporizada. En lugar de utilizar contadores y esperas activas, los temporizadores proporcionan una manera determinista de ejecutar funciones periódicamente. En esta práctica se utilizarán para hacer parpadear unos LEDs, y adicionalmente controlar los rebotes de una entrada como un botón.

---

## [Práctica 6](practica6/practica6.pdf) - Periféricos externos - Display y Drivers

Hasta ahora, todos los periféricos que hemos visto son internos al procesador. Cumplen funciones diferentes a la de la simple ejecución de instrucciones, pero no se "ven" desde fuera. En esta práctica conectaremos con el display externo, y escribiremos un pequeño driver para controlarlo a través del controlador de memoria flexible (FMC) del procesador.

---

## [Práctica 7](practica7/practica7.pdf) - Buses de expansión - I2C y pantalla táctil

Los buses de expansión permiten la interconexión de numerosos dispositivos externos a través de líneas compartidas de datos. Esto permite una gran flexibilidad a la hora de ampliar las funcionalidades de nuestro sistema empotrado. En esta práctica, vemos uno de los buses más extendidos (el I2C), y aprendemos a configurar los periféricos internos del procesador necesarios para utilizarlo. Con él, nos conectaremos al panel táctil para recibir las coordenadas pulsadas por el usuario.
alla.

---

## [Práctica 8](practica8/practica8.pdf) - Bootloader y actualización automática

Hacer aplicaciones perfectas a la primera es algo muy complicado. Aún habiéndolas hecho, normalmente se requieren actualizaciones a lo largo del tiempo. Una vez hemos fabricado un dispositivo y está operativo, el enlace de depuración se suele perder, así que se requieren métodos más sofisticados para reprogramarlo. Uno de los más extendidos es el de programar un pequeño Bootloader, o cargador, que se encarga además de actualizar el código principal si es necesario. En esta práctica programaremos un bootloader capaz de descargar aplicaciones via Wifi, grabarlas en la Flash, y por último cederles el control. Aprenderemos además cómo tenemos que compilar nuestras aplicaciones para que el bootloader las pueda cargar.

---
