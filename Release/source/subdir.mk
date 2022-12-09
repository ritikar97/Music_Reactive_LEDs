################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/analog_in.c \
../source/led_out.c \
../source/main.c \
../source/mtb.c \
../source/neopixel_lib.c \
../source/semihost_hardfault.c 

OBJS += \
./source/analog_in.o \
./source/led_out.o \
./source/main.o \
./source/mtb.o \
./source/neopixel_lib.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/analog_in.d \
./source/led_out.d \
./source/main.d \
./source/mtb.d \
./source/neopixel_lib.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\board" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\source" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\startup" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\CMSIS" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\drivers" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\utilities" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


