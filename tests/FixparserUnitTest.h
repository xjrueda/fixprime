/*
 * File:   FixparserUnitTest.h
 * Author: DeveloperPrime
 *
 * Created on Jun 26, 2015, 2:58:39 PM
 */

#ifndef FIXPARSERUNITTEST_H
#define	FIXPARSERUNITTEST_H

#include <cppunit/extensions/HelperMacros.h>

class FixparserUnitTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(FixparserUnitTest);

    CPPUNIT_TEST(testParseMessage);

    CPPUNIT_TEST_SUITE_END();

public:
    FixparserUnitTest();
    virtual ~FixparserUnitTest();
    void setUp();
    void tearDown();

private:
    void testParseMessage();

};

#endif	/* FIXPARSERUNITTEST_H */

