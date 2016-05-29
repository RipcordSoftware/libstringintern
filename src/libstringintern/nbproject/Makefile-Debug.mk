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
	${OBJECTDIR}/_ext/1406610357/xxhash.o \
	${OBJECTDIR}/string_hash.o \
	${OBJECTDIR}/string_intern.o \
	${OBJECTDIR}/string_page.o \
	${OBJECTDIR}/string_pages.o \
	${OBJECTDIR}/string_reference.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=--coverage
CXXFLAGS=--coverage

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstringintern.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstringintern.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstringintern.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstringintern.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstringintern.a

${OBJECTDIR}/_ext/1406610357/xxhash.o: ../../externals/xxHash/xxhash.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1406610357
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1406610357/xxhash.o ../../externals/xxHash/xxhash.c

${OBJECTDIR}/string_hash.o: string_hash.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_hash.o string_hash.cpp

${OBJECTDIR}/string_intern.o: string_intern.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_intern.o string_intern.cpp

${OBJECTDIR}/string_page.o: string_page.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page.o string_page.cpp

${OBJECTDIR}/string_pages.o: string_pages.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_pages.o string_pages.cpp

${OBJECTDIR}/string_reference.o: string_reference.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_reference.o string_reference.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/string_page_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread 


${TESTDIR}/tests/string_page_tests.o: tests/string_page_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_page_tests.o tests/string_page_tests.cpp


${OBJECTDIR}/_ext/1406610357/xxhash_nomain.o: ${OBJECTDIR}/_ext/1406610357/xxhash.o ../../externals/xxHash/xxhash.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1406610357
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1406610357/xxhash.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1406610357/xxhash_nomain.o ../../externals/xxHash/xxhash.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1406610357/xxhash.o ${OBJECTDIR}/_ext/1406610357/xxhash_nomain.o;\
	fi

${OBJECTDIR}/string_hash_nomain.o: ${OBJECTDIR}/string_hash.o string_hash.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_hash.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_hash_nomain.o string_hash.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_hash.o ${OBJECTDIR}/string_hash_nomain.o;\
	fi

${OBJECTDIR}/string_intern_nomain.o: ${OBJECTDIR}/string_intern.o string_intern.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_intern.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_intern_nomain.o string_intern.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_intern.o ${OBJECTDIR}/string_intern_nomain.o;\
	fi

${OBJECTDIR}/string_page_nomain.o: ${OBJECTDIR}/string_page.o string_page.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_page.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_nomain.o string_page.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_page.o ${OBJECTDIR}/string_page_nomain.o;\
	fi

${OBJECTDIR}/string_pages_nomain.o: ${OBJECTDIR}/string_pages.o string_pages.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_pages.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_pages_nomain.o string_pages.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_pages.o ${OBJECTDIR}/string_pages_nomain.o;\
	fi

${OBJECTDIR}/string_reference_nomain.o: ${OBJECTDIR}/string_reference.o string_reference.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_reference.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_reference_nomain.o string_reference.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_reference.o ${OBJECTDIR}/string_reference_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstringintern.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
