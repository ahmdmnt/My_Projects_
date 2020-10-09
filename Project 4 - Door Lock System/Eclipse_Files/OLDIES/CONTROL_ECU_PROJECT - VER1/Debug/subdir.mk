################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO.c \
../TWI.c \
../UART.c \
../alarm.c \
../cont_ecu_appl.c \
../dc_motor.c \
../ext_eeprom.c \
../timer.c 

OBJS += \
./DIO.o \
./TWI.o \
./UART.o \
./alarm.o \
./cont_ecu_appl.o \
./dc_motor.o \
./ext_eeprom.o \
./timer.o 

C_DEPS += \
./DIO.d \
./TWI.d \
./UART.d \
./alarm.d \
./cont_ecu_appl.d \
./dc_motor.d \
./ext_eeprom.d \
./timer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


