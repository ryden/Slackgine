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
	${OBJECTDIR}/delete_unused.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/delete_unused_textures.o \
	${OBJECTDIR}/delete_duplicates.o \
	${OBJECTDIR}/clean_texture_ids.o \
	${OBJECTDIR}/filter.o


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
LDLIBSOPTIONS=../l3m/dist/Release/GNU-Linux-x86/libl3m.a ../renderer/dist/Release/GNU-Linux-x86/librenderer.a `pkg-config --libs glew` ../shared/dist/Release/GNU-Linux-x86/libshared.a `pkg-config --libs libpng` ../core/dist/Release/GNU-Linux-x86/libcore.a -lrt  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer: ../l3m/dist/Release/GNU-Linux-x86/libl3m.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer: ../renderer/dist/Release/GNU-Linux-x86/librenderer.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer: ../shared/dist/Release/GNU-Linux-x86/libshared.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer: ../core/dist/Release/GNU-Linux-x86/libcore.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/delete_unused.o: delete_unused.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I.. `pkg-config --cflags glew` `pkg-config --cflags libpng`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/delete_unused.o delete_unused.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I.. `pkg-config --cflags glew` `pkg-config --cflags libpng`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/delete_unused_textures.o: delete_unused_textures.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I.. `pkg-config --cflags glew` `pkg-config --cflags libpng`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/delete_unused_textures.o delete_unused_textures.cpp

${OBJECTDIR}/delete_duplicates.o: delete_duplicates.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I.. `pkg-config --cflags glew` `pkg-config --cflags libpng`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/delete_duplicates.o delete_duplicates.cpp

${OBJECTDIR}/clean_texture_ids.o: clean_texture_ids.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I.. `pkg-config --cflags glew` `pkg-config --cflags libpng`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/clean_texture_ids.o clean_texture_ids.cpp

${OBJECTDIR}/filter.o: filter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I.. `pkg-config --cflags glew` `pkg-config --cflags libpng`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/filter.o filter.cpp

# Subprojects
.build-subprojects:
	cd ../l3m && ${MAKE}  -f Makefile CONF=Release
	cd ../renderer && ${MAKE}  -f Makefile CONF=Release
	cd ../shared && ${MAKE}  -f Makefile CONF=Release
	cd ../core && ${MAKE} -j -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/model_optimizer

# Subprojects
.clean-subprojects:
	cd ../l3m && ${MAKE}  -f Makefile CONF=Release clean
	cd ../renderer && ${MAKE}  -f Makefile CONF=Release clean
	cd ../shared && ${MAKE}  -f Makefile CONF=Release clean
	cd ../core && ${MAKE} -j -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
