################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../common/lexers/stringstream.cpp \
../common/lexers/tokenstream.cpp 

OBJS += \
./common/lexers/stringstream.o \
./common/lexers/tokenstream.o 

CPP_DEPS += \
./common/lexers/stringstream.d \
./common/lexers/tokenstream.d 


# Each subdirectory must supply rules for building sources it contributes
common/lexers/%.o: ../common/lexers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_30,code=sm_30 -m64 -odir "common/lexers" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 --compile -m64  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


