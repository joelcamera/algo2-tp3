#ifndef DICCNAT_H_
#define DICCNAT_H_

#include "Tipos.h"
#include "aed2.h"
#include <iostream>
#include <cassert>

using namespace std;


template <typename T>
class diccNat{

	public:

		diccNat();
		diccNat(const diccNat<T>& otro);
		~diccNat();

		void Definir(Nat clave, T& sign);
		bool Definido(Nat clave) const;
		T& Significado(Nat clave) const;
		void Borrar(Nat clave);
		bool EsVacio() const;
		Nat CantClaves() const;
		Nat ClaveMinima() const;
		Nat ClaveMaxima() const;

	private:

		struct Nodo{
			
			Nodo(){
				padre = NULL;
				hizq = NULL;
				hder = NULL;
			}

			Nodo(Nat _clave, const T& _sign) : clave(_clave), sign(_sign) {
				padre = NULL;
				hizq = NULL;
				hder = NULL;
			}

			Nat clave;
			T sign;
			Nodo* padre;
			Nodo* hizq;
			Nodo* hder;
		};

		
		//ESTRUCTURA

		Nodo* raiz;
		Nodo* masChico;
		Nodo* masAlto;
		Nat cantnodos;


		/*************************************************************
		*                  FUNCIONES AUXILIARES                      *
		**************************************************************/

		typename diccNat<T>::Nodo* BuscaNodoParaInsertar(Nat clave);
		typename diccNat<T>::Nodo* BuscaNodo(Nat clave) const;
		void BorrarArbol(typename diccNat<T>::Nodo* a);
		bool TieneHijoIzq(typename diccNat<T>::Nodo* a);
		void AgregarNodos(typename diccNat<T>::Nodo* b);
		typename diccNat<T>::Nodo* BuscarNodoMasDerecha(typename diccNat<T>::Nodo* a);

		// Auxiliares en Borrar
		bool NoTieneHijos(typename diccNat<T>::Nodo* pb);
		void BorrarCasoNoTieneHijos(typename diccNat<T>::Nodo* pb);
		bool TieneUnHijo(typename diccNat<T>::Nodo* pb);
		void BorrarCasoTieneUnHijo(typename diccNat<T>::Nodo* pb);
		void BorrarCasoTieneDosHijos(typename diccNat<T>::Nodo* pb);
		bool EsHijoDerecho(typename diccNat<T>::Nodo* pbpadre, Nat pbclave);
		bool TieneHijoDerecho(typename diccNat<T>::Nodo* pb);
		typename diccNat<T>::Nodo* BuscarNodoMasIzq(typename diccNat<T>::Nodo* der);
		void AcomodoNodoMasIzq(typename diccNat<T>::Nodo* pb, typename diccNat<T>::Nodo* masizq);

};



/*************************************************************
*                    IMPLEMENTACION diccNat                  *
**************************************************************/

template <typename T>
diccNat<T>::diccNat(){
	this->raiz = NULL;
	this->masChico = NULL;
	this->masAlto = NULL;
	this->cantnodos = 0;
}

template <typename T>
diccNat<T>::diccNat(const diccNat<T>& otro){
	this->raiz = NULL;
	this->masChico = NULL;
	this->masAlto = NULL;
	this->cantnodos = 0;

	if (otro.cantnodos > 0){
		Nodo* b = otro.raiz;
		AgregarNodos(b);
	}
}

template <typename T>
diccNat<T>::~diccNat(){
	if (this->raiz != NULL){
		BorrarArbol(this->raiz);
		this->cantnodos = 0;
	}
}

template <typename T>
void diccNat<T>::Definir(Nat clave, T& sign){

	if (!Definido(clave)){ //no esta definido, lo agrego

		typename diccNat<T>::Nodo* nuevonodo = new Nodo(clave, sign);

		if (this->raiz == NULL){
			//el arbol esta vacio
			this->raiz = nuevonodo;
			this->masChico = nuevonodo;
			this->masAlto = nuevonodo;

		} else {
			//el arbol NO esta vacio, busco al padre y lo agrego en su lugar
			typename diccNat<T>::Nodo* npapa = BuscaNodoParaInsertar(clave);
			
			if (clave < npapa->clave && npapa->hizq == NULL) {
				npapa->hizq = nuevonodo;
				nuevonodo->padre = npapa;
			} else if (clave > npapa->clave && npapa->hder == NULL){
				npapa->hder = nuevonodo;
				nuevonodo->padre = npapa;
			}

			//si la clave es mas chica que la clave de this->masChico o la clave
			//es mas grande que this->masAlto cambio el puntero
			if(clave < this->masChico->clave){
				this->masChico = nuevonodo;
			} else if(clave > this->masAlto->clave){
				this->masAlto = nuevonodo;
			}
		}

		this->cantnodos++;

	} else { //esta definido, lo piso

		typename diccNat<T>::Nodo* nodo = BuscaNodo(clave);
		
		nodo->sign = sign;
	}
}

template <typename T>
bool diccNat<T>::Definido(Nat clave) const{
	return BuscaNodo(clave) != NULL;
}

template <typename T>
T& diccNat<T>::Significado(Nat clave) const{
	assert(Definido(clave));
	return BuscaNodo(clave)->sign;
}

template <typename T>
void diccNat<T>::Borrar(Nat clave){

	if (Definido(clave)){
		Nodo* paraborrar = BuscaNodo(clave);

		//reviso si borro la clave mas chica.
		if(this->masChico->clave == clave){
			//voy a borrar el mas chico
			if(TieneHijoDerecho(this->masChico)){
				this->masChico = BuscarNodoMasIzq(this->masChico->hder);
			
			} else if(this->masChico->padre != NULL){ //no tiene hijo derecho, tiene padre??
				this->masChico = this->masChico->padre;
			
			} else { //no tiene hijo derecho ni padre, es null
				this->masChico = NULL;
			}
		}

		//reviso si borro la clave mas alta
		if(this->masAlto->clave == clave){
			//voy a borrar el mas chico
			if(TieneHijoIzq(this->masAlto)){
				this->masAlto = BuscarNodoMasDerecha(this->masAlto->hizq);
			
			} else if(this->masAlto->padre != NULL){ //no tiene hijo derecho, tiene padre??
				this->masAlto = this->masAlto->padre;
			
			} else { //no tiene hijo derecho ni padre, es null
				this->masAlto = NULL;
			}
		}		


		if (NoTieneHijos(paraborrar)){

			BorrarCasoNoTieneHijos(paraborrar);

		} else if (TieneUnHijo(paraborrar)){

			BorrarCasoTieneUnHijo(paraborrar);

		} else {
		
			BorrarCasoTieneDosHijos(paraborrar);

		}

		this->cantnodos--;
		delete paraborrar;
	}
}

template <typename T>
bool diccNat<T>::EsVacio() const{
	return this->raiz == NULL && this->cantnodos == 0;
}

template <typename T>
Nat diccNat<T>::CantClaves() const{
	return this->cantnodos;
}

template <typename T>
Nat diccNat<T>::ClaveMinima() const{
	assert( !(this->EsVacio()) );
	return this->masChico->clave;
}

template <typename T>
Nat diccNat<T>::ClaveMaxima() const{
	assert( !(this->EsVacio()) );
	return this->masAlto->clave;
}



/*************************************************************
*                    AUXILIARES diccNat                      *
**************************************************************/



template <typename T>
typename diccNat<T>::Nodo* diccNat<T>::BuscaNodoParaInsertar(Nat clave){
	//No hay nodo que tenga como clave c, aqui estoy buscando al padre para poder insertar
	//un nodo con la clave c

	typename diccNat<T>::Nodo* buscanodo = this->raiz;
	typename diccNat<T>::Nodo* nodores = NULL;

	while (buscanodo != NULL && nodores == NULL){
		if (clave < buscanodo->clave && buscanodo->hizq != NULL){
			buscanodo = buscanodo->hizq;
		} else if (clave > buscanodo->clave && buscanodo->hder != NULL){
			buscanodo = buscanodo->hder;
		} else if ((clave > buscanodo->clave && buscanodo->hder == NULL) ||
					(clave < buscanodo->clave && buscanodo->hizq == NULL) ){
			nodores = buscanodo;
		}
	}
	return nodores;
}

template <typename T>
typename diccNat<T>::Nodo* diccNat<T>::BuscaNodo(Nat clave) const{
	typename diccNat<T>::Nodo* buscanodo = this->raiz;

	while (buscanodo != NULL && buscanodo->clave != clave)
		buscanodo = clave < buscanodo->clave ? buscanodo->hizq : buscanodo->hder;
	
	return buscanodo;
}

template <typename T>
bool diccNat<T>::TieneHijoDerecho(typename diccNat<T>::Nodo* pb){
	return (pb->hder != NULL);
}

template <typename T>
bool diccNat<T>::TieneHijoIzq(typename diccNat<T>::Nodo* a){
	return (a->hizq != NULL);
}

template <typename T>
bool diccNat<T>::NoTieneHijos(typename diccNat<T>::Nodo* pb){
	return (pb->hder == NULL && pb->hizq == NULL);
}

template <typename T>
void diccNat<T>::BorrarCasoNoTieneHijos(typename diccNat<T>::Nodo* pb){
	if (pb->padre == NULL){
		this->raiz = NULL;

	} else {

		if (EsHijoDerecho(pb->padre, pb->clave)){
			pb->padre->hder = NULL;

		} else {
			pb->padre->hizq = NULL;
		} //end if interno
	}
}

template <typename T>
bool diccNat<T>::TieneUnHijo(typename diccNat<T>::Nodo* pb){
	return ((pb->hder != NULL && pb->hizq == NULL) ||
			(pb->hder == NULL && pb->hizq != NULL));
}

template <typename T>
void diccNat<T>::BorrarCasoTieneUnHijo(typename diccNat<T>::Nodo* pb){
	if (pb->padre == NULL){ // no tiene padre

		if (TieneHijoDerecho(pb)){
			this->raiz = pb->hder;
			pb->hder->padre = NULL;

		} else {
			this->raiz = pb->hizq;
			pb->hizq->padre = NULL;
		}

	} else { // tiene padre

		if (TieneHijoDerecho(pb)){
			
			if (EsHijoDerecho(pb->padre, pb->clave)){
				pb->padre->hder = pb->hder;
			} else {
				pb->padre->hizq = pb->hder;
			}

			pb->hder->padre = pb->padre;

		} else {
			
			if (EsHijoDerecho(pb->padre, pb->clave)){
				pb->padre->hder = pb->hizq;
			} else {
				pb->padre->hizq = pb->hizq;
			}

			pb->hizq->padre = pb->padre;

		}

	}
}

template <typename T>
void diccNat<T>::BorrarCasoTieneDosHijos(typename diccNat<T>::Nodo* pb){
	diccNat<T>::Nodo* masizq = BuscarNodoMasIzq(pb->hder);

	// acomodo hijos
	// si el nodo masizq es hijo de pb
	if (pb->hder->clave == masizq->clave){

		masizq->hizq = pb->hizq;
		pb->hizq->padre = masizq;

	} else { // si el nodo masizq NO es hijo de pb

		AcomodoNodoMasIzq(pb, masizq);
	}
	
	// acomodo el padre de pb y masizq
	if (pb->padre == NULL){
		masizq->padre = NULL;
		this->raiz = masizq;

	} else {
		masizq->padre = pb->padre;
		
		if (EsHijoDerecho(pb->padre, pb->clave)){
			pb->padre->hder = masizq;
		} else {
			pb->padre->hizq = masizq;

		} //end if interno
	}

}

template <typename T>
bool diccNat<T>::EsHijoDerecho(typename diccNat<T>::Nodo* pbpadre, Nat pbclave){
	return (pbpadre->hder != NULL && pbpadre->hder->clave == pbclave);
}

template <typename T>
typename diccNat<T>::Nodo* diccNat<T>::BuscarNodoMasIzq(typename diccNat<T>::Nodo* der){
	Nodo* buscanodo = der;
	
	if (buscanodo != NULL){
		while (buscanodo->hizq != NULL) buscanodo = buscanodo->hizq;
	}

	return buscanodo;
}

template <typename T>
void diccNat<T>::AcomodoNodoMasIzq(typename diccNat<T>::Nodo* pb, typename diccNat<T>::Nodo* masizq){

	// el hijo que puede tener es el derecho
	if (TieneUnHijo(masizq)){

		masizq->hder->padre = masizq->padre;
		masizq->padre->hizq = masizq->hder;

	} else { // no tiene hijo

		masizq->padre->hizq = NULL;
		masizq->padre = NULL;
	}

	// acomodo los hijos de pb con masizq
	masizq->hder = pb->hder;
	pb->hder->padre = masizq;
	masizq->hizq = pb->hizq;
	pb->hizq->padre = masizq;
}

template <typename T>
void diccNat<T>::AgregarNodos(typename diccNat<T>::Nodo* b){
	Definir(b->clave, b->sign);

	if (TieneHijoDerecho(b)) AgregarNodos(b->hder);

	if (TieneHijoIzq(b)) AgregarNodos(b->hizq);

}

template <typename T>
typename diccNat<T>::Nodo* diccNat<T>::BuscarNodoMasDerecha(typename diccNat<T>::Nodo* a){
	if(a != NULL){
		while (a->hder != NULL) a = a->hder;
	}
	
	return a;
}


template <typename T>
void diccNat<T>::BorrarArbol(typename diccNat<T>::Nodo* a){
	if (a->hizq != NULL && a->hder == NULL){
		BorrarArbol(a->hizq);
	} else if (a->hizq == NULL && a->hder != NULL){
		BorrarArbol(a->hder);
	} else if (a->hizq != NULL && a->hder != NULL){
		BorrarArbol(a->hizq);
		BorrarArbol(a->hder);
	}
	delete a;
}

#endif // DICCNAT_H_
