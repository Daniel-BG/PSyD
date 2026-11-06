#include <stdint.h>
#include <bsp.h>

/* ========================================================================== */
/* Cooperative Scheduler Infrastructure                                       */
/* ========================================================================== */

#define MAX_TASKS 10

// Task structure defining what a task is
typedef struct {
    void (*task_function)(void); // Pointer to the task function
    uint32_t period_ms;          // How often the task should execute (in ms)
    uint32_t last_run;           // The sys_ticks timestamp when it last executed
    uint8_t ready;				 // True if the task should run
} Task_TypeDef;

// Tasks in our program
static Task_TypeDef tasks[MAX_TASKS] = {0};

// 1. Task Implementations (The cooperative tasks)
void Task_BlinkGreen(void) {
	GPIO_PIN_TOGGLE(GPIOB, 1);
}

void Task_BlinkBlue(void) {
	GPIO_PIN_TOGGLE(GPIOA, 5);
}

void Task_BlinkRed(void) {
	GPIO_PIN_TOGGLE(GPIOA, 7);
}

uint32_t create_task( void (*pfunction)(void), uint32_t period ) {
	uint32_t id;

	//... completar buscar una entrada libre en la tabla de tareasa
	//... completar iniicializar los campos de tarea

	return id;
}

void delete_task (uint32_t id ) {
    // ... completar inicializar la estructura a 0
    // ... para luego poder identificar si hay o no tareas
    // ... o si están o no listas
}

void scheduler_init (void) {
    // ... ejecuta delete_task para todas las tareas, a fin
    // ... de reiniciarlas
}

void scheduler (void) {
	// ... completar mirar el momento de tiempo actual (GetTick())
	// ... recorrer la lista de tareas,
	// ... si la trea existe, ver si le toca ya (en función
	// ... del tiempo) ejecutarse, y en ese caso marcar como
	// ... ready y ajustar valores para que no se dispare de nuevo
	// ... hasta que le vuelva a tocar
}

void dispacher (void) {
	// ... completar recorrer la lista de tareas
	// ... completar si la tarea está lista, ejecutar su función
	// y marcar como no lista
}
/* ========================================================================== */
/* Hardware Initialization                                                    */
/* ========================================================================== */

void GPIO_Init(void) {
	// 1. Enable AHB1 peripheral clocks for GPIOA and GPIOB
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	RCC_AHB1ENR->bits.GPIOBEN = 1;

	// 2. Configure PA7 (Red LED) and PA5 (Blue LED) and PB1 (Green LED) as General Purpose Outputs
	GPIO_CONFIG(GPIOA, 5, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);
	GPIO_CONFIG(GPIOA, 7, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);
	GPIO_CONFIG(GPIOB, 1, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);
}


/* ========================================================================== */
/* Main Loop & Dispatcher                                                    */
/* ========================================================================== */

void SysTick_UserCallback() {
	scheduler();
}

int main(void) {
	SysTick_Init();
    GPIO_Init();
    scheduler_init();

    create_task(Task_BlinkBlue, 250);
    create_task(Task_BlinkGreen, 500);
    create_task(Task_BlinkRed, 1000);

    // Scheduler
    while (1) {
        // Low-power sleep: Wait for the next SysTick interrupt before executing the scheduler loop again
        __asm volatile ("wfi");
        dispacher();
    }

    return 0;
}
