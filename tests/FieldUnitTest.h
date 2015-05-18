/*
 * File:   FieldUnitTest.h
 * Author: DeveloperPrime
 *
 * Created on May 1, 2015, 8:28:33 PM
 */

#ifndef FIELDUNITTEST_H
#define	FIELDUNITTEST_H

#include <cppunit/extensions/HelperMacros.h>

class FieldUnitTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(FieldUnitTest);

    CPPUNIT_TEST(testId);
    CPPUNIT_TEST(testName);
    CPPUNIT_TEST(testDataType);
    CPPUNIT_TEST(testComponentPointer);
    CPPUNIT_TEST(testValidValue);

    CPPUNIT_TEST_SUITE_END();

public:
    FieldUnitTest();
    virtual ~FieldUnitTest();
    void setUp();
    void tearDown();

private:
    void testId();
    void testName();
    void testDataType();
    void testComponentPointer();
    void testValidValue();

};

#endif	/* FIELDUNITTEST_H */

