################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/Adafruit_GFX.cpp \
../libraries/Adafruit_NFCShield_I2C.cpp \
../libraries/Adafruit_TFTLCD.cpp \
../libraries/TouchScreen.cpp \
../libraries/Wire.cpp 

C_SRCS += \
../libraries/glcdfont.c \
../libraries/twi.c 

OBJS += \
./libraries/Adafruit_GFX.o \
./libraries/Adafruit_NFCShield_I2C.o \
./libraries/Adafruit_TFTLCD.o \
./libraries/TouchScreen.o \
./libraries/Wire.o \
./libraries/glcdfont.o \
./libraries/twi.o 

C_DEPS += \
./libraries/glcdfont.d \
./libraries/twi.d 

CPP_DEPS += \
./libraries/Adafruit_GFX.d \
./libraries/Adafruit_NFCShield_I2C.d \
./libraries/Adafruit_TFTLCD.d \
./libraries/TouchScreen.d \
./libraries/Wire.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/%.o: ../libraries/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"D:\Arduino\nfc_pos\src" -I"D:\Arduino\nfc_pos\libraries" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -g2 -gstabs -ffunction-sections -fdata-sections -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraries/%.o: ../libraries/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Arduino\nfc_pos\libraries" -I"D:\Arduino\nfc_pos\src" -ID:/Arduino/nfc_pos -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -std=gnu99 -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


