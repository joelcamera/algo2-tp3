#ifndef REGISTRO_H_
#define REGISTRO_H_


#include "Tipos.h"
#include "dato.h"
#include "aed2.h"
#include <iostream>
#include <cassert>
//#include "aed2/Dicc.h"

class registro : public Dicc<NombreCampo,dato>
{
	public:
		Conj<NombreCampo> Campos() const;
		bool CoincidenTodos(const registro& r1, const Conj<NombreCampo>& cc) const;
		void AgregarCampos(const registro& r2);

		bool operator==(const registro& otro) const;
		bool operator!=(const registro& otro) const;
	private:
		void RestaCampos(Conj<NombreCampo>& cr2, const Conj<NombreCampo>& cr1) const;
};


#endif //REGISTRO_H_