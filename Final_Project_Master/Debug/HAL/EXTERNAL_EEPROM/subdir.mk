################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/EXTERNAL_EEPROM/program.c 

OBJS += \
./HAL/EXTERNAL_EEPROM/program.o 

C_DEPS += \
./HAL/EXTERNAL_EEPROM/program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/EXTERNAL_EEPROM/%.o: ../HAL/EXTERNAL_EEPROM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


