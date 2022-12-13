################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MAX7219.c \
../Src/main.c 

OBJS += \
./Src/MAX7219.o \
./Src/main.o 

C_DEPS += \
./Src/MAX7219.d \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -c -I"D:/STM32F030/01_Project/STM32F030_Minimal/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/MAX7219.d ./Src/MAX7219.o ./Src/MAX7219.su ./Src/main.d ./Src/main.o ./Src/main.su

.PHONY: clean-Src

