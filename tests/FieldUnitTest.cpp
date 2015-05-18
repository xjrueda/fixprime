/*
 * File:   FieldUnitTest.cpp
 * Author: DeveloperPrime
 *
 * Created on May 1, 2015, 8:28:34 PM
 */

#include <stdexcept>

#include "FieldUnitTest.h"
#include "Field.h"
#include "Component.h"


CPPUNIT_TEST_SUITE_REGISTRATION(FieldUnitTest);

FieldUnitTest::FieldUnitTest() {
}

FieldUnitTest::~FieldUnitTest() {
}

void FieldUnitTest::setUp() {
}

void FieldUnitTest::tearDown() {
}

void FieldUnitTest::testId() {
    int p0;
    CPPUNIT_ASSERT_THROW(hfe::Field field(p0), std::runtime_error);
    
    int p1 = 234;
    hfe::Field field2(p1);
    CPPUNIT_ASSERT(field2.getId() == p1);
    
    
}

void FieldUnitTest::testName(){
    string p0;
    hfe::Field field(1);
    CPPUNIT_ASSERT_THROW(field.setName(p0), std::runtime_error);
    
    string p1 = "FieldName";
    field.setName(p1);
    CPPUNIT_ASSERT(field.getName() == p1);
}

void FieldUnitTest::testDataType(){
    string p0;
    hfe::Field field(1);
    CPPUNIT_ASSERT_THROW(field.setDataType(p0), std::runtime_error);
    
    string p1 = "DataType1";
    field.setDataType(p1);
    CPPUNIT_ASSERT(field.getDataType() == p1);
}



void FieldUnitTest::testValidValue() {
    string desc;
    hfe::Field field(1);
    field.addValidValue("val1", "Desc Value 1");
    field.addValidValue("val2", desc);
    CPPUNIT_ASSERT(field.validateValidValue("val1"));
    CPPUNIT_ASSERT(field.validateValidValue("val2"));
    
    string p0;
    CPPUNIT_ASSERT_THROW(field.addValidValue(p0,"desc null value"), std::runtime_error);
    
    
    
}
