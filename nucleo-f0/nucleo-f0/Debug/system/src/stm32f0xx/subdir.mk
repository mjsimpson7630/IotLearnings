################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f0xx/stm32f0xx_hal.c \
../system/src/stm32f0xx/stm32f0xx_hal_cortex.c \
../system/src/stm32f0xx/stm32f0xx_hal_dma.c \
../system/src/stm32f0xx/stm32f0xx_hal_flash.c \
../system/src/stm32f0xx/stm32f0xx_hal_flash_ex.c \
../system/src/stm32f0xx/stm32f0xx_hal_gpio.c \
../system/src/stm32f0xx/stm32f0xx_hal_i2c.c \
../system/src/stm32f0xx/stm32f0xx_hal_i2c_ex.c \
../system/src/stm32f0xx/stm32f0xx_hal_pwr.c \
../system/src/stm32f0xx/stm32f0xx_hal_pwr_ex.c \
../system/src/stm32f0xx/stm32f0xx_hal_rcc.c \
../system/src/stm32f0xx/stm32f0xx_hal_rcc_ex.c \
../system/src/stm32f0xx/stm32f0xx_hal_tim.c \
../system/src/stm32f0xx/stm32f0xx_hal_tim_ex.c 

OBJS += \
./system/src/stm32f0xx/stm32f0xx_hal.o \
./system/src/stm32f0xx/stm32f0xx_hal_cortex.o \
./system/src/stm32f0xx/stm32f0xx_hal_dma.o \
./system/src/stm32f0xx/stm32f0xx_hal_flash.o \
./system/src/stm32f0xx/stm32f0xx_hal_flash_ex.o \
./system/src/stm32f0xx/stm32f0xx_hal_gpio.o \
./system/src/stm32f0xx/stm32f0xx_hal_i2c.o \
./system/src/stm32f0xx/stm32f0xx_hal_i2c_ex.o \
./system/src/stm32f0xx/stm32f0xx_hal_pwr.o \
./system/src/stm32f0xx/stm32f0xx_hal_pwr_ex.o \
./system/src/stm32f0xx/stm32f0xx_hal_rcc.o \
./system/src/stm32f0xx/stm32f0xx_hal_rcc_ex.o \
./system/src/stm32f0xx/stm32f0xx_hal_tim.o \
./system/src/stm32f0xx/stm32f0xx_hal_tim_ex.o 

C_DEPS += \
./system/src/stm32f0xx/stm32f0xx_hal.d \
./system/src/stm32f0xx/stm32f0xx_hal_cortex.d \
./system/src/stm32f0xx/stm32f0xx_hal_dma.d \
./system/src/stm32f0xx/stm32f0xx_hal_flash.d \
./system/src/stm32f0xx/stm32f0xx_hal_flash_ex.d \
./system/src/stm32f0xx/stm32f0xx_hal_gpio.d \
./system/src/stm32f0xx/stm32f0xx_hal_i2c.d \
./system/src/stm32f0xx/stm32f0xx_hal_i2c_ex.d \
./system/src/stm32f0xx/stm32f0xx_hal_pwr.d \
./system/src/stm32f0xx/stm32f0xx_hal_pwr_ex.d \
./system/src/stm32f0xx/stm32f0xx_hal_rcc.d \
./system/src/stm32f0xx/stm32f0xx_hal_rcc_ex.d \
./system/src/stm32f0xx/stm32f0xx_hal_tim.d \
./system/src/stm32f0xx/stm32f0xx_hal_tim_ex.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f0xx/%.o: ../system/src/stm32f0xx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F030x8 -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


