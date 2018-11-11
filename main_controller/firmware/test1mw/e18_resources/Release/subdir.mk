################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../4343WA1_bin.c \
../4343WA1_clm_blob.c \
../aws_client_cer.c \
../aws_privkey_cer.c \
../fight_wav.c \
../rootca_cer.c \
../winner_wav.c 

OBJS += \
./4343WA1_bin.o \
./4343WA1_clm_blob.o \
./aws_client_cer.o \
./aws_privkey_cer.o \
./fight_wav.o \
./rootca_cer.o \
./winner_wav.o 

C_DEPS += \
./4343WA1_bin.d \
./4343WA1_clm_blob.d \
./aws_client_cer.d \
./aws_privkey_cer.d \
./fight_wav.d \
./rootca_cer.d \
./winner_wav.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -O0  -g -I"C:/Users/kmwh/ModusToolbox_1.0/libraries/wiced_base-1.0/components/WIFI-SDK/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


