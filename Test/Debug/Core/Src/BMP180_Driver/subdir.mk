################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BMP180_Driver/bmp180driver.c 

OBJS += \
./Core/Src/BMP180_Driver/bmp180driver.o 

C_DEPS += \
./Core/Src/BMP180_Driver/bmp180driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/BMP180_Driver/bmp180driver.o: ../Core/Src/BMP180_Driver/bmp180driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/BMP180_Driver/bmp180driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

