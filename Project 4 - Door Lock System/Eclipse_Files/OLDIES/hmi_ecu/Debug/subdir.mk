################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO.c \
../LCD.c \
../UART.c \
../appl_hmi_ecu.c \
../external_interrupt.c \
../keypad.c \
../tim.c 

OBJS += \
./DIO.o \
./LCD.o \
./UART.o \
./appl_hmi_ecu.o \
./external_interrupt.o \
./keypad.o \
./tim.o 

C_DEPS += \
./DIO.d \
./LCD.d \
./UART.d \
./appl_hmi_ecu.d \
./external_interrupt.d \
./keypad.d \
./tim.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


