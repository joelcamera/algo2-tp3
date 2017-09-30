// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>

#include "registro.h"
#include "Tipos.h"
#include "test.h"
#include <string>
#include <iostream>

using namespace std;


void test_campos(){
	NombreCampo nc[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	registro r1;
	//campos esta vacio
	Conj<NombreCampo> c1 = r1.Campos();
	ASSERT( c1.EsVacio() );

	registro r2;
	for(int i = 0; i < 10; i++){
		dato d(i);
		r2.Definir(nc[i],d);
	}

	Conj<NombreCampo> c2 = r2.Campos();
	for(int i = 0; i < 10; i++){
		ASSERT( c2.Pertenece(nc[i]) );
	}
	ASSERT_EQ(c2.Cardinal(), 10);
}

void test_coincidentodos(){
	registro r1;
	registro r2;
	NombreCampo nc[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	for(int i = 0; i < 10; i++){
		dato d(i);
		r1.Definir(nc[i],d);
		r2.Definir(nc[i],d);
	}

	ASSERT( r1.CoincidenTodos(r2, r1.Campos()) );
	ASSERT( r1.CoincidenTodos(r2, r2.Campos()) );
	ASSERT( r2.CoincidenTodos(r1, r1.Campos()) );
	ASSERT( r2.CoincidenTodos(r1, r2.Campos()) );

	Conj<NombreCampo> c1 = r1.Campos();
	Conj<NombreCampo> c2 = r2.Campos();
	c1.Eliminar(nc[0]);
	c1.Eliminar(nc[3]);
	ASSERT( r1.CoincidenTodos(r2, c1) );
	ASSERT( r2.CoincidenTodos(r1, c1) );

	for (int i = 5; i < 10; ++i){
		c2.Eliminar(nc[i]);
	}
	ASSERT( r1.CoincidenTodos(r2, c2) );
	ASSERT( r2.CoincidenTodos(r1, c2) );

	Conj<NombreCampo> c3;
	ASSERT( r1.CoincidenTodos(r2, c3) );
	ASSERT( r2.CoincidenTodos(r1, c3) );
}

void test_agregarcampos(){
	registro r1;
	registro r2;
	NombreCampo nc[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};

	for(int i = 0; i < 10; i++){
		dato d(i);
		r2.Definir(nc[i],d);
	}
	r1.AgregarCampos(r2);

	for(int i = 0; i < 10; i++){
		ASSERT( r1.Definido(nc[i]) );
	}

	registro r3;
	registro r4;
	for(int i = 1; i <= 5; i++){
		dato d2(i*10);
		r4.Definir(nc[i],d2);
	}
	for(int i = 1; i <= 10; i++){
		dato d3(i);
		r3.Definir(nc[i],d3);
	}

	r3.AgregarCampos(r4);
	for(int i = 1; i <=10; i++){
		dato d4(i);
		ASSERT( r3.Definido(nc[i]) );
		ASSERT(r3.Significado(nc[i]) == d4);
	}

	r4.AgregarCampos(r3);
	for(int i = 1; i <= 10; i++){
		ASSERT( r4.Definido(nc[i]) );
		
		if (i < 6){
			dato d5(i*10);
			ASSERT(r4.Significado(nc[i]) == d5);
		} else {
			dato d6(i);
			ASSERT(r4.Significado(nc[i]) == d6);
		}
	}

	registro r5;
	registro r6;
	for(int i = 1; i <= 11; i++){
		dato d7(i);

		if(i < 4 || i > 8){
			r5.Definir(nc[i], d7);
		} else {
			r6.Definir(nc[i], d7);
		}
	}

	r5.AgregarCampos(r6);
	for(int i = 1; i <= 11; i++){
		dato d8(i);
		ASSERT( r5.Definido(nc[i]) );
		ASSERT(r5.Significado(nc[i]) == d8);
	}

	r6.AgregarCampos(r5);
	for(int i = 1; i <= 11; i++){
		dato d9(i);
		ASSERT( r6.Definido(nc[i]) );
		ASSERT(r6.Significado(nc[i]) == d9);
	}


	registro r7;
	registro r8;
	for(int i = 0; i < 10; i++){
		dato d10(i*100);
		r7.Definir(nc[i],d10);
	}
	for(int i = 0; i < 10; i++){
		dato d11(i);
		r8.Definir(nc[i], d11);
	}

	r7.AgregarCampos(r8);
	for(int i = 0; i < 10; i++){
		dato d12(i*100);
		ASSERT( r7.Definido(nc[i]) );
		ASSERT(r7.Significado(nc[i]) == d12);
	}

	r8.AgregarCampos(r7);
	for(int i = 0; i < 10; i++){
		dato d13(i);
		ASSERT( r8.Definido(nc[i]) );
		ASSERT(r8.Significado(nc[i]) == d13);
	}
}


void test_operadorigualdad_reg(){
	NombreCampo nc[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	registro r1;
	registro r2;
	registro r3;
	registro r4;

	//comparo registros vacios
	ASSERT( r1 == r2 );
	ASSERT( !(r1 != r2) );

	for(int i = 0; i < 10; i++){
		dato d1(i);
		r1.Definir(nc[i], d1);
		r2.Definir(nc[i], d1);
	}

	//comparo registros iguales
	ASSERT( r1 == r2 );
	ASSERT( !(r1 != r2) );

	for(int i = 0; i < 10; i++){
		if (i < 5){
			dato d2(i);
			r3.Definir(nc[i], d2);
			r4.Definir(nc[i], d2);
		} else {
			dato d3(nc[i]);
			r3.Definir(nc[i], d3);
			r4.Definir(nc[i], d3);
		}
	}

	//comparo registros iguales con strings y nat como significados
	ASSERT( r3 == r4 && !(r3 != r4) );

	//los registros son distintos a los anteriores
	ASSERT( (r1 != r3) && (r2 != r3) && (r1 != r4) && (r2 != r4) );
}



void testRegistro(int argc, char **argv) {
	if(!testSelect(argc,argv,"registro"))
		return;

	cout << "Test de registro" << endl;
	cout << "-----------------------------" << endl;
	
	RUN_TEST( test_campos );
	RUN_TEST( test_coincidentodos );
	RUN_TEST( test_agregarcampos );
	RUN_TEST( test_operadorigualdad_reg );

	cout << "-----------------------------" << endl;

}
