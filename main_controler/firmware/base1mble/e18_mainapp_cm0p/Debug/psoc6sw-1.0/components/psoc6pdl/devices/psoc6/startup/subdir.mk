################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/system_psoc6_cm0plus.c 

OBJS += \
./psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/system_psoc6_cm0plus.o 

C_DEPS += \
./psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/system_psoc6_cm0plus.d 


# Each subdirectory must supply rules for building sources it contributes
psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/%.o: ../psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


