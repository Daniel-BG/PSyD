# Prácticas PSyD

Aquí se recogen todas las prácticas de la asignatura PSyD. 

## [Práctica 0](initial_config/initial_config.pdf) - Configuración del entorno de programación

El entorno de prácticas consiste en una máquina virtual previamente configurada con la suite oficial de herramientas de **STMicroelectronics**, necesarias para la programación y desarrollo en placas y microcontroladores **STM32**.

Todas las herramientas se pueden instalar igualmente de manera nativa en un ordenador Linux, Windows o Mac.

En cualquiera de los dos casos, las instrucciones, herramientas y paquetes necesarios se describen en esta práctica.

---

## [Práctica 1](memory_mapped_io/memory_mapped_io.pdf) - Acceso elemental a dispositivos mapeados en memoria - Registros y depuración

En esta práctica se presenta la estructura de control del procesador, mediante accesos mapeados en memoria. También se introducen las nociones básicas de creación y depuración de proyectos.

---

## [Práctica 2](board_support_package/board_support_package.pdf) - Creación de BSP

En esta práctica se introduce la idea de BSP, un paquete que permite trabajar de manera cómoda con los elementos del procesador y placa. Se realizará la creación de un BSP personalizado para el proyecto.

---

## [Práctica 3](programmed_input_output/programmed_input_output.pdf) - Entrada / Salida programada - UART TX

La UART es uno de los periféricos más extendidos para intercomunicación de dispositivos empotrados por su sencillez de implementación. No es lo más rápido, pero sí uno de los protocolos más interoperativos. En esta práctica se programa una UART para comunicación directa con el ordenador.

---

## [Práctica 4](interrupts/interrupts.pdf) - Entrada / Salida por interrupciones - UART RX y botones

Las interrupciones permiten que el procesador ejecute cierta funcionalidad únicamente cuando ocurran eventos preprogramados. Su gestión requiere de una configuración concreta que se explora en esta práctica, mediante interrupciones para la recepción de información por UART y la detección de pulsaciones de botones.

---

## [Práctica 5](timers/timers.pdf) - Temporizadores

Determinados eventos en el procesador requieren de una ejecución temporizada. En lugar de utilizar contadores y esperas activas, los temporizadores proporcionan una manera determinista de ejecutar funciones periódicamente. En esta práctica se utilizarán para hacer parpadear unos LEDs, y adicionalmente controlar los rebotes de una entrada como un botón.

---

## [Práctica 6](systick/systick.pdf) - Ticker del sistema

Para medir el tiempo transcurrido dentro del procesador, se suele utilizar un marcador temporal o *ticker* que, cada cierto tiempo (configurable), incrementa una variable. Controlando esos tiempos de incremento podemos realizar esperas activas o medir el tiempo que transcurre entre eventos del procesador. En esta práctica se utiliza para hacer una función **delay** robusta, y para identificar dobles click de botón.

---

## [Práctica 7](display_and_drivers/display_and_drivers.pdf) - Periféricos externos - Display y Drivers

Hasta ahora, todos los periféricos que hemos visto son internos al procesador. Cumplen funciones diferentes a la de la simple ejecución de instrucciones, pero no se "ven" desde fuera. En esta práctica conectaremos con el display externo, y escribiremos un pequeño driver para controlarlo a través del controlador de memoria flexible (FMC) del procesador.

---

## [Práctica 8](i2c_and_touch/i2c_and_touch.pdf) - Buses de expansión - I2C y pantalla táctil

Los buses de expansión permiten la interconexión de numerosos dispositivos externos a través de líneas compartidas de datos. Esto permite una gran flexibilidad a la hora de ampliar las funcionalidades de nuestro sistema empotrado. En esta práctica, vemos uno de los buses más extendidos (el I2C), y aprendemos a configurar los periféricos internos del procesador necesarios para utilizarlo. Con él, nos conectaremos al panel táctil para recibir las coordenadas pulsadas por el usuario.
alla.

---

## [Práctica 9](persistence/persistence.pdf) - Persistencia - Memoria FLASH

No todas las zonas de memoria del procesador mantienen la información tras un reseteo. Si queremos guardar datos como configuraciones de usuario, deberemos hacerlo en memoria persistente. En esta práctica veremos cómo escribir sobre la memoria FLASH.

---

## [Práctica 10](cooperative_multitasking/cooperative_multitasking.pdf) - Planificadores - Cooperativo

## [Práctica 11](preemtive_multitasking/preemptive_multitasking.pdf) - Planificadores - Expropiativo

---

## [Práctica 10](thingsboard_data_control/thingsboard_data_control.pdf) - Comunicación remota con ThingsBoard

Aunque numerosos sistemas empotrados viven sus días aislados del mundo exterior (internet), muchos otros requieren de comunicación constante. Existen infinidad de plataformas de control, así como protocolos, que nos permiten precisamente esto. Podemos tanto recibir información, como mandar comandos de control desde y hacia nuestros dispositivos. En esta práctica vemos un ejemplo utilizando MQTT y Thingsboard.

---

## [Práctica 11](thingsboard_ota/thingsboard_ota.pdf) - Actualización remota (OTA) utilizando ThingsBoard

Hacer aplicaciones perfectas a la primera es algo muy complicado. Aún habiéndolas hecho, normalmente se requieren actualizaciones a lo largo del tiempo. Una vez hemos fabricado un dispositivo y está operativo, el enlace de depuración se suele perder, así que se requieren métodos más sofisticados para reprogramarlo. Uno de los más extendidos es el de dividir la memoria en dos, para crear un buffer de ping-pong donde una aplicación será la activa, y la otra la actualizable. En esta práctica ampliamos la anterior, añadiendo la capacidad de descargar aplicaciones via Wifi, grabarlas en la Flash, y por último cederles el control. Aprenderemos además cómo tenemos que compilar nuestras aplicaciones para que se puedan cargar de esta manera dual.

---


## [Práctica 12](automated_bsp_cubemx/automated_bsp_cubemx.pdf) - Creación automática de BSP

La creación manual de los BSP tiene la gran ventaja de utilizar única y exclusivamente las funcionalidades que nosotros queramos. Sin embargo, en ocasiones es muy deseable dejar este trabajo a otros, y conseguir un BSP robusto de manera automática, aunque incluya más funciones de la cuenta (con su consecuente coste en uso de memoria). En esta práctica aprendemos a crear automáticamente un BSP con la herramienta STMCubeMX, que nos permitirá seleccionar todos los periféricos que vayamos a utilizar, con su configuración incluida, para preocuparnos sólo de escribir la lógica del programa.

---


