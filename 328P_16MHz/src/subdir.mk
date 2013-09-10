################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CDC.cpp \
../src/HID.cpp \
../src/HardwareSerial.cpp \
../src/Print.cpp \
../src/SPI.cpp \
../src/Stream.cpp \
../src/Tone.cpp \
../src/USBCore.cpp \
../src/WMath.cpp \
../src/WString.cpp \
../src/main.cpp \
../src/new.cpp 

C_SRCS += \
../src/WInterrupts.c \
../src/wiring.c \
../src/wiring_analog.c \
../src/wiring_digital.c \
../src/wiring_pulse.c \
../src/wiring_shift.c 

OBJS += \
./src/CDC.o \
./src/HID.o \
./src/HardwareSerial.o \
./src/Print.o \
./src/SPI.o \
./src/Stream.o \
./src/Tone.o \
./src/USBCore.o \
./src/WInterrupts.o \
./src/WMath.o \
./src/WString.o \
./src/main.o \
./src/new.o \
./src/wiring.o \
./src/wiring_analog.o \
./src/wiring_digital.o \
./src/wiring_pulse.o \
./src/wiring_shift.o 

C_DEPS += \
./src/WInterrupts.d \
./src/wiring.d \
./src/wiring_analog.d \
./src/wiring_digital.d \
./src/wiring_pulse.d \
./src/wiring_shift.d 

CPP_DEPS += \
./src/CDC.d \
./src/HID.d \
./src/HardwareSerial.d \
./src/Print.d \
./src/SPI.d \
./src/Stream.d \
./src/Tone.d \
./src/USBCore.d \
./src/WMath.d \
./src/WString.d \
./src/main.d \
./src/new.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-gcc -I"D:\Arduino\nfc_pos\src" -I"D:\Arduino\nfc_pos\libraries" -DARDUINO=105 -Wall -ffunction-sections -fdata-sections -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Arduino\nfc_pos\libraries" -I"D:\Arduino\nfc_pos\src" -DARDUINO=105 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


