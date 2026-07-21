# Prácticas PSyD

Aquí se recogen todas las prácticas de la asignatura PSyD. 

## Entorno de Prácticas: STM32

El entorno de prácticas consiste en una máquina virtual previamente configurada con la suite oficial de herramientas de **STMicroelectronics**, necesarias para la programación y desarrollo en placas y microcontroladores **STM32**.

---

### 🧰 Software Principal (Suite ST)

* 🛠️ **[STM32CubeIDE](https://www.st.com/content/st_com/en/stm32cubeide.html)**  
  Entorno de desarrollo integrado (IDE) C/C++ *"todo en uno"*. Integra funciones de configuración de periféricos, generación de código, compilación y depuración avanzada para toda la familia STM32.

* ⚙️ **[STM32CubeMX](https://www.st.com/content/st_com/en/stm32cubemx.html)**  
  Herramienta gráfica de configuración que permite seleccionar el microcontrolador, configurar sus periféricos, pines y reloj de forma visual, y generar automáticamente el código de inicialización en C.

* 🔌 **[STM32CubeProgrammer](https://www.st.com/content/st_com/en/stm32cubeprogrammer.html)**  
  Software de programación de memoria (Flash, RAM, registros). Permite leer, escribir y verificar el *firmware* del microcontrolador a través de interfaces de depuración (`SWD`, `JTAG`) o cargadores de arranque (`UART`, `USB`, `SPI`, `I2C`, `CAN`).

---

### 📚 Documentación y Manuales de Referencia

En la carpeta **Documentos** del entorno se encuentran varios recursos en forma de manuales. 

> **Nota:** Los dos primeros (**RM0431** y **UM2140**) son **fundamentales y obligatorios** para poder programar el dispositivo. El resto son auxiliares para comprender mejor la arquitectura del procesador.

#### Imprescindibles
1. **[RM0431 - Reference Manual](https://www.st.com/resource/en/reference_manual/rm0431-stm32f72xxx-and-stm32f73xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)**  
   Manual principal de referencia. Detalla toda la funcionalidad de los procesadores de la serie **STM32F723**, incluyendo periféricos, mapa de memoria, registros, modos de uso, etc.
2. **[UM2140 - User Manual](https://www.st.com/resource/en/user_manual/um2140-discovery-kit-with-stm32f723ie-mcu-stmicroelectronics.pdf)**  
   Manual con la descripción de conexiones y *pinout* detallado del kit de desarrollo **32F723EDISCOVERY**.

#### Auxiliares
* **[DB3105 - Data Brief](https://www.st.com/resource/en/data_brief/32f723ediscovery.pdf)**: Resumen de características del kit de desarrollo 32F723EDISCOVERY.
* **[DS11853 - Datasheet](https://www.st.com/resource/en/datasheet/stm32f722ic.pdf)**: Funcionalidad genérica, especificaciones físicas y características electrónicas del procesador STM32F723.
* **[PM0253 - Programming Manual](https://www.st.com/resource/en/programming_manual/pm0253-stm32f7-series-and-stm32h7-series-cortexm7-processor-programming-manual-stmicroelectronics.pdf)**: Manual de programación de la serie **Cortex-M7**, con la referencia completa del conjunto de instrucciones ensamblador.

---

### 📂 Repositorio de Ejemplos Base

Se incluye la colección de ejemplos oficiales **STM32CubeF7**. 

> **Nota:** Esta colección utiliza librerías de alto nivel (HAL/LL). En la primera parte de las prácticas programaremos *"desde cero"* (a nivel de registro), por lo que no usaremos estas librerías directamente. Sin embargo, los ejemplos son un buen punto de referencia para explorar las capacidades de la placa.

* **[STM32CubeF7 (GitHub)](https://github.com/STMicroelectronics/STM32Cubef7)**  
  Colección de ejemplos base. Incluye proyectos para múltiples placas, pero nos centraremos únicamente en la **32F723E**. 
  > **Atención:** Al clonar manualmente el repositorio, es imprescindible inicializar los submódulos para incluir todas las librerías requeridas. Mira bien las instrucciones del repositorio.

* **[STM32CubeF7 Patch](https://www.st.com/en/embedded-software/stm32cubef7.html)**  
  Parche que se debe sobrescribir en el repositorio una vez clonado. Añade librerías propietarias de terceros necesarias para funciones como el control táctil o el procesamiento de audio.

---

### 💻 Máquina Virtual (Debian 13.6)

El software y los recursos anteriores ya están preinstalados en una máquina virtual basada en **Debian 13.6**. Cuenta con un entorno ligero (gestor de ventanas, navegador básico) y las *VirtualBox Guest Additions* para habilitar el passthrough de dispositivos USB (necesario para conectar la placa).

#### 📥 Descarga rápida (Recomendado)
Puedes descargar la máquina virtual ya configurada y lista para importar en VirtualBox:
* **[Descargar Máquina Virtual (Google Drive)](https://drive.google.com/file/d/1U7Qvnkb-LfkJrcboyH4Jzs9iNczMntQg/view?usp=drivesdk)**

---

#### 🔨 Guía de recreación paso a paso (Opcional)

Si prefieres montar la máquina virtual desde cero de forma manual, sigue estos pasos:

1. **Preparar el anfitrión:**
   * Instala la versión más reciente de [VirtualBox](https://www.virtualbox.org/wiki/Downloads).
   * Instala el **VirtualBox Extension Pack** (disponible en la misma página de descargas).

2. **Crear la VM:**
   * Descarga la ISO de Debian desde [debian.org](https://www.debian.org/index.es.html).
   * Crea una máquina virtual nueva asignando al menos **4096 MB de RAM** y **2 vCPUs**.

3. **Instalar el SO:**
   * Inicia la VM con la ISO e instala Debian (mediante la instalación gráfica o manual).

4. **Instalar dependencias para Guest Additions:**
   Abre una terminal e instala los paquetes necesarios para compilar los módulos del kernel:
   ```bash
   sudo apt update
   sudo apt install build-essential dkms linux-headers-$(uname -r) -y
   ```

5. **Instalar VirtualBox Guest additions:**
    * En el menú superior de VirtualBox, seleccionar Devices -> Insert Guest Additions CD Image
    * Abre una terminal en la ruta donde se monta el CD (normalmente /media/cdrom) y ejecuta:
    ```bash
    sudo ./VBoxLinuxAdditions.run
    ```

6. **Instalar software extra y manuales:**
    * Descarga e instala las herramientas STM32CubeIDE, STM32CubeMX, y STM32CubeProgrammer siguiendo las instrucciones de cada uno.
    * Descarga y guarda los manuales PDF en una carpeta (por ejemplo, Documentos).
    * Clona el repositorio de ejemplos con submódulos:
    ```bash
    sudo apt-get install git -y
    git clone https://github.com/STMicroelectronics/STM32Cubef7.git
    cd STM32Cubef7
    git submodule update --init --recursive
    ```
    * Descarga y aplica el parche con las librerías extra.

---

## [Práctica 1](practica1) - Acceso elemental a dispositivos mapeados en memoria - Registros y depuración

### Objetivos:
  
* Crear un proyecto de ejemplo desde cero para la placa.
* Familiarizarse con el entorno STMCubeIDE para desarrollo y depuración.
* Entender la vista de depuración y las partes internas del procesador que son visibles:
    - Registros, memoria, registros especiales, depuración, desensamblado, ...
* Entender el concepto de dispositivo mapeado en memoria.
* Crear un pequeño programa que encienda un LED.
    


### Para hacer más

Busca el GPIO del botón de la placa, configúralo en modo entrada, y haz que el LED se encienda o apague cada vez que se pulse el botón, en lugar de hacerlo de manera automática.

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