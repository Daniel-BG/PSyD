################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/ESP01S.c \
../Inc/MQTTConnectClient.c \
../Inc/MQTTDeserializePublish.c \
../Inc/MQTTFormat.c \
../Inc/MQTTPacket.c \
../Inc/MQTTSerializePublish.c \
../Inc/MQTTSubscribeClient.c \
../Inc/RingBuffer.c \
../Inc/bsp.c \
../Inc/ota.c 

OBJS += \
./Inc/ESP01S.o \
./Inc/MQTTConnectClient.o \
./Inc/MQTTDeserializePublish.o \
./Inc/MQTTFormat.o \
./Inc/MQTTPacket.o \
./Inc/MQTTSerializePublish.o \
./Inc/MQTTSubscribeClient.o \
./Inc/RingBuffer.o \
./Inc/bsp.o \
./Inc/ota.o 

C_DEPS += \
./Inc/ESP01S.d \
./Inc/MQTTConnectClient.d \
./Inc/MQTTDeserializePublish.d \
./Inc/MQTTFormat.d \
./Inc/MQTTPacket.d \
./Inc/MQTTSerializePublish.d \
./Inc/MQTTSubscribeClient.d \
./Inc/RingBuffer.d \
./Inc/bsp.d \
./Inc/ota.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F723E_DISCO -DSTM32 -DSTM32F723IEKx -DSTM32F7 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/ESP01S.cyclo ./Inc/ESP01S.d ./Inc/ESP01S.o ./Inc/ESP01S.su ./Inc/MQTTConnectClient.cyclo ./Inc/MQTTConnectClient.d ./Inc/MQTTConnectClient.o ./Inc/MQTTConnectClient.su ./Inc/MQTTDeserializePublish.cyclo ./Inc/MQTTDeserializePublish.d ./Inc/MQTTDeserializePublish.o ./Inc/MQTTDeserializePublish.su ./Inc/MQTTFormat.cyclo ./Inc/MQTTFormat.d ./Inc/MQTTFormat.o ./Inc/MQTTFormat.su ./Inc/MQTTPacket.cyclo ./Inc/MQTTPacket.d ./Inc/MQTTPacket.o ./Inc/MQTTPacket.su ./Inc/MQTTSerializePublish.cyclo ./Inc/MQTTSerializePublish.d ./Inc/MQTTSerializePublish.o ./Inc/MQTTSerializePublish.su ./Inc/MQTTSubscribeClient.cyclo ./Inc/MQTTSubscribeClient.d ./Inc/MQTTSubscribeClient.o ./Inc/MQTTSubscribeClient.su ./Inc/RingBuffer.cyclo ./Inc/RingBuffer.d ./Inc/RingBuffer.o ./Inc/RingBuffer.su ./Inc/bsp.cyclo ./Inc/bsp.d ./Inc/bsp.o ./Inc/bsp.su ./Inc/ota.cyclo ./Inc/ota.d ./Inc/ota.o ./Inc/ota.su

.PHONY: clean-Inc

