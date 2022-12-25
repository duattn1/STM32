################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libopencm3/lib/stm32/common/gpio_common_all.c \
../libopencm3/lib/stm32/common/gpio_common_f0234.c \
../libopencm3/lib/stm32/common/rcc_common_all.c 

OBJS += \
./libopencm3/lib/stm32/common/gpio_common_all.o \
./libopencm3/lib/stm32/common/gpio_common_f0234.o \
./libopencm3/lib/stm32/common/rcc_common_all.o 

C_DEPS += \
./libopencm3/lib/stm32/common/gpio_common_all.d \
./libopencm3/lib/stm32/common/gpio_common_f0234.d \
./libopencm3/lib/stm32/common/rcc_common_all.d 


# Each subdirectory must supply rules for building sources it contributes
libopencm3/lib/stm32/common/%.o libopencm3/lib/stm32/common/%.su: ../libopencm3/lib/stm32/common/%.c libopencm3/lib/stm32/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F0 -c -I"D:/STM32F030/01_Project/STM32F030_libopencm3/libopencm3/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libopencm3-2f-lib-2f-stm32-2f-common

clean-libopencm3-2f-lib-2f-stm32-2f-common:
	-$(RM) ./libopencm3/lib/stm32/common/gpio_common_all.d ./libopencm3/lib/stm32/common/gpio_common_all.o ./libopencm3/lib/stm32/common/gpio_common_all.su ./libopencm3/lib/stm32/common/gpio_common_f0234.d ./libopencm3/lib/stm32/common/gpio_common_f0234.o ./libopencm3/lib/stm32/common/gpio_common_f0234.su ./libopencm3/lib/stm32/common/rcc_common_all.d ./libopencm3/lib/stm32/common/rcc_common_all.o ./libopencm3/lib/stm32/common/rcc_common_all.su

.PHONY: clean-libopencm3-2f-lib-2f-stm32-2f-common

