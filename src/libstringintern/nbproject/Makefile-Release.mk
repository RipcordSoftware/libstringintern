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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1406610357/xxhash.o \
	${OBJECTDIR}/string_intern.o \
	${OBJECTDIR}/string_page.o \
	${OBJECTDIR}/string_reference.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibstringintern.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibstringintern.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibstringintern.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibstringintern.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibstringintern.a

${OBJECTDIR}/_ext/1406610357/xxhash.o: ../../externals/xxHash/xxhash.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1406610357
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1406610357/xxhash.o ../../externals/xxHash/xxhash.c

${OBJECTDIR}/string_intern.o: string_intern.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_intern.o string_intern.cpp

${OBJECTDIR}/string_page.o: string_page.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page.o string_page.cpp

${OBJECTDIR}/string_reference.o: string_reference.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_reference.o string_reference.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibstringintern.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
