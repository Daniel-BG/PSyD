################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/bsp.c \
../Inc/heap_4.c \
../Inc/list.c \
../Inc/port.c \
../Inc/queue.c \
../Inc/tasks.c \
../Inc/timers.c 

OBJS += \
./Inc/bsp.o \
./Inc/heap_4.o \
./Inc/list.o \
./Inc/port.o \
./Inc/queue.o \
./Inc/tasks.o \
./Inc/timers.o 

C_DEPS += \
./Inc/bsp.d \
./Inc/heap_4.d \
./Inc/list.d \
./Inc/port.d \
./Inc/queue.d \
./Inc/tasks.d \
./Inc/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F723E_DISCO -DSTM32 -DSTM32F723IEKx -DSTM32F7 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/bsp.cyclo ./Inc/bsp.d ./Inc/bsp.o ./Inc/bsp.su ./Inc/heap_4.cyclo ./Inc/heap_4.d ./Inc/heap_4.o ./Inc/heap_4.su ./Inc/list.cyclo ./Inc/list.d ./Inc/list.o ./Inc/list.su ./Inc/port.cyclo ./Inc/port.d ./Inc/port.o ./Inc/port.su ./Inc/queue.cyclo ./Inc/queue.d ./Inc/queue.o ./Inc/queue.su ./Inc/tasks.cyclo ./Inc/tasks.d ./Inc/tasks.o ./Inc/tasks.su ./Inc/timers.cyclo ./Inc/timers.d ./Inc/timers.o ./Inc/timers.su

.PHONY: clean-Inc

