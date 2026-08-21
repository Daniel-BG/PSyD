## Práctica XXX - Creación de BSP con CubeMX

Desde cubeMX hacer un proyecto sencillo con lo mínimo imprescindible (seleccionar por ejemplo una UART y los GPIO)
Ese proyecto se exporta, y se ve cómo importar desde CubeIDE, y cómo luego se configura un led y la UART para enviar algo





Hablar también de cómo importar el BSP (básicamente, hay que meter absolutamente todos los periféricos en cubeMX (just in case) y luego copiar los ficheros del BSP y de Utilidades dentro (quizá se puedan linkar?). Además hay que linkarlos como includes para que funcionen.

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

## Práctica XX - FreeRTOS

A Real-Time Operating System (RTOS) is used in embedded systems where tasks must happen with exact, predictable timing. Unlike a normal computer OS (like Windows or macOS) that focuses on running many programs at once even if some lag, an RTOS guarantees that high-priority jobs finish within a strict time limit. Popular options like FreeRTOS or VxWorks control critical hardware safely.Real-World UsesAutomotive: Airbag deployment systems, anti-lock brakes (ABS), and engine fuel injection. Missing a microsecond deadline here can cause a crash.Medical Devices: Pacemakers, heart monitors, and insulin pumps. They must read body signals and deliver medicine with zero delay.Aerospace & Defense: Flight control computers, radar tracking, and drone stabilization systems.Industrial Automation: Factory robot arms and assembly line cutters that must sync movements precisely to avoid breaking parts or hurting workers.Consumer Electronics: Smartwatches tracking heart rates while handling Bluetooth audio and screen touches simultaneously without freezing.Core Benefits

## Planificación pines y eso con CubeMX?

## Hacer interfaces y eso con CubeFX?

## Práctica 10 - Zephyr RTOS - Introducción
    
    https://docs.zephyrproject.org/latest/develop/tools/stm32cubeide.html

## Práctica 11 - Zephyr RTOS - Multitarea, semáforos e interrupciones

## Práctica 12 - Zephyr RTOS - Device tree y drivers

## Práctica 13 - Zephyr RTOS - MCUBoot y OTA

## Práctica 14 - 

## Práctica 4 - Técnicas de depuración SWD y USB?

## Práctica 6 - Entrada / Salida por DMA - Sonido



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





Código para otras cosas

#define SYSTICK_BASE      (0xE000E010UL)

typedef struct {
    __IO uint32_t CTRL;     // 0x00
    __IO uint32_t LOAD;     // 0x04
    __IO uint32_t VAL;      // 0x08
    __IO uint32_t CALIB;    // 0x0C
} SysTick_TypeDef;

#define SysTick           ((SysTick_TypeDef *) SYSTICK_BASE)

void SysTick_Handler(void)
{
    msTicks++;
}

void SysTick_Init(void)
{
    // Default HSI clock is 16MHz on reset. 1ms tick = 16,000 cycles.
    SysTick->LOAD = (16000U - 1U);
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | (1U << 0); // Processor Clock, Int Enable, Enable
}

void SysTick_Disable(void)
{
	SysTick->LOAD = 0U;
	SysTick->VAL  = 0U;
	SysTick->CTRL = 0U;
}

uint32_t GetTick(void)
{
    return msTicks;
}

void Delay_ms(uint32_t ms)
{
    uint32_t start = GetTick();
    while ((GetTick() - start) < ms);
}