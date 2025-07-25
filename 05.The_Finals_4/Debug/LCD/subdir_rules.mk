################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
LCD/%.obj: ../LCD/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccs2020/ccs/ccs_base/msp430/include" --include_path="D:/git/example/05.The_Finals_4/Base" --include_path="D:/git/example/05.The_Finals_4/Measure/include" --include_path="D:/git/example/05.The_Finals_4/Measure/source" --include_path="D:/git/example/05.The_Finals_4/LCD" --include_path="D:/git/example/05.The_Finals_4/Measure" --include_path="D:/git/example/05.The_Finals_4/Menu" --include_path="D:/git/example/05.The_Finals_4" --include_path="C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="LCD/$(basename $(<F)).d_raw" --obj_directory="LCD" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


