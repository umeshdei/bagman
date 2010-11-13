################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../io/Instance.cpp \
../io/Point.cpp \
../io/Result.cpp 

OBJS += \
./io/Instance.o \
./io/Point.o \
./io/Result.o 

CPP_DEPS += \
./io/Instance.d \
./io/Point.d \
./io/Result.d 


# Each subdirectory must supply rules for building sources it contributes
io/%.o: ../io/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/prog/workspace/Asimetric_TSP/generator" -I"/home/prog/workspace/Asimetric_TSP" -I"/home/prog/workspace/Asimetric_TSP/io" -I"/home/prog/workspace/Asimetric_TSP/solver" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


