################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/internal/subdir.mk
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
all: e18_dct.elf secondary-outputs

dependents:
	-cd C:/Users/kmwh/e18new2890/e18_resources/Release && $(MAKE) all

# Tool invocations
e18_dct.elf: $(OBJS) $(USER_OBJS) C:/Users/kmwh/e18new2890/e18_resources/Release/libe18_resources.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wall  -g -T "C:/Users/kmwh/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/GCC/cy8c6x7/dct.ld" -nostartfiles -LC:/Users/kmwh/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/lib -LC:/Users/kmwh/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/GCC/cy8c6x7 -Wl,-Map,"e18_dct.map" -Wno-strict-aliasing -Xlinker --gc-sections -std=gnu11 -Wl,-A,thumb -o "e18_dct.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) e18_dct.elf
	-@echo ' '

post-build:
	-C:/Users/kmwh/ModusToolbox_1.0/tools/modus-shell-1.0/bin/bash --norc C:/Users/kmwh/ModusToolbox_1.0/tools/wiced-scripts-1.0/process_elf.bash C:/Users/kmwh/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/bin C:\Users\kmwh\e18new2890\e18_dct/Release C:\Users\kmwh\e18new2890\e18_dct/Release/e18_dct.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents post-build
C:/Users/kmwh/e18new2890/e18_resources/Release/libe18_resources.a:

-include ../makefile.targets
