################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wiced_electronica18-1.0/components/WIFI-SDK/platforms/CY8CKIT_062_IFLASH/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wifi/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wiced_log/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/ring_buffer/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/mini_printf/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/crc/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/bufmgr/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/base64/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/utilities/TLV/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/inputs/gpio_button/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/inputs/button_manager/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/daemons/DHCP_server/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/spi_flash/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries/sdio/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WWD/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WAF/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/GCC/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/platform/ARM_CM4/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/internal/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/chips/4343x/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols/SDIO/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/WWD/CM3_CM4/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/WWD/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/WICED/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/subdir.mk
-include psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/subdir.mk
-include psoc6sw-1.0/components/psoc6mw/capsense/subdir.mk
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
all: e18_mainapp.elf secondary-outputs

dependents:
	-cd C:/Users/kmwh/e18new2890/e18_resources/Debug && $(MAKE) all
	-cd C:/Users/kmwh/e18new2890/e18_bootloader/Debug && $(MAKE) all
	-cd C:/Users/kmwh/e18new2890/e18_dct/Debug && $(MAKE) all
	-cd C:/Users/kmwh/e18new2890/e18_mainapp_cm0p/Debug && $(MAKE) all
	-cd C:/Users/kmwh/e18new2890/e18_mainapp_psoc6pdl/Debug && $(MAKE) all
	-cd C:/Users/kmwh/e18new2890/e18_mainapp_PROTOCOLS/Debug && $(MAKE) all
	-cd C:/Users/kmwh/e18new2890/e18_mainapp_BESLMBEDTLS/Debug && $(MAKE) all
	-cd C:/Users/kmwh/e18new2890/e18_mainapp_NETXDuoLib/Debug && $(MAKE) all

# Tool invocations
e18_mainapp.elf: $(OBJS) $(USER_OBJS) C:/Users/kmwh/e18new2890/e18_resources/Debug/libe18_resources.a C:/Users/kmwh/e18new2890/e18_bootloader/Debug/e18_bootloader.elf C:/Users/kmwh/e18new2890/e18_dct/Debug/e18_dct.elf C:/Users/kmwh/e18new2890/e18_mainapp_cm0p/Debug/e18_mainapp_cm0p.elf C:/Users/kmwh/e18new2890/e18_mainapp_psoc6pdl/Debug/libe18_mainapp_psoc6pdl.a C:/Users/kmwh/e18new2890/e18_mainapp_PROTOCOLS/Debug/libe18_mainapp_PROTOCOLS.a C:/Users/kmwh/e18new2890/e18_mainapp_BESLMBEDTLS/Debug/libe18_mainapp_BESLMBEDTLS.a C:/Users/kmwh/e18new2890/e18_mainapp_NETXDuoLib/Debug/libe18_mainapp_NETXDuoLib.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wall  -g3 -T "C:/Users/kmwh/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/GCC/app_with_bootloader.ld" -nostartfiles -LC:/Users/kmwh/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/lib -LC:/Users/kmwh/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/GCC -LC:/Users/kmwh/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/GCC/cy8c6x7 -Wl,-Map,"e18_mainapp.map" -Wno-strict-aliasing -Xlinker --gc-sections -std=gnu11 -Wl,-A,thumb -Wl,--defsym,__STACKSIZE__=8000 -Wl,--defsym,FIQ_STACK_SIZE=0 -Wl,--defsym,IRQ_STACK_SIZE=1024 -Wl,--defsym,SYS_STACK_SIZE=0 -o "e18_mainapp.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) e18_mainapp.elf
	-@echo ' '

post-build:
	-C:/Users/kmwh/ModusToolbox_1.0/tools/modus-shell-1.0/bin/bash --norc C:/Users/kmwh/ModusToolbox_1.0/tools/wiced-scripts-1.0/process_app.bash C:/Users/kmwh/ModusToolbox_1.0/tools/modus-shell-1.0 C:/Users/kmwh/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/bin C:/Users/kmwh/ModusToolbox_1.0/tools/wiced-scripts-1.0 C:\Users\kmwh\e18new2890\e18_mainapp/Debug C:\Users\kmwh\e18new2890\e18_mainapp/Debug/e18_mainapp.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents post-build
C:/Users/kmwh/e18new2890/e18_resources/Debug/libe18_resources.a:
C:/Users/kmwh/e18new2890/e18_bootloader/Debug/e18_bootloader.elf:
C:/Users/kmwh/e18new2890/e18_dct/Debug/e18_dct.elf:
C:/Users/kmwh/e18new2890/e18_mainapp_cm0p/Debug/e18_mainapp_cm0p.elf:
C:/Users/kmwh/e18new2890/e18_mainapp_psoc6pdl/Debug/libe18_mainapp_psoc6pdl.a:
C:/Users/kmwh/e18new2890/e18_mainapp_PROTOCOLS/Debug/libe18_mainapp_PROTOCOLS.a:
C:/Users/kmwh/e18new2890/e18_mainapp_BESLMBEDTLS/Debug/libe18_mainapp_BESLMBEDTLS.a:
C:/Users/kmwh/e18new2890/e18_mainapp_NETXDuoLib/Debug/libe18_mainapp_NETXDuoLib.a:

-include ../makefile.targets
