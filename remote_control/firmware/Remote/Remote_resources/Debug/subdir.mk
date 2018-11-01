################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../4343WA1_bin.c \
../4343WA1_clm_blob.c \
../aws_config_html.c \
../client_cer.c \
../privkey_cer.c \
../rootca_cer.c 

OBJS += \
./4343WA1_bin.o \
./4343WA1_clm_blob.o \
./aws_config_html.o \
./client_cer.o \
./privkey_cer.o \
./rootca_cer.o 

C_DEPS += \
./4343WA1_bin.d \
./4343WA1_clm_blob.d \
./aws_config_html.d \
./client_cer.d \
./privkey_cer.d \
./rootca_cer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -O0  -g3 -I"C:/Users/gjl.CYSEMI/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


