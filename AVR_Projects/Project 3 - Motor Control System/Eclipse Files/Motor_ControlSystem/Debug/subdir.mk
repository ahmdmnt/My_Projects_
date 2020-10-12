################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DIO.c \
../LCD.c \
../PWM.c \
../appl.c \
../external_interrupt.c \
../motor_dc.c 

OBJS += \
./ADC.o \
./DIO.o \
./LCD.o \
./PWM.o \
./appl.o \
./external_interrupt.o \
./motor_dc.o 

C_DEPS += \
./ADC.d \
./DIO.d \
./LCD.d \
./PWM.d \
./appl.d \
./external_interrupt.d \
./motor_dc.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


