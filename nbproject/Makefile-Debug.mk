#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/I2Cdev.o \
	${OBJECTDIR}/IMU.o \
	${OBJECTDIR}/MPU6050.o \
	${OBJECTDIR}/Motors.o \
	${OBJECTDIR}/RC.o \
	${OBJECTDIR}/parallel.o \
	${OBJECTDIR}/welcome.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lpthread
CXXFLAGS=-lpthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../Raspberry_pi_projects/control_law/dist/Debug/GNU-Linux-x86/libcontrol_law.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/threads

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/threads: ../Raspberry_pi_projects/control_law/dist/Debug/GNU-Linux-x86/libcontrol_law.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/threads: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/threads ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/I2Cdev.o: I2Cdev.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Raspberry_pi_projects/control_law -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/I2Cdev.o I2Cdev.cpp

${OBJECTDIR}/IMU.o: IMU.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Raspberry_pi_projects/control_law -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IMU.o IMU.cpp

${OBJECTDIR}/MPU6050.o: MPU6050.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Raspberry_pi_projects/control_law -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MPU6050.o MPU6050.cpp

${OBJECTDIR}/Motors.o: Motors.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Raspberry_pi_projects/control_law -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Motors.o Motors.cpp

${OBJECTDIR}/RC.o: RC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Raspberry_pi_projects/control_law -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RC.o RC.cpp

${OBJECTDIR}/parallel.o: parallel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Raspberry_pi_projects/control_law -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parallel.o parallel.cpp

${OBJECTDIR}/welcome.o: welcome.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Raspberry_pi_projects/control_law -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/welcome.o welcome.cc

# Subprojects
.build-subprojects:
	cd ../Raspberry_pi_projects/control_law && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/threads

# Subprojects
.clean-subprojects:
	cd ../Raspberry_pi_projects/control_law && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
