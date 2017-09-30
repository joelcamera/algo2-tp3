// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>

#include "test.h"
#include "dato.h"
#include "aed2.h"

#include <string>
#include <iostream>

using namespace std;

void test_crearDatoConNat(){
	dato d1(1);
	ASSERT( d1.esNat() );
	ASSERT( !d1.esString() );
	ASSERT_EQ(d1.valorNat(), 1);

	dato d2(2);
	ASSERT( d2.esNat() );
	ASSERT( !d2.esString() );
	ASSERT_EQ(d2.valorNat(), 2);

	dato d3(3);
	ASSERT( d3.esNat() );
	ASSERT( !d3.esString() );
	ASSERT_EQ(d3.valorNat(), 3);

	dato d4(4);
	ASSERT( d4.esNat() );
	ASSERT( !d4.esString() );
	ASSERT_EQ(d4.valorNat(), 4);
}

void test_crearDatoConStr(){
	dato d1("Joel");
	ASSERT( !d1.esNat() );
	ASSERT( d1.esString() );
	ASSERT_EQ(d1.valorStr(), "Joel");

	dato d2("Martin");
	ASSERT( !d2.esNat() );
	ASSERT( d2.esString() );
	ASSERT_EQ(d2.valorStr(), "Martin");

	dato d3("German");
	ASSERT( !d3.esNat() );
	ASSERT( d3.esString() );
	ASSERT_EQ(d3.valorStr(), "German");

	dato d4("NN");
	ASSERT( !d4.esNat() );
	ASSERT( d4.esString() );
	ASSERT_EQ(d4.valorStr(), "NN");	
}

void test_MismoTipo(){
	dato dn1(1);
	dato dn2(2);
	dato ds1("hola");
	dato ds2("lalala");

	ASSERT( dn1.mismoTipo(dn2) );
	ASSERT( dn2.mismoTipo(dn1) );

	ASSERT( ds1.mismoTipo(ds2) );
	ASSERT( ds2.mismoTipo(ds1) );

	ASSERT( !dn1.mismoTipo(ds1) );
	ASSERT( !dn1.mismoTipo(ds2) );
	
	ASSERT( !dn2.mismoTipo(ds1) );
	ASSERT( !dn2.mismoTipo(ds2) );
	
	ASSERT( !ds1.mismoTipo(dn1) );
	ASSERT( !ds1.mismoTipo(dn2) );
	
	ASSERT( !ds2.mismoTipo(dn1) );
	ASSERT( !ds2.mismoTipo(dn2) );
}

void test_operadorigualdad(){
	dato dn1(1);
	dato dn11(1);
	dato dn2(2);
	dato dn22(2);
	dato ds1("asdf");
	dato ds11("asdf");
	dato ds2("lolo");
	dato ds22("lolo");

	ASSERT(dn1 == dn1);
	ASSERT(dn11 == dn11);
	ASSERT(dn1 == dn11);
	ASSERT(dn11 == dn1);
	ASSERT(dn2 == dn2);
	ASSERT(dn22 == dn22);
	ASSERT(dn2 == dn22);
	ASSERT(dn22 == dn2);
	ASSERT(ds1 == ds1);
	ASSERT(ds11 == ds11);
	ASSERT(ds1 == ds11);
	ASSERT(ds11 == ds1);
	ASSERT(ds2 == ds2);
	ASSERT(ds22 == ds22);
	ASSERT(ds2 == ds22);
	ASSERT(ds22 == ds2);

	ASSERT( !(dn1 == dn2) );
	ASSERT( !(dn1 == dn22) );
	ASSERT( !(dn1 == ds1) );
	ASSERT( !(dn1 == ds11) );
	ASSERT( !(dn1 == ds2) );
	ASSERT( !(dn1 == ds22) );

	ASSERT( !(dn2 == dn1) );
	ASSERT( !(dn2 == dn11) );
	ASSERT( !(dn2 == ds1) );
	ASSERT( !(dn2 == ds11) );
	ASSERT( !(dn2 == ds2) );
	ASSERT( !(dn2 == ds22) );

	ASSERT( !(dn11 == dn2) );
	ASSERT( !(dn11 == dn22) );
	ASSERT( !(dn11 == ds1) );
	ASSERT( !(dn11 == ds11) );
	ASSERT( !(dn11 == ds2) );
	ASSERT( !(dn11 == ds22) );

	ASSERT( !(dn22 == dn1) );
	ASSERT( !(dn22 == dn11) );
	ASSERT( !(dn22 == ds1) );
	ASSERT( !(dn22 == ds11) );
	ASSERT( !(dn22 == ds2) );
	ASSERT( !(dn22 == ds22) );

	ASSERT( !(ds1 == dn1) );
	ASSERT( !(ds1 == dn11) );
	ASSERT( !(ds1 == dn2) );
	ASSERT( !(ds1 == dn22) );
	ASSERT( !(ds1 == ds2) );
	ASSERT( !(ds1 == ds22) );

	ASSERT( !(ds11 == dn1) );
	ASSERT( !(ds11 == dn11) );
	ASSERT( !(ds11 == dn2) );
	ASSERT( !(ds11 == dn22) );
	ASSERT( !(ds11 == ds2) );
	ASSERT( !(ds11 == ds22) );

	ASSERT( !(ds2 == dn1) );
	ASSERT( !(ds2 == dn11) );
	ASSERT( !(ds2 == dn2) );
	ASSERT( !(ds2 == dn22) );
	ASSERT( !(ds2 == ds1) );
	ASSERT( !(ds2 == ds11) );

	ASSERT( !(ds22 == dn1) );
	ASSERT( !(ds22 == dn11) );
	ASSERT( !(ds22 == dn2) );
	ASSERT( !(ds22 == dn22) );
	ASSERT( !(ds22 == ds1) );
	ASSERT( !(ds22 == ds11) );
}

void test_ConstructorPorCopia(){
	dato dn1(1);
	dato dn2(2);
	dato ds1("hola");
	dato ds2("mundo");

	dato an1(dn1);
	ASSERT(an1 == dn1);
	dato an2(dn2);
	ASSERT(an2 == dn2);
	dato bs1(ds1);
	ASSERT(bs1 == ds1);
	dato bs2(ds2);
	ASSERT(bs2 == ds2);
}


void testDato(int argc, char **argv)
{
	if(!testSelect(argc,argv,"dato"))
		return;


	cout << "Test de dato" << endl;
	cout << "-----------------------------" << endl;

	RUN_TEST( test_crearDatoConNat );
	RUN_TEST( test_crearDatoConStr );
	RUN_TEST( test_MismoTipo );
	RUN_TEST( test_operadorigualdad );
	RUN_TEST( test_ConstructorPorCopia );
	cout << "-----------------------------" << endl;

}
