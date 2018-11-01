################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list/linked_list.c 

OBJS += \
./wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list/linked_list.o 

C_DEPS += \
./wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list/linked_list.d 


# Each subdirectory must supply rules for building sources it contributes
wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list/linked_list.o: /Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list/linked_list.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wall  -g -DCY8C6247BZI_D54 -DWICED_DISABLE_MCU_POWERSAVE -DHSE_VALUE=26000000 -DBUS='"SDIO"' -DBOOTLOADER_MAGIC_NUMBER=0x4d435242 -DSFLASH_APPS_HEADER_LOC=0x0000 -DWWD_STARTUP_DELAY=10 -DWWD_BUS_SDIO_AFTER_RESET_DELAY=1000 -DMAX_WATCHDOG_TIMEOUT_SECONDS=2.5 -DDEFAULT_SYSTEM_MONITOR_PERIOD=2500 -DPLATFORM='"CY8CKIT-062-WIFI-BT"' -DAPPS_CHIP_REVISION='""' -DPLATFORM_POWER_DOWN_THREAD_PREEMPTION_ALLOWED -DWICED -DWLAN_CHIP_FAMILY=4343W -DWLAN_CHIP=4343W -DCRLF_STDIO_REPLACEMENT -DWICED_USE_BESL -DWWD_DOWNLOAD_CLM_BLOB -DUSING_WICEDFS -DWWD_DIRECT_RESOURCES -DUDB_SDIO -DMODUSTOOLBOX=1 -DBCM_WICED -Dwifi_firmware_image=resources_firmware_DIR_4343W_DIR_4343WA1_bin -Dwifi_firmware_clm_blob=resources_firmware_DIR_4343W_DIR_4343WA1_clm_blob -DNX_INCLUDE_USER_DEFINE_FILE -DNETWORK_NetX_Duo=1 -DNetX_Duo_VERSION='"ver5.10_sp3"' -DRTOS_ThreadX=1 -DTX_INCLUDE_USER_DEFINE_FILE -DThreadX_VERSION='"ver5.8"' -DLib_USBX_VERSION='"v5.7"' -DADD_NETX_EAPOL_SUPPORT -DNXD_EXTENDED_BSD_SOCKET_SUPPORT -D__TARGET_ARCH_ARM=7 -D__THUMB_INTERWORK -DAPP_NAME=remote -I"/Users/arh/Documents/iotexpert-projects/emb2018/arh1/remote_mainapp" -I"/Users/arh/Documents/iotexpert-projects/emb2018/arh1/remote_config/GeneratedSource" -I"/Users/arh/Documents/iotexpert-projects/emb2018/arh1/remote_config" -I"/Users/arh/Documents/iotexpert-projects/emb2018/arh1/remote_dct" -I"/Users/arh/Documents/iotexpert-projects/emb2018/arh1/remote_resources" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/include/ip" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/PostgreSQL/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/TLS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/P2P" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/DTLS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/crypto_internal" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/supplicant" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/host/WICED" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/mbedtls_open/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/GCC" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wifi" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/RTOS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security/BESL/WPS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/include/network" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NetX_Duo/ver5.10_sp3" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NetX_Duo/WICED" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NetX_Duo/WWD" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/WWD" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/WWD/CM3_CM4" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/WICED" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/ver5.8" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/ver5.8/Cortex_M3_M4/GCC" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/AWS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/COAP/client" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/COAP/parser" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/COAP/server" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/COAP" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/DNS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/MQTT" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/SMTP" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/SNTP" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/HTTP_client" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols/Xively" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/cJSON" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/JSON_parser" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/gki/common" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/udrv/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/hcis" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/hcis/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/fw2/mpaf/components/stack/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/fw2/mpaf/components/stack/brcm" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/fw2/mpaf/components/stack/btm" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/fw2/mpaf/components/stack/gatt/legattdb" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/fw2/mpaf/components/stack/gatt/legattdb/inc" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Components/fw2/mpaf/components/stack/gatt" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/Projects/bte/main" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/WICED" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/bt_logmsg" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/BTE/proto_disp" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/include" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/internal" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/ARM_CM4" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/init" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/CapSense" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries/creator" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/libraries/sdio" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/peripherals/spi_flash" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WAF" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus/WWD" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols" -I"/Applications/ModusToolbox_1.0/libraries/wiced_electronica18-1.0/components/WIFI-SDK/WICED/WWD/internal/chips/4343x" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/daemons/DHCP_server" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/base64" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/crc" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/linked_list" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/mini_printf" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/ring_buffer" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/TLV" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/wiced_log" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities/bufmgr" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs/button_manager" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs/gpio_button" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs/src" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/test/TraceX" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX/ver5.8/Cortex_M3_M4" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6mw/capsense" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/drivers/source" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"/Applications/ModusToolbox_1.0/libraries/wiced_electronica18-1.0/components/WIFI-SDK/platforms/CY8CKIT_062_IFLASH" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/platform/MCU/PSoC6_Modus" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/chips/4343x" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/WWD/internal/bus_protocols/SDIO" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/protocols" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/utilities" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/inputs" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/security" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/filesystems/wicedfs" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/network/NetX_Duo" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/WICED/RTOS/ThreadX" -I"/Applications/ModusToolbox_1.0/libraries/psoc6sw-1.0/components/psoc6mw/capsense/softfp" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/low_energy" -I"/Applications/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/firmware" -std=gnu11 -Wno-strict-aliasing -std=gnu11 -std=gnu11 -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/include" -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include" -isystem "/Applications/ModusToolbox_1.0/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include-fixed" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


