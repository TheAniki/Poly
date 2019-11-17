#include <string>
#include <list>

#include <cppunit/TestCase.h>

#include <cppunit/TestFixture.h>

#include <cppunit/ui/text/TextTestRunner.h>

#include <cppunit/extensions/HelperMacros.h>

#include <cppunit/extensions/TestFactoryRegistry.h>

#include <cppunit/TestResult.h>

#include <cppunit/TestResultCollector.h>

#include <cppunit/TestRunner.h>

#include <cppunit/BriefTestProgressListener.h>

#include <cppunit/CompilerOutputter.h>

#include <cppunit/XmlOutputter.h>

#include <netinet/in.h>


#include "../Emission.h"

#include "../Chaine.h"


using namespace CppUnit;

using namespace std;


//-----------------------------------------------------------------------------


class EmissionTest : public CppUnit::TestFixture

{

    CPPUNIT_TEST_SUITE(EmissionTest);

    CPPUNIT_TEST(testgetters);

    CPPUNIT_TEST(trouverEmission);

    CPPUNIT_TEST(trouverEmission2);

    CPPUNIT_TEST_SUITE_END();

    

public:

    void setUp(void);

    void tearDown(void);

    

protected:

    void testgetters(void);

    void trouverEmission(void);

    void trouverEmission2(void);

    

private:

    

    Emission *ems;

};


// ------------------------ IMPLEMENTATION ------------------------


void EmissionTest::testgetters(void)

{

    string titre = ems->getTitre();

    string animateur = ems->getAnimateur();

    /*string chaineName = ems->getChaineName();

    string chaineCodePostal = ems->getChaineCodePostal();

    string chaineAddress = ems->getChaineAddress();

    */

    Chaine* chaine = ems->getChaine();

    

    if (titre == "titreTest"

        && animateur == "animateurTest"

        && chaine->getChaineName() == "chaineNameTest"

        && chaine->getChaineCodePostal() == "chaineCodePostalTest"

        && chaine->getChaineAddress() == "chaineAddressTest") {

        CPPUNIT_ASSERT(true);

    } else {

        CPPUNIT_ASSERT(false);

    }

    

}


void EmissionTest::trouverEmission(void)

{

    Emission * a = ems->trouverEmission ("../DB.txt", "test");

    if (a == NULL) {

        CPPUNIT_ASSERT(true);

    } else {

        CPPUNIT_ASSERT(false);

    }

}



void EmissionTest::trouverEmission2(void)

{

    Emission * a = ems->trouverEmission ("../DB.txt", "titreTest");

    if (a != NULL) {

        CPPUNIT_ASSERT(true);

    } else {

        CPPUNIT_ASSERT(false);

    }

}


void EmissionTest::setUp(void)

{

    ems = new Emission("titreTest",

                      "animateurTest",

                      "chaineNameTest",

                      "chaineCodePostalTest",

                      "chaineAddressTest");

}


void EmissionTest::tearDown(void)

{

    delete ems;

}

