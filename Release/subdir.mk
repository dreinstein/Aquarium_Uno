################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../AquariumSteuerung.ino 

CPP_SRCS += \
../.ino.cpp \
../Display.cpp \
../Heater.cpp \
../Light.cpp \
../Pump.cpp 

LINK_OBJ += \
./.ino.cpp.o \
./Display.cpp.o \
./Heater.cpp.o \
./Light.cpp.o \
./Pump.cpp.o 

INO_DEPS += \
.\AquariumSteuerung.ino.d 

CPP_DEPS += \
.\.ino.cpp.d \
.\Display.cpp.d \
.\Heater.cpp.d \
.\Light.cpp.d \
.\Pump.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\EclipseArduino\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\cores\arduino" -I"C:\AController\AquariumSteuerung\DallasTemperature" -I"C:\AController\AquariumSteuerung\DS3231" -I"C:\AController\AquariumSteuerung\OneWire-master" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\variants\standard" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI\src" -I"C:\AController\AquariumSteuerung\NTPClient-3.1.0" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

AquariumSteuerung.o: ../AquariumSteuerung.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\EclipseArduino\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\cores\arduino" -I"C:\AController\AquariumSteuerung\DallasTemperature" -I"C:\AController\AquariumSteuerung\DS3231" -I"C:\AController\AquariumSteuerung\OneWire-master" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\variants\standard" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI\src" -I"C:\AController\AquariumSteuerung\NTPClient-3.1.0" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Display.cpp.o: ../Display.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\EclipseArduino\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\cores\arduino" -I"C:\AController\AquariumSteuerung\DallasTemperature" -I"C:\AController\AquariumSteuerung\DS3231" -I"C:\AController\AquariumSteuerung\OneWire-master" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\variants\standard" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI\src" -I"C:\AController\AquariumSteuerung\NTPClient-3.1.0" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Heater.cpp.o: ../Heater.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\EclipseArduino\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\cores\arduino" -I"C:\AController\AquariumSteuerung\DallasTemperature" -I"C:\AController\AquariumSteuerung\DS3231" -I"C:\AController\AquariumSteuerung\OneWire-master" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\variants\standard" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI\src" -I"C:\AController\AquariumSteuerung\NTPClient-3.1.0" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Light.cpp.o: ../Light.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\EclipseArduino\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\cores\arduino" -I"C:\AController\AquariumSteuerung\DallasTemperature" -I"C:\AController\AquariumSteuerung\DS3231" -I"C:\AController\AquariumSteuerung\OneWire-master" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\variants\standard" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI\src" -I"C:\AController\AquariumSteuerung\NTPClient-3.1.0" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Pump.cpp.o: ../Pump.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\EclipseArduino\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\cores\arduino" -I"C:\AController\AquariumSteuerung\DallasTemperature" -I"C:\AController\AquariumSteuerung\DS3231" -I"C:\AController\AquariumSteuerung\OneWire-master" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\variants\standard" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\Wire\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\Ethernet\1.1.2\src" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI" -I"C:\EclipseArduino\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.18\libraries\SPI\src" -I"C:\AController\AquariumSteuerung\NTPClient-3.1.0" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4" -I"C:\EclipseArduino\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.4\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


