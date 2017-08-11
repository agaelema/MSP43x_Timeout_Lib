################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/Timeout Lib - F5529 - Example 01 - ms - driverlib - v2.80" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/Timeout Lib - F5529 - Example 01 - ms - driverlib - v2.80/driverlib/MSP430F5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power="none" --define=DEPRECATED --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer_timeout.obj: ../timer_timeout.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/Timeout Lib - F5529 - Example 01 - ms - driverlib - v2.80" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/Timeout Lib - F5529 - Example 01 - ms - driverlib - v2.80/driverlib/MSP430F5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power="none" --define=DEPRECATED --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="timer_timeout.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer_timeout_setup.obj: ../timer_timeout_setup.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/Timeout Lib - F5529 - Example 01 - ms - driverlib - v2.80" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/Timeout Lib - F5529 - Example 01 - ms - driverlib - v2.80/driverlib/MSP430F5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power="none" --define=DEPRECATED --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="timer_timeout_setup.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


