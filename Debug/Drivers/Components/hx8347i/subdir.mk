################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/hx8347i/hx8347i.c 

C_DEPS += \
./Drivers/Components/hx8347i/hx8347i.d 

OBJS += \
./Drivers/Components/hx8347i/hx8347i.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/hx8347i/%.o Drivers/Components/hx8347i/%.su Drivers/Components/hx8347i/%.cyclo: ../Drivers/Components/hx8347i/%.c Drivers/Components/hx8347i/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"/home/junseokshim/STM32CubeIDE/workspace_1.17.0/FreeRTOS/Drivers/BSP" -I"/home/junseokshim/STM32CubeIDE/workspace_1.17.0/FreeRTOS/Drivers/BSP/B-L475E-IOT01" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-hx8347i

clean-Drivers-2f-Components-2f-hx8347i:
	-$(RM) ./Drivers/Components/hx8347i/hx8347i.cyclo ./Drivers/Components/hx8347i/hx8347i.d ./Drivers/Components/hx8347i/hx8347i.o ./Drivers/Components/hx8347i/hx8347i.su

.PHONY: clean-Drivers-2f-Components-2f-hx8347i

