 #include "base.h"



BaseDeDatos::BaseDeDatos() 
	: tablaMaxima("")
	, maxModificaciones(0)
{

}

BaseDeDatos::~BaseDeDatos() {

}


//Funciones sobre tablas
bool BaseDeDatos::AgregarTabla(const Tabla& t) {
	assert(t.registros().Cardinal() == 0);
	if(tablas.Definido(t.nombre())) return false;
	tablas.Definir(t.nombre(), infoTabla(t));
	return true;
}

Conj<NombreTabla>::const_Iterador BaseDeDatos::Tablas() const {
	return tablas.CrearItClaves();
}

Tabla& BaseDeDatos::DameTabla(const NombreTabla& t) {
	assert(tablas.Definido(t));
	return tablas.Significado(t).tabla;
}

const Tabla& BaseDeDatos::DameTabla(const NombreTabla& t) const {
	assert(tablas.Definido(t));
	return tablas.Significado(t).tabla;
}

Nat BaseDeDatos::CantidadDeAccesos(const NombreTabla& t) const {
	assert(tablas.Definido(t));
	return tablas.Significado(t).tabla.cantidadDeAccesos();
}

const NombreTabla& BaseDeDatos::TablaMaxima() const {
	return tablaMaxima;
}

//Operaciones sobre registros
void BaseDeDatos::InsertarEntrada(const registro& reg, const NombreTabla& t) {
	assert(tablas.Definido(t));

	infoTabla& it = tablas.Significado(t);
	Tabla& t1 = it.tabla;
	t1.agregarRegistro(reg);

	MantenerCambios(it, reg, false);
	if(t1.cantidadDeAccesos() > maxModificaciones) {
		maxModificaciones = t1.cantidadDeAccesos();
		tablaMaxima = t;
	}
} 

void BaseDeDatos::Borrar(const registro& cr, const NombreTabla& t) {
	assert(tablas.Definido(t));
	assert(cr.Campos().Cardinal() == 1);
	assert(tablas.Significado(t).tabla.claves().Pertenece( cr.Campos().CrearIt().Siguiente()  ));	

	infoTabla& it = tablas.Significado(t);
	Tabla& t1 = it.tabla;
	t1.borrarRegistro(cr);

	MantenerCambios(it, cr, true);
	if(t1.cantidadDeAccesos() > maxModificaciones) {
		maxModificaciones = t1.cantidadDeAccesos();
		tablaMaxima = t;
	}

}

const Conj<registro>& BaseDeDatos::Registros(const NombreTabla& t) const {
	assert(tablas.Definido(t));
	return tablas.Significado(t).tabla.registros();
}

Conj<registro> BaseDeDatos::Buscar(const registro& criterio, const NombreTabla& t) const {
	assert(tablas.Definido(t));
	return tablas.Significado(t).tabla.coincidencias(criterio);
}

//Operaciones sobre joins
bool BaseDeDatos::HayJoin(const NombreTabla& t1, const NombreTabla& t2) const {
	return tablas.Definido(t1) && tablas.Significado(t1).joinsCon.Definido(t2);
}

const NombreCampo& BaseDeDatos::CampoJoin(const NombreTabla& t1, const NombreTabla& t2) const {
	assert(HayJoin(t1, t2));
	return tablas.Significado(t1).joinsCon.Significado(t2).campo;
}

Conj<registro>::const_Iterador BaseDeDatos::GenerarVistaJoin(const NombreTabla& n1, const NombreTabla& n2, const NombreCampo& c) {
	assert(n1 != n2);
	assert(tablas.Definido(n1));
	assert(tablas.Definido(n2));
	infoTabla& inft1 = tablas.Significado(n1);
	infoTabla& inft2 = tablas.Significado(n2);
	Tabla& t1 = inft1.tabla;
	Tabla& t2 = inft2.tabla;
	assert(t1.claves().Pertenece(c));
	assert(t2.claves().Pertenece(c));
	assert(t1.tipoCampo(c) == t2.tipoCampo(c));
	assert(!HayJoin(n1,n2));

	const Conj<registro>& rt2 = t2.registros();
	Conj<registro> regsJoin = t1.combinarRegistros(c, rt2);
	Conj<registro>::const_Iterador itrj = regsJoin.CrearIt();

	Conj<NombreCampo> claves;
	claves.Agregar(c);

	Tabla join("", claves, ColumnasJoin(t1, t2));
	inft1.joinsCon.Definir(n2, infoJoin(c, join));
	infoJoin& ij = inft1.joinsCon.Significado(n2);
	ij.join.indexar(c);

	inft2.esJoinDe.Definir(n1, &ij);
	while( itrj.HaySiguiente() ) {
		ij.join.agregarRegistro(itrj.Siguiente());
		itrj.Avanzar();
	}
	return ij.join.registros().CrearIt();
}

Conj<registro>::const_Iterador BaseDeDatos::VistaJoin(const NombreTabla& n1, const NombreTabla& n2) {
	assert(HayJoin(n1,n2));

	infoTabla& inft1 = tablas.Significado(n1);
	infoTabla& inft2 = tablas.Significado(n2);
	Tabla& t1 = inft1.tabla;
	Tabla& t2 = inft2.tabla;
	infoJoin& ij = inft1.joinsCon.Significado(n2);
	const NombreCampo& c = CampoJoin(n1, n2);
	ActualizarCambios(ij.cambiosT1, c, t2, ij.join);
	ActualizarCambios(ij.cambiosT2, c, t1, ij.join);
	return ij.join.registros().CrearIt();
}

void BaseDeDatos::BorrarJoin(const NombreTabla& t1, const NombreTabla& t2) {
	assert(HayJoin(t1,t2));
	infoTabla& inft1 = tablas.Significado(t1);
	infoTabla& inft2 = tablas.Significado(t2);
	inft1.joinsCon.Borrar(t2);
	inft2.esJoinDe.Borrar(t1);	
}

void BaseDeDatos::MantenerCambios(infoTabla& it, const registro& r, bool borrado) {
	Conj<String>::const_Iterador iter = it.joinsCon.CrearItClaves();
	while( iter.HaySiguiente() ) {
		infoJoin& ij = it.joinsCon.Significado( iter.Siguiente() );
		ij.cambiosT1.AgregarAtras( cambio(borrado, r));
		iter.Avanzar();
	}

	Conj<String>::const_Iterador iter2 = it.esJoinDe.CrearItClaves();
	while( iter2.HaySiguiente() ) {
		infoJoin* ij = it.esJoinDe.Significado( iter2.Siguiente() );
		ij->cambiosT2.AgregarAtras( cambio(borrado, r));
		iter2.Avanzar();
	}
}

registro BaseDeDatos::ColumnasJoin(const Tabla& t1, const Tabla& t2) const {
	
	registro res;
	Conj<NombreCampo> camposT1 = t1.campos();
	Conj<NombreCampo> camposT2 = t2.campos();
	Conj<NombreCampo>::const_Iterador itc1 = camposT1.CrearIt();
	Conj<NombreCampo>::const_Iterador itc2 = camposT2.CrearIt();

	while( itc1.HaySiguiente() ) {
		const NombreCampo& nc = itc1.Siguiente();
		if(t1.tipoCampo(nc) == NAT) { res.DefinirRapido(nc, dato(0)); } else { res.DefinirRapido(nc, dato(""));	}
		itc1.Avanzar();
	}

	while( itc2.HaySiguiente() ) {
		const NombreCampo& nc = itc2.Siguiente();
		if( !res.Definido(nc) ) {
			if(t2.tipoCampo(nc) == NAT) { res.DefinirRapido(nc, dato(0)); } else { res.DefinirRapido(nc, dato(""));	}
		}
		itc2.Avanzar();
	}

	return res;
}

void BaseDeDatos::ActualizarCambios(Lista<cambio>& cambios, const NombreCampo& c, const Tabla& t, Tabla& join) {

	Lista<cambio>::Iterador it = cambios.CrearIt();
	while( it.HaySiguiente() ) {
		cambio& cr = it.Siguiente();
		
		if(cr.borrado) {
			registro criterio;
			criterio.DefinirRapido(c, cr.reg.Significado(c) );
			join.borrarRegistro(criterio);
		} else {
			Conj<registro> conjDeUno;
			conjDeUno.AgregarRapido(cr.reg);
			Conj<registro> regsJoin = t.combinarRegistros(c, conjDeUno);
			Conj<registro>::Iterador itrj = regsJoin.CrearIt();
			if( itrj.HaySiguiente() ) {
				join.agregarRegistro(itrj.Siguiente());
			}
		}
		it.Avanzar();
		it.EliminarAnterior();
	}

}

