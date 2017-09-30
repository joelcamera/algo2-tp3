#ifndef TEST_H
#define TEST_H

#include <string>
#include "mini_test.h"

bool testSelect(int argc,char** argv,std::string clave);

void testDriver(int argc, char **argv);
void testBase(int argc, char **argv);
void testTabla(int argc, char**argv);
void testDato(int argc, char **argv);
void testRegistro(int argc, char **argv);
void testDiccNat(int argc, char **argv);
void testDiccString(int argc, char **argv);

#endif /*TEST_H*/