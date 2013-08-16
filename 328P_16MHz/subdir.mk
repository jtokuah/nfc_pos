################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../nfc_pos_display.cpp \
../nfc_pos_main.cpp \
../nfc_pos_transaction.cpp 

OBJS += \
./nfc_pos_display.o \
./nfc_pos_main.o \
./nfc_pos_transaction.o 

CPP_DEPS += \
./nfc_pos_display.d \
./nfc_pos_main.d \
./nfc_pos_transaction.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"D:\Arduino\nfc_pos\src" -I"D:\Arduino\nfc_pos\libraries" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -g2 -gstabs -ffunction-sections -fdata-sections -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


