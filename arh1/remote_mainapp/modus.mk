DEVICE=CY8C6247BZI-D54
#
# Copyright 2018, Cypress Semiconductor Corporation or a subsidiary of
# Cypress Semiconductor Corporation. All Rights Reserved.
#
# This software, including source code, documentation and related
# materials ("Software"), is owned by Cypress Semiconductor Corporation
# or one of its subsidiaries ("Cypress") and is protected by and subject to
# worldwide patent protection (United States and foreign),
# United States copyright laws and international treaty provisions.
# Therefore, you may use this Software only as provided in the license
# agreement accompanying the software package from which you
# obtained this Software ("EULA").
# If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
# non-transferable license to copy, modify, and compile the Software
# source code solely for use in connection with Cypress's
# integrated circuit products. Any reproduction, modification, translation,
# compilation, or representation of this Software except as specified
# above is prohibited without the express written permission of Cypress.
#
# Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
# reserves the right to make changes to the Software without notice. Cypress
# does not assume any liability arising out of the application or use of the
# Software or any product or circuit described in the Software. Cypress does
# not authorize its products for use in any products where a malfunction or
# failure of the Cypress product may reasonably be expected to result in
# significant property damage, injury or death ("High Risk Product"). By
# including Cypress's product in a High Risk Product, the manufacturer
# of such system or application assumes all risk of such use and in doing
# so agrees to indemnify Cypress against all liability.
#

# This file has two purposes.  The first purpose is to provide information
# to the makefile build system.  The second purpose is to provide information
# to any IDE about the example.  Therefore, this file should not contain any
# thing other than make variables.  Any other more complex make file magic
# should go into some other file.
#

#
# The library to search to find the recipe for building this example. This library
# must exist in the target SDK
#
CY_BUILD_LIBRARY = wiced_base-1.0

#
# The toolchain we are using.  This is not the specific version, but just
# the general type (e.g. GCC, IAR, CLAGS, etc.)
#
TOOLCHAIN=GCC

#
# The target platform for the example.  A platform is a set of hardware that
# is targeted by this example.  Many examples work with multiple PLATFORM
# values and can be retargeted to a new PLATFORM by just including the
# new PLATFORM value as part of the make invocation.  Some platforms require
# additional information and this must be provided as well
#
# Examples of the PSoC 6 based platform
#    PLATFORM=PSOC64343W
#    CY_PSOC6_MPN=CY8C6247BZI_D54
#
#
# This is the default target for this example
#
PLATFORMS_VERSION =1.0
PLATFORM=CY8CKIT-062-WIFI-BT-INT-FLASH

#
# The target OSNS.  This is the RTOS and network stack to be targeted
# for this example.
#
OSNS=ThreadX_NetXDuo

#
# The configuration.  Valid values are Debug or Release
#
CONFIG = Release

#
# The design.modus file
#
CYCONFIG_DESIGN_MODUS=design.modus

#
# The name of this example.  This is used as a default name for
# any IDE that is creating a new project based on this example
#
CY_EXAMPLE_NAME = AWSIoTPublisher

#
# For an IDE, this is the description of the example project to display
#
CY_EXAMPLE_DESCRIPTION =This application snippet demonstrates how to publish the data to AWS cloud using MQTT component.

#
# If this is true, this example is shown as part of the new project dialog
# process in and IDE.  If this is false, this is not shown
#
CY_SHOW_NEW_PROJECT=true

#
# This is the list of valid platforms for this example
#
CY_VALID_PLATFORMS= CY8CKIT-062-WIFI-BT-INT-FLASH

#
# This is the list of valid OSNS combinations for this example
#
CY_VALID_OSNS= ThreadX_NetXDuo ThreadX_NetX FreeRTOS_LwIP

#
# This is the required SDK for this example
#
CY_REQUIRED_SDK=Cypress SDK[1.0]

#
# The list of valid devices for this example.  If this is empty
# there this example works for all devices
#
CY_VALID_DEVICES=

#
# The source code for the application
#
CY_APP_SOURCE = \
	publisher.c \
	wifi_config_dct.h \
	publisher.cyrsc

#
# The Optional set of software components used by the application.
#
# NOTE: This variable cannot be renamed or moved to a different file.
# It is updated by the Modus IDE middleware editor.
CY_MAINAPP_SWCOMP_USED= \
    wiced_base-1.0/components/WIFI-SDK/libraries/utilities/cJSON \
    psoc6sw-1.0/components/psoc6mw/capsense/softfp \
    wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/low_energy \
    wiced_base-1.0/components/WIFI-SDK/libraries/drivers/bluetooth/firmware

#
# The set of software components owned by the
# developer and are required as dependencies.  These
# will not be part of the makefile build
#
# NOTE: This variable cannot be renamed or moved to a different file.
# It is updated by the Modus IDE middleware editor.
CY_MAINAPP_SWCOMP_EXT= \
    


#
# Defines specific to the application
#
APP_MAINAPP_DEFINES = -DAPP_NAME=$(CY_EXAMPLE_NAME)

#
# Includes specific to the application
#
APP_MAINAPP_INCLUDES= \
    -I.

#
# Include resources needed from the top level
#
APP_MAINAPP_RESOURCES = \
    publisher.cyrsc \
    $(CY_GENERATED_DIR)/$(CY_MAINAPP_NAME)/publisher.cyrsc

#
# Defines specific to the DCT
#
APP_DCT_DEFINES = \
	-DWIFI_CONFIG_APPLICATION_DEFINED

#
# Includes specific to the DCT
#
APP_DCT_INCLUDES= \
    -I$(CY_GENERATED_DIR)/$(CY_MAINAPP_NAME)

#
# Check to be sure we can find the SDK.  The SDK is found via the
# CYSDK environment variable
#
ifndef CYSDK
$(error The SDK must be defined via the CYSDK environment variable)
endif

#
# Include the main makefile for building this type of example
#
include $(CYSDK)/libraries/platforms-$(PLATFORMS_VERSION)/common/find_platform.mk
