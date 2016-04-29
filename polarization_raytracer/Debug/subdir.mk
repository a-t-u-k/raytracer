################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../objects.cpp \
../z_pol.cpp 

OBJ_SRCS += \
../bunny.obj \
../hollow_cylinder_360.obj \
../hollow_sphere_128.obj \
../sphere_64x64.obj \
../wineglassgoblet.obj 

CU_SRCS += \
../accel.cu 

CU_DEPS += \
./accel.d 

OBJS += \
./accel.o \
./objects.o \
./z_pol.o 

CPP_DEPS += \
./objects.d \
./z_pol.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_30,code=sm_30 -m64 -odir "." -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 --compile --relocatable-device-code=false -gencode arch=compute_30,code=compute_30 -gencode arch=compute_30,code=sm_30 -m64  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_30,code=sm_30 -m64 -odir "." -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -std=c++11 --compile -m64  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


