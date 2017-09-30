#ifndef BASE_H_
#define BASE_H_

#include "diccString.h"
#include "tabla.h"
#include "aed2.h"
#include "Tipos.h"

using namespace std;
using namespace aed2;

class BaseDeDatos {

  public:

	BaseDeDatos();
	~BaseDeDatos();

	//Funciones sobre tablas
	bool AgregarTabla(const Tabla& t);
	Conj<NombreTabla>::const_Iterador Tablas() const;
	Tabla& DameTabla(const NombreTabla& t);
	const Tabla& DameTabla(const NombreTabla& t) const;
	Nat CantidadDeAccesos(const NombreTabla& t) const;
	const NombreTabla& TablaMaxima() const;

	//Operaciones sobre registros
	void InsertarEntrada(const registro& reg, const NombreTabla& t);
	void Borrar(const registro& cr, const NombreTabla& t);
	const Conj<registro>& Registros(const NombreTabla& t) const;
	Conj<registro> Buscar(const registro& criterio, const NombreTabla& t) const;

	//Operaciones sobre joins
	bool HayJoin(const NombreTabla& t1, const NombreTabla& t2) const;
	const NombreCampo& CampoJoin(const NombreTabla& t1, const NombreTabla& t2) const;
	Conj<registro>::const_Iterador GenerarVistaJoin(const NombreTabla& t1, const NombreTabla& t2, const NombreCampo& c);
	Conj<registro>::const_Iterador VistaJoin(const NombreTabla& n1, const NombreTabla& n2);
	void BorrarJoin(const NombreTabla& t1, const NombreTabla& t2);	


  private:


	struct cambio {
		bool borrado;
		registro reg;
		cambio(bool b, const registro& r) : borrado(b), reg(r) {}
	};


	struct infoJoin {
		NombreCampo campo;
		Tabla join;
		Lista<cambio> cambiosT1;
		Lista<cambio> cambiosT2;		
		infoJoin(const NombreCampo& c, const Tabla& j) : campo(c), join(j) {}
	};

	struct infoTabla {
		Tabla tabla;
		DiccString<infoJoin> joinsCon;
		DiccString<infoJoin*> esJoinDe;
		infoTabla(const Tabla& t) : tabla(t) {}
	};

	DiccString<infoTabla> 	tablas;
	NombreTabla 			tablaMaxima;
	Nat 					maxModificaciones;

  	void MantenerCambios(infoTabla& it, const registro& r, bool borrado);
  	registro ColumnasJoin(const Tabla& t1, const Tabla& t2) const;
  	void ActualizarCambios(Lista<cambio>& cambios, const NombreCampo& c, const Tabla& t, Tabla& join);


};


#endif //BASE_H_