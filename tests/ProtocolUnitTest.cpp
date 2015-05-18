/*
 * File:   newtestclass2.cpp
 * Author: DeveloperPrime
 *
 * Created on May 1, 2015, 3:31:58 PM
 */

#include "ProtocolUnitTest.h"
#include "Protocol.h"
#include "FixDictionary.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ProtocolUnitTest);

ProtocolUnitTest::ProtocolUnitTest() {
}

ProtocolUnitTest::~ProtocolUnitTest() {
}

void ProtocolUnitTest::setUp() {
}

void ProtocolUnitTest::tearDown() {
}

void ProtocolUnitTest::testLoad() {
    hfe::FixDictionary fixDictionary;
    fixDictionary.loadProtocols("./FixSpecifications/FixVersions.json");
    hfe::Protocol::ProtocolPtr fix44 = fixDictionary.getProtocol("FIX 4.4");

    hfe::Message logon = fix44->getMessage("A");
    hfe::Node header = logon.getHeader();
    logon.header(8).setValue("FIX 4.4");
    logon.header(627).appendGroupInstance();
    logon.header(627)[1](628).setValue("XX");

    //CPPUNIT_ASSERT(true);
    CPPUNIT_ASSERT("XX" == logon.header(627)[1](628).getValue());

}

void ProtocolUnitTest::testNestedGroups() {
    hfe::FixDictionary fixDictionary;
    fixDictionary.loadProtocols("./FixSpecifications/FixVersions.json");
    hfe::Protocol::ProtocolPtr fix44 = fixDictionary.getProtocol("FIX 4.4");

    hfe::Message msg = fix44->getMessage("D");
    hfe::Node header = msg.getHeader();
    msg.header(8).setValue("FIX 4.4");
    
    msg.body(453).appendGroupInstance();
    CPPUNIT_ASSERT_THROW_MESSAGE("Repeating group value assigment",msg.body(453).setValue("1");, std::runtime_error);
    
    msg.body(453)[1](448).setValue("2");
    
    //Nested group value assigment  
    CPPUNIT_ASSERT_MESSAGE("Nested group value assigment","2" == msg.body(453)[1](448).getValue());
    
    msg.body(453)[1](802).appendGroupInstance();
    
    
    

}

