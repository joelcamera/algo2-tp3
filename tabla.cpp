#include "tabla.h"


//--------------------------------------------------------------------------
Tabla::Tabla(const NombreTabla& nombre, const Conj<NombreCampo>& claves, const registro& columnas)
{
	assert(not claves.EsVacio());// && )
	_nombre = nombre;
	_columnas = columnas;
	_claves = claves;
	_indices.iNat = "";
	_indices.iStr = "";
	_ctAccesos = 0;
	//_registros, _indiceNat e _indiceStr se construyen vacios

}
//--------------------------------------------------------------------------
Conj<registro>::const_Iterador Tabla::agregarRegistro(const registro &r)
{
	_ctAccesos++;
	Conj<registro>::Iterador itreg = _registros.AgregarRapido(r);
	agregarClavesIndices(itreg);
	return itreg;
}
//--------------------------------------------------------------------------
void Tabla::agregarClavesIndices(Conj<registro>::Iterador &r)
{
	if(_indices.iNat != "")
		agregarClaveIndiceNat(r);
	
	if(_indices.iStr != "")
		agregarClaveIndiceStr(r);
}
//--------------------------------------------------------------------------
void Tabla::agregarClaveIndiceNat(Conj<registro>::Iterador &r)
{

	Nat clave = r.Siguiente().Significado(_indices.iNat).valorNat();
	
	if(_indiceNat.Definido(clave))
	{
		ConjItReg cr = _indiceNat.Significado(clave);
		cr.AgregarRapido(r);
		_indiceNat.Definir(clave,cr);
	}
	else
	{
		ConjItReg cr;
		cr.AgregarRapido(r);
		_indiceNat.Definir(clave,cr);
	}
	
}
//--------------------------------------------------------------------------
void Tabla::agregarClaveIndiceStr(Conj<registro>::Iterador &r)
{
	String clave = r.Siguiente().Significado(_indices.iStr).valorStr();
	
	if(_indiceStr.Definido(clave))
	{
		ConjItReg cr = _indiceStr.Significado(clave);
		cr.AgregarRapido(r);
		_indiceStr.Definir(clave,cr);
	}
	else
	{
		ConjItReg cr;
		cr.AgregarRapido(r);
		_indiceStr.Definir(clave,cr);
	}	
}
//--------------------------------------------------------------------------
void Tabla::borrarRegistro(const registro &criterio) //interface
{
	NombreCampo campoCrit = criterio.CrearIt().SiguienteClave();
	if(campoCrit == _indices.iNat)
		borrarPorIndiceNat(criterio);
	else if (campoCrit == _indices.iStr)
		borrarPorIndiceStr(criterio);
	else
		borrarSinIndice(criterio);

	
}
//--------------------------------------------------------------------------
void Tabla::borrarPorIndiceNat(const registro &criterio) //privada
{
	NombreCampo campoCrit = criterio.CrearIt().SiguienteClave();
	dato datoCrit = criterio.CrearIt().SiguienteSignificado();

	if(_indiceNat.Definido(datoCrit.valorNat()))
	{
		ConjItReg mismoIndice = _indiceNat.Significado(datoCrit.valorNat());
		Conj<registro>::Iterador itreg = mismoIndice.CrearIt().Siguiente();
		borrarClavesIndices(itreg.Siguiente());
		itreg.EliminarSiguiente();
		//elimino uno solo porque el criterio siempre es clave
		_ctAccesos++;
	}
}
//--------------------------------------------------------------------------
void Tabla::borrarPorIndiceStr(const registro &criterio) //privada
{
	NombreCampo campoCrit = criterio.CrearIt().SiguienteClave();
	dato datoCrit = criterio.CrearIt().SiguienteSignificado();

	if(_indiceStr.Definido(datoCrit.valorStr()))
	{
		ConjItReg mismoIndice = _indiceStr.Significado(datoCrit.valorStr());
		Conj<registro>::Iterador itreg = mismoIndice.CrearIt().Siguiente();
		borrarClavesIndices(itreg.Siguiente());
		itreg.EliminarSiguiente();
		//elimino uno solo porque el criterio siempre es clave
		_ctAccesos++;
	}
}
//--------------------------------------------------------------------------
void Tabla::borrarSinIndice(const registro &criterio) //privada
{
	NombreCampo campoCrit = criterio.CrearIt().SiguienteClave();
	dato datoCrit = criterio.CrearIt().SiguienteSignificado();
	Conj<registro>::Iterador itreg = _registros.CrearIt();
	while(itreg.HaySiguiente() && !(itreg.Siguiente().Significado(campoCrit) == datoCrit))
		itreg.Avanzar();

	if(itreg.HaySiguiente())
	{
		borrarClavesIndices(itreg.Siguiente());
		itreg.EliminarSiguiente();
		//elimino uno solo porque el criterio siempre es clave
		_ctAccesos++;
	}
	
}
//--------------------------------------------------------------------------
void Tabla::borrarClavesIndices(const registro &criterio) //privada
{
	if(_indices.iNat != "")
		_indiceNat.Borrar(criterio.Significado(_indices.iNat).valorNat());
	if(_indices.iStr != "")
		_indiceStr.Borrar(criterio.Significado(_indices.iStr).valorStr());
}
//--------------------------------------------------------------------------
bool Tabla::indexar(const NombreCampo& campo) //interface
{
	bool res = puedeIndexar(campo);
	if(res)
	{
		if(tipoCampo(campo) == NAT)
			indexarNat(campo);
		else
			indexarStr(campo);
	}
	return res;
}
//--------------------------------------------------------------------------
void Tabla::indexarNat(const NombreCampo& campo) //interface
{
	_indices.iNat = campo;
	Conj<registro>::Iterador itReg = _registros.CrearIt();
	while(itReg.HaySiguiente())
	{
		agregarClaveIndiceNat(itReg);
		itReg.Avanzar();
	}
	
}
//--------------------------------------------------------------------------
void Tabla::indexarStr(const NombreCampo& campo) //interface
{
	_indices.iStr = campo;
	Conj<registro>::Iterador itReg = _registros.CrearIt();
	while(itReg.HaySiguiente())
	{
		agregarClaveIndiceStr(itReg);
		itReg.Avanzar();
	}
		
}
//--------------------------------------------------------------------------
const String& Tabla::nombre() const
{
	return this->_nombre;
}
//--------------------------------------------------------------------------
Conj<NombreCampo> Tabla::claves() const
{
	return this->_claves;
}
//--------------------------------------------------------------------------
Conj<NombreCampo> Tabla::indices() const
{
	Conj<NombreCampo> res;

	if(_indices.iStr != "")
		res.AgregarRapido(_indices.iStr);

	if(_indices.iNat != "")
		res.AgregarRapido(_indices.iNat);

	return res;
}
//--------------------------------------------------------------------------
Conj<NombreCampo> Tabla::campos() const
{
	return _columnas.Campos();
}
//--------------------------------------------------------------------------
const TipoCampo Tabla::tipoCampo(const NombreCampo& campo) const
{
	assert(_columnas.Definido(campo));
	return (_columnas.Significado(campo).esNat() ? NAT : STR);
}
//--------------------------------------------------------------------------
const Conj<registro>& Tabla::registros() const
{
	return _registros;
}
//--------------------------------------------------------------------------
Nat Tabla::cantidadDeAccesos() const
{
	return _ctAccesos;
}
//--------------------------------------------------------------------------
dato Tabla::minimo(const NombreCampo &c) const
{
	if(c == _indices.iNat)
		return dato(_indiceNat.ClaveMinima());
	else if(c == _indices.iStr)
		return dato(_indiceStr.ClaveMinima());
	else
		assert(false);
}
//--------------------------------------------------------------------------
dato Tabla::maximo(const NombreCampo &c) const
{
	if(c == _indices.iNat)
		return dato(_indiceNat.ClaveMaxima());
	else if(c == _indices.iStr)
		return dato(_indiceStr.ClaveMaxima());
	else
		assert(false);
}
//--------------------------------------------------------------------------
bool Tabla::puedeIndexar(const NombreCampo &c) const
{
	bool res = _columnas.Definido(c);
	if(tipoCampo(c) == NAT)
		res &= (_indices.iNat == "");
	else
		res &= (_indices.iStr == "");

	return res;
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::combinarRegistros(const NombreCampo& c,const  Conj<registro> &r) const
{
	if(_indices.iNat == c)
		return combinarRegistrosIndiceNat(c,r);
	else if (_indices.iStr == c)
		return combinarRegistrosIndiceStr(c,r);
	else
		return combinarRegistrosSinIndice(c,r);
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::combinarRegistrosIndiceNat(const NombreCampo &c,const  Conj<registro> &r) const 
{
	Conj<registro> res;
	Conj<registro>::const_Iterador itreg1 = r.CrearIt();
	while(itreg1.HaySiguiente())
	{
		Nat filtro = itreg1.Siguiente().Significado(c).valorNat();
		if(_indiceNat.Definido(filtro))
		{
			registro rcopia = itreg1.Siguiente();
			rcopia.AgregarCampos(_indiceNat.Significado(filtro).CrearIt().Siguiente().Siguiente());
			res.AgregarRapido(rcopia);
		}
		itreg1.Avanzar();
	}
	return res;		
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::combinarRegistrosIndiceStr(const NombreCampo& c,const  Conj<registro> &r) const
{
	Conj<registro> res;
	Conj<registro>::const_Iterador itreg1 = r.CrearIt();
	while(itreg1.HaySiguiente())
	{
		String filtro = itreg1.Siguiente().Significado(c).valorStr();
		if(_indiceStr.Definido(filtro))
		{
			registro rcopia = itreg1.Siguiente();
			rcopia.AgregarCampos(_indiceStr.Significado(filtro).CrearIt().Siguiente().Siguiente());
			res.AgregarRapido(rcopia);
		}
		itreg1.Avanzar();
	}
	return res;	
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::combinarRegistrosSinIndice(const NombreCampo& c,const  Conj<registro> &r) const 
{
	Conj<registro> res;
	Conj<registro>::const_Iterador itreg1 = _registros.CrearIt();
	while(itreg1.HaySiguiente())
	{
		Conj<registro>::const_Iterador itreg2 = r.CrearIt();
		while(itreg2.HaySiguiente())
		{
			assert(itreg1.Siguiente().Definido(c) && itreg2.Siguiente().Definido(c));  
			if(itreg1.Siguiente().Significado(c) == itreg2.Siguiente().Significado(c))
			{
				registro rcopia = itreg1.Siguiente();
				rcopia.AgregarCampos(itreg2.Siguiente());
				res.AgregarRapido(rcopia);
				
			}
			itreg2.Avanzar();
		}
		itreg1.Avanzar();
	}
	return res;
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::coincidencias(const registro &crit) const
{
	if(crit.Definido(_indices.iNat))
		return coincidenciasIndiceNat(crit);
	else if(crit.Definido(_indices.iStr))
		return coincidenciasIndiceStr(crit);
	else
		return coincidenciasSinIndice(crit);
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::coincidenciasSinIndice(const registro &crit) const
{
	Conj<registro> res;
	Conj<registro>::const_Iterador itreg = _registros.CrearIt();
	while(itreg.HaySiguiente())
	{
		if(crit.CoincidenTodos(itreg.Siguiente(),crit.Campos()))
			res.AgregarRapido(itreg.Siguiente());
		itreg.Avanzar();
	}
	return res;
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::coincidenciasIndiceNat(const registro &crit) const
{
	Conj<registro> res;
	Nat filtro = crit.Significado(_indices.iNat).valorNat();
	if(_indiceNat.Definido(filtro))
	{
		ConjItReg::const_Iterador itcreg = _indiceNat.Significado(filtro).CrearIt();
		while(itcreg.HaySiguiente())
		{
			if(crit.CoincidenTodos(itcreg.Siguiente().Siguiente(),crit.Campos()))
				res.AgregarRapido(itcreg.Siguiente().Siguiente());
			itcreg.Avanzar();		
		}
	}
	return res;
}
//--------------------------------------------------------------------------
Conj<registro> Tabla::coincidenciasIndiceStr(const registro &crit) const
{
	Conj<registro> res;
	String filtro = crit.Significado(_indices.iStr).valorStr();
	if(_indiceStr.Definido(filtro))
	{
		ConjItReg::const_Iterador itcreg = _indiceStr.Significado(filtro).CrearIt();
		while(itcreg.HaySiguiente())
		{
			if(crit.CoincidenTodos(itcreg.Siguiente().Siguiente(),crit.Campos()))
				res.AgregarRapido(itcreg.Siguiente().Siguiente());
			itcreg.Avanzar();		
		}
	}
	return res;
}
//--------------------------------------------------------------------------
const DiccIndiceNat& Tabla::indiceNat()
{
	return _indiceNat;
}
//--------------------------------------------------------------------------
const DiccIndiceStr& Tabla::indiceStr()
{
	return _indiceStr;
}
//--------------------------------------------------------------------------
