################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\Wire\src\utility\twi.c 

C_DEPS += \
.\libraries\Wire\src\utility\twi.c.d 

LINK_OBJ += \
.\libraries\Wire\src\utility\twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries\Wire\src\utility\twi.c.o: D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\Wire\src\utility\twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"D:\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\cores\arduino" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\variants\standard" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\Wire" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\Wire\src" -I"D:\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"D:\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI\src" -I"D:\code\Neu\AController\AquariumSteuerung\NTPClient-3.1.0" -I"D:\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7" -I"D:\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"D:\sloeber\arduinoPlugin\libraries\WiFi\1.2.6" -I"D:\sloeber\arduinoPlugin\libraries\WiFi\1.2.6\src" -I"D:\sloeber\arduinoPlugin\libraries\Keyboard\1.0.1" -I"D:\sloeber\arduinoPlugin\libraries\Keyboard\1.0.1\src" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\HID" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\HID\src" -I"D:\sloeber\arduinoPlugin\libraries\LiquidCrystal_I2C-1.1.2\1.1.2" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\cores\arduino" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\variants\standard" -I"D:\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"D:\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\HID" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\HID\src" -I"D:\sloeber\arduinoPlugin\libraries\Keyboard\1.0.1" -I"D:\sloeber\arduinoPlugin\libraries\Keyboard\1.0.1\src" -I"D:\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7" -I"D:\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"D:\sloeber\arduinoPlugin\libraries\LiquidCrystal_I2C-1.1.2\1.1.2" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI\src" -I"D:\sloeber\arduinoPlugin\libraries\WiFi\1.2.6" -I"D:\sloeber\arduinoPlugin\libraries\WiFi\1.2.6\src" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\Wire" -I"D:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


