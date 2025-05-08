#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-pic32mx_usb_sk2_int_dyn.mk)" "nbproject/Makefile-local-pic32mx_usb_sk2_int_dyn.mk"
include nbproject/Makefile-local-pic32mx_usb_sk2_int_dyn.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mx_usb_sk2_int_dyn
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../src/app_gen.c ../src/Generateur.c ../src/GesPec12.c ../src/Mc32Debounce.c ../src/Mc32NVMUtil.c ../src/Mc32SpiUtil.c ../src/Mc32gestSPiDac.c ../src/MenuGen.c ../src/Mc32gest_SerComm.c ../../../../../../bsp/pic32mx_skes/bsp.c ../../../../../../bsp/pic32mx_skes/Mc32Delays.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c ../src/Mc32_I2cUtilCCS.c ../src/Mc32gest_I2c_Eeprom.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1150414583/sys_devcon.o ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o ${OBJECTDIR}/_ext/1774247193/system_init.o ${OBJECTDIR}/_ext/1774247193/system_interrupt.o ${OBJECTDIR}/_ext/1774247193/system_exceptions.o ${OBJECTDIR}/_ext/1774247193/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app_gen.o ${OBJECTDIR}/_ext/1360937237/Generateur.o ${OBJECTDIR}/_ext/1360937237/GesPec12.o ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o ${OBJECTDIR}/_ext/1360937237/MenuGen.o ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o ${OBJECTDIR}/_ext/326400065/bsp.o ${OBJECTDIR}/_ext/326400065/Mc32Delays.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d ${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d ${OBJECTDIR}/_ext/1774247193/system_init.o.d ${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d ${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d ${OBJECTDIR}/_ext/1774247193/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app_gen.o.d ${OBJECTDIR}/_ext/1360937237/Generateur.o.d ${OBJECTDIR}/_ext/1360937237/GesPec12.o.d ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d ${OBJECTDIR}/_ext/1360937237/MenuGen.o.d ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d ${OBJECTDIR}/_ext/326400065/bsp.o.d ${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d ${OBJECTDIR}/_ext/692885480/usb_device.o.d ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o.d ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1150414583/sys_devcon.o ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o ${OBJECTDIR}/_ext/1774247193/system_init.o ${OBJECTDIR}/_ext/1774247193/system_interrupt.o ${OBJECTDIR}/_ext/1774247193/system_exceptions.o ${OBJECTDIR}/_ext/1774247193/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app_gen.o ${OBJECTDIR}/_ext/1360937237/Generateur.o ${OBJECTDIR}/_ext/1360937237/GesPec12.o ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o ${OBJECTDIR}/_ext/1360937237/MenuGen.o ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o ${OBJECTDIR}/_ext/326400065/bsp.o ${OBJECTDIR}/_ext/326400065/Mc32Delays.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../src/app_gen.c ../src/Generateur.c ../src/GesPec12.c ../src/Mc32Debounce.c ../src/Mc32NVMUtil.c ../src/Mc32SpiUtil.c ../src/Mc32gestSPiDac.c ../src/MenuGen.c ../src/Mc32gest_SerComm.c ../../../../../../bsp/pic32mx_skes/bsp.c ../../../../../../bsp/pic32mx_skes/Mc32Delays.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c ../src/Mc32_I2cUtilCCS.c ../src/Mc32gest_I2c_Eeprom.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-pic32mx_usb_sk2_int_dyn.mk dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/af543f2af4bab849901b35c893cfe7daa87566e3 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1944736928" 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/c678d0c93af44c8c8d4f4c5cffb11b8c617ace4c .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1944736928" 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d" -o ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/f2dce40947e3c09fbe9d8263e9bd00234f09e529 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/102310384" 
	@${RM} ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1150414583/sys_devcon.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/96e8c739d12d39441bc2df0c554c7454dd21e810 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1150414583" 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1150414583/sys_devcon.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/2e9963ca06acc0ed39366fe8ed1a946abcb5dbf9 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1150414583" 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956551008/sys_ports_static.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/adfc6ab34bdf4fe81e473a908401cb0490af556e .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1956551008" 
	@${RM} ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_init.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/81976732500300d616cb8ad03c69e4e46ddd2b36 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_init.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_init.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_interrupt.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/b17c770cc8fae663b514839b0efecb7a38fa36d5 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_interrupt.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_exceptions.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/ad8ee5449fa1028dc1442ced943691ee7c139ed2 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_exceptions.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_tasks.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/3f98beb45126a4905d2f4068c2e87a3b76652f07 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_tasks.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/d11aeb49dc1d538a156eef847d258508e9186581 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/30febd3caa96faf0d442aad4c78c56b3d569fe82 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app_gen.o: ../src/app_gen.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/7d573ffeaa205b96fd43ca49b2771b5f2e0d382c .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_gen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_gen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_gen.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_gen.o ../src/app_gen.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Generateur.o: ../src/Generateur.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/54128a734a842f8a6e7a66e1f7c249a0f05f4c82 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Generateur.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Generateur.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Generateur.o.d" -o ${OBJECTDIR}/_ext/1360937237/Generateur.o ../src/Generateur.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/GesPec12.o: ../src/GesPec12.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/b905a534dad443aad8432d81c9218cbbb7fe967f .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/GesPec12.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/GesPec12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/GesPec12.o.d" -o ${OBJECTDIR}/_ext/1360937237/GesPec12.o ../src/GesPec12.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o: ../src/Mc32Debounce.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a2601ef8682c83f2abeac53af831dcdf621420e0 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o ../src/Mc32Debounce.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o: ../src/Mc32NVMUtil.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/633310d66acb3eb6b3048d055418a527b3ca84ac .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o ../src/Mc32NVMUtil.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o: ../src/Mc32SpiUtil.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/f3db1b2b6a18e7a34752ec1a17e6477a0b3ad929 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ../src/Mc32SpiUtil.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o: ../src/Mc32gestSPiDac.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/f67e515116c864311686def3fb54a4f648407eda .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o ../src/Mc32gestSPiDac.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/MenuGen.o: ../src/MenuGen.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/fe422cf821106aafdfe56e5fd6b6691fd0378de9 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MenuGen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MenuGen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/MenuGen.o.d" -o ${OBJECTDIR}/_ext/1360937237/MenuGen.o ../src/MenuGen.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o: ../src/Mc32gest_SerComm.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/1972b630106a444ce49aa087e3990293bda0ff55 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o ../src/Mc32gest_SerComm.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/bsp.o: ../../../../../../bsp/pic32mx_skes/bsp.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/592cf6ad03c22e184fb0d2e6cede5e76bd1202ca .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/bsp.o.d" -o ${OBJECTDIR}/_ext/326400065/bsp.o ../../../../../../bsp/pic32mx_skes/bsp.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32Delays.o: ../../../../../../bsp/pic32mx_skes/Mc32Delays.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/c06dba355ef5276a95a16d9d7a3307cf07d774e9 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32Delays.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32Delays.o ../../../../../../bsp/pic32mx_skes/Mc32Delays.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/dd727db7240c6fca9cfbc68d7cd6b4e21e193e55 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/8975c4432e9fe45a2fc3ab4c5d4de71dbb6a3149 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/355809b8d3d8ac97efe9c86822bf623f075ea8b7 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o: ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/e888b3194a07e87c1cde4f152bd260dfdc8065ac .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/495978c4dff137d7b0cea09c2b7eed6c19b7bc71 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/904e033c164bb50642f952e404aac30f246321bf .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a4df688e1758a8682a836308ec7ef94c3d38f592 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/711155467" 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/cbc3282082e2cb627bbbd911ca9a8d64d2cc0de3 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a2fae9e8b92f88f7eea885c229cbb127c6195230 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/31f62f21682a82c51f79f017103cf83bcb199268 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o: ../src/Mc32_I2cUtilCCS.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/17b91f201ee3609d21a4a2bb53b87290b4ec2592 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o ../src/Mc32_I2cUtilCCS.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o: ../src/Mc32gest_I2c_Eeprom.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/2fb4e5a39e81a582325ca9a54510a32794570f6f .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o ../src/Mc32gest_I2c_Eeprom.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/1de932b6ded4e8807071b667b3f233fa886a85bf .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1944736928" 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/eb54fda8d063823aed22d15a8469df9034c48f6f .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1944736928" 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d" -o ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/f172859e94343b5ef63323078740fb7fa9db810c .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/102310384" 
	@${RM} ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1150414583/sys_devcon.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/50b1d174200bb7682f4be268602acd46074346ce .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1150414583" 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1150414583/sys_devcon.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/67566e73dcf927fc1da22c2b35f71031fbbab1c1 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1150414583" 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956551008/sys_ports_static.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/4ff9b1d38b5a448551c9ab73749c3b1eca572d50 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1956551008" 
	@${RM} ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_init.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/397eecf73a07715ee393c180548daac0d6e5f030 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_init.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_init.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_interrupt.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a45365d4eb83fb22b002d1d6a441c5e453913116 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_interrupt.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_exceptions.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/b527b787c561ee91422a515f0566199f355765bb .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_exceptions.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_tasks.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/b4a4fffca22717797eb5df75b57bfabe78ea912c .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_tasks.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/208fabf4f2b89c44a346fd2bf2a228a7474e6cd2 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/800b3c7b867034a3fd4b3abbb9ead9ffb1d923bf .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app_gen.o: ../src/app_gen.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/408af08e70223894462007b661dc2f7e71bfd039 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_gen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_gen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_gen.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_gen.o ../src/app_gen.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Generateur.o: ../src/Generateur.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/cc4247278f91ea9ded23c3114750a47b1db7ded1 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Generateur.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Generateur.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Generateur.o.d" -o ${OBJECTDIR}/_ext/1360937237/Generateur.o ../src/Generateur.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/GesPec12.o: ../src/GesPec12.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/925769119d5f46bfd5b63c8ed0ab20d3d09bdddb .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/GesPec12.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/GesPec12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/GesPec12.o.d" -o ${OBJECTDIR}/_ext/1360937237/GesPec12.o ../src/GesPec12.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o: ../src/Mc32Debounce.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/da5b0bffed113de456bccf5690906cbe5d6d617f .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o ../src/Mc32Debounce.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o: ../src/Mc32NVMUtil.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/2dc130dafb5bdc61656b0566259b8cb63c3e591e .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o ../src/Mc32NVMUtil.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o: ../src/Mc32SpiUtil.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/839655f1aef1733f76df7c816b82ae0c50576c0b .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ../src/Mc32SpiUtil.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o: ../src/Mc32gestSPiDac.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/bc448f72ad510c20a0d3cfe7d0094f4f06c223b5 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o ../src/Mc32gestSPiDac.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/MenuGen.o: ../src/MenuGen.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/afbad83648e4d7c4890ecc1f34586e9dcff51eb2 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MenuGen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MenuGen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/MenuGen.o.d" -o ${OBJECTDIR}/_ext/1360937237/MenuGen.o ../src/MenuGen.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o: ../src/Mc32gest_SerComm.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/5673b99011888866578c37bbb930330eb112e233 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o ../src/Mc32gest_SerComm.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/bsp.o: ../../../../../../bsp/pic32mx_skes/bsp.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/3cf765003e133b699b52359bf97fbed83c750028 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/bsp.o.d" -o ${OBJECTDIR}/_ext/326400065/bsp.o ../../../../../../bsp/pic32mx_skes/bsp.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32Delays.o: ../../../../../../bsp/pic32mx_skes/Mc32Delays.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a3d90779b3ef44a7f12ad200b36c1d3ead51d3b6 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32Delays.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32Delays.o ../../../../../../bsp/pic32mx_skes/Mc32Delays.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a752fd9f8fb3853a46d92abac98470cf1362499c .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/2c874972e6a538dc28aad2448b49491f5e02b175 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/c7ea664539c3130802c210123ef72a863a30063e .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o: ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/6d6bf4f63ad8ba68211bc7bd75a28e8f0c7393da .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/df772a44c7f64405474d8e4308805ef6d680ea15 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/dfded54541eb803b83bdff96d9b33712c654dffd .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/eff0a2aaacbba575a5249c2a0cab791714865836 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/711155467" 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/9512a242708ce31d7ddad57ddacaa2a76ea73075 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a5944ec2f663e90b95cf450aa6df2d1d0243ba12 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/acef3161ca7192c5d396794a5a687cdc023001b .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o: ../src/Mc32_I2cUtilCCS.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/10b17443519077210abb27691af60f060a590ae3 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cUtilCCS.o ../src/Mc32_I2cUtilCCS.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o: ../src/Mc32gest_I2c_Eeprom.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/70bc9c1000456b4e19caed0511784cf38ee50562 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gest_I2c_Eeprom.o ../src/Mc32gest_I2c_Eeprom.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mx_usb_sk2_int_dyn
	${RM} -r dist/pic32mx_usb_sk2_int_dyn

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
