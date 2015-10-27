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
	${OBJECTDIR}/src/Acceptor.o \
	${OBJECTDIR}/src/CallbacksManager.o \
	${OBJECTDIR}/src/Component.o \
	${OBJECTDIR}/src/DataHolderFactory.o \
	${OBJECTDIR}/src/Engine.o \
	${OBJECTDIR}/src/Field.o \
	${OBJECTDIR}/src/FixDictionary.o \
	${OBJECTDIR}/src/FixLoader.o \
	${OBJECTDIR}/src/FixParser.o \
	${OBJECTDIR}/src/FixSession.o \
	${OBJECTDIR}/src/FixSessionSetup.o \
	${OBJECTDIR}/src/Initiator.o \
	${OBJECTDIR}/src/IntDataHolder.o \
	${OBJECTDIR}/src/Message.o \
	${OBJECTDIR}/src/Node.o \
	${OBJECTDIR}/src/Protocol.o \
	${OBJECTDIR}/src/StringDataHolder.o \
	${OBJECTDIR}/src/UIntDataHolder.o \
	${OBJECTDIR}/src/Value.o \
	${OBJECTDIR}/src/jsoncpp.o


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
LDLIBSOPTIONS=`cppunit-config --libs` -lcunit `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f1

${TESTDIR}/TestFiles/f1: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Acceptor.o: src/Acceptor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Acceptor.o src/Acceptor.cpp

${OBJECTDIR}/src/CallbacksManager.o: src/CallbacksManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CallbacksManager.o src/CallbacksManager.cpp

${OBJECTDIR}/src/Component.o: src/Component.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Component.o src/Component.cpp

${OBJECTDIR}/src/DataHolderFactory.o: src/DataHolderFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DataHolderFactory.o src/DataHolderFactory.cpp

${OBJECTDIR}/src/Engine.o: src/Engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Engine.o src/Engine.cpp

${OBJECTDIR}/src/Field.o: src/Field.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Field.o src/Field.cpp

${OBJECTDIR}/src/FixDictionary.o: src/FixDictionary.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixDictionary.o src/FixDictionary.cpp

${OBJECTDIR}/src/FixLoader.o: src/FixLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixLoader.o src/FixLoader.cpp

${OBJECTDIR}/src/FixParser.o: src/FixParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixParser.o src/FixParser.cpp

${OBJECTDIR}/src/FixSession.o: src/FixSession.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixSession.o src/FixSession.cpp

${OBJECTDIR}/src/FixSessionSetup.o: src/FixSessionSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FixSessionSetup.o src/FixSessionSetup.cpp

${OBJECTDIR}/src/Initiator.o: src/Initiator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Initiator.o src/Initiator.cpp

${OBJECTDIR}/src/IntDataHolder.o: src/IntDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IntDataHolder.o src/IntDataHolder.cpp

${OBJECTDIR}/src/Message.o: src/Message.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Message.o src/Message.cpp

${OBJECTDIR}/src/Node.o: src/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Node.o src/Node.cpp

${OBJECTDIR}/src/Protocol.o: src/Protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Protocol.o src/Protocol.cpp

${OBJECTDIR}/src/StringDataHolder.o: src/StringDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/StringDataHolder.o src/StringDataHolder.cpp

${OBJECTDIR}/src/UIntDataHolder.o: src/UIntDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/UIntDataHolder.o src/UIntDataHolder.cpp

${OBJECTDIR}/src/Value.o: src/Value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Value.o src/Value.cpp

${OBJECTDIR}/src/jsoncpp.o: src/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jsoncpp.o src/jsoncpp.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
