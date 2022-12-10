################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_MKL25Z4.c 

OBJS += \
./CMSIS/system_MKL25Z4.o 

C_DEPS += \
./CMSIS/system_MKL25Z4.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c CMSIS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DDEBUG -DCPU_MKL25Z128VLK4 -DFSL_RTOS_FREE_RTOS -DFRDM_KL25Z -DFREEDOM -DCPU_MKL25Z128VLK4_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project\board" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project\source" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project\CMSIS" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project\drivers" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project\utilities" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project\freertos" -I"C:\Users\ritik\Documents\MCUXpressoIDE_11.5.1_7266\workspace\frdmkl25z_rtos_examples_freertos_hello_project\startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


