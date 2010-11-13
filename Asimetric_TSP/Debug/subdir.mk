################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tsp.cpp 

OBJS += \
./tsp.o 

CPP_DEPS += \
./tsp.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/prog/workspace/Asimetric_TSP/generator" -I"/home/prog/workspace/Asimetric_TSP" -I"/home/prog/workspace/Asimetric_TSP/io" -I"/home/prog/workspace/Asimetric_TSP/solver" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


