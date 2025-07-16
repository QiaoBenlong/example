################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS

GEN_OPTS__FLAG := @"syscfg/device.opt" 
GEN_CMDS__FLAG := -Wl,-l"syscfg/device_linker.cmd" 

ORDERED_OBJS += \
"./zzz_test1.o" \
"./syscfg/ti_msp_dl_config.o" \
"./startup_mspm0g350x_ticlang.o" \
"./User/BTN.o" \
"./User/Encoder.o" \
"./User/RGBLED.o" \
"./User/Tick.o" \
"./User/UserTask.o" \
"./User/UserUART.o" \
"./User/adc.o" \
$(GEN_CMDS__FLAG) \
-Wl,-ldevice.cmd.genlibs \
-Wl,-llibc.a \
-Wl,-l"C:/ti/mspm0_sdk_2_03_00_07/source/ti/driverlib/lib/ticlang/m0p/mspm0g1x0x_g3x0x/driverlib.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include User/subdir_vars.mk
-include subdir_rules.mk
-include User/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
zzz_test1.out 

EXE_OUTPUTS__QUOTED += \
"zzz_test1.out" 

BIN_OUTPUTS += \
zzz_test1.txt 

BIN_OUTPUTS__QUOTED += \
"zzz_test1.txt" 


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "zzz_test1.out" secondary-outputs

# Tool invocations
zzz_test1.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" @"syscfg/device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -D__MSPM0G3507__ -gdwarf-3 -Wl,-m"zzz_test1.map" -Wl,-i"C:/ti/mspm0_sdk_2_03_00_07/source" -Wl,-i"D:/git/example/zzz_test1/Debug/syscfg" -Wl,-i"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/lib" -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="zzz_test1_linkInfo.xml" -Wl,--rom_model -o "zzz_test1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

zzz_test1.txt: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmhex.exe" --memwidth=8 --romwidth=8 --diag_wrap=off --ti_txt -o "zzz_test1.txt" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "zzz_test1.o" "syscfg\ti_msp_dl_config.o" "startup_mspm0g350x_ticlang.o" "User\BTN.o" "User\Encoder.o" "User\RGBLED.o" "User\Tick.o" "User\UserTask.o" "User\UserUART.o" "User\adc.o" 
	-$(RM) "zzz_test1.d" "syscfg\ti_msp_dl_config.d" "startup_mspm0g350x_ticlang.d" "User\BTN.d" "User\Encoder.d" "User\RGBLED.d" "User\Tick.d" "User\UserTask.d" "User\UserUART.d" "User\adc.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

