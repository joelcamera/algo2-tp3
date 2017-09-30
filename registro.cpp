#include "registro.h"


//--------------------------------------------------------------------------------------
Conj<NombreCampo> registro::Campos() const
{
		Conj<NombreCampo> res;
		registro::const_Iterador it = this->CrearIt();
		while(it.HaySiguiente()){
			res.AgregarRapido(it.SiguienteClave());
			it.Avanzar();
		}
		return res;
}
//--------------------------------------------------------------------------------------
bool registro::CoincidenTodos(const registro& r1, const Conj<NombreCampo>& cc) const{
	Conj<NombreCampo>::const_Iterador itc = cc.CrearIt();
	bool res = true;

	while(itc.HaySiguiente() && res){
		res = r1.Significado(itc.Siguiente()) == this->Significado(itc.Siguiente());
		itc.Avanzar();
	}

	return res;
}
//--------------------------------------------------------------------------------------
void registro::AgregarCampos(const registro& r2){
	Conj<NombreCampo> cr1 = Campos();
	Conj<NombreCampo> cr2 = r2.Campos();
	RestaCampos(cr2, cr1);

	Conj<NombreCampo>::Iterador itc = cr2.CrearIt();

	while(itc.HaySiguiente()){
		this->DefinirRapido(itc.Siguiente(), r2.Significado(itc.Siguiente()));
		itc.Avanzar();
	}
}
//--------------------------------------------------------------------------------------
void registro::RestaCampos(Conj<NombreCampo>& cr2, const Conj<NombreCampo>& cr1) const{
	Conj<NombreCampo>::Iterador itcr2 = cr2.CrearIt();

	while(itcr2.HaySiguiente()){
		if(cr1.Pertenece(itcr2.Siguiente())){
			itcr2.EliminarSiguiente();
		} else {
			itcr2.Avanzar();
		}
	}
}
//--------------------------------------------------------------------------------------
bool registro::operator==(const registro& otro) const
{
	bool retval = this->CantClaves() == otro.CantClaves();
	registro::const_Iterador it1 = this->CrearIt();
	while(retval and it1.HaySiguiente())
	{
		registro::const_Iterador it2 = otro.Buscar(it1.SiguienteClave());
		retval = it2.HaySiguiente() and it1.SiguienteSignificado() == it2.SiguienteSignificado();
		it1.Avanzar();
	}
	return retval;
}
//--------------------------------------------------------------------------------------
bool registro::operator!=(const registro& otro) const
{
	return !(*this == otro);
}
//--------------------------------------------------------------------------------------