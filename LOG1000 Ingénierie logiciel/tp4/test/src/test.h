#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// Le fichier à tester, qui se trouve dans un répertoire différent.
#include "../../src/rabais.h"

class Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Test);
	CPPUNIT_TEST(TestRabaisZero);
	CPPUNIT_TEST(TestRabais90k);
	CPPUNIT_TEST(TestRabais65);
	CPPUNIT_TEST(TestRabaisG0X);
	CPPUNIT_TEST(TestRabaisH4L);
	CPPUNIT_TEST(TestRabaisH2X);
	CPPUNIT_TEST(TestRabais5);
	CPPUNIT_TEST(TestRabaisMoins500);
	CPPUNIT_TEST(TestRabaisPlus500);
	CPPUNIT_TEST(TestRabaisGen);
	CPPUNIT_TEST_SUITE_END();
	
private:
	Rabais* ObjetTest;

public:
	// Fonctions d'échafaudage

	void setUp();
	void tearDown();

	// Fonctions de tests

	void TestRabaisZero();
	void TestRabais90k();
	void TestRabais65();
	void TestRabaisG0X();
	void TestRabaisH4L();
	void TestRabaisH2X();
	void TestRabais5();
	void TestRabaisMoins500();
	void TestRabaisPlus500();
	void TestRabaisGen();
	
};




