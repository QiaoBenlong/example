################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/git/example/RFWBAmpCtrl_MSPM0G3507 copy 8" -I"D:/git/example/RFWBAmpCtrl_MSPM0G3507 copy 8/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -I"D:/git/example/RFWBAmpCtrl_MSPM0G3507 copy 8/User" -gdwarf-3 -MMD -MP -MF"User/$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/git/example/RFWBAmpCtrl_MSPM0G3507 copy 8/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


