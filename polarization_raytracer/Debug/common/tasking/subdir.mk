################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../common/tasking/taskscheduler_mic.cpp \
../common/tasking/taskscheduler_tbb.cpp \
../common/tasking/tasksys.cpp 

OBJS += \
./common/tasking/taskscheduler_mic.o \
./common/tasking/taskscheduler_tbb.o \
./common/tasking/tasksys.o 

CPP_DEPS += \
./common/tasking/taskscheduler_mic.d \
./common/tasking/taskscheduler_tbb.d \
./common/tasking/tasksys.d 


# Each subdirectory must supply rules for building sources it contributes
common/tasking/%.o: ../common/tasking/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_30,code=sm_30 -m64 -odir "common/tasking" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 --compile -m64  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


