#ifndef TABLA_H
#define TABLA_H

#include "registro.h"
#include "aed2/Conj.h"
#include "aed2/Dicc.h"
#include "Tipos.h"
#include "dato.h"
#include "diccNat.h"
#include "diccString.h"


typedef Conj< Conj<registro>::Iterador> ConjItReg;
typedef diccNat<ConjItReg> DiccIndiceNat; 
typedef DiccString<ConjItReg> DiccIndiceStr; 


using namespace aed2;

class Tabla
{
	public:
		Tabla(const NombreTabla& nombre, const Conj<NombreCampo>& claves, const registro& columnas);
		Conj<registro>::const_Iterador agregarRegistro(const registro &columnas);
		void borrarRegistro(const registro &criterio);
		bool indexar(const NombreCampo& campo);
		const String& nombre() const;
		Conj<NombreCampo> claves() const;
		Conj<NombreCampo> indices() const;
		Conj<NombreCampo> campos() const;
		const TipoCampo tipoCampo(const NombreCampo& campo) const;
		const Conj<registro>& registros() const;
		Nat cantidadDeAccesos() const;
		dato minimo(const NombreCampo& c) const;
		dato maximo(const NombreCampo& c) const;
		bool puedeIndexar(const NombreCampo& c) const;
		Conj<registro> combinarRegistros(const NombreCampo &c, const Conj<registro> &r) const;
		Conj<registro> coincidencias(const registro &crit) const;
		
	private:
		const DiccIndiceNat& indiceNat();
		const DiccIndiceStr& indiceStr();

		String _nombre;
		struct {NombreCampo iNat; NombreCampo iStr;} _indices;
		Conj<NombreCampo> _claves;
		registro _columnas;
		Conj<registro> _registros;
		DiccIndiceNat _indiceNat;
		DiccIndiceStr _indiceStr;
		Nat _ctAccesos;

		//funciones auxiliares
		void agregarClavesIndices(Conj<registro>::Iterador &r);
		void agregarClaveIndiceNat(Conj<registro>::Iterador &r);
		void agregarClaveIndiceStr(Conj<registro>::Iterador &r);

		void borrarPorIndiceNat(const registro &criterio);
		void borrarPorIndiceStr(const registro &criterio);
		void borrarSinIndice(const registro &criterio);
		void borrarClavesIndices(const registro &r);
		
		void indexarNat(const NombreCampo& campo);
		void indexarStr(const NombreCampo& campo);

		Conj<registro> combinarRegistrosIndiceNat(const NombreCampo &c,const Conj<registro> &r) const;
		Conj<registro> combinarRegistrosIndiceStr(const NombreCampo &c,const Conj<registro> &r) const;
		Conj<registro> combinarRegistrosSinIndice(const NombreCampo &c,const Conj<registro> &r) const;

		Conj<registro> coincidenciasIndiceNat(const registro &crit) const;
		Conj<registro> coincidenciasIndiceStr(const registro &crit) const;
		Conj<registro> coincidenciasSinIndice(const registro &crit) const;

};


#endif /*TABLA_H*/