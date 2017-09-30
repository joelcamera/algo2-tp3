#include "test.h"

#include "diccString.h"

void test_dicstr_basico() {

	string c1("ClaveDefinida");
	string c2("ClaveNoDefinida");

	DiccString<Nat> d;
	d.Definir(c1, 1);
	ASSERT( d.Definido(c1) );
	ASSERT( !d.Definido(c2) );
	ASSERT( d.Significado(c1) == 1 );
	d.Borrar(c1);
	ASSERT( !d.Definido(c1) );
	
}
 
int donde(Arreglo<String>& a, string& c) {
	for(Nat i = 0; i < a.Tamanho(); i++) {
		if(a[i].compare(c)==0) return i;
	}
	return -1;
}



void test_dicstr_it_claves_min_max() {

	Arreglo<string> claves(10);
	claves.Definir(0, "");
	claves.Definir(1, "a");
	claves.Definir(2, "aca");
	claves.Definir(3, "bla");
	claves.Definir(4, "zzzz");

	DiccString<Nat> d;
	for(Nat i = 0; i < 5; i++) {
		d.Definir(claves[i], i);
	}

	Conj<String>::const_Iterador it = d.CrearItClaves();
	for(Nat i = 0; i < 5; i++) {
		string c = it.Siguiente();
		Nat j = donde(claves, c);
		ASSERT( j >=0 );
		ASSERT_EQ(it.Siguiente(), claves[j]);
		ASSERT(d.Significado(it.Siguiente()) == j);
		it.Avanzar();
	}

	ASSERT_EQ(d.ClaveMinima(), "");
	ASSERT_EQ(d.ClaveMaxima(), "zzzz");
	d.Borrar("");
	ASSERT_EQ(d.ClaveMinima(), "a");

}

void completarDicc(DiccString<Nat>& d) {

	Arreglo<string> claves(10);
	claves.Definir(0, "");
	claves.Definir(1, "a");
	claves.Definir(2, "aca");
	claves.Definir(3, "bla");
	claves.Definir(4, "zzzz");

	for(Nat i = 0; i < 5; i++) {
		d.Definir(claves[i], i);
	}

}

void test_dicstr_copies() {

	DiccString<Nat> d;
	completarDicc(d);
	
	DiccString<Nat> d2(d);
	ASSERT((d == d2) == true);

	d = d2;
	ASSERT((d == d2) == true);

}

void test_dicstr_de_dicstr() {

	DiccString<Nat> d;
	completarDicc(d);

	DiccString<Nat> d2;
	completarDicc(d2);

	DiccString< DiccString<Nat> > dd;
	dd.Definir("dicc1", d);	
	dd.Definir("dicc2", d2);	

	ASSERT( d == dd.Significado("dicc1") );
	ASSERT( d2 == dd.Significado("dicc2") );

}


void testDiccString(int argc, char **argv) {

	if(!testSelect(argc,argv,"diccstring"))
		return;

	cout << "Test de diccstring" << endl;
	cout << "-----------------------------" << endl;
	RUN_TEST( test_dicstr_basico );
	RUN_TEST( test_dicstr_it_claves_min_max );
	RUN_TEST( test_dicstr_copies );
	RUN_TEST( test_dicstr_de_dicstr );
	cout << "-----------------------------" << endl;

}