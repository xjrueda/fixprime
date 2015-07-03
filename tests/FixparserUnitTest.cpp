/*
 * File:   FixparserUnitTest.cpp
 * Author: DeveloperPrime
 *
 * Created on Jun 26, 2015, 2:58:42 PM
 */

#include "FixparserUnitTest.h"
#include "FixParser.h"
#include "Protocol.h"
#include "FixDictionary.h"


CPPUNIT_TEST_SUITE_REGISTRATION(FixparserUnitTest);

FixparserUnitTest::FixparserUnitTest() {
}

FixparserUnitTest::~FixparserUnitTest() {
}

void FixparserUnitTest::setUp() {
}

void FixparserUnitTest::tearDown() {
}

void FixparserUnitTest::testParseMessage() {
    hfe::FixDictionary::FixDictionaryPtr fixDictionaryPtr(new hfe::FixDictionary);
    fixDictionaryPtr->loadProtocols("./FixSpecifications/FixVersions.json");


    hfe::Protocol::ProtocolPtr protocolPtr = fixDictionaryPtr->getProtocol("FIX.4.4");


    std::string msg = "8=FIX.4.49=00036135=849=XTRM56=02934=957=029X0552=20150612-17:14:19.33437=201506121046311=20150612_62453=4448=CC1029OBO447=C452=11448=CC1029OBO447=C452=36448=029X05447=C452=12448=029447=C452=117=53727150=039=01=P010763=148=T16U15F22=99167=FUT762=FUTU711=1309=T16305=99763=UNDL54=238=2040=244=101.9559=0151=2014=060=20150612-17:14:19.00010=099";

    hfe::FixParser parser;
    parser.setProtocol(protocolPtr);
    parser.setSeparator('\001');

    hfe::FixParser::FlatMessage flatMessage = parser.explode(msg);
    hfe::Message fixmsg = parser.parseMessage(flatMessage);

    CPPUNIT_ASSERT_MESSAGE("Getting begin string", "FIX.4.4" == fixmsg.header(8).getValue());

    CPPUNIT_ASSERT_MESSAGE("Getting repeating group instance value", "CC1029OBO" == fixmsg.body(453)[1](448).getValue());
}

