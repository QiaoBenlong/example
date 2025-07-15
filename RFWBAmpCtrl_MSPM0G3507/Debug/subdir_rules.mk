################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2001/ccs/tools/compiler/ti-cgt-armllvm_4.0.1.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug" -I"C:/ti/mspm0_sdk_1_30_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_1_30_00_03/source" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/User" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-697236833: ../RFWBAmpCtrl_MSPM0G3507.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.19.0/sysconfig_cli.bat" --script "C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/RFWBAmpCtrl_MSPM0G3507.syscfg" -o "syscfg" -s "C:/ti/mspm0_sdk_1_30_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/device_linker.cmd: build-697236833 ../RFWBAmpCtrl_MSPM0G3507.syscfg
syscfg/device.opt: build-697236833
syscfg/device.cmd.genlibs: build-697236833
syscfg/ti_msp_dl_config.c: build-697236833
syscfg/ti_msp_dl_config.h: build-697236833
syscfg/Event.dot: build-697236833
syscfg: build-697236833
C:/ti/mspm0_sdk_1_30_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c: build-697236833

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2001/ccs/tools/compiler/ti-cgt-armllvm_4.0.1.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug" -I"C:/ti/mspm0_sdk_1_30_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_1_30_00_03/source" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/User" -gdwarf-3 -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug/syscfg"  @"syscfg/device.opt" -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_1_30_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2001/ccs/tools/compiler/ti-cgt-armllvm_4.0.1.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug" -I"C:/ti/mspm0_sdk_1_30_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_1_30_00_03/source" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/User" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/19351/workspace_ccstheia/RFWBAmpCtrl_MSPM0G3507/Debug/syscfg"  @"syscfg/device.opt" -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


