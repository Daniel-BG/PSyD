# Prácticas PSyD

Aquí se recogen todas las prácticas de la asignatura PSyD. 

## [Práctica 0](practica0/practica0.pdf) - Configuración del entorno de programación

El entorno de prácticas consiste en una máquina virtual previamente configurada con la suite oficial de herramientas de **STMicroelectronics**, necesarias para la programación y desarrollo en placas y microcontroladores **STM32**.

Todas las herramientas se pueden instalar igualmente de manera nativa en un ordenador Linux, Windows o Mac.

En cualquiera de los dos casos, las instrucciones, herramientas y paquetes necesarios se describen en esta práctica.

---

## [Práctica 1](practica1/practica1.pdf) - Acceso elemental a dispositivos mapeados en memoria - Registros y depuración

### Objetivos:
  
* Crear un proyecto de ejemplo desde cero para la placa.
* Familiarizarse con el entorno STMCubeIDE para desarrollo y depuración.
* Entender la vista de depuración y las partes internas del procesador que son visibles:
    - Registros, memoria, registros especiales, depuración, desensamblado, ...
* Entender el concepto de dispositivo mapeado en memoria.
* Crear un pequeño programa que encienda un LED.

### Para hacer más

Busca el GPIO del botón de la placa, configúralo en modo entrada, y haz que el LED se encienda o apague cada vez que se pulse el botón, en lugar de hacerlo de manera automática.

---

## Práctica 2 - Creación de BSP

    Objetivos:
        * Crear un BSP para facilitar las tareas al programador.
        * Entender la organización y estructura de un BSP básico

    Para hacer más -> Abre el proyecto BSP de ejemplo e investiga cómo están organizadas las funciones y demás, ahí se encuentra el paquete completo.

## Práctica 3 - Entrada / Salida programada - UART TX

    Objetivos:
        * Comprender el concepto de "periférico" dentro de un procesador
        * Aprender a programar un periférico 
        * Interactuar con el periférico desde fuera de la placa

    Para hacer más -> Averigua cómo hacer transferencias en modo DMA para poder seguir ejecutando código mientras la UART hace su trabajo "sola".

## Práctica 4 Entrada / Salida por interrupciones - UART RX

    Objetivos:
        * Aprender a trabajar con las interrupciones de los periféricos
        * Comprender las diferentes líneas de interrupción y cómo multiplexarlas.
        

    Para hacer más ->


## Práctica 5 - Entrada / Salida mediante interrupciones - Control de rebotes y timers y cuenta de tiempo real

    Objetivos:
        * Aprender a utilizar los timers, y el RTC para eventos temporizados
        * Aprender a enmascarar y desenmascarar interrupciones para conseguir funcionalidades complejas
        * Ver la diferencia entre la precisión de los timers internos y el RTC

    Para hacer más -> 

## Práctica 6 - Drivers avanzados - Display (Avanzados porque le mandas comandos en lugar de ser solo config de registros)

    Objetivos:
        * Enteder el concepto de driver
        * Trabajar con un periférico interno que controla uno externo
        * Aprender a configurar los periféricos externos

    Partir del ejemplo de LCD_Pictures (se puede comentar muchas cosas si se overridea la funcion HAL_delay, que estaría bien implementar bien)
    Introducir PWM a la parte de la backlight 

    The FSMC (Flexible Static Memory Controller) on STM32 microcontrollers is a built-in peripheral designed to interface with external memories (like SRAM, NOR/NAND Flash, and PSRAM) and parallel devices (like TFT LCDs). It maps external devices directly to the microcontroller's memory address space, allowing you to read and write to them as if they were internal RAM

    ST7789H2 sitronix for the LCD driver. Al parecer el TFT tiene también sus cosas pero no hay datasheet.

    Para hacer más -> Amplía la librería con funciones de dibujado de líneas, rectángulos, círculos... Explora la documentación para ver si hay maneras más rápidas de pintar la pantalla.

## Práctica 7 - Buses de expansión - I2C y pantalla táctil

    Objetivos:
        * Comprender el funcionamiento y uso de un bus de expansión, así como sus líneas de conexión
        * Comprender las interrupciones externas a traves de buses de expansión
        * Programar e interactuar con un dispositivo remoto

    Para hacer más -> Crea funciones de calibrado de la pantalla táctil para poder ajustar la pulsación recibida al marco real de la pantalla.

## Práctica 8 - DFU (hay ejemplo para ello)

## Práctica 9 - Multitarea cooperativa

    Objetivos:
        * Comprender cómo diseñar un framework para la ejecución múltiple de tareas
        * Comprender las limitaciones y ventajas de este método para ejecución en tiempo real.
        * Entender la utilidad de SystickHandler

    Para hacer más -> Añade tareas extra más complejas

## Práctica 9B - Multitarea expropiativa

    Objetivos 
        * Comprender y diseñar un framework para la ejecución de múltiples tareas - aunque se bloqueen
        * Entender la pila de funciones, registros, etc

    Para hacer más -> Ampliar el planificador para que si una tarea de baja prioridad se atasca, no atasque al resto.

## Práctica 10 - Zephyr RTOS - Introducción
    
    https://docs.zephyrproject.org/latest/develop/tools/stm32cubeide.html

## Práctica 11 - Zephyr RTOS - Multitarea, semáforos e interrupciones

## Práctica 12 - Zephyr RTOS - Device tree y drivers

## Práctica 13 - Zephyr RTOS - MCUBoot y OTA

## Práctica 14 - 

## Práctica 4 - Técnicas de depuración SWD y USB?

## Práctica 6 - Entrada / Salida por DMA - Sonido


Falta por meter en algún lado:
    Temporizadores (quizá en la 3 para que emita cada X tiempo?)




Transparencias de laboratorios:
Laboratorio 1: Acceso elemental a dispositivos (i): dispositivos externos mapeados en memoria.
Laboratorio 2: Acceso elemental a dispositivos (ii): dispositivos internos mapeados en memoria y dispositivos externos conectados a puertos de E/S.
Laboratorio 3: Drivers de dispositivos elementales: salida por leds y displays 7-segmentos.
Laboratorio 4: E/S programada: control de una UART y comunicación con un terminal serie.
Laboratorio 5: Gestión básica de interrupciones: programación de un reloj de tiempo real.
Laboratorio 6: Medida del tiempo: control de temporizadores y entrada por pulsadores y keypads.
Laboratorio 7: Salida por un LCD.
Laboratorio 8: Bus IIC: lectura/escritura de una EEPROM.
Laboratorio 9: E/S por DMA y Bus IIS: reproducción/grabación de sonido con un Audio Codec.
Laboratorio 10: Conversión analógico-digital: entrada por un touchpad.
Laboratorio 11: Autoarranque desde ROM.
Laboratorio 12: Multitarea cooperativa.
Laboratorio 13: Multitarea bajo un kernel de planificación no expropiativo.
Laboratorio 14: Multitarea bajo RTOS uC/OS-II.
Proyecto: Recreativa 1978. Space Invaders, Taito Corp.




Quiero que me ayudes a redactar una práctica para un curso de sistemas empotrados. En el curso estamos utilizando las placas 32F723EDISCOVERY (adjunto documentación relacionada). El enunciado debe estar redactado en latex, introduciendo poco a poco los conceptos básicos y construyendo código de una forma guiada y progresiva, dando snippets que se deberán rellenar siguiendo la documentación. 

Para esta práctica, el objetivo es entender cómo funcionan los periféricos mapeados en memoria mediante un LED encendido desde el sistema de GPIO. Te adjunto un código de ejemplo para otra placa similar. Deberíamos tener primero una explicación de todo el sistema (idealmente con referencias a la documentación) y luego el desarrollo del código guiado.

Quiero que me devuelvas el enunciado en latex de la práctica, gracias!