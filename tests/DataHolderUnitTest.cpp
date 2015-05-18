/*
 * File:   DataTypeUnitTest.cpp
 * Author: DeveloperPrime
 *
 * Created on May 2, 2015, 7:31:59 AM
 */

#include "DataHolderUnitTest.h"
#include "DataHolder.h"
#include "DataHolderFactory.h"


CPPUNIT_TEST_SUITE_REGISTRATION(DataHolderUnitTest);

DataHolderUnitTest::DataHolderUnitTest() {
}

DataHolderUnitTest::~DataHolderUnitTest() {
}

void DataHolderUnitTest::setUp() {
}

void DataHolderUnitTest::tearDown() {
}

void DataHolderUnitTest::testIntValidate() {
    
    hfe::DataHolderFactory factory;
    hfe::DataHolder::DataTypePtr intDataHolder = factory.create("Int");
    
    //alfanumeric test
    intDataHolder->set("AA"); 
    CPPUNIT_ASSERT_MESSAGE("alfanumeric test",!intDataHolder->validate());
    
    // special character test
    intDataHolder->set("##");
    CPPUNIT_ASSERT_MESSAGE("special character test",!intDataHolder->validate());
    
    // happy path test
    intDataHolder->set("123");
    CPPUNIT_ASSERT_MESSAGE("happy path test",intDataHolder->validate());
    
    // happy path with negative integer
    intDataHolder->set("-123");
    CPPUNIT_ASSERT_MESSAGE("happy path with negative integer",intDataHolder->validate());
    
    // numeric overflow test
    intDataHolder->set("2147483647999999");
    CPPUNIT_ASSERT_MESSAGE("numeric overflow test",!intDataHolder->validate());
    
    // Decimal test
    intDataHolder->set("21474.001254000");
    CPPUNIT_ASSERT_MESSAGE("Decimal test",!intDataHolder->validate());
    
    // negative decimal test
    intDataHolder->set("-21474.001254000");
    CPPUNIT_ASSERT_MESSAGE("negative decimal test",!intDataHolder->validate());
    
    // Octal numbers
    intDataHolder->set("\001");
    CPPUNIT_ASSERT_MESSAGE("Octal numbers",!intDataHolder->validate());
   
 }

void DataHolderUnitTest::testUIntValidate() {
    
    hfe::DataHolderFactory factory;
    hfe::DataHolder::DataTypePtr uIntDataHolder = factory.create("Length");
    
    //alfanumeric test
    uIntDataHolder->set("AA"); 
    CPPUNIT_ASSERT_MESSAGE("alfanumeric test",!uIntDataHolder->validate());
    
    // special character test
    uIntDataHolder->set("##");
    CPPUNIT_ASSERT_MESSAGE("special character test", !uIntDataHolder->validate());
    
    // happy path test
    uIntDataHolder->set("123");
    CPPUNIT_ASSERT_MESSAGE("happy path test",uIntDataHolder->validate());
    
    // negative integer test
    uIntDataHolder->set("-123");
    CPPUNIT_ASSERT_MESSAGE("negative integer test",!uIntDataHolder->validate());
    
    // numeric overflow test
    uIntDataHolder->set("2147483647999999");
    CPPUNIT_ASSERT_MESSAGE("numeric overflow test",!uIntDataHolder->validate());
    
    // Decimal test
    uIntDataHolder->set("21474.001254000");
    CPPUNIT_ASSERT_MESSAGE("Decimal test",!uIntDataHolder->validate());
    
    // negative decimal test
    uIntDataHolder->set("-21474.001254000");
    CPPUNIT_ASSERT_MESSAGE("negative decimal test",!uIntDataHolder->validate());
    
    // Octal numbers
    uIntDataHolder->set("\001");
    CPPUNIT_ASSERT_MESSAGE("Octal numbers",!uIntDataHolder->validate());   
 }

void DataHolderUnitTest::testConversionFunctions() {
    
    hfe::DataHolderFactory factory;
    hfe::DataHolder::DataTypePtr stringDataHolder = factory.create("String");
    
    //alfanumeric test
    stringDataHolder->set("AAAAAAAAAAA"); 
    CPPUNIT_ASSERT_THROW_MESSAGE("alfanumeric test",!stringDataHolder->toDouble(),std::runtime_error);
    
    // special character test
    stringDataHolder->set("##");
    CPPUNIT_ASSERT_THROW_MESSAGE("special character test", stringDataHolder->toInt(),std::runtime_error);
    
    // happy path test
    stringDataHolder->set("2147483647");
    CPPUNIT_ASSERT_MESSAGE("happy path test",stringDataHolder->toInt());
    
    // negative integer test
    stringDataHolder->set("-2147483648");
    CPPUNIT_ASSERT_MESSAGE("negative integer test",stringDataHolder->toInt());
    
    // numeric 
    stringDataHolder->set("2147483647999999999999999999999999999999999999999999999");
    CPPUNIT_ASSERT_MESSAGE("numeric overflow test",stringDataHolder->toLongDouble());
    
     // numeric overflow test
    stringDataHolder->set("2147483647999999999999999999999999999999999999999999999");
    CPPUNIT_ASSERT_THROW_MESSAGE("numeric overflow test",stringDataHolder->toInt(),std::runtime_error);
    
 }

