################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0/main.c 

OBJS += \
./wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0/main.o 

C_DEPS += \
./wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0/main.d 


# Each subdirectory must supply rules for building sources it contributes
wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0/%.o: ../wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C6247BZI_D54 -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\kmwh\e18new2890\e18_config" -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\kmwh\e18new2890\e18_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


