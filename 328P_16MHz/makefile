################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/avr-libc/subdir.mk
-include src/subdir.mk
-include source/subdir.mk
-include libraries/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
FLASH_IMAGE += \
nfc_pos.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: nfc_pos.elf secondary-outputs

# Tool invocations
nfc_pos.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc --cref -s -Os -o"nfc_pos.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm -Wl,-Map,nfc_pos.map,--cref -Wl,--gc-sections -L"D:\Arduino\nfc_pos\328P_16MHz" -mmcu=atmega328p
	@echo 'Finished building target: $@'
	@echo ' '

nfc_pos.hex: nfc_pos.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex nfc_pos.elf  "nfc_pos.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: nfc_pos.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p nfc_pos.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: nfc_pos.elf
	@echo 'Invoking: AVRDude'
	D:\WinAVR-20100110\bin\avrdude -pm328p -carduino -P\\.\COM6 -b115200 -F -Uflash:w:nfc_pos.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ELFS)$(FLASH_IMAGE)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(AVRDUDEDUMMY)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) nfc_pos.elf
	-@echo ' '

secondary-outputs: $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
