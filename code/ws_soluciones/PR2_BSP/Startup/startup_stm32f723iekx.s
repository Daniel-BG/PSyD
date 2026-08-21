.syntax unified
.cpu cortex-m4
.thumb

.global g_pfnVectors
.global Reset_Handler

/* 1. THE MINIMAL VECTOR TABLE */
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object

g_pfnVectors:
  .word _estack        /* Vector 0: Top of Stack (Defined in Linker Script) */
  .word Reset_Handler  /* Vector 1: Reset Handler (Where CPU starts executing) */

.size g_pfnVectors, .-g_pfnVectors

/* 2. THE MINIMAL RESET HANDLER */
.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* Set the stack pointer manually */

  b     main            /* Branch straight to your main() function in C */

.size Reset_Handler, .-Reset_Handler
