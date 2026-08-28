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
	// search for first free entry
	for (id = 0; id < MAX_TASKS && tasks[id].task_function; id++);

	tasks[id].task_function = pfunction;
	tasks[id].period_ms = period;
	tasks[id].last_run = GetTick();
	tasks[id].ready = 0;

	return id;
}

void delete_task (uint32_t id ) {
	tasks[id].task_function = 0;
	tasks[id].period_ms = 0;
	tasks[id].last_run = 0;
	tasks[id].ready = 0;
}

void scheduler_init (void) {
	uint32_t id;
	for( id=0; id<MAX_TASKS; id++ )
		delete_task( id );
}

void scheduler (void) {
	uint32_t tick = GetTick();
	for (uint32_t id = 0; id < MAX_TASKS; id++)
		if (tasks[id].task_function) //if there is a task here
			if (tasks[id].last_run + tasks[id].period_ms <= tick) {
				tasks[id].last_run = tick;
				tasks[id].ready = 1;
			}
}

void dispacher (void) {
	uint32_t id;
	for (id = 0; id < MAX_TASKS; id++)
		if (tasks[id].ready) {
			(*tasks[id].task_function)();
			tasks[id].ready = 0;
		}
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
