################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
USB_config/UsbIsr.obj: ../USB_config/UsbIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/a0227507/workspace_v8/chord_keyboard/USB_config" --include_path="C:/Users/a0227507/workspace_v8/chord_keyboard/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/a0227507/workspace_v8/chord_keyboard" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="USB_config/UsbIsr.d_raw" --obj_directory="USB_config" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

USB_config/descriptors.obj: ../USB_config/descriptors.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/a0227507/workspace_v8/chord_keyboard/USB_config" --include_path="C:/Users/a0227507/workspace_v8/chord_keyboard/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/a0227507/workspace_v8/chord_keyboard" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="USB_config/descriptors.d_raw" --obj_directory="USB_config" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


