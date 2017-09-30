
#include "test.h"
#include "tabla.h"
#include <iostream>



//using namespace std;
//------------------------------------------------------------------------------
Tabla tablaVacia()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	return Tabla("personas",claves,columnas);
}
//------------------------------------------------------------------------------

void testTablaVacia()
{
	Tabla tabla = tablaVacia();

	Conj<NombreCampo> campos;
	campos.Agregar("Nombre");
	campos.Agregar("Apellido");
	campos.Agregar("DNI");
	ASSERT(campos == tabla.campos());
	Conj<NombreCampo> claves;
	claves.Agregar("DNI");
	ASSERT(claves == tabla.claves());
	
	ASSERT(tabla.indices().EsVacio());
	ASSERT(tabla.registros().EsVacio());
}
//------------------------------------------------------------------------------
void testAgregarRegistro()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	Tabla tabla("personas",claves,columnas);

	registro nuevo;
	nuevo.Definir("Nombre",dato("Pedro"));
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	tabla.agregarRegistro(nuevo);
	ASSERT(not tabla.registros().EsVacio());
	ASSERT(tabla.registros().Cardinal() == 1);
	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(not tabla.registros().Pertenece(nuevo1));
	ASSERT(not tabla.registros().Pertenece(nuevo2));
	ASSERT(tabla.cantidadDeAccesos() == 1);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);
	ASSERT(tabla.registros().Cardinal() == 3);
	ASSERT(tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));
	ASSERT(tabla.cantidadDeAccesos() == 3);
}
//------------------------------------------------------------------------------
void testBorrarRegistro()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	Tabla tabla("personas",claves,columnas);

	registro nuevo;
	nuevo.Definir("Nombre",dato("Pedro"));
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	tabla.agregarRegistro(nuevo);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);
	ASSERT(not tabla.registros().EsVacio());
	ASSERT(tabla.registros().Cardinal() == 3);
	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));

	registro criterio;
	criterio.Definir("DNI",dato(104100257));
	tabla.borrarRegistro(criterio);

	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(!tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));
}
//------------------------------------------------------------------------------
void testAgregarIndice()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	Tabla tabla("personas",claves,columnas);

	tabla.indexar("DNI");
	Conj<NombreCampo> indices;
	indices.Agregar("DNI");

	ASSERT(tabla.indices() == indices);
	tabla.indexar("Apellido");

	ASSERT(!(tabla.indices() == indices));
	indices.Agregar("Apellido");
	ASSERT(tabla.indices() == indices);

}
//------------------------------------------------------------------------------
void testAgregarIndiceConRegistros()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	Tabla tabla("personas",claves,columnas);

	registro nuevo;
	nuevo.Definir("Nombre",dato("Pedro"));
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	tabla.agregarRegistro(nuevo);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);

	tabla.indexar("DNI");
	Conj<NombreCampo> indices;
	indices.Agregar("DNI");
	ASSERT(tabla.indices() == indices);
	tabla.indexar("Apellido");

	ASSERT(!(tabla.indices() == indices));
	indices.Agregar("Apellido");
	ASSERT(tabla.indices() == indices);

}
//------------------------------------------------------------------------------
void testAgregarRegistrosConIndice()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");

	Tabla tabla("personas",claves,columnas);

	tabla.indexar("DNI");
	Conj<NombreCampo> indices;
	indices.Agregar("DNI");
	ASSERT(tabla.indices() == indices);
	tabla.indexar("Apellido");

	ASSERT(!(tabla.indices() == indices));
	indices.Agregar("Apellido");
	ASSERT(tabla.indices() == indices);

	registro nuevo;
	nuevo.Definir("Nombre",dato("Pedro"));
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	tabla.agregarRegistro(nuevo);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);

	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));
	
}
//------------------------------------------------------------------------------
void testBorrarRegistroConIndice()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");
	claves.Agregar("Apellido");

	Tabla tabla("personas",claves,columnas);

	tabla.indexar("DNI");
	tabla.indexar("Apellido");

	registro nuevo;
	nuevo.Definir("Nombre",dato("Pedro"));
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	registro nuevo3;
	nuevo3.Definir("Nombre",dato("Pedro3"));
	nuevo3.Definir("Apellido",dato("Lopez3"));
	nuevo3.Definir("DNI",dato(104100259));

	tabla.agregarRegistro(nuevo);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);
	ASSERT(not tabla.registros().EsVacio());
	ASSERT(tabla.registros().Cardinal() == 3);
	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));

	registro criterio;
	criterio.Definir("DNI",dato(104100257));
	tabla.borrarRegistro(criterio);

	//ASSERT_EQ(tabla.indiceNat().CantClaves(),2);
	//ASSERT_EQ(tabla.indiceStr().CantClaves(),2);


	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(!tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));

	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo3);

	ASSERT(tabla.registros().Cardinal() == 4);
	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));
	ASSERT(tabla.registros().Pertenece(nuevo3));

	ASSERT(tabla.claves() == claves);

	//ASSERT(tabla.indiceNat().CantClaves() == 4);
	//ASSERT(tabla.indiceStr().CantClaves() == 4);

	registro criterio1;
	criterio1.Definir("Apellido",dato("Lopez3"));
	tabla.borrarRegistro(criterio1);

	ASSERT_EQ(tabla.registros().Cardinal(),3);
	ASSERT(tabla.registros().Pertenece(nuevo));
	ASSERT(tabla.registros().Pertenece(nuevo1));
	ASSERT(tabla.registros().Pertenece(nuevo2));
	ASSERT(!tabla.registros().Pertenece(nuevo3));

	//ASSERT_EQ(tabla.indiceNat().CantClaves(),3);
	//ASSERT_EQ(tabla.indiceStr().CantClaves(),3);
	/*
	{
		DiccIndiceNat::const_Iterador itdicc = tabla.indiceNat().CrearIt();
		cout << endl << "Indice Nat" << endl;
		while(itdicc.HaySiguiente())
		{
			cout << itdicc.SiguienteClave() << "|" << endl;
			itdicc.Avanzar();
		}
	}
	{
		DiccIndiceStr::const_Iterador itdicc = tabla.indiceStr().CrearIt();
		cout << endl << "Indice Str" << endl;
		while(itdicc.HaySiguiente())
		{
			cout << itdicc.SiguienteClave() << "|" << endl;
			itdicc.Avanzar();
		}
	}
	*/
}
//------------------------------------------------------------------------------
void testCombinarRegistrosSinIndice()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	registro columnas2;
	columnas2.Definir("Carrera",dato(""));
	columnas2.Definir("Curso",dato(""));
	columnas2.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");
	claves.Agregar("Apellido");

	Conj<NombreCampo> claves2;
	claves2.Agregar("DNI");
	
	registro nuevo; 
	nuevo.Definir("Nombre",dato("Pedro")); 
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	registro nuevo3;
	nuevo3.Definir("Nombre",dato("Pedro3"));
	nuevo3.Definir("Apellido",dato("Lopez3"));
	nuevo3.Definir("DNI",dato(104100259));


	registro t2nuevo; 
	t2nuevo.Definir("Carrera",dato("Computacion")); 
	t2nuevo.Definir("Curso",dato("Facil"));
	t2nuevo.Definir("DNI",dato(104100256));

	registro t2nuevo1;
	t2nuevo1.Definir("Carrera",dato("Quimica"));
	t2nuevo1.Definir("Curso",dato("Dificil"));
	t2nuevo1.Definir("DNI",dato(104100257));

	Tabla tabla("personas",claves,columnas);

	//tabla.indexar("DNI");
	//tabla.indexar("Apellido");

	tabla.agregarRegistro(nuevo);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);
	tabla.agregarRegistro(nuevo3);

	Tabla tabla2("cursos",claves2,columnas2);

	//tabla.indexar("DNI");
	
	tabla2.agregarRegistro(t2nuevo);
	tabla2.agregarRegistro(t2nuevo1);
	
	Conj<registro> resJoin = tabla.combinarRegistros("DNI",tabla2.registros());
	Conj<registro> join;
	t2nuevo.AgregarCampos(nuevo);
	t2nuevo1.AgregarCampos(nuevo1);
	join.Agregar(t2nuevo);
	join.Agregar(t2nuevo1);
	ASSERT(resJoin == join);

	/*Conj<registro>::Iterador itJoin = resJoin.CrearIt();
	cout << endl << "Join" << endl;
	while(itJoin.HaySiguiente())
	{
		registro::const_Iterador itrg = itJoin.Siguiente().CrearIt(); 
		while(itrg.HaySiguiente())
		{
			if(itrg.SiguienteSignificado().esNat())
				cout << itrg.SiguienteSignificado().valorNat();
			else
				cout << itrg.SiguienteSignificado().valorStr();	
			itrg.Avanzar();
			cout << " | ";
		}
		cout << endl;
		itJoin.Avanzar();
	}
	*/	
}
//------------------------------------------------------------------------------
void testCombinarRegistrosIndiceNat()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	registro columnas2;
	columnas2.Definir("Carrera",dato(""));
	columnas2.Definir("Curso",dato(""));
	columnas2.Definir("DNI",dato(0));

	Conj<NombreCampo> claves;
	claves.Agregar("DNI");
	claves.Agregar("Apellido");

	Conj<NombreCampo> claves2;
	claves2.Agregar("DNI");
	
	registro nuevo; 
	nuevo.Definir("Nombre",dato("Pedro")); 
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	registro nuevo3;
	nuevo3.Definir("Nombre",dato("Pedro3"));
	nuevo3.Definir("Apellido",dato("Lopez3"));
	nuevo3.Definir("DNI",dato(104100259));


	registro t2nuevo; 
	t2nuevo.Definir("Carrera",dato("Computacion")); 
	t2nuevo.Definir("Curso",dato("Facil"));
	t2nuevo.Definir("DNI",dato(104100256));

	registro t2nuevo1;
	t2nuevo1.Definir("Carrera",dato("Quimica"));
	t2nuevo1.Definir("Curso",dato("Dificil"));
	t2nuevo1.Definir("DNI",dato(104100257));

	Tabla tabla("personas",claves,columnas);

	tabla.indexar("DNI");
	//tabla.indexar("Apellido");

	tabla.agregarRegistro(nuevo);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);
	tabla.agregarRegistro(nuevo3);

	Tabla tabla2("cursos",claves2,columnas2);

	//tabla2.indexar("DNI");
	tabla2.agregarRegistro(t2nuevo);
	tabla2.agregarRegistro(t2nuevo1);
	
	//tabla2.indexar("DNI");

	Conj<registro> resJoin = tabla.combinarRegistros("DNI",tabla2.registros());
	Conj<registro> join;
	t2nuevo.AgregarCampos(nuevo);
	t2nuevo1.AgregarCampos(nuevo1);
	join.Agregar(t2nuevo);
	join.Agregar(t2nuevo1);
	ASSERT(resJoin == join);
	/*
	Conj<registro>::const_Iterador itJoin = resJoin.CrearIt();
	cout << endl << "Join" << endl;
	while(itJoin.HaySiguiente())
	{
		registro::const_Iterador itrg = itJoin.Siguiente().CrearIt(); 
		while(itrg.HaySiguiente())
		{
			if(itrg.SiguienteSignificado().esNat())
				cout << itrg.SiguienteSignificado().valorNat();
			else
				cout << itrg.SiguienteSignificado().valorStr();	
			itrg.Avanzar();
			cout << " | ";
		}
		cout << endl;
		itJoin.Avanzar();
	}
	*/
}
//------------------------------------------------------------------------------
void testCombinarRegistrosIndiceStr()
{
	registro columnas;
	columnas.Definir("Nombre",dato(""));
	columnas.Definir("Apellido",dato(""));
	columnas.Definir("DNI",dato(0));

	registro columnas2;
	columnas2.Definir("Carrera",dato(""));
	columnas2.Definir("Curso",dato(""));
	columnas2.Definir("Apellido",dato(""));


	Conj<NombreCampo> claves;
	claves.Agregar("DNI");
	claves.Agregar("Apellido");

	Conj<NombreCampo> claves2;
	claves2.Agregar("Apellido");
	
	registro nuevo; 
	nuevo.Definir("Nombre",dato("Pedro")); 
	nuevo.Definir("Apellido",dato("Lopez"));
	nuevo.Definir("DNI",dato(104100256));

	registro nuevo1;
	nuevo1.Definir("Nombre",dato("Pedro1"));
	nuevo1.Definir("Apellido",dato("Lopez1"));
	nuevo1.Definir("DNI",dato(104100257));

	registro nuevo2;
	nuevo2.Definir("Nombre",dato("Pedro2"));
	nuevo2.Definir("Apellido",dato("Lopez2"));
	nuevo2.Definir("DNI",dato(104100258));

	registro nuevo3;
	nuevo3.Definir("Nombre",dato("Pedro3"));
	nuevo3.Definir("Apellido",dato("Lopez3"));
	nuevo3.Definir("DNI",dato(104100259));


	registro t2nuevo; 
	t2nuevo.Definir("Carrera",dato("Computacion")); 
	t2nuevo.Definir("Curso",dato("Facil"));
	t2nuevo.Definir("Apellido",dato("Lopez3"));

	registro t2nuevo1;
	t2nuevo1.Definir("Carrera",dato("Quimica"));
	t2nuevo1.Definir("Curso",dato("Dificil"));
	t2nuevo1.Definir("Apellido",dato("Lopez2"));

	Tabla tabla("personas",claves,columnas);

	tabla.indexar("Apellido");
	//tabla.indexar("Apellido");

	tabla.agregarRegistro(nuevo);
	tabla.agregarRegistro(nuevo1);
	tabla.agregarRegistro(nuevo2);
	tabla.agregarRegistro(nuevo3);

	Tabla tabla2("cursos",claves2,columnas2);

	//tabla2.indexar("DNI");
	tabla2.agregarRegistro(t2nuevo);
	tabla2.agregarRegistro(t2nuevo1);
	
	//tabla2.indexar("DNI");

	Conj<registro> resJoin = tabla.combinarRegistros("Apellido",tabla2.registros());
	Conj<registro> join;
	t2nuevo.AgregarCampos(nuevo3);
	t2nuevo1.AgregarCampos(nuevo2);
	join.Agregar(t2nuevo);
	join.Agregar(t2nuevo1);
	ASSERT(resJoin == join);

	/*Conj<registro>::const_Iterador itJoin = resJoin.CrearIt();
	cout << endl << "Join" << endl;
	while(itJoin.HaySiguiente())
	{
		registro::const_Iterador itrg = itJoin.Siguiente().CrearIt(); 
		while(itrg.HaySiguiente())
		{
			if(itrg.SiguienteSignificado().esNat())
				cout << itrg.SiguienteSignificado().valorNat();
			else
				cout << itrg.SiguienteSignificado().valorStr();	
			itrg.Avanzar();
			cout << " | ";
		}
		cout << endl;
		itJoin.Avanzar();
	}*/
}
//------------------------------------------------------------------------------
typedef struct DATA_REG{
		NombreCampo campo;
		dato valor;
	} DATA_REG;

registro setRegistro(DATA_REG datos[])
{
	registro res;
	
	for(int i = 0;datos[i].campo != "";++i)
	{	
		res.Definir(datos[i].campo,datos[i].valor);
	}
	return res;
}
//------------------------------------------------------------------------------
Conj<NombreCampo> setCampos(NombreCampo campos[])
{
	Conj<NombreCampo> res;

	for(int i = 0;campos[i] != "";++i)
		res.Agregar(campos[i]);
	return res;
}
//------------------------------------------------------------------------------
void testCoincidenciasSinIndice()
{
	NombreCampo claves[] = {"DNI",""};
	DATA_REG columnas[] = {{"Nombre",dato("")},{"Apellido",dato("")},{"DNI",dato(0)},{"",dato(0)}};

	DATA_REG datosTabla[][4] = {
		{{"Nombre",dato("Carlos")},{"Apellido",dato("Gimenez")},{"DNI",dato(120)},{"",dato(0)}},
		{{"Nombre",dato("Mr")},{"Apellido",dato("Bean")},{"DNI",dato(130)},{"",dato(0)}},
		{{"Nombre",dato("Jose")},{"Apellido",dato("Cuervo")},{"DNI",dato(250)},{"",dato(0)}},
		{{"Nombre",dato("Max")},{"Apellido",dato("Power")},{"DNI",dato(10010)},{"",dato(0)}},
		{{"Nombre",dato("Max")},{"Apellido",dato("Pepino")},{"DNI",dato(10011)},{"",dato(0)}},
		{{"",dato(0)},{"",dato(0)},{"",dato(0)},{"",dato(0)}}
	};

	Tabla tabla("personar",setCampos(claves),setRegistro(columnas));

	Conj<NombreCampo> c;
	c.Agregar("DNI");

	Conj<NombreCampo> cc;
	cc.Agregar("DNI");
	cc.Agregar("Apellido");
	cc.Agregar("Nombre");

	ASSERT(tabla.claves() == c);
	ASSERT(tabla.campos() == cc);

	ASSERT(tabla.tipoCampo("DNI") == NAT);
	ASSERT(tabla.tipoCampo("Nombre") == STR);
	ASSERT(tabla.tipoCampo("Apellido") == STR);

	for(int i = 0;datosTabla[i][0].campo != "";++i)
		tabla.agregarRegistro(setRegistro(datosTabla[i]));
	
	DATA_REG buscar[] = {{"Nombre",dato("Max")},{"",dato(0)}};

	Conj<registro> busqueda = tabla.coincidencias(setRegistro(buscar));
	ASSERT_EQ(busqueda.Cardinal(),2);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[3])));
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[4])));

	DATA_REG buscar1[] = {{"Nombre",dato("Jose")},{"",dato(0)}};

	busqueda = tabla.coincidencias(setRegistro(buscar1));
	ASSERT_EQ(busqueda.Cardinal(),1);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[2])));

	//ASSERT(busqueda.Pertenece(setRegistro(datosTabla[4])));
	//ASSERT(busqueda.Pertenece(setRegistro(datosTabla[2])));

}
//------------------------------------------------------------------------------
void testCoincidenciasIndiceNat()
{
	NombreCampo claves[] = {"DNI",""};
	DATA_REG columnas[] = {{"Nombre",dato("")},{"Apellido",dato("")},{"DNI",dato(0)},{"",dato(0)}};

	DATA_REG datosTabla[][4] = {
		{{"Nombre",dato("Carlos")},{"Apellido",dato("Gimenez")},{"DNI",dato(120)},{"",dato(0)}},
		{{"Nombre",dato("Mr")},{"Apellido",dato("Bean")},{"DNI",dato(130)},{"",dato(0)}},
		{{"Nombre",dato("Jose")},{"Apellido",dato("Cuervo")},{"DNI",dato(250)},{"",dato(0)}},
		{{"Nombre",dato("Max")},{"Apellido",dato("Power")},{"DNI",dato(10010)},{"",dato(0)}},
		{{"Nombre",dato("Max")},{"Apellido",dato("Pepino")},{"DNI",dato(10011)},{"",dato(0)}},
		{{"",dato(0)},{"",dato(0)},{"",dato(0)},{"",dato(0)}}
	};

	Tabla tabla("personar",setCampos(claves),setRegistro(columnas));

	Conj<NombreCampo> c;
	c.Agregar("DNI");

	Conj<NombreCampo> cc;
	cc.Agregar("DNI");
	cc.Agregar("Apellido");
	cc.Agregar("Nombre");

	ASSERT(tabla.claves() == c);
	ASSERT(tabla.campos() == cc);

	ASSERT(tabla.tipoCampo("DNI") == NAT);
	ASSERT(tabla.tipoCampo("Nombre") == STR);
	ASSERT(tabla.tipoCampo("Apellido") == STR);

	for(int i = 0;datosTabla[i][0].campo != "";++i)
		tabla.agregarRegistro(setRegistro(datosTabla[i]));
	
	DATA_REG buscar[] = {{"Nombre",dato("Max")},{"",dato(0)}};

	Conj<registro> busqueda = tabla.coincidencias(setRegistro(buscar));
	ASSERT_EQ(busqueda.Cardinal(),2);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[3])));
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[4])));

	DATA_REG buscar1[] = {{"Nombre",dato("Jose")},{"",dato(0)}};
	busqueda = tabla.coincidencias(setRegistro(buscar1));

	ASSERT_EQ(busqueda.Cardinal(),1);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[2])));

	tabla.indexar("DNI");

	DATA_REG buscar2[] = {{"DNI",dato(130)},{"",dato(0)}};
	busqueda = tabla.coincidencias(setRegistro(buscar2));
	
	ASSERT_EQ(busqueda.Cardinal(),1);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[1])));

	//ASSERT(busqueda.Pertenece(setRegistro(datosTabla[4])));
	//ASSERT(busqueda.Pertenece(setRegistro(datosTabla[2])));

}
//------------------------------------------------------------------------------
void testCoincidenciasIndiceStr()
{
	NombreCampo claves[] = {"DNI",""};
	DATA_REG columnas[] = {{"Nombre",dato("")},{"Apellido",dato("")},{"DNI",dato(0)},{"",dato(0)}};

	DATA_REG datosTabla[][4] = {
		{{"Nombre",dato("Carlos")},{"Apellido",dato("Gimenez")},{"DNI",dato(120)},{"",dato(0)}},
		{{"Nombre",dato("Mr")},{"Apellido",dato("Bean")},{"DNI",dato(130)},{"",dato(0)}},
		{{"Nombre",dato("Jose")},{"Apellido",dato("Cuervo")},{"DNI",dato(250)},{"",dato(0)}},
		{{"Nombre",dato("Max")},{"Apellido",dato("Power")},{"DNI",dato(10010)},{"",dato(0)}},
		{{"Nombre",dato("Max")},{"Apellido",dato("Pepino")},{"DNI",dato(10011)},{"",dato(0)}},
		{{"",dato(0)},{"",dato(0)},{"",dato(0)},{"",dato(0)}}
	};

	Tabla tabla("personar",setCampos(claves),setRegistro(columnas));

	Conj<NombreCampo> c;
	c.Agregar("DNI");

	Conj<NombreCampo> cc;
	cc.Agregar("DNI");
	cc.Agregar("Apellido");
	cc.Agregar("Nombre");

	ASSERT(tabla.claves() == c);
	ASSERT(tabla.campos() == cc);

	ASSERT(tabla.tipoCampo("DNI") == NAT);
	ASSERT(tabla.tipoCampo("Nombre") == STR);
	ASSERT(tabla.tipoCampo("Apellido") == STR);

	for(int i = 0;datosTabla[i][0].campo != "";++i)
		tabla.agregarRegistro(setRegistro(datosTabla[i]));
	
	DATA_REG buscar[] = {{"Nombre",dato("Max")},{"",dato(0)}};

	Conj<registro> busqueda = tabla.coincidencias(setRegistro(buscar));
	ASSERT_EQ(busqueda.Cardinal(),2);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[3])));
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[4])));

	DATA_REG buscar1[] = {{"Nombre",dato("Jose")},{"",dato(0)}};
	busqueda = tabla.coincidencias(setRegistro(buscar1));

	ASSERT_EQ(busqueda.Cardinal(),1);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[2])));

	tabla.indexar("Apellido");

	DATA_REG buscar2[] = {{"Apellido",dato("Power")},{"",dato(0)}};
	busqueda = tabla.coincidencias(setRegistro(buscar2));
	
	ASSERT_EQ(busqueda.Cardinal(),1);
	ASSERT(busqueda.Pertenece(setRegistro(datosTabla[3])));

	//ASSERT(busqueda.Pertenece(setRegistro(datosTabla[4])));
	//ASSERT(busqueda.Pertenece(setRegistro(datosTabla[2])));

}
//------------------------------------------------------------------------------
void testTabla(int argc, char**argv)
{
	if(!testSelect(argc,argv,"tabla"))
		return;

	cout << "Tests de tabla" << endl;
	cout << "-----------------------------" << endl;

	RUN_TEST( testTablaVacia );
	RUN_TEST( testAgregarRegistro );
	RUN_TEST( testBorrarRegistro );
	RUN_TEST( testAgregarIndice );
	RUN_TEST( testAgregarIndiceConRegistros );
	RUN_TEST( testAgregarRegistrosConIndice );
	RUN_TEST( testBorrarRegistroConIndice );
	RUN_TEST( testCombinarRegistrosSinIndice);
	RUN_TEST( testCombinarRegistrosIndiceNat);
	RUN_TEST( testCombinarRegistrosIndiceStr);
	RUN_TEST( testCoincidenciasSinIndice);
	RUN_TEST( testCoincidenciasIndiceNat);
	RUN_TEST( testCoincidenciasIndiceStr);
	cout << "-----------------------------" << endl;
}
//------------------------------------------------------------------------------