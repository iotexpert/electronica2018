################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg.c \
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_capsense.c \
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_clocks.c \
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_connectivity.c \
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_peripherals.c \
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_pins.c \
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_platform.c 

OBJS += \
./e18MainController_config/GeneratedSource/cycfg.o \
./e18MainController_config/GeneratedSource/cycfg_capsense.o \
./e18MainController_config/GeneratedSource/cycfg_clocks.o \
./e18MainController_config/GeneratedSource/cycfg_connectivity.o \
./e18MainController_config/GeneratedSource/cycfg_peripherals.o \
./e18MainController_config/GeneratedSource/cycfg_pins.o \
./e18MainController_config/GeneratedSource/cycfg_platform.o 

C_DEPS += \
./e18MainController_config/GeneratedSource/cycfg.d \
./e18MainController_config/GeneratedSource/cycfg_capsense.d \
./e18MainController_config/GeneratedSource/cycfg_clocks.d \
./e18MainController_config/GeneratedSource/cycfg_connectivity.d \
./e18MainController_config/GeneratedSource/cycfg_peripherals.d \
./e18MainController_config/GeneratedSource/cycfg_pins.d \
./e18MainController_config/GeneratedSource/cycfg_platform.d 


# Each subdirectory must supply rules for building sources it contributes
e18MainController_config/GeneratedSource/cycfg.o: /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C624ABZI_D44 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

e18MainController_config/GeneratedSource/cycfg_capsense.o: /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_capsense.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C624ABZI_D44 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

e18MainController_config/GeneratedSource/cycfg_clocks.o: /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_clocks.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C624ABZI_D44 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

e18MainController_config/GeneratedSource/cycfg_connectivity.o: /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_connectivity.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C624ABZI_D44 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

e18MainController_config/GeneratedSource/cycfg_peripherals.o: /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_peripherals.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C624ABZI_D44 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

e18MainController_config/GeneratedSource/cycfg_pins.o: /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_pins.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C624ABZI_D44 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

e18MainController_config/GeneratedSource/cycfg_platform.o: /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource/cycfg_platform.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g -DCY8C624ABZI_D44 -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_low" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm0p_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18MainController_config/GeneratedSource" -std=gnu11 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


