################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO.c \
../TWI.c \
../UART.c \
../appl_control_ecu.c \
../dc_motor.c \
../ext_eeprom.c \
../tim.c 

OBJS += \
./DIO.o \
./TWI.o \
./UART.o \
./appl_control_ecu.o \
./dc_motor.o \
./ext_eeprom.o \
./tim.o 

C_DEPS += \
./DIO.d \
./TWI.d \
./UART.d \
./appl_control_ecu.d \
./dc_motor.d \
./ext_eeprom.d \
./tim.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


