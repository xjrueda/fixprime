/*
 * File:   newtestclass2.h
 * Author: DeveloperPrime
 *
 * Created on May 1, 2015, 3:31:57 PM
 */

#ifndef NEWTESTCLASS2_H
#define	NEWTESTCLASS2_H

#include <cppunit/extensions/HelperMacros.h>

class ProtocolUnitTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ProtocolUnitTest);

    CPPUNIT_TEST(testLoad);
    CPPUNIT_TEST(testNestedGroups);

    CPPUNIT_TEST_SUITE_END();

public:
    ProtocolUnitTest();
    virtual ~ProtocolUnitTest();
    void setUp();
    void tearDown();

private:
    void testLoad();
    void testNestedGroups();   
};

#endif	/* NEWTESTCLASS2_H */

