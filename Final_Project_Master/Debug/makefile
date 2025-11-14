################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART_DRIVER/subdir.mk
-include MCAL/TWI_DRIVER/subdir.mk
-include MCAL/TIMER_DRIVER/TIMER2/subdir.mk
-include MCAL/TIMER_DRIVER/TIMER1/subdir.mk
-include MCAL/TIMER_DRIVER/TIMER0/subdir.mk
-include MCAL/SPI_DRIVER/subdir.mk
-include MCAL/EXT_INTERRUPT/subdir.mk
-include MCAL/DIO_DRIVER/subdir.mk
-include MCAL/ADC_DRIVER/subdir.mk
-include HAL/LM35/subdir.mk
-include HAL/LEDS/subdir.mk
-include HAL/LDR/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/FAN/subdir.mk
-include HAL/EXTERNAL_EEPROM/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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
LSS += \
Final_Project_1.lss \

FLASH_IMAGE += \
Final_Project_1.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Final_Project_1.elf secondary-outputs

# Tool invocations
Final_Project_1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Final_Project_1.map -mmcu=atmega32 -o "Final_Project_1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Final_Project_1.lss: Final_Project_1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Final_Project_1.elf  >"Final_Project_1.lss"
	@echo 'Finished building: $@'
	@echo ' '

Final_Project_1.hex: Final_Project_1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Final_Project_1.elf  "Final_Project_1.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Final_Project_1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Final_Project_1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Final_Project_1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
