#ifndef DATO_H_
#define DATO_H_

#include "Tipos.h"
#include "aed2.h"
#include <string>
#include <iostream>
#include <cassert>

class dato{

	public:
		dato(const Nat& _valorN);
		dato(const String& _valorS);

		bool esNat() const;		//Nat?
		bool esString() const;	//String?
		const Nat& valorNat() const;
		const String& valorStr() const;
		bool mismoTipo(const dato& otro);

		bool operator==(const dato& otro) const;

	private:

	Nat valorN;
	String valorS;
	bool esN;
};



#endif // DATO_H_