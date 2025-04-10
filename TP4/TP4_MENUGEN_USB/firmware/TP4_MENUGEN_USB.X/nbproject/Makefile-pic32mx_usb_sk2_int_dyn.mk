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
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../src/app_gen.c ../src/Generateur.c ../src/GesPec12.c ../src/Mc32Debounce.c ../src/Mc32NVMUtil.c ../src/Mc32SpiUtil.c ../src/Mc32gestSPiDac.c ../src/MenuGen.c ../src/Mc32gest_SerComm.c ../../../../../../bsp/pic32mx_skes/bsp.c ../../../../../../bsp/pic32mx_skes/Mc32Delays.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1150414583/sys_devcon.o ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o ${OBJECTDIR}/_ext/1774247193/system_init.o ${OBJECTDIR}/_ext/1774247193/system_interrupt.o ${OBJECTDIR}/_ext/1774247193/system_exceptions.o ${OBJECTDIR}/_ext/1774247193/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app_gen.o ${OBJECTDIR}/_ext/1360937237/Generateur.o ${OBJECTDIR}/_ext/1360937237/GesPec12.o ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o ${OBJECTDIR}/_ext/1360937237/MenuGen.o ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o ${OBJECTDIR}/_ext/326400065/bsp.o ${OBJECTDIR}/_ext/326400065/Mc32Delays.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d ${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d ${OBJECTDIR}/_ext/1774247193/system_init.o.d ${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d ${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d ${OBJECTDIR}/_ext/1774247193/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app_gen.o.d ${OBJECTDIR}/_ext/1360937237/Generateur.o.d ${OBJECTDIR}/_ext/1360937237/GesPec12.o.d ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d ${OBJECTDIR}/_ext/1360937237/MenuGen.o.d ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d ${OBJECTDIR}/_ext/326400065/bsp.o.d ${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d ${OBJECTDIR}/_ext/692885480/usb_device.o.d ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1150414583/sys_devcon.o ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o ${OBJECTDIR}/_ext/1774247193/system_init.o ${OBJECTDIR}/_ext/1774247193/system_interrupt.o ${OBJECTDIR}/_ext/1774247193/system_exceptions.o ${OBJECTDIR}/_ext/1774247193/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app_gen.o ${OBJECTDIR}/_ext/1360937237/Generateur.o ${OBJECTDIR}/_ext/1360937237/GesPec12.o ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o ${OBJECTDIR}/_ext/1360937237/MenuGen.o ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o ${OBJECTDIR}/_ext/326400065/bsp.o ${OBJECTDIR}/_ext/326400065/Mc32Delays.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../src/app_gen.c ../src/Generateur.c ../src/GesPec12.c ../src/Mc32Debounce.c ../src/Mc32NVMUtil.c ../src/Mc32SpiUtil.c ../src/Mc32gestSPiDac.c ../src/MenuGen.c ../src/Mc32gest_SerComm.c ../../../../../../bsp/pic32mx_skes/bsp.c ../../../../../../bsp/pic32mx_skes/Mc32Delays.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c



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
${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/aad63f7fd2e9c724ec7e83249de379a96c3759ac .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1944736928" 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/1944736928/drv_tmr_static.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_static.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/9f51e62cccf7e0777c148682e5cc354e6a29ca03 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1944736928" 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o.d" -o ${OBJECTDIR}/_ext/1944736928/drv_tmr_mapping.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/driver/tmr/src/drv_tmr_mapping.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/f9165fa6e62ffbe6fa8c02187531c15e2a4d6439 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/102310384" 
	@${RM} ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/102310384/sys_clk_pic32mx.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1150414583/sys_devcon.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/14cba951af955942164d87ce12df958e80beb8ff .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1150414583" 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1150414583/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1150414583/sys_devcon.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/8b9abfbea89fb702892378222a1f9a1d9d80010 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1150414583" 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1150414583/sys_devcon_pic32mx.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956551008/sys_ports_static.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/bbcae40ca0afc20dd0d82935129b2b4f0f125b65 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1956551008" 
	@${RM} ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1956551008/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1956551008/sys_ports_static.o ../src/system_config/pic32mx_usb_sk2_int_dyn/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_init.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/e2951b5956baf932a6446a38b56bd383ec0d6ef3 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_init.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_init.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_init.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_interrupt.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/c8b6d30942a6f973162ba68e6c80dfd2c48f5e3f .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_interrupt.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_interrupt.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_exceptions.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/e62f02d0a2fda95f378698f163a622f95fbe3cac .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_exceptions.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_exceptions.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1774247193/system_tasks.o: ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/396b405713aa4059a86336de631bb40c0e91866f .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1774247193" 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1774247193/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1774247193/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1774247193/system_tasks.o ../src/system_config/pic32mx_usb_sk2_int_dyn/system_tasks.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/895620d99ca1e5ca101093985fe2ed1e2975d4b4 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/a099ea2425d240f50d5bba2ce37d129ada41b523 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app_gen.o: ../src/app_gen.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/b43283263b4dd8a6e72d9799981ebadbeed4b253 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_gen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_gen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_gen.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_gen.o ../src/app_gen.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Generateur.o: ../src/Generateur.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/47f86dd487ba16354b5d4527df7f409046f44eb9 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Generateur.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Generateur.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Generateur.o.d" -o ${OBJECTDIR}/_ext/1360937237/Generateur.o ../src/Generateur.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/GesPec12.o: ../src/GesPec12.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/b6c870768d64f8bf8ac31e23a2c5f0bd93724203 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/GesPec12.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/GesPec12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/GesPec12.o.d" -o ${OBJECTDIR}/_ext/1360937237/GesPec12.o ../src/GesPec12.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o: ../src/Mc32Debounce.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/f22501337c1468bde96161cfc94ccdcc1116cd93 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32Debounce.o ../src/Mc32Debounce.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o: ../src/Mc32NVMUtil.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/3b5e09727137162f16583ae8b84907d89198ac88 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32NVMUtil.o ../src/Mc32NVMUtil.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o: ../src/Mc32SpiUtil.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/556cd26ca9912f5cdb2ed69b2a8aa797e682a607 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ../src/Mc32SpiUtil.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o: ../src/Mc32gestSPiDac.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/9616ee8d3f506620847f7dfbb9a73b53933ed559 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gestSPiDac.o ../src/Mc32gestSPiDac.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/MenuGen.o: ../src/MenuGen.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/e5be2f23b73451a1c63f01acab282b4e156534cd .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MenuGen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MenuGen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/MenuGen.o.d" -o ${OBJECTDIR}/_ext/1360937237/MenuGen.o ../src/MenuGen.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o: ../src/Mc32gest_SerComm.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/4153d923043c0ae66fa6f73c9a25b0192b19ae37 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32gest_SerComm.o ../src/Mc32gest_SerComm.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/bsp.o: ../../../../../../bsp/pic32mx_skes/bsp.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/4c0fc9919b77d88a429ddd218d207d56e1063503 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/bsp.o.d" -o ${OBJECTDIR}/_ext/326400065/bsp.o ../../../../../../bsp/pic32mx_skes/bsp.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32Delays.o: ../../../../../../bsp/pic32mx_skes/Mc32Delays.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/6121d8d35a97a5edf283136df672438a3d5512ad .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32Delays.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32Delays.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32Delays.o ../../../../../../bsp/pic32mx_skes/Mc32Delays.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/4f2e7291d3d2a21485d815e0a9efb0641f5345cc .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdc.o ../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/72442079a6f1f928018544e8c98841197444e868 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverAdcAlt.o ../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o: ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/704c82618ef2c2fcb48f4dc44c009a8a044d989e .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32DriverLcd.o ../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o: ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/6c87a814ac4e50d35bf3905db414a3dd71b35e4a .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/326400065" 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o.d" -o ${OBJECTDIR}/_ext/326400065/Mc32CoreTimer.o ../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/8c36d71b84b1b1320d1e9ad67eed4d5e2b74d0ea .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/cd24964e70ff0773e6bba58915ce682466b594f .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/384130928a0ac4a8efaa96901df2af8444124823 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/711155467" 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/f21f83019abd0cee58abea005c4b29aee9907ba1 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/9224a897813979fd8c433d8217df53d4282d0758 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c  .generated_files/flags/pic32mx_usb_sk2_int_dyn/4a9adb7243482b13b89ea2d171c366394840a2d5 .generated_files/flags/pic32mx_usb_sk2_int_dyn/9482caba2dc1e17ca639a65609d3577e06590893
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../../../../../../bsp/pic32mx_usb_sk2" -I"/system_config/pic32mx_usb_sk2_int_dyn" -I"/pic32mx_usb_sk2_int_dyn" -I"/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"/system_config/pic32mx_usb_sk2_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx_usb_sk2_int_dyn" -I"../src/pic32mx_usb_sk2_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx_usb_sk2_int_dyn/framework" -I"../../../../../../bsp/pic32mx_skes" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TP4_MENUGEN_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -DXPRJ_pic32mx_usb_sk2_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
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
