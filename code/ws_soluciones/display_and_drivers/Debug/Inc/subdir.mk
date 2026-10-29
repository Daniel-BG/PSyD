################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/ST7789h2.c \
../Inc/bsp.c \
../Inc/gfx.c 

OBJS += \
./Inc/ST7789h2.o \
./Inc/bsp.o \
./Inc/gfx.o 

C_DEPS += \
./Inc/ST7789h2.d \
./Inc/bsp.d \
./Inc/gfx.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F723E_DISCO -DSTM32 -DSTM32F723IEKx -DSTM32F7 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/ST7789h2.cyclo ./Inc/ST7789h2.d ./Inc/ST7789h2.o ./Inc/ST7789h2.su ./Inc/bsp.cyclo ./Inc/bsp.d ./Inc/bsp.o ./Inc/bsp.su ./Inc/gfx.cyclo ./Inc/gfx.d ./Inc/gfx.o ./Inc/gfx.su

.PHONY: clean-Inc

