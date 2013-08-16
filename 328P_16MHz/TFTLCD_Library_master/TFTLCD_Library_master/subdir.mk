################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Program\ Files\ (x86)/Arduino/libraries/TFTLCD_Library_master/TFTLCD_Library_master/Adafruit_TFTLCD.cpp 

OBJS += \
./TFTLCD_Library_master/TFTLCD_Library_master/Adafruit_TFTLCD.o 

CPP_DEPS += \
./TFTLCD_Library_master/TFTLCD_Library_master/Adafruit_TFTLCD.d 


# Each subdirectory must supply rules for building sources it contributes
TFTLCD_Library_master/TFTLCD_Library_master/Adafruit_TFTLCD.o: C:/Program\ Files\ (x86)/Arduino/libraries/TFTLCD_Library_master/TFTLCD_Library_master/Adafruit_TFTLCD.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../LCDTest/Arduino_Uno/arduino -I"C:\Arduino\arduino_core\src" -I../LCDTest/Arduino_Uno/standard -I../LCDTest/LCDTest -IC:/Arduino/LCDTest/LCDTest/graphicstest -I../LCDTest/TFTLCD_Library_master -I"C:\Program Files (x86)\Arduino\libraries\Adafruit-GFX-Library-master" -I"C:\Program Files (x86)\Arduino\libraries\TFTLCD_Library_master" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -g2 -gstabs -ffunction-sections -fdata-sections -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


