/*
 * File:   DataTypeUnitTest.h
 * Author: DeveloperPrime
 *
 * Created on May 2, 2015, 7:31:58 AM
 */

#ifndef DATATYPEUNITTEST_H
#define	DATATYPEUNITTEST_H

#include <cppunit/extensions/HelperMacros.h>


class DataHolderUnitTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(DataHolderUnitTest);

    CPPUNIT_TEST(testIntValidate);
    CPPUNIT_TEST(testUIntValidate);
    CPPUNIT_TEST(testConversionFunctions);

    CPPUNIT_TEST_SUITE_END();

public:
    DataHolderUnitTest();
    virtual ~DataHolderUnitTest();
    void setUp();
    void tearDown();

private:
    void testIntValidate();
    void testUIntValidate();
    void testConversionFunctions();

};

#endif	/* DATATYPEUNITTEST_H */

