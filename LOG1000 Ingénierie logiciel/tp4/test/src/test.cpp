
#include "test.h"


void Test::setUp() {

	this->ObjetTest = new Rabais();

}

void Test::tearDown() 
{

	delete this->ObjetTest;
}

void Test::TestRabaisZero() 
{
	tm ad;
	ad.tm_year = 2018;
	ObjetTest->ajouterClient(new Client(6000, "Mohand", "Azhar", 34, "G4S", ad));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, ObjetTest->getRabais(facture, 6000), FLT_EPSILON);
}

void Test::TestRabais90k() 
{
	ObjetTest->ajouterClient(new Client(96000, "Mohand", "Azhar", 35, "H4L", {15, 11, 3}));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, ObjetTest->getRabais(facture, 96000), FLT_EPSILON);
}

void Test::TestRabais65() 
{
	tm ad;
	ad.tm_year = 2018;
	ObjetTest->ajouterClient(new Client(480, "Mohand", "Azhar", 70, "G4S", ad));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.05, ObjetTest->getRabais(facture, 480), FLT_EPSILON);
}

void Test::TestRabaisG0X() 
{
	tm ad;
	ad.tm_year = 2018;
	ObjetTest->ajouterClient(new Client(55, "Mohand", "Azhar", 25, "G0X", ad));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.02, ObjetTest->getRabais(facture, 55), FLT_EPSILON);
}

void Test::TestRabaisH4L() 
{
	tm ad;
	ad.tm_year = 2018;
	ObjetTest->ajouterClient(new Client(55, "Mohand", "Azhar", 25, "H4L", ad));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.01, ObjetTest->getRabais(facture, 55), FLT_EPSILON);
}

void Test::TestRabaisH2X() 
{
	tm ad;
	ad.tm_year = 2018;
	ObjetTest->ajouterClient(new Client(55, "Mohand", "Azhar", 25, "H2X", ad));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.01, ObjetTest->getRabais(facture, 55), FLT_EPSILON);
}

void Test::TestRabais5() 
{
	tm ad;
	ad.tm_year = 2000;
	ObjetTest->ajouterClient(new Client(55, "Mohand", "Azhar", 25, "G4S", ad));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.05, ObjetTest->getRabais(facture, 55), FLT_EPSILON);
}

void Test::TestRabaisMoins500() 
{
	tm ad;
	ad.tm_year = 2018;
	ObjetTest->ajouterClient(new Client(55, "Mohand", "Azhar", 25, "G4S", ad));
	Facture facture;
	facture.ajouterItem(50.0);
	facture.ajouterItem(320.0);
	facture.ajouterItem(30.0);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.04, ObjetTest->getRabais(facture, 55), FLT_EPSILON);
}

void Test::TestRabaisPlus500() 
{
	tm ad;
	ad.tm_year = 2018;
	ObjetTest->ajouterClient(new Client(55, "Mohand", "Azhar", 25, "G4S", ad));
	Facture facture;
	facture.ajouterItem(50.0);
	facture.ajouterItem(320.0);
	facture.ajouterItem(200.0);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.05, ObjetTest->getRabais(facture, 55), FLT_EPSILON);
}

void Test::TestRabaisGen() 
{
	tm ad;
	ad.tm_year = 2001;
	ObjetTest->ajouterClient(new Client(55, "Mohand", "Azhar", 75, "H2X", ad));
	Facture facture;
	facture.ajouterItem(50.0);
	facture.ajouterItem(320.0);
	facture.ajouterItem(240.5);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.16, ObjetTest->getRabais(facture, 55), FLT_EPSILON);
}
