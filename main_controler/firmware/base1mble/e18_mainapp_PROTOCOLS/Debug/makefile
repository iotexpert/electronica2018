################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/Xively/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/SNTP/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/SMTP/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/MQTT/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/HTTP_client/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/DNS/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/COAP/server/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/COAP/parser/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/COAP/client/subdir.mk
-include wiced_base-1.0/components/WIFI-SDK/libraries/protocols/AWS/subdir.mk
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
all: libe18_mainapp_PROTOCOLS.a

# Tool invocations
libe18_mainapp_PROTOCOLS.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross Archiver'
	arm-none-eabi-ar -r  "libe18_mainapp_PROTOCOLS.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ARCHIVES)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) libe18_mainapp_PROTOCOLS.a
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
