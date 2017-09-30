// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>


#include "dato.h"
#include "aed2.h"
#include "diccNat.h"
#include "registro.h"
#include "Driver.h"

#include "test.h"
#include <string>
#include <iostream>

using namespace std;

bool testSelect(int argc,char** argv,string clave)
{
	int positivos = 0;

	Conj<string> args;
	for(int i = 1; i < argc; ++i)
	{
		if(argv[i][0] != '-')
			positivos++;
		args.Agregar(argv[i]);
	}
	return ((argc == 1) || (positivos==0) || args.Pertenece(clave) || args.Pertenece("all")) && (!args.Pertenece("-"+clave));
}

int main(int argc, char **argv) {
  
  cout << endl << endl << "Test de clases de TP3" << endl;
  cout << "-----------------------------" << endl;
  cout << ">Para correr un test en particular indique como parametro la o las clases." << endl;
  cout << ">Para quitar un test indique \'-\' y el test." << endl;
  cout << ">Para ejecutar todos no indique nada o \"all\"" << endl << endl;


  
  	testDriver(argc, argv);
  	testBase(argc, argv);
  	testTabla(argc, argv);
	testDato(argc, argv);
	testRegistro(argc, argv);
	testDiccNat( argc, argv);
	testDiccString( argc, argv );

	/********************************************************************
	* TODO: escribir casos de test exhaustivos para todas              *
	* las funcionalidades de cada módulo.                              *
	* La interacción con el TAD principal se debe hacer exclusivamente *
	* a través de la interfaz del driver.                              *
	********************************************************************/

	return 0;
}
