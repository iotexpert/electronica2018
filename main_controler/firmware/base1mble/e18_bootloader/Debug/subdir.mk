################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cycfg_init.c 

OBJS += \
./cycfg_init.o 

C_DEPS += \
./cycfg_init.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wall  -g3 -DCY8C6247BZI_D54 -DWICED_DISABLE_MCU_POWERSAVE -DHSE_VALUE=26000000 -DBUS='"SDIO"' -DBOOTLOADER_MAGIC_NUMBER=0x4d435242 -DSFLASH_APPS_HEADER_LOC=0x0000 -Dwifi_firmware_image=resources_firmware_DIR_4343W_DIR_4343WA1_bin -Dwifi_firmware_clm_blob=resources_firmware_DIR_4343W_DIR_4343WA1_clm_blob -DWWD_STARTUP_DELAY=10 -DWWD_BUS_SDIO_AFTER_RESET_DELAY=1000 -DMAX_WATCHDOG_TIMEOUT_SECONDS=2.5 -DDEFAULT_SYSTEM_MONITOR_PERIOD=2500 -DPLATFORM='"CY8CKIT_062"' -DAPPS_CHIP_REVISION='""' -DPLATFORM_POWER_DOWN_THREAD_PREEMPTION_ALLOWED -DWICED -DWLAN_CHIP_FAMILY=4343W -DWLAN_CHIP=4343W -DCRLF_STDIO_REPLACEMENT -DWICED_NO_WIFI -DPLATFORM_NO_GMAC=1 -DNETWORK_NoNS=1 -DWICED_DISABLE_WATCHDOG -DRTOS_NoOS=1 -DNO_WIFI_FIRMWARE -DBOOTLOADER -DNO_WICED_API -DDCT_CRC32_CALCULATION_SIZE_ON_STACK=1024 -DWICED_DCACHE_WTHROUGH -DWICED_DISABLE_STDIO -DBCMM2MDEV_ENABLED -DNoOS_FIQ_STACK=0 -DNoOS_IRQ_STACK=256 -DNoOS_SYS_STACK=0 -DWWD_DOWNLOAD_CLM_BLOB -DUSING_WICEDFS -DWWD_DIRECT_RESOURCES -DUDB_SDIO -DMODUSTOOLBOX=1 -DBCM_WICED -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_bootloader" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_config" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_dct" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_resources" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/internal" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/NoOS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/NoOS/WWD" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/host/WICED" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/mbedtls_open/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/crypto_internal" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/NoOS/WWD/Cortex_M3_M4" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wifi" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/RTOS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/WPS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/network" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/GCC" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/ARM_CM4" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols" -I"/Applications/ModusToolbox_1.0/libraries/wiced_electronica18-1.0/components/WIFI-SDK/WICED/WWD/internal/chips/4343x" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/PostgreSQL/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/base64" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/crc" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/mini_printf" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/ring_buffer" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/TLV" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wiced_log" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/bufmgr" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs/button_manager" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs/gpio_button" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/init" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/CapSense" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries/creator" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries/sdio" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/spi_flash" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WAF" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WWD" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NoNS/WWD" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/bootloader" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs" -I"/Applications/ModusToolbox_1.0/libraries/wiced_electronica18-1.0/components/WIFI-SDK/platforms/CY8CKIT_062_IFLASH" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/chips/4343x" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols/SDIO" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NoNS" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_config/GeneratedSource" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6mw/capsense" -std=gnu11 -g3 -fomit-frame-pointer -Wno-strict-aliasing -std=gnu11 -std=gnu11 -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/include" -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include" -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include-fixed" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


