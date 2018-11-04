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
-include Remote_config/GeneratedSource/subdir.mk
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
all: Remote_mainapp_cm0p.elf secondary-outputs

dependents:
	-cd C:/Git/electronica2018/remote_control/firmware/Remote/Remote_mainapp_cm0p_psoc6pdl/Debug && $(MAKE) clean all

# Tool invocations
Remote_mainapp_cm0p.elf: $(OBJS) $(USER_OBJS) C:/Git/electronica2018/remote_control/firmware/Remote/Remote_mainapp_cm0p_psoc6pdl/Debug/libRemote_mainapp_cm0p_psoc6pdl.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -Wall  -g3 -T "C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/linker/gcc/wiced_cm0plus.ld" -Xlinker --gc-sections -Wl,-Map,"Remote_mainapp_cm0p.map" --specs=nano.specs -ffat-lto-objects -g --enable-objc-gc -o "Remote_mainapp_cm0p.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Remote_mainapp_cm0p.elf
	-@echo ' '

post-build:
	-C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/modus-shell-1.0/bin/bash --norc C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/wiced-scripts-1.0/process_app.bash C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/modus-shell-1.0 C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/bin C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/wiced-scripts-1.0 C:\Git\electronica2018\remote_control\firmware\Remote\Remote_mainapp_cm0p/Debug C:\Git\electronica2018\remote_control\firmware\Remote\Remote_mainapp_cm0p/Debug/Remote_mainapp_cm0p.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents post-build
C:/Git/electronica2018/remote_control/firmware/Remote/Remote_mainapp_cm0p_psoc6pdl/Debug/libRemote_mainapp_cm0p_psoc6pdl.a:

-include ../makefile.targets
