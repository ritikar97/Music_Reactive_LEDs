################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl25z4.c 

OBJS += \
./startup/startup_mkl25z4.o 

C_DEPS += \
./startup/startup_mkl25z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DDEBUG -DCPU_MKL25Z128VLK4 -DFSL_RTOS_FREE_RTOS -DFRDM_KL25Z -DFREEDOM -DCPU_MKL25Z128VLK4_cm0plus -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DSDK_DEBUGCONSOLE=0 -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\board" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\source" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\CMSIS" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\drivers" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\utilities" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\freertos" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\Music_Reactive_LEDs\startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


