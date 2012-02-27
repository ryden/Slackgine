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
CND_CONF=Profiling
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/memory_leak_detector.o \
	${OBJECTDIR}/memory.o \
	${OBJECTDIR}/pixmap.o \
	${OBJECTDIR}/thread.o \
	${OBJECTDIR}/thread_condition.o \
	${OBJECTDIR}/log.o \
	${OBJECTDIR}/mutex.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-ansi -pipe -pg
CXXFLAGS=-ansi -pipe -pg

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libshared.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libshared.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libshared.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libshared.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libshared.a

${OBJECTDIR}/memory_leak_detector.o: memory_leak_detector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DDEBUG_VERY_VERBOSE -DDETECT_MEMORY_LEAKS -DPROFILING -I. -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory_leak_detector.o memory_leak_detector.cpp

${OBJECTDIR}/memory.o: memory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DDEBUG_VERY_VERBOSE -DDETECT_MEMORY_LEAKS -DPROFILING -I. -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory.o memory.cpp

${OBJECTDIR}/pixmap.o: pixmap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DDEBUG_VERY_VERBOSE -DDETECT_MEMORY_LEAKS -DPROFILING -I. -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/pixmap.o pixmap.cpp

${OBJECTDIR}/thread.o: thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DDEBUG_VERY_VERBOSE -DDETECT_MEMORY_LEAKS -DPROFILING -I. -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/thread.o thread.cpp

${OBJECTDIR}/thread_condition.o: thread_condition.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DDEBUG_VERY_VERBOSE -DDETECT_MEMORY_LEAKS -DPROFILING -I. -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/thread_condition.o thread_condition.cpp

${OBJECTDIR}/log.o: log.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DDEBUG_VERY_VERBOSE -DDETECT_MEMORY_LEAKS -DPROFILING -I. -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/log.o log.cpp

${OBJECTDIR}/mutex.o: mutex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DDEBUG_VERY_VERBOSE -DDETECT_MEMORY_LEAKS -DPROFILING -I. -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/mutex.o mutex.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libshared.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc