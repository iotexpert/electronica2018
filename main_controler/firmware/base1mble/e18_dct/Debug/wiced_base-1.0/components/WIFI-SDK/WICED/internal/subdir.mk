################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/internal/dct.c 

OBJS += \
./wiced_base-1.0/components/WIFI-SDK/WICED/internal/dct.o 

C_DEPS += \
./wiced_base-1.0/components/WIFI-SDK/WICED/internal/dct.d 


# Each subdirectory must supply rules for building sources it contributes
wiced_base-1.0/components/WIFI-SDK/WICED/internal/dct.o: /Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/internal/dct.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wall  -g3 -DCY8C6247BZI_D54 -DWICED_DISABLE_MCU_POWERSAVE -DHSE_VALUE=26000000 -DBUS='"SDIO"' -DBOOTLOADER_MAGIC_NUMBER=0x4d435242 -DSFLASH_APPS_HEADER_LOC=0x0000 -Dwifi_firmware_image=resources_firmware_DIR_4343W_DIR_4343WA1_bin -Dwifi_firmware_clm_blob=resources_firmware_DIR_4343W_DIR_4343WA1_clm_blob -DWWD_STARTUP_DELAY=10 -DWWD_BUS_SDIO_AFTER_RESET_DELAY=1000 -DMAX_WATCHDOG_TIMEOUT_SECONDS=2.5 -DDEFAULT_SYSTEM_MONITOR_PERIOD=2500 -DPLATFORM='"CY8CKIT-062-WIFI-BT-INT-FLASH"' -DAPPS_CHIP_REVISION='""' -DPLATFORM_POWER_DOWN_THREAD_PREEMPTION_ALLOWED -DWICED -DWLAN_CHIP_FAMILY=4343W -DWLAN_CHIP=4343W -DCRLF_STDIO_REPLACEMENT -DWICED_USE_BESL -DWWD_DOWNLOAD_CLM_BLOB -DUSING_WICEDFS -DWWD_DIRECT_RESOURCES -DUDB_SDIO -DMODUSTOOLBOX=1 -DBCM_WICED -DNETWORK_NoNS=1 -DRTOS_NoOS=1 -DNoOS_FIQ_STACK=0 -DNoOS_IRQ_STACK=256 -DNoOS_SYS_STACK=0 -DDCT_CRC32_CALCULATION_SIZE_ON_STACK=1024 -DWIFI_CONFIG_APPLICATION_DEFINED -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_dct" -I"/Users/arh/Documents/iotexpert-projects/electronica2018/main_controler/firmware/base1mble/e18_mainapp" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/GCC" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/internal" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/crc" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/ring_buffer" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wifi" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/RTOS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/WPS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/network" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/include" -std=gnu11 -Wno-strict-aliasing -std=gnu11 -std=gnu11 -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/include" -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include" -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include-fixed" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


