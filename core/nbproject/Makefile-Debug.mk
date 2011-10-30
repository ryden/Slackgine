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
	${OBJECTDIR}/model_renderer_factory.o \
	${OBJECTDIR}/shader.o \
	${OBJECTDIR}/world.o \
	${OBJECTDIR}/time.o \
	${OBJECTDIR}/shader_manager.o \
	${OBJECTDIR}/entity_components/scene.o \
	${OBJECTDIR}/program.o \
	${OBJECTDIR}/model_manager.o \
	${OBJECTDIR}/transformable.o \
	${OBJECTDIR}/texture_manager.o \
	${OBJECTDIR}/camera.o \
	${OBJECTDIR}/slackgine.o \
	${OBJECTDIR}/entity_components/model_renderer.o \
	${OBJECTDIR}/entity.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pipe -ansi
CXXFLAGS=-pipe -ansi

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore.a

${OBJECTDIR}/model_renderer_factory.o: model_renderer_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/model_renderer_factory.o model_renderer_factory.cpp

${OBJECTDIR}/shader.o: shader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/shader.o shader.cpp

${OBJECTDIR}/world.o: world.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/world.o world.cpp

${OBJECTDIR}/time.o: time.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/time.o time.cpp

${OBJECTDIR}/shader_manager.o: shader_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/shader_manager.o shader_manager.cpp

${OBJECTDIR}/entity_components/scene.o: entity_components/scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/entity_components
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/entity_components/scene.o entity_components/scene.cpp

${OBJECTDIR}/program.o: program.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/program.o program.cpp

${OBJECTDIR}/model_manager.o: model_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/model_manager.o model_manager.cpp

${OBJECTDIR}/transformable.o: transformable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/transformable.o transformable.cpp

${OBJECTDIR}/texture_manager.o: texture_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/texture_manager.o texture_manager.cpp

${OBJECTDIR}/camera.o: camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/camera.o camera.cpp

${OBJECTDIR}/slackgine.o: slackgine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/slackgine.o slackgine.cpp

${OBJECTDIR}/entity_components/model_renderer.o: entity_components/model_renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/entity_components
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/entity_components/model_renderer.o entity_components/model_renderer.cpp

${OBJECTDIR}/entity.o: entity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DUSE_THREADS -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/entity.o entity.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
