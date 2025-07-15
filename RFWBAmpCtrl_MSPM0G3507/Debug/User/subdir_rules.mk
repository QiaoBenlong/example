################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2001/ccs/tools/compiler/ti-cgt-armllvm_4.0.1.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug" -I"C:/ti/mspm0_sdk_1_30_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_1_30_00_03/source" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/User" -gdwarf-3 -MMD -MP -MF"User/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug/syscfg"  @"syscfg/device.opt" -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


