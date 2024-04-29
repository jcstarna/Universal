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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/TempUAA.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/TempUAA.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/TempUAA.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/TempUAA.o

# Source Files
SOURCEFILES=../src/TempUAA.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_CC="C:\Program Files (x86)\PICC\CCSCON.exe"
MP_LD="C:\Program Files (x86)\PICC\CCSCON.exe"
sourceline.device=sourceline="\#device PIC12F675"
sourceline.xccompat=sourceline="\#device ANSI" sourceline="\#device PASS_STRINGS=IN_RAM" sourceline="\#device CONST=READ_ONLY" sourceline="\#case" sourceline="\#TYPE SIGNED" sourceline="\#type INT=16, LONG=32"
sourceline.gcccompat=sourceline="\#device ANSI" sourceline="\#device PASS_STRINGS=IN_RAM" sourceline="\#device CONST=READ_ONLY" sourceline="\#case" sourceline="\#TYPE SIGNED"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/TempUAA.o: ../src/TempUAA.c  nbproject/Makefile-${CND_CONF}.mk 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
ifeq (2,1) 
	${MKDIR} ${DISTDIR} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1360937237"  ../src/TempUAA.c +FM +DF +CC #__DEBUG=1 +ICD +Y=9 +EA I+="C:\Program Files (x86)\PICC\Devices" I+="C:\Program Files (x86)\PICC\Drivers" +DF +LN +T +A +M +J +Z -P #__12F675=1 
	@mv ${OBJECTDIR}/_ext/1360937237/TempUAA.cof "${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1360937237/TempUAA.hex "${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1360937237"" ../src/TempUAA.c +EXPORT +FM +DF +CC #__DEBUG=1 +ICD +Y=9 +EA I+="C:\Program Files (x86)\PICC\Devices" I+="C:\Program Files (x86)\PICC\Drivers" +DF +LN +T +A +M +J +Z -P #__12F675=1 +EXPORTD="${OBJECTDIR}/_ext/1360937237"  
	
endif 
	
else
${OBJECTDIR}/_ext/1360937237/TempUAA.o: ../src/TempUAA.c  nbproject/Makefile-${CND_CONF}.mk 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
ifeq (2,1) 
	${MKDIR} ${DISTDIR} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1360937237"  ../src/TempUAA.c +FM +DF +CC +Y=9 +EA I+="C:\Program Files (x86)\PICC\Devices" I+="C:\Program Files (x86)\PICC\Drivers" +DF +LN +T +A +M +J +Z -P #__12F675=1 
	@mv ${OBJECTDIR}/_ext/1360937237/TempUAA.cof "${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1360937237/TempUAA.hex "${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1360937237"" ../src/TempUAA.c +EXPORT +FM +DF +CC +Y=9 +EA I+="C:\Program Files (x86)\PICC\Devices" I+="C:\Program Files (x86)\PICC\Drivers" +DF +LN +T +A +M +J +Z -P #__12F675=1 +EXPORTD="${OBJECTDIR}/_ext/1360937237"  
	
endif 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	${MKDIR} ${DISTDIR} 
ifeq (2,1) 
	
else 
	${MP_LD}   out="${DISTDIR}"  +FM +DF +CC LINK=TempUAA.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/_ext/1360937237/TempUAA.o +Y=9 +EA I+="C:\Program Files (x86)\PICC\Devices" I+="C:\Program Files (x86)\PICC\Drivers" +DF +LN +T +A +M +J +Z -P
	
endif 
	
else
${DISTDIR}/TempUAA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	${MKDIR} ${DISTDIR} 
ifeq (2,1) 
	
else 
	${MP_LD}   out="${DISTDIR}"  +FM +DF +CC LINK=TempUAA.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/_ext/1360937237/TempUAA.o +Y=9 +EA I+="C:\Program Files (x86)\PICC\Devices" I+="C:\Program Files (x86)\PICC\Drivers" +DF +LN +T +A +M +J +Z -P
	
endif 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
