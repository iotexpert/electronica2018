################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.S 

OBJS += \
./psoc6sw-1.0/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.o 

S_UPPER_DEPS += \
./psoc6sw-1.0/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.d 


# Each subdirectory must supply rules for building sources it contributes
psoc6sw-1.0/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.o: C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -x assembler-with-cpp -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

