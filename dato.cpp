#include "dato.h"

using namespace std;

dato::dato(const Nat& _valorN)
	: valorN(_valorN)
	, valorS("")
	, esN(true)
{
}

dato::dato(const String& _valorS)
	: valorN(0)
	, valorS(_valorS)
	, esN(false)
{
}

bool dato::esNat() const{
	return this->esN;
}

bool dato::esString() const{
	return !esNat();
}

const Nat& dato::valorNat() const{
	assert(this->esN);
	return this->valorN;
}

const String& dato::valorStr() const{
	assert( !(this->esN) );
	return this->valorS;
}

bool dato::mismoTipo(const dato& otro){
	return this->esNat() == otro.esNat();
}

bool dato::operator==(const dato& otro) const{
	bool res;
	if( esNat() && otro.esNat() ) {
		res = valorNat() == otro.valorNat();
	} else if(esString() && otro.esString()) {
		res = valorStr() == otro.valorStr();
	} else {
		res = false;
	}

	return res;
}