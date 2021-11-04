################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/USART/USART.c 

OBJS += \
./MCAL/USART/USART.o 

C_DEPS += \
./MCAL/USART/USART.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/USART/USART.o: ../MCAL/USART/USART.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/STM32CubeIDE WorkSpace/workspace/STM32F103xx_Drivers/HAL/includes" -I"D:/STM32CubeIDE WorkSpace/workspace/STM32F103xx_Drivers/MCAL/inc" -I../Inc -I"D:/STM32CubeIDE WorkSpace/workspace/STM32F103xx_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/USART/USART.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

