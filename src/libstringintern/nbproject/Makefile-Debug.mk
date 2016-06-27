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
	${OBJECTDIR}/string_page_archive.o \
	${OBJECTDIR}/string_page_catalog.o \
	${OBJECTDIR}/string_page_nursery.o \
	${OBJECTDIR}/string_page_ptr.o \
	${OBJECTDIR}/string_page_sizes.o \
	${OBJECTDIR}/string_pages.o \
	${OBJECTDIR}/string_reference.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4

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

${OBJECTDIR}/string_page_archive.o: string_page_archive.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_archive.o string_page_archive.cpp

${OBJECTDIR}/string_page_catalog.o: string_page_catalog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_catalog.o string_page_catalog.cpp

${OBJECTDIR}/string_page_nursery.o: string_page_nursery.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_nursery.o string_page_nursery.cpp

${OBJECTDIR}/string_page_ptr.o: string_page_ptr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_ptr.o string_page_ptr.cpp

${OBJECTDIR}/string_page_sizes.o: string_page_sizes.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_sizes.o string_page_sizes.cpp

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
${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/string_hash_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/string_page_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/string_page_archive_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/string_page_catalog_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/string_page_ptr_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 

${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/string_pages_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/string_page_sizes_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/string_reference_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libgtest_main.a -lpthread -latomic 


${TESTDIR}/tests/string_hash_tests.o: tests/string_hash_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_hash_tests.o tests/string_hash_tests.cpp


${TESTDIR}/tests/string_page_tests.o: tests/string_page_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_page_tests.o tests/string_page_tests.cpp


${TESTDIR}/tests/string_page_archive_tests.o: tests/string_page_archive_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_page_archive_tests.o tests/string_page_archive_tests.cpp


${TESTDIR}/tests/string_page_catalog_tests.o: tests/string_page_catalog_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_page_catalog_tests.o tests/string_page_catalog_tests.cpp


${TESTDIR}/tests/string_page_ptr_tests.o: tests/string_page_ptr_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_page_ptr_tests.o tests/string_page_ptr_tests.cpp


${TESTDIR}/tests/string_pages_tests.o: tests/string_pages_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_pages_tests.o tests/string_pages_tests.cpp


${TESTDIR}/tests/string_page_sizes_tests.o: tests/string_page_sizes_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_page_sizes_tests.o tests/string_page_sizes_tests.cpp


${TESTDIR}/tests/string_reference_tests.o: tests/string_reference_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/xxHash -I../../externals/installed/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_reference_tests.o tests/string_reference_tests.cpp


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

${OBJECTDIR}/string_page_archive_nomain.o: ${OBJECTDIR}/string_page_archive.o string_page_archive.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_page_archive.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_archive_nomain.o string_page_archive.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_page_archive.o ${OBJECTDIR}/string_page_archive_nomain.o;\
	fi

${OBJECTDIR}/string_page_catalog_nomain.o: ${OBJECTDIR}/string_page_catalog.o string_page_catalog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_page_catalog.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_catalog_nomain.o string_page_catalog.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_page_catalog.o ${OBJECTDIR}/string_page_catalog_nomain.o;\
	fi

${OBJECTDIR}/string_page_nursery_nomain.o: ${OBJECTDIR}/string_page_nursery.o string_page_nursery.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_page_nursery.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_nursery_nomain.o string_page_nursery.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_page_nursery.o ${OBJECTDIR}/string_page_nursery_nomain.o;\
	fi

${OBJECTDIR}/string_page_ptr_nomain.o: ${OBJECTDIR}/string_page_ptr.o string_page_ptr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_page_ptr.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_ptr_nomain.o string_page_ptr.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_page_ptr.o ${OBJECTDIR}/string_page_ptr_nomain.o;\
	fi

${OBJECTDIR}/string_page_sizes_nomain.o: ${OBJECTDIR}/string_page_sizes.o string_page_sizes.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/string_page_sizes.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../externals/xxHash -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_page_sizes_nomain.o string_page_sizes.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/string_page_sizes.o ${OBJECTDIR}/string_page_sizes_nomain.o;\
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
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
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
