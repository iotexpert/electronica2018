################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg.c \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_capsense.c \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_clocks.c \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_connectivity.c \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_dmas.c \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_peripherals.c \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_pins.c \
C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_platform.c 

OBJS += \
./Remote_config/GeneratedSource/cycfg.o \
./Remote_config/GeneratedSource/cycfg_capsense.o \
./Remote_config/GeneratedSource/cycfg_clocks.o \
./Remote_config/GeneratedSource/cycfg_connectivity.o \
./Remote_config/GeneratedSource/cycfg_dmas.o \
./Remote_config/GeneratedSource/cycfg_peripherals.o \
./Remote_config/GeneratedSource/cycfg_pins.o \
./Remote_config/GeneratedSource/cycfg_platform.o 

C_DEPS += \
./Remote_config/GeneratedSource/cycfg.d \
./Remote_config/GeneratedSource/cycfg_capsense.d \
./Remote_config/GeneratedSource/cycfg_clocks.d \
./Remote_config/GeneratedSource/cycfg_connectivity.d \
./Remote_config/GeneratedSource/cycfg_dmas.d \
./Remote_config/GeneratedSource/cycfg_peripherals.d \
./Remote_config/GeneratedSource/cycfg_pins.d \
./Remote_config/GeneratedSource/cycfg_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Remote_config/GeneratedSource/cycfg.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Remote_config/GeneratedSource/cycfg_capsense.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_capsense.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Remote_config/GeneratedSource/cycfg_clocks.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_clocks.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Remote_config/GeneratedSource/cycfg_connectivity.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_connectivity.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Remote_config/GeneratedSource/cycfg_dmas.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_dmas.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Remote_config/GeneratedSource/cycfg_peripherals.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_peripherals.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Remote_config/GeneratedSource/cycfg_pins.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_pins.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Remote_config/GeneratedSource/cycfg_platform.o: C:/Users/gjl.CYSEMI/mtw/Remote/Remote_config/GeneratedSource/cycfg_platform.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -DCY8C6247BZI_D54 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"C:\Users\gjl.CYSEMI\mtw\Remote\Remote_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


