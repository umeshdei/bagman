################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../solver/TSPGreedySolver.cpp \
../solver/TSPGreedySolver2.cpp \
../solver/TSPLocalSearch.cpp \
../solver/TSPRandomSolver.cpp \
../solver/TSPSolver.cpp \
../solver/TSPSteepestSolver.cpp 

OBJS += \
./solver/TSPGreedySolver.o \
./solver/TSPGreedySolver2.o \
./solver/TSPLocalSearch.o \
./solver/TSPRandomSolver.o \
./solver/TSPSolver.o \
./solver/TSPSteepestSolver.o 

CPP_DEPS += \
./solver/TSPGreedySolver.d \
./solver/TSPGreedySolver2.d \
./solver/TSPLocalSearch.d \
./solver/TSPRandomSolver.d \
./solver/TSPSolver.d \
./solver/TSPSteepestSolver.d 


# Each subdirectory must supply rules for building sources it contributes
solver/%.o: ../solver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/prog/workspace/Asimetric_TSP/generator" -I"/home/prog/workspace/Asimetric_TSP" -I"/home/prog/workspace/Asimetric_TSP/io" -I"/home/prog/workspace/Asimetric_TSP/solver" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


