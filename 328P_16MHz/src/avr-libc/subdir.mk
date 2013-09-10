################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/avr-libc/malloc.c \
../src/avr-libc/realloc.c 

OBJS += \
./src/avr-libc/malloc.o \
./src/avr-libc/realloc.o 

C_DEPS += \
./src/avr-libc/malloc.d \
./src/avr-libc/realloc.d 


# Each subdirectory must supply rules for building sources it contributes
src/avr-libc/%.o: ../src/avr-libc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Arduino\nfc_pos\libraries" -I"D:\Arduino\nfc_pos\src" -DARDUINO=105 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


