################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc.c \
../source/dma.c \
../source/main.c \
../source/mtb.c \
../source/retarget_itm.c \
../source/ring.c \
../source/uart.c 

OBJS += \
./source/adc.o \
./source/dma.o \
./source/main.o \
./source/mtb.o \
./source/retarget_itm.o \
./source/ring.o \
./source/uart.o 

C_DEPS += \
./source/adc.d \
./source/dma.d \
./source/main.d \
./source/mtb.d \
./source/retarget_itm.d \
./source/ring.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DDEBUG -DPRINTF_FLOAT_ENABLE=1 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DCR_INTEGER_PRINTF -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_DEBUGCONSOLE_ITM -D__MCUXPRESSO -D__USE_CMSIS -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I../board -I../Include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


