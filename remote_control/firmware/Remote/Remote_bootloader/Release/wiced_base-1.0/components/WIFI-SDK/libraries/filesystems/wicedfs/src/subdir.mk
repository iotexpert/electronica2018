################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src/wicedfs.c 

OBJS += \
./wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src/wicedfs.o 

C_DEPS += \
./wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src/wicedfs.d 


# Each subdirectory must supply rules for building sources it contributes
wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src/wicedfs.o: C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src/wicedfs.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wall  -g -DCY8C6247BZI_D54 -DWICED_DISABLE_MCU_POWERSAVE -DHSE_VALUE=26000000 -DBUS='"SDIO"' -DBOOTLOADER_MAGIC_NUMBER=0x4d435242 -DSFLASH_APPS_HEADER_LOC=0x0000 -Dwifi_firmware_image=resources_firmware_DIR_4343W_DIR_4343WA1_bin -Dwifi_firmware_clm_blob=resources_firmware_DIR_4343W_DIR_4343WA1_clm_blob -DWWD_STARTUP_DELAY=10 -DWWD_BUS_SDIO_AFTER_RESET_DELAY=1000 -DMAX_WATCHDOG_TIMEOUT_SECONDS=2.5 -DDEFAULT_SYSTEM_MONITOR_PERIOD=2500 -DPLATFORM='"CY8CKIT_062"' -DAPPS_CHIP_REVISION='""' -DPLATFORM_POWER_DOWN_THREAD_PREEMPTION_ALLOWED -DWICED -DWLAN_CHIP_FAMILY=4343W -DWLAN_CHIP=4343W -DCRLF_STDIO_REPLACEMENT -DWICED_NO_WIFI -DPLATFORM_NO_GMAC=1 -DNETWORK_NoNS=1 -DWICED_DISABLE_WATCHDOG -DRTOS_NoOS=1 -DNO_WIFI_FIRMWARE -DBOOTLOADER -DNO_WICED_API -DDCT_CRC32_CALCULATION_SIZE_ON_STACK=1024 -DWICED_DCACHE_WTHROUGH -DWICED_DISABLE_STDIO -DBCMM2MDEV_ENABLED -DNoOS_FIQ_STACK=0 -DNoOS_IRQ_STACK=256 -DNoOS_SYS_STACK=0 -DWWD_DOWNLOAD_CLM_BLOB -DUSING_WICEDFS -DWWD_DIRECT_RESOURCES -DUDB_SDIO -DMODUSTOOLBOX=1 -DBCM_WICED -I"C:\Git\electronica2018\remote_control\firmware\Remote\Remote_bootloader" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6mw/capsense" -I"C:\Git\electronica2018\remote_control\firmware\Remote\Remote_config" -I"C:\Git\electronica2018\remote_control\firmware\Remote\Remote_dct" -I"C:\Git\electronica2018\remote_control\firmware\Remote\Remote_resources" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/internal" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/NoOS" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/NoOS/WWD" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/host/WICED" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/mbedtls_open/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/crypto_internal" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/NoOS/WWD/Cortex_M3_M4" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wifi" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/RTOS" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/WPS" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/network" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/GCC" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/ARM_CM4" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_electronica18-1.0/components/WIFI-SDK/WICED/WWD/internal/chips/4343x" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/PostgreSQL/include" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/base64" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/crc" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/mini_printf" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/ring_buffer" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/TLV" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wiced_log" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/bufmgr" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs/button_manager" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs/gpio_button" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/init" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/CapSense" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries/creator" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries/sdio" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/spi_flash" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WAF" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WWD" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NoNS/WWD" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/apps/waf/bootloader" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_electronica18-1.0/components/WIFI-SDK/platforms/CY8CKIT_062_IFLASH" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/chips/4343x" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols/SDIO" -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NoNS" -I"C:\Git\electronica2018\remote_control\firmware\Remote\Remote_config/GeneratedSource" -std=gnu11 -Wno-strict-aliasing -std=gnu11 -std=gnu11 -isystem "C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/include" -isystem "C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include" -isystem "C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include-fixed" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


