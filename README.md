# 📟 PSyD 📟

Bienvenido al sitio web del material de la asignatura de Programación de Sistemas y Dispositivos, del grado en Ingeniería de Computadores en la UCM. Desde aquí puedes acceder a todos los recursos.

## 📖 [Teoría](teoria/main.pdf)
* 📄 [1 - Del alto nivel a la memoria física](teoria/c_to_physical/c_to_physical.pdf)
* 📄 [2 - Estructuras y definiciones hardware](teoria/hardware_structs/hardware_structs.pdf)
* 📄 [3 - Enlazado e inicialización](teoria/linking/linking.pdf)
* 📄 [4 - Interrupciones, barreras y callbacks](teoria/interrupts/interrupts.pdf)
* 📄 [5 - Periféricos](teoria/peripherals/peripherals.pdf)
* 📄 [6 - Temporización](teoria/timing/timing.pdf)
* 📄 [7 - Buses externos](teoria/external_peripherals_buses/external_peripherals_buses.pdf)

## 🛠️ [Prácticas](practicas/main.pdf)
* 📁 [Punto de entrada a las prácticas](practicas/practicas.md)
* 📁 [Enunciado de la Práctica  0 - Configuración Inicial](practicas/initial_config/initial_config.pdf)
* 📁 [Enunciado de la Práctica  1 - Memory Mapped IO](practicas/memory_mapped_io/memory_mapped_io.pdf)
* 📁 [Enunciado de la Práctica  2 - Board Support Package](practicas/board_support_package/board_support_package.pdf)
* 📁 [Enunciado de la Práctica  3 - E/S Programada](practicas/programmed_input_output/programmed_input_output.pdf)
* 📁 [Enunciado de la Práctica  4 - Interrupciones](practicas/interrupts/interrupts.pdf)
* 📁 [Enunciado de la Práctica  5 - Timers](practicas/timers/timers.pdf)
* 📁 [Enunciado de la Práctica  6 - Systick](practicas/systick/systick.pdf)
* 📁 [Enunciado de la Práctica  7 - Display y drivers](practicas/display_and_drivers/display_and_drivers.pdf)
* 📁 [Enunciado de la Práctica  8 - I2C y panel táctil](practicas/i2c_and_touch/i2c_and_touch.pdf)
* 📁 [Enunciado de la Práctica  9 - Persistencia](practicas/persistence/persistence.pdf)
* 📁 [Enunciado de la Práctica 10 - Multitarea cooperativa](practicas/cooperative_multitasking/cooperative_multitasking.pdf)
* 📁 [Enunciado de la Práctica 11 - Integración de RTOS](practicas/rtos_integration/rtos_integration.pdf)
* 📁 [Enunciado de la Práctica 12 - Thingsboard - Control](practicas/thingsboard_data_control/thingsboard_data_control.pdf)
* 📁 [Enunciado de la Práctica 13 - Thingsboard - OTA](practicas/thingsboard_ota/thingsboard_ota.pdf)
* 📁 [Enunciado de la Práctica 14 - BSP automatizado con cubeMX](practicas/automated_bsp_cubemx/automated_bsp_cubemx.pdf)
* 🏁 [Proyecto final - práctica libre](practicas/final_project/final_project.pdf)

## 📝 Colección de preguntas de examen
* ❓ [Sólo enunciados](examenes/main_preguntas.pdf)
* 💯 [Con soluciones](examenes/main_soluciones.pdf)

## 🔄 Actualizando el repositorio

Es posible que el repositorio cambie con correcciones o adiciones a lo largo del curso. Si ves que ha cambiado (o tu profesor te avisa), ejecuta los siguientes comandos para no perder el trabajo realizado que tú hayas hecho localmente.

```bash
git add .
git commit -m "Checkpoint before pull"
git pull
```

Con esto crearás un punto de referencia local (commit) al que poder volver si las cosas van mal. Tras ello, con pull, descargarás los nuevos cambios.

---

### ⚠️ ¿Y si hay un conflicto de Merge?

Si has modificado un fichero en la misma línea que se ha modificado en el repositorio, Git te dirá que resuelvas un **conflicto de merge**. 

1. Abre el fichero afectado y busca los marcadores de conflicto:
   ```c
   <<<<<<< HEAD (Your Code)
   //aquí estará tu código
   =======
   //aquí estará el código del repositorio que entra en conflicto
   >>>>>>> [commit-hash]
   ```
2. Borra las líneas de conflicto (`<<<<<<<`, `=======`, `>>>>>>>`) y quédate con el código correcto.
3. Puedes a continuación marcar el conflicto como resuelto en un nuevo commit.
   ```bash
   git add .
   git commit -m "Resolved merge conflict"
   ```