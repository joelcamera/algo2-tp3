#include "Driver.h"

bool aed2::operator == (const aed2::Columna& c1, const aed2::Columna& c2)
{
  return c1.nombre == c2.nombre and c1.tipo == c2.tipo;
}

using namespace aed2;

////////////////////////////////////////////////////////////////////////////////
// Dato
////////////////////////////////////////////////////////////////////////////////

Driver::Dato::Dato(const aed2::Nat& x)
  : tipo_( NAT ), nat_( x )
{}

Driver::Dato::Dato(const aed2::String& x)
  : tipo_( STR ), str_( x )
{}

bool Driver::Dato::esNat() const
{
  return tipo_ == NAT;
}

bool Driver::Dato::esString() const
{
  return tipo_ == STR;
}

TipoCampo Driver::Dato::tipo() const
{
  return tipo_;
}

const aed2::Nat& Driver::Dato::dameNat() const
{
  assert( esNat() );
  return nat_;
}

const aed2::String& Driver::Dato::dameString() const
{
  assert( esString() );
  return str_;
}

bool Driver::Dato::operator == (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ == otro.nat_ ) or
    ( tipo_ == STR and str_ == otro.str_ )
  );
}

bool Driver::Dato::operator != (const Dato& otro) const
{
  return not (*this == otro);
}

////////////////////////////////////////////////////////////////////////////////
// Base de datos
////////////////////////////////////////////////////////////////////////////////

Driver::Driver()
{
}

Driver::~Driver()
{
}

// Tablas

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
{

  aed2::Conj<Columna>::const_Iterador it = columnas.CrearIt();
  registro regColumnas;
  while( it.HaySiguiente() ) {
    Columna c = it.Siguiente();
    if(c.tipo == NAT) {
      regColumnas.Definir(c.nombre, dato(0));
    } else {
      regColumnas.Definir(c.nombre, dato(""));
    }
    it.Avanzar();
  }

  base.AgregarTabla(Tabla(nombre, claves, regColumnas));
}

void Driver::insertarRegistro(const NombreTabla& tabla, const Registro& registro)
{
  base.InsertarEntrada( fromDriverReg(registro), tabla );
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor)
{
  registro critero;
  critero.Definir(columna, fromDriverDato(valor));
  base.Borrar(critero, tabla);
}



aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabla) const
{
  const Tabla& t = base.DameTabla(tabla);
  aed2::Conj<Columna> res;
  Conj<NombreCampo> campos = t.campos();
  Conj<NombreCampo>::const_Iterador itCampos = campos.CrearIt();
  while( itCampos.HaySiguiente() ) {
    const NombreCampo& n = itCampos.Siguiente();
    Columna c;
    c.nombre = n;
    c.tipo = t.tipoCampo(n);
    res.AgregarRapido(c);
    itCampos.Avanzar();
  }
  return res;
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabla) const
{
  return base.DameTabla(tabla).claves();
}

aed2::Conj<Driver::Registro> Driver::registrosDeTabla(const NombreTabla& tabla) const
{
  aed2::Conj<Driver::Registro> res;
  const Conj<registro>& regs = base.Registros(tabla);
  Conj<registro>::const_Iterador it = regs.CrearIt();
  while( it.HaySiguiente() ) {
    res.AgregarRapido( toDriverReg( it.Siguiente() ) );
    it.Avanzar();
  }
  return res;
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const
{
  return base.CantidadDeAccesos(tabla);
}

Driver::Dato Driver::minimo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  return toDriverDato(base.DameTabla(tabla).minimo(columna));
}

Driver::Dato Driver::maximo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  return toDriverDato(base.DameTabla(tabla).maximo(columna));
}

aed2::Conj<Driver::Registro> Driver::buscar(const NombreTabla& tabla, const Registro& criterio) const
{
  aed2::Conj<Driver::Registro> res;
  const Conj<registro>& regs = base.Buscar(fromDriverReg(criterio), tabla);
  Conj<registro>::const_Iterador it = regs.CrearIt();
  while( it.HaySiguiente() ) {
    res.AgregarRapido( toDriverReg( it.Siguiente() ) );
    it.Avanzar();
  }
  return res;
}

aed2::Conj<NombreTabla> Driver::tablas() const
{
  Conj<NombreTabla> tablas;
  Conj<NombreTabla>::const_Iterador it = base.Tablas();
  while( it.HaySiguiente() ) {
    tablas.AgregarRapido( it.Siguiente() );
    it.Avanzar();
  }
  return tablas;
}

const NombreTabla Driver::tablaMaxima() const
{
  return base.TablaMaxima();
}

// Indices

bool Driver::tieneIndiceDeTipo(const NombreTabla& tabla, bool nat, NombreCampo& nombre) const
{
  const Tabla& t = base.DameTabla(tabla);
  Conj<NombreCampo> indices = t.indices();
  Conj<NombreCampo>::const_Iterador it = indices.CrearIt();
  while(it.HaySiguiente()) {
    if( t.tipoCampo(it.Siguiente()) == (nat ? NAT : STR)) {
      nombre = it.Siguiente();
      return true;
    }
    it.Avanzar();
  }
  return false;
}


bool Driver::tieneIndiceNat(const NombreTabla& tabla) const
{
  NombreCampo n;
  return tieneIndiceDeTipo(tabla, true, n);
}

bool Driver::tieneIndiceString(const NombreTabla& tabla) const
{
  NombreCampo n;
  return tieneIndiceDeTipo(tabla, false, n);
}

const NombreCampo& Driver::campoIndiceNat(const NombreTabla& tabla) const
{
  NombreCampo n;
  bool tiene = tieneIndiceDeTipo(tabla, true, n);
  assert(tiene);
  const NombreCampo& tmp = indicesNat.Significado(tabla);
  assert(n == tmp);
  return tmp;
}

const NombreCampo& Driver::campoIndiceString(const NombreTabla& tabla) const
{
  NombreCampo n;
  bool tiene = tieneIndiceDeTipo(tabla, false, n);
  assert(tiene);
  const NombreCampo& tmp = indicesStr.Significado(tabla);
  assert(n == tmp);
  return tmp;
}

void Driver::crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo)
{
  indicesNat.Definir(tabla, campo);
  base.DameTabla(tabla).indexar(campo);
}

void Driver::crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo)
{
  indicesStr.Definir(tabla, campo);
  base.DameTabla(tabla).indexar(campo);
}

// Joins

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  return base.HayJoin(tabla1, tabla2);
}

const NombreCampo& Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  return base.CampoJoin(tabla1, tabla2);
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo)
{
  base.GenerarVistaJoin(tabla1, tabla2, campo);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
  base.BorrarJoin(tabla1, tabla2);
}

// Driver::Registro unir(const Driver::Registro& reg1, const Driver::Registro& reg2, const NombreCampo& clave)
// {
//   // TODO ...
//   assert(false);
// }

aed2::Conj<Driver::Registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
  Conj<Driver::Registro> res;
  Conj<registro>::const_Iterador it = base.VistaJoin(tabla1, tabla2);
  while(it.HaySiguiente()) {
    res.AgregarRapido(toDriverReg(it.Siguiente()));
    it.Avanzar();
  }
  return res;
}


Driver::Dato Driver::toDriverDato(const dato& d) const {
  if(d.esNat()) return Dato(d.valorNat());
  return Dato(d.valorStr());
}

dato Driver::fromDriverDato(const Driver::Dato& d) const {
  if(d.tipo() == NAT) return dato(d.dameNat());
  return dato(d.dameString());
}

aed2::Dicc<NombreCampo, Driver::Dato> Driver::toDriverReg(const registro& reg) const {
  aed2::Dicc<NombreCampo, Driver::Dato> r;
  registro::const_Iterador it = reg.CrearIt();
  while( it.HaySiguiente() ) {
    r.Definir(it.SiguienteClave(), toDriverDato(it.SiguienteSignificado()) );
    it.Avanzar();
  }
  return r;  
}

registro Driver::fromDriverReg(const aed2::Dicc<NombreCampo, Driver::Dato>& reg) const {
  registro r;
  aed2::Dicc<NombreCampo, Driver::Dato>::const_Iterador it = reg.CrearIt();
  while( it.HaySiguiente() ) {
    r.Definir(it.SiguienteClave(), fromDriverDato(it.SiguienteSignificado()) );
    it.Avanzar();
  }
  return r;
}
