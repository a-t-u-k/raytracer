################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../objTester/list.cpp \
../objTester/objLoader.cpp \
../objTester/obj_parser.cpp \
../objTester/string_extra.cpp 

OBJS += \
./objTester/list.o \
./objTester/objLoader.o \
./objTester/obj_parser.o \
./objTester/string_extra.o 

CPP_DEPS += \
./objTester/list.d \
./objTester/objLoader.d \
./objTester/obj_parser.d \
./objTester/string_extra.d 


# Each subdirectory must supply rules for building sources it contributes
objTester/%.o: ../objTester/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_30,code=sm_30 -m64 -odir "objTester" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 --compile -m64  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


