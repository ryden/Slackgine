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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/vertex.o \
	${OBJECTDIR}/strategies/default.o \
	${OBJECTDIR}/strategies/render_strategy.o \
	${OBJECTDIR}/renderers/opengl3/opengl3.o \
	${OBJECTDIR}/geometry.o \
	${OBJECTDIR}/renderers/opengl3/renderer.o \
	${OBJECTDIR}/mesh.o \
	${OBJECTDIR}/renderers/opengl3/program.o \
	${OBJECTDIR}/morph.o \
	${OBJECTDIR}/renderers/opengl3/geometry.o \
	${OBJECTDIR}/renderers/opengl3/shader.o \
	${OBJECTDIR}/pose.o \
	${OBJECTDIR}/renderers/opengl3/texture.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librenderer.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librenderer.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librenderer.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librenderer.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librenderer.a

${OBJECTDIR}/vertex.o: vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/vertex.o vertex.cpp

${OBJECTDIR}/strategies/default.o: strategies/default.cpp 
	${MKDIR} -p ${OBJECTDIR}/strategies
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/strategies/default.o strategies/default.cpp

${OBJECTDIR}/strategies/render_strategy.o: strategies/render_strategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/strategies
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/strategies/render_strategy.o strategies/render_strategy.cpp

${OBJECTDIR}/renderers/opengl3/opengl3.o: renderers/opengl3/opengl3.cpp 
	${MKDIR} -p ${OBJECTDIR}/renderers/opengl3
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/renderers/opengl3/opengl3.o renderers/opengl3/opengl3.cpp

${OBJECTDIR}/geometry.o: geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/geometry.o geometry.cpp

${OBJECTDIR}/renderers/opengl3/renderer.o: renderers/opengl3/renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/renderers/opengl3
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/renderers/opengl3/renderer.o renderers/opengl3/renderer.cpp

${OBJECTDIR}/mesh.o: mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/mesh.o mesh.cpp

${OBJECTDIR}/renderers/opengl3/program.o: renderers/opengl3/program.cpp 
	${MKDIR} -p ${OBJECTDIR}/renderers/opengl3
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/renderers/opengl3/program.o renderers/opengl3/program.cpp

${OBJECTDIR}/morph.o: morph.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/morph.o morph.cpp

${OBJECTDIR}/renderers/opengl3/geometry.o: renderers/opengl3/geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/renderers/opengl3
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/renderers/opengl3/geometry.o renderers/opengl3/geometry.cpp

${OBJECTDIR}/renderers/opengl3/shader.o: renderers/opengl3/shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/renderers/opengl3
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/renderers/opengl3/shader.o renderers/opengl3/shader.cpp

${OBJECTDIR}/pose.o: pose.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/pose.o pose.cpp

${OBJECTDIR}/renderers/opengl3/texture.o: renderers/opengl3/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/renderers/opengl3
	${RM} $@.d
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/renderers/opengl3/texture.o renderers/opengl3/texture.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librenderer.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
