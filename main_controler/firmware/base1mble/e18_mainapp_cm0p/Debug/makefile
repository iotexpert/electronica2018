################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wiced_base-1.0/components/WIFI-SDK/apps/waf/cm0/subdir.mk
-include psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/gcc/subdir.mk
-include psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/subdir.mk
-include e18_config/GeneratedSource/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: e18_mainapp_cm0p.elf secondary-outputs

dependents:
	-cd /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_mainapp_cm0p_psoc6pdl/Debug && $(MAKE) clean all

# Tool invocations
e18_mainapp_cm0p.elf: $(OBJS) $(USER_OBJS) /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_mainapp_cm0p_psoc6pdl/Debug/libe18_mainapp_cm0p_psoc6pdl.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -T "/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/linker/gcc/wiced_cm0plus.ld" -Xlinker --gc-sections -Wl,-Map,"e18_mainapp_cm0p.map" --specs=nano.specs -ffat-lto-objects -g --enable-objc-gc -o "e18_mainapp_cm0p.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) e18_mainapp_cm0p.elf
	-@echo ' '

post-build:
	-/Applications/ModusToolbox_1.0/tools/modus-shell-1.0/bin/bash --norc /Applications/ModusToolbox_1.0/tools/wiced-scripts-1.0/process_app.bash /Applications/ModusToolbox_1.0/tools/modus-shell-1.0 /Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/bin /Applications/ModusToolbox_1.0/tools/wiced-scripts-1.0 /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_mainapp_cm0p/Debug /Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_mainapp_cm0p/Debug/e18_mainapp_cm0p.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents post-build
/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_mainapp_cm0p_psoc6pdl/Debug/libe18_mainapp_cm0p_psoc6pdl.a:

-include ../makefile.targets
