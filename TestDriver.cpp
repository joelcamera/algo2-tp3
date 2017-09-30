#include "test.h" 
#include "Driver.h"

Columna col(NombreCampo nombre, TipoCampo tipo) {
	Columna c;
	c.nombre = nombre;
	c.tipo = tipo;
	return c;
}

void crearTablaAux1(Driver& d, const NombreTabla& t) {
	aed2::Conj<Columna> columnas;
	columnas.Agregar(col("Nombre",   STR));
	columnas.Agregar(col("Apellido", STR));
	columnas.Agregar(col("DNI",      NAT));
	aed2::Conj<NombreCampo> claves;
	claves.Agregar("DNI");
	
	d.crearTabla(t, columnas, claves);

}

void crearTablaAux2(Driver& d, const NombreTabla& t) {
	aed2::Conj<Columna> columnas;
	columnas.Agregar(col("Direccion", STR));
	columnas.Agregar(col("DNI",      NAT));
	aed2::Conj<NombreCampo> claves;
	claves.Agregar("DNI");
	
	d.crearTabla(t, columnas, claves);
}


void insertarAux1(Driver& d, const NombreTabla& n, const Driver::Dato& nombre, const Driver::Dato& apellido, const Driver::Dato& dni) {
	aed2::Dicc<NombreCampo, Driver::Dato> r;
	r.Definir("Nombre",nombre);
	r.Definir("Apellido",apellido);
	r.Definir("DNI",dni);
	d.insertarRegistro(n, r);
}

void insertarAux2(Driver& d, const NombreTabla& n, const Driver::Dato& direccion, const Driver::Dato& dni) {
	aed2::Dicc<NombreCampo, Driver::Dato> r;
	r.Definir("Direccion",direccion);
	r.Definir("DNI",dni);
	d.insertarRegistro(n, r);
}


void test_driver_1() {
	Driver d;
	NombreTabla n("tabla1");
	crearTablaAux1(d, n);
	Conj<Columna> cols = d.columnasDeTabla(n);
	Conj<NombreCampo> claves = d.columnasClaveDeTabla(n);
	ASSERT( cols.Pertenece(col("Nombre",   STR)) );
	ASSERT( cols.Pertenece(col("Apellido",   STR)) );
	ASSERT( cols.Pertenece(col("DNI",   NAT)) );
	ASSERT_EQ( cols.Cardinal(), 3);
	ASSERT_EQ( claves.Cardinal(), 1);
	ASSERT( claves.Pertenece("DNI") );

}


void test_driver_insertar_borrar() {
	Driver d;
	NombreTabla n("tabla1");
	crearTablaAux1(d, n);
	insertarAux1(d, n, Driver::Dato("juan"), Driver::Dato("perez"), Driver::Dato(123));
	d.borrarRegistro(n, "DNI", Driver::Dato(123));
}



void test_driver_accessos_minimo_maximo() {
	Driver d;
	NombreTabla n("tabla1");
	crearTablaAux1(d, n);

	ASSERT(!d.tieneIndiceNat(n));
	ASSERT(!d.tieneIndiceString(n));

	d.crearIndiceString(n, "Nombre");
	ASSERT(!d.tieneIndiceNat(n));
	ASSERT(d.tieneIndiceString(n));

	d.crearIndiceNat(n, "DNI");
	ASSERT(d.tieneIndiceNat(n));
	ASSERT(d.tieneIndiceString(n));

	ASSERT_EQ(d.campoIndiceString(n), "Nombre");
	ASSERT_EQ(d.campoIndiceNat(n), "DNI");

	insertarAux1(d, n, Driver::Dato("juan"), Driver::Dato("perez"), Driver::Dato(123));
	ASSERT_EQ(d.cantidadDeAccesosDeTabla(n), 1);
	insertarAux1(d, n, Driver::Dato("aaa"), Driver::Dato("bbb"), Driver::Dato(555));
	ASSERT_EQ(d.cantidadDeAccesosDeTabla(n), 2);
	insertarAux1(d, n, Driver::Dato("xxxa"), Driver::Dato("yyy"), Driver::Dato(0));
	ASSERT_EQ(d.cantidadDeAccesosDeTabla(n), 3);
	insertarAux1(d, n, Driver::Dato("xxxb"), Driver::Dato("zzz"), Driver::Dato(1));
	ASSERT_EQ(d.cantidadDeAccesosDeTabla(n), 4);

	ASSERT(d.minimo(n, "Nombre")   == Driver::Dato("aaa"));
	ASSERT(d.minimo(n, "DNI")      == Driver::Dato(0));
	ASSERT(d.maximo(n, "Nombre")   == Driver::Dato("xxxb"));
	ASSERT(d.maximo(n, "DNI")      == Driver::Dato(555));

	d.borrarRegistro(n, "DNI", Driver::Dato(123));
	ASSERT_EQ(d.cantidadDeAccesosDeTabla(n), 5);

	d.borrarRegistro(n, "DNI", Driver::Dato(0));
	d.borrarRegistro(n, "DNI", Driver::Dato(1));
	ASSERT_EQ(d.cantidadDeAccesosDeTabla(n), 7);

	ASSERT(d.minimo(n, "Nombre")   == Driver::Dato("aaa"));
	ASSERT(d.minimo(n, "DNI")      == Driver::Dato(555));
	ASSERT(d.maximo(n, "Nombre")   == Driver::Dato("aaa"));
	ASSERT(d.maximo(n, "DNI")      == Driver::Dato(555));
}


void test_driver_joins() {

	NombreTabla n1("tabla1");
	NombreTabla n2("tabla2");
	Driver d;
	crearTablaAux1(d, n1);
	crearTablaAux2(d, n2);


	insertarAux1(d, n1, Driver::Dato("juan"),    Driver::Dato("perez"), Driver::Dato(123));
	insertarAux1(d, n1, Driver::Dato("alberto"), Driver::Dato("perez"), Driver::Dato(0));
	insertarAux2(d, n2, Driver::Dato("aca cerca"),              Driver::Dato(123));
	insertarAux2(d, n2, Driver::Dato("un poco mas lejos"),      Driver::Dato(2));


	ASSERT( !d.hayJoin(n1, n2) );
	d.generarVistaJoin(n1, n2, "DNI");
	ASSERT( d.hayJoin(n1, n2) );
	
	Conj< Dicc<NombreCampo, Driver::Dato> >regs = d.vistaJoin(n1, n2);
	Conj< Dicc<NombreCampo, Driver::Dato> >::const_Iterador it = regs.CrearIt();
	ASSERT( it.HaySiguiente() );
	const Dicc<NombreCampo, Driver::Dato>& r = it.Siguiente();
	ASSERT( r.Significado("Nombre")    == Driver::Dato("juan"));
	ASSERT( r.Significado("Apellido" ) == Driver::Dato("perez"));
	ASSERT( r.Significado("Direccion") == Driver::Dato("aca cerca"));
	ASSERT( r.Significado("DNI")       == Driver::Dato(123));
	ASSERT_EQ( r.CantClaves(), 4);
	it.Avanzar();
	ASSERT( !it.HaySiguiente() );

	ASSERT( d.hayJoin(n1, n2) );
	ASSERT_EQ( d.campoJoin(n1, n2), "DNI");
	d.borrarVistaJoin( n1, n2 );
	ASSERT( !d.hayJoin(n1, n2) );


}



void testDriver(int argc, char **argv) {


	if(!testSelect(argc,argv,"driver"))
		return;

	cout << "Test de Driver" << endl;
	cout << "-----------------------------" << endl;
	RUN_TEST( test_driver_1 );
	RUN_TEST( test_driver_insertar_borrar );
	RUN_TEST( test_driver_accessos_minimo_maximo );
	RUN_TEST( test_driver_joins );
	cout << "-----------------------------" << endl;

}
