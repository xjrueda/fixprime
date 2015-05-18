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
	${OBJECTDIR}/src/Component.o \
	${OBJECTDIR}/src/DataHolderFactory.o \
	${OBJECTDIR}/src/Field.o \
	${OBJECTDIR}/src/FixDictionary.o \
	${OBJECTDIR}/src/FixLoader.o \
	${OBJECTDIR}/src/Hypersonic.o \
	${OBJECTDIR}/src/IntDataHolder.o \
	${OBJECTDIR}/src/Message.o \
	${OBJECTDIR}/src/Node.o \
	${OBJECTDIR}/src/Protocol.o \
	${OBJECTDIR}/src/StringDataHolder.o \
	${OBJECTDIR}/src/UIntDataHolder.o \
	${OBJECTDIR}/src/Value.o \
	${OBJECTDIR}/src/jsoncpp.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f4

# C Compiler Flags
CFLAGS=`cppunit-config --cflags` 

# CC Compiler Flags
CCFLAGS=-m64 `cppunit-config --cflags` 
CXXFLAGS=-m64 `cppunit-config --cflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`cppunit-config --libs` -lcunit `cppunit-config --libs` `cppunit-config --libs`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f3

${TESTDIR}/TestFiles/f3: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Component.o: src/Component.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Component.o src/Component.cpp

${OBJECTDIR}/src/DataHolderFactory.o: src/DataHolderFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DataHolderFactory.o src/DataHolderFactory.cpp

${OBJECTDIR}/src/Field.o: src/Field.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Field.o src/Field.cpp

${OBJECTDIR}/src/FixDictionary.o: src/FixDictionary.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixDictionary.o src/FixDictionary.cpp

${OBJECTDIR}/src/FixLoader.o: src/FixLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixLoader.o src/FixLoader.cpp

${OBJECTDIR}/src/Hypersonic.o: src/Hypersonic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hypersonic.o src/Hypersonic.cpp

${OBJECTDIR}/src/IntDataHolder.o: src/IntDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IntDataHolder.o src/IntDataHolder.cpp

${OBJECTDIR}/src/Message.o: src/Message.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Message.o src/Message.cpp

${OBJECTDIR}/src/Node.o: src/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Node.o src/Node.cpp

${OBJECTDIR}/src/Protocol.o: src/Protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Protocol.o src/Protocol.cpp

${OBJECTDIR}/src/StringDataHolder.o: src/StringDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/StringDataHolder.o src/StringDataHolder.cpp

${OBJECTDIR}/src/UIntDataHolder.o: src/UIntDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/UIntDataHolder.o src/UIntDataHolder.cpp

${OBJECTDIR}/src/Value.o: src/Value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Value.o src/Value.cpp

${OBJECTDIR}/src/jsoncpp.o: src/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jsoncpp.o src/jsoncpp.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/DataHolderUnitTest.o ${TESTDIR}/tests/DataHolderUnitTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/FieldUnitTest.o ${TESTDIR}/tests/FieldUnitTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} `cppunit-config --libs` `cppunit-config --libs`   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/ProtocolUnitTest.o ${TESTDIR}/tests/ProtocolUnitTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/tests/DataHolderUnitTest.o: tests/DataHolderUnitTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/DataHolderUnitTest.o tests/DataHolderUnitTest.cpp


${TESTDIR}/tests/DataHolderUnitTestRunner.o: tests/DataHolderUnitTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/DataHolderUnitTestRunner.o tests/DataHolderUnitTestRunner.cpp


${TESTDIR}/tests/FieldUnitTest.o: tests/FieldUnitTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/FieldUnitTest.o tests/FieldUnitTest.cpp


${TESTDIR}/tests/FieldUnitTestRunner.o: tests/FieldUnitTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/FieldUnitTestRunner.o tests/FieldUnitTestRunner.cpp


${TESTDIR}/tests/ProtocolUnitTest.o: tests/ProtocolUnitTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ProtocolUnitTest.o tests/ProtocolUnitTest.cpp


${TESTDIR}/tests/ProtocolUnitTestRunner.o: tests/ProtocolUnitTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ProtocolUnitTestRunner.o tests/ProtocolUnitTestRunner.cpp


${OBJECTDIR}/src/Component_nomain.o: ${OBJECTDIR}/src/Component.o src/Component.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Component.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Component_nomain.o src/Component.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Component.o ${OBJECTDIR}/src/Component_nomain.o;\
	fi

${OBJECTDIR}/src/DataHolderFactory_nomain.o: ${OBJECTDIR}/src/DataHolderFactory.o src/DataHolderFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/DataHolderFactory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DataHolderFactory_nomain.o src/DataHolderFactory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/DataHolderFactory.o ${OBJECTDIR}/src/DataHolderFactory_nomain.o;\
	fi

${OBJECTDIR}/src/Field_nomain.o: ${OBJECTDIR}/src/Field.o src/Field.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Field.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Field_nomain.o src/Field.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Field.o ${OBJECTDIR}/src/Field_nomain.o;\
	fi

${OBJECTDIR}/src/FixDictionary_nomain.o: ${OBJECTDIR}/src/FixDictionary.o src/FixDictionary.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/FixDictionary.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixDictionary_nomain.o src/FixDictionary.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/FixDictionary.o ${OBJECTDIR}/src/FixDictionary_nomain.o;\
	fi

${OBJECTDIR}/src/FixLoader_nomain.o: ${OBJECTDIR}/src/FixLoader.o src/FixLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/FixLoader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixLoader_nomain.o src/FixLoader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/FixLoader.o ${OBJECTDIR}/src/FixLoader_nomain.o;\
	fi

${OBJECTDIR}/src/Hypersonic_nomain.o: ${OBJECTDIR}/src/Hypersonic.o src/Hypersonic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Hypersonic.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hypersonic_nomain.o src/Hypersonic.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Hypersonic.o ${OBJECTDIR}/src/Hypersonic_nomain.o;\
	fi

${OBJECTDIR}/src/IntDataHolder_nomain.o: ${OBJECTDIR}/src/IntDataHolder.o src/IntDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/IntDataHolder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IntDataHolder_nomain.o src/IntDataHolder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/IntDataHolder.o ${OBJECTDIR}/src/IntDataHolder_nomain.o;\
	fi

${OBJECTDIR}/src/Message_nomain.o: ${OBJECTDIR}/src/Message.o src/Message.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Message.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Message_nomain.o src/Message.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Message.o ${OBJECTDIR}/src/Message_nomain.o;\
	fi

${OBJECTDIR}/src/Node_nomain.o: ${OBJECTDIR}/src/Node.o src/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Node.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Node_nomain.o src/Node.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Node.o ${OBJECTDIR}/src/Node_nomain.o;\
	fi

${OBJECTDIR}/src/Protocol_nomain.o: ${OBJECTDIR}/src/Protocol.o src/Protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Protocol.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Protocol_nomain.o src/Protocol.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Protocol.o ${OBJECTDIR}/src/Protocol_nomain.o;\
	fi

${OBJECTDIR}/src/StringDataHolder_nomain.o: ${OBJECTDIR}/src/StringDataHolder.o src/StringDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/StringDataHolder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/StringDataHolder_nomain.o src/StringDataHolder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/StringDataHolder.o ${OBJECTDIR}/src/StringDataHolder_nomain.o;\
	fi

${OBJECTDIR}/src/UIntDataHolder_nomain.o: ${OBJECTDIR}/src/UIntDataHolder.o src/UIntDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/UIntDataHolder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/UIntDataHolder_nomain.o src/UIntDataHolder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/UIntDataHolder.o ${OBJECTDIR}/src/UIntDataHolder_nomain.o;\
	fi

${OBJECTDIR}/src/Value_nomain.o: ${OBJECTDIR}/src/Value.o src/Value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Value.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Value_nomain.o src/Value.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Value.o ${OBJECTDIR}/src/Value_nomain.o;\
	fi

${OBJECTDIR}/src/jsoncpp_nomain.o: ${OBJECTDIR}/src/jsoncpp.o src/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/jsoncpp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I. -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jsoncpp_nomain.o src/jsoncpp.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/jsoncpp.o ${OBJECTDIR}/src/jsoncpp_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f3

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
