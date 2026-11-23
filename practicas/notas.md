## Práctica 9B - Multitarea expropiativa

    Objetivos 
        * Comprender y diseñar un framework para la ejecución de múltiples tareas - aunque se bloqueen
        * Entender la pila de funciones, registros, etc

    Para hacer más -> Ampliar el planificador para que si una tarea de baja prioridad se atasca, no atasque al resto.


## Práctica XX - Bootloader (como lo pone mendi, básicamente el código .s que inicializa el sistema)

    Esto se puede hacer en teoría como práctica pequeña


## Práctica XX - Energy Management

## Práctica XX - PWM/ADC/DAC


## Diseño de Interfaces con CubeFX?
## Zephyr RTOS - Introducción
## Zephyr RTOS - Multitarea, semáforos e interrupciones
## Zephyr RTOS - Device tree y drivers
## Zephyr RTOS - MCUBoot y OTA
## Técnicas de depuración SWD y USB?
## Entrada / Salida por DMA - Sonido



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





https://github.com/eclipse-paho/paho.mqtt.embedded-c




    Para zephyr:
    https://docs.zephyrproject.org/latest/develop/getting_started/index.html#getting-started

    Instalar cubeprogrammer
    (NO SUDO) https://www.st.com/content/st_com/en/stm32cubeprogrammer.html?dl=redirect#st-get-software

    Para zephyr SDK
    # 1. Download the 1.0.1 minimal tarball
    wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v1.0.1/zephyr-sdk-1.0.1_linux-x86_64_minimal.tar.xz

    # 2. Extract it into your tools folder (or where you want it)
    tar xvf zephyr-sdk-1.0.1_linux-x86_64_minimal.tar.xz

    # 3. Enter the new SDK folder
    cd zephyr-sdk-1.0.1

    # Install ONLY the arm toolchain (-t) and host tools (-c)
    > sudo apt-get install cmake
    ./setup.sh -t arm-zephyr-eabi -c

    Crear una carpeta y dentro un venv para west:
    # 1. Create and enter your fresh workspace directory
    mkdir zephyr-stm32-workspace
    cd zephyr-stm32-workspace

    # 2. Create a virtual environment named '.venv' inside this folder
    python3 -m venv .venv

    # 3. Activate the virtual environment
    source .venv/bin/activate

    # 1. Install west inside the virtual environment
    pip install west

    # 2. Initialize the workspace (using "." tells West to use the current folder)
    west init -m https://github.com/zephyrproject-rtos/zephyr .

    # 3. Apply the filter to block all other heavy vendor HALs
    west config manifest.project-filter -- "-hal_.*,+hal_stm32,+hal_nordic" (quizá con esto valga, pero si no quitar con
    west config manifest.project-filter -- "" (y ejecutar para que traiga todo, al parecer los ejemplos tienen dependencias aleatorias)

    # 4. Download only the required Zephyr + STM32 files
    west update

    > pip3 install -r scripts/requirements.txt

    # Copy the blinky sample recursively to a new folder
    cp -r zephyr/samples/basic/blinky my_blinky
    > cd my_blinky
    > west build -b stm32f412g_disco
    (otra terminal) > python3 -m serial.tools.miniterm /dev/ttyACM0 115200
    > west flash




    
    > git clone https://github.com/zephyrproject-rtos/zephyr.git
    > sudo apt-get install ninja-build
    > sudo apt install python3-pip python3-venv
    > source venv/bin/activate
	> pip3 install -r scripts/requirements.txt
	west init -l .
	west update
	west build -b stm32f412g_disco samples/hello_world