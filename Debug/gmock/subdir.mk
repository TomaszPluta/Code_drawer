################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../gmock/gmock-gtest-all.cc 

OBJS += \
./gmock/gmock-gtest-all.o 

CC_DEPS += \
./gmock/gmock-gtest-all.d 


# Each subdirectory must supply rules for building sources it contributes
gmock/%.o: ../gmock/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/tomek/stm32workspace/Code_drawer/gmock" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


