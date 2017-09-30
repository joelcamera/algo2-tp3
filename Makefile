# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS= -g -Wall

# flags de linkeo
LDFLAGS=

# Agrear acá los directorios a incluir en la compilación [COMPLETAR]
INCDIR=

# Agregar acá los archivos .cpp a compilar [COMPLETAR]
SOURCES= tests.cpp TestDriver.cpp testBase.cpp testDiccString.cpp testsregistro.cpp testtabla.cpp testsdato.cpp testsdiccNat.cpp base.cpp tabla.cpp dato.cpp registro.cpp Driver.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@
