#include "base.h"
#include "test.h"
#include "tabla.h"


Tabla tablaVaciaAux2(const NombreTabla& n)
{
	registro columnas;
	columnas.Definir("Direccion",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	return Tabla(n,claves,columnas);
}


Tabla tablaVaciaAux(const NombreTabla& n)
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	return Tabla(n,claves,columnas);
}


void insertarAux1(BaseDeDatos& b, const NombreTabla& n, const dato& nombre, const dato& apellido, const dato& dni) {
	registro r;
	r.Definir("Nombre",nombre);
	r.Definir("Apellido",apellido);
	r.Definir("DNI",dni);
	b.InsertarEntrada(r, n);
}

void insertarAux2(BaseDeDatos& b, const NombreTabla& n, const dato& direccion, const dato& dni) {
	registro r;
	r.Definir("Direccion",direccion);
	r.Definir("DNI",dni);
	b.InsertarEntrada(r, n);
}


void test_base_agregar_tabla() {

	BaseDeDatos b;
	Tabla t1 = tablaVaciaAux("tabla1");
	Tabla t2 = tablaVaciaAux("tabla2");
	
	ASSERT( b.AgregarTabla(t1) );
	ASSERT( !b.AgregarTabla(t1) );
	ASSERT( b.AgregarTabla(t2) );

	Conj<NombreTabla>::const_Iterador it = b.Tablas();
	ASSERT( it.HaySiguiente() );
	ASSERT_EQ( it.Siguiente(), "tabla2" );
	it.Avanzar();
	ASSERT( it.HaySiguiente() );
	ASSERT_EQ( it.Siguiente(), "tabla1" );
	it.Avanzar();
	ASSERT( !it.HaySiguiente() );

}


void test_base_dame_tabla() {

	BaseDeDatos b;
	Tabla t1 = tablaVaciaAux("tabla1");
	Tabla t2 = tablaVaciaAux("tabla2");
	
	ASSERT( b.AgregarTabla(t1) );
	ASSERT( b.AgregarTabla(t2) );
	ASSERT_EQ( b.DameTabla("tabla1").nombre(), t1.nombre());
	ASSERT_EQ( b.DameTabla("tabla2").nombre(), t2.nombre());

}


void test_base_insertar_entrada_y_borrar() {

	NombreTabla n("tabla1");
	BaseDeDatos b;
	Tabla t1 = tablaVaciaAux(n);
	
	ASSERT( b.AgregarTabla(t1) );

	ASSERT_EQ( b.TablaMaxima(), "");

	insertarAux1(b, n, dato("juan"), dato("perez"), dato(123));


	ASSERT_EQ( b.TablaMaxima(), n);
	ASSERT_EQ( b.CantidadDeAccesos(n), 1);

	insertarAux1(b, n, dato("juan"), dato("perez"), dato(1234));

	ASSERT_EQ( b.CantidadDeAccesos(n), 2);

	registro criterio;
	criterio.Definir("DNI",dato(123));
	b.Borrar(criterio, n);
	ASSERT_EQ( b.CantidadDeAccesos(n), 3);

}



void test_base_generar_vista_join() {

	NombreTabla n1("tabla1");
	NombreTabla n2("tabla2");
	BaseDeDatos b;
	Tabla t1 = tablaVaciaAux(n1);
	Tabla t2 = tablaVaciaAux2(n2);
	
	ASSERT( b.AgregarTabla(t1) );
	ASSERT( b.AgregarTabla(t2) );

	insertarAux1(b, n1, dato("juan"),    dato("perez"), dato(123));
	insertarAux1(b, n1, dato("alberto"), dato("perez"), dato(0));
	insertarAux2(b, n2, dato("aca cerca"),              dato(123));
	insertarAux2(b, n2, dato("un poco mas lejos"),      dato(2));

	Conj<registro>::const_Iterador it = b.GenerarVistaJoin(n1, n2, "DNI");
	ASSERT( it.HaySiguiente() );
	const registro& r = it.Siguiente();
	ASSERT( r.Significado("Nombre")    == dato("juan"));
	ASSERT( r.Significado("Apellido" ) == dato("perez"));
	ASSERT( r.Significado("Direccion") == dato("aca cerca"));
	ASSERT( r.Significado("DNI")       == dato(123));
	ASSERT_EQ( r.Campos().Cardinal(), 4);
	it.Avanzar();
	ASSERT( !it.HaySiguiente() );

	ASSERT( b.HayJoin(n1, n2) );
	ASSERT_EQ( b.CampoJoin(n1, n2), "DNI");
	b.BorrarJoin( n1, n2 );
	ASSERT( !b.HayJoin(n1, n2) );


}




void test_base_vista_join() {

	NombreTabla n1("tabla1");
	NombreTabla n2("tabla2");
	BaseDeDatos b;
	Tabla t1 = tablaVaciaAux(n1);
	Tabla t2 = tablaVaciaAux2(n2);
	
	ASSERT( b.AgregarTabla(t1) );
	ASSERT( b.AgregarTabla(t2) );

	insertarAux1(b, n1, dato("juan"),    dato("perez"), dato(123));
	insertarAux1(b, n1, dato("alberto"), dato("perez"), dato(0));
	insertarAux2(b, n2, dato("aca cerca"),              dato(123));
	insertarAux2(b, n2, dato("un poco mas lejos"),      dato(2));

	b.GenerarVistaJoin(n1, n2, "DNI");

	insertarAux1(b, n1, dato("roberto"), dato("bla bla"), dato(2));

	registro criterio;
	criterio.Definir("DNI",dato(123));
	b.Borrar(criterio, n2);


	Conj<registro>::const_Iterador it = b.VistaJoin(n1, n2);
	ASSERT( it.HaySiguiente() );
	const registro& r = it.Siguiente();
	ASSERT( r.Significado("Nombre")    == dato("roberto"));
	ASSERT( r.Significado("Apellido" ) == dato("bla bla"));
	ASSERT( r.Significado("Direccion") == dato("un poco mas lejos"));
	ASSERT( r.Significado("DNI")       == dato(2));
	ASSERT_EQ( r.Campos().Cardinal(), 4);
	it.Avanzar();
	ASSERT( !it.HaySiguiente() );

	criterio.Definir("DNI",dato(2));
	b.Borrar(criterio, n2);

	it = b.VistaJoin(n1, n2);
	ASSERT( !it.HaySiguiente() );


}


void testBase(int argc, char **argv) {


	if(!testSelect(argc,argv,"base"))
		return;

	cout << "Test de base" << endl;
	cout << "-----------------------------" << endl;
	RUN_TEST( test_base_agregar_tabla );
	RUN_TEST( test_base_dame_tabla );
	RUN_TEST( test_base_insertar_entrada_y_borrar );
	RUN_TEST( test_base_generar_vista_join );
	RUN_TEST( test_base_vista_join );
	cout << "-----------------------------" << endl;

}

