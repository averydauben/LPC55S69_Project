################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LPC55S69_Project.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/LPC55S69_Project.d \
./source/semihost_hardfault.d 

OBJS += \
./source/LPC55S69_Project.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\board" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\source" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\utilities" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\drivers" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\component\uart" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\component\serial_manager" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\device" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\CMSIS" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\component\lists" -I"C:\Users\avery\Documents\MCUXpressoIDE_24.9.25\workspace\LPC55S69_Project\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/LPC55S69_Project.d ./source/LPC55S69_Project.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

