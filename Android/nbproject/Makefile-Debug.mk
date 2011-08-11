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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/278521276/program.o \
	${OBJECTDIR}/_ext/278521276/shader.o \
	${OBJECTDIR}/_ext/278521276/renderer.o \
	${OBJECTDIR}/jni/Slackgine.o \
	${OBJECTDIR}/jni/l3m.o \
	${OBJECTDIR}/jni/Renderer.o \
	${OBJECTDIR}/jni/STLiostream.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAndroid.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAndroid.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAndroid.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/278521276/program.o: ../renderer/renderers/AndroidGLES20/program.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/278521276
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/278521276/program.o ../renderer/renderers/AndroidGLES20/program.cpp

${OBJECTDIR}/_ext/278521276/shader.o: ../renderer/renderers/AndroidGLES20/shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/278521276
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/278521276/shader.o ../renderer/renderers/AndroidGLES20/shader.cpp

${OBJECTDIR}/_ext/278521276/renderer.o: ../renderer/renderers/AndroidGLES20/renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/278521276
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/278521276/renderer.o ../renderer/renderers/AndroidGLES20/renderer.cpp

${OBJECTDIR}/jni/Slackgine.o: jni/Slackgine.cpp 
	${MKDIR} -p ${OBJECTDIR}/jni
	${RM} $@.d
	$(COMPILE.cc) -g -I/soft/dev/android-ndk/platforms/android-8/arch-arm/usr/include -I.. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/jni/Slackgine.o jni/Slackgine.cpp

${OBJECTDIR}/jni/l3m.o: jni/l3m.cpp 
	${MKDIR} -p ${OBJECTDIR}/jni
	${RM} $@.d
	$(COMPILE.cc) -g -I/soft/dev/android-ndk/platforms/android-8/arch-arm/usr/include -I.. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/jni/l3m.o jni/l3m.cpp

${OBJECTDIR}/jni/Renderer.o: jni/Renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/jni
	${RM} $@.d
	$(COMPILE.cc) -g -I/soft/dev/android-ndk/platforms/android-8/arch-arm/usr/include -I.. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/jni/Renderer.o jni/Renderer.cpp

${OBJECTDIR}/jni/STLiostream.o: jni/STLiostream.cpp 
	${MKDIR} -p ${OBJECTDIR}/jni
	${RM} $@.d
	$(COMPILE.cc) -g -I/soft/dev/android-ndk/platforms/android-8/arch-arm/usr/include -I.. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/jni/STLiostream.o jni/STLiostream.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAndroid.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
