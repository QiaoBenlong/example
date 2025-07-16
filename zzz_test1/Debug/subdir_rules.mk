################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/DSP/Include" -I"D:/git/example/zzz_test1" -I"D:/git/example/zzz_test1/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -I"D:/git/example/zzz_test1/User" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/git/example/zzz_test1/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-464648033: ../zzz_test1.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.22.0/sysconfig_cli.bat" --script "D:/git/example/zzz_test1/zzz_test1.syscfg" -o "syscfg" -s "C:/ti/mspm0_sdk_2_03_00_07/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/device_linker.cmd: build-464648033 ../zzz_test1.syscfg
syscfg/device.opt: build-464648033
syscfg/device.cmd.genlibs: build-464648033
syscfg/ti_msp_dl_config.c: build-464648033
syscfg/ti_msp_dl_config.h: build-464648033
syscfg/Event.dot: build-464648033
syscfg: build-464648033

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/DSP/Include" -I"D:/git/example/zzz_test1" -I"D:/git/example/zzz_test1/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -I"D:/git/example/zzz_test1/User" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/git/example/zzz_test1/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_03_00_07/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/DSP/Include" -I"D:/git/example/zzz_test1" -I"D:/git/example/zzz_test1/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -I"D:/git/example/zzz_test1/User" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/git/example/zzz_test1/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


