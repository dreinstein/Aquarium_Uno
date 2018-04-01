################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src\Wire.cpp 

LINK_OBJ += \
.\libraries\Wire\src\Wire.cpp.o 

CPP_DEPS += \
.\libraries\Wire\src\Wire.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\Wire\src\Wire.cpp.o: C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src\Wire.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\EclipseArduino\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\cores\arduino" -I"C:\AController\AquariumSteuerung\DallasTemperature" -I"C:\AController\AquariumSteuerung\DS3231" -I"C:\AController\AquariumSteuerung\OneWire-master" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\variants\standard" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI\src" -I"C:\AController\AquariumSteuerung\NTPClient-3.1.0" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\WiFi\1.2.6" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\WiFi\1.2.6\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Keyboard\1.0.1" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Keyboard\1.0.1\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\HID" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\HID\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal_I2C-1.1.2\1.1.2" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


