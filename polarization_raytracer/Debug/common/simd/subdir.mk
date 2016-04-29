################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../common/simd/bool16_avx512.cpp \
../common/simd/sse.cpp 

OBJS += \
./common/simd/bool16_avx512.o \
./common/simd/sse.o 

CPP_DEPS += \
./common/simd/bool16_avx512.d \
./common/simd/sse.d 


# Each subdirectory must supply rules for building sources it contributes
common/simd/%.o: ../common/simd/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_30,code=sm_30 -m64 -odir "common/simd" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 --compile -m64  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


