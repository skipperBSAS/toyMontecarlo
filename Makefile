FITSIOROOT = /home/mariano/MEGAsync/CCD/Datos_Fe55/cfitsio/
CFITSIO = $(FITSIOROOT)
CPP = g++
CC = gcc
GCCNEWERTHAN47 := $(shell expr `gcc -dumpversion` \>= 4.7)
CFLAGS = -Wall -I$(CFITSIO) $(shell root-config --cflags)
LIBS = -L$(CFITSIO) -lcfitsio -lm $(shell root-config --libs)
GLIBS = 
GLIBS +=
ifeq "$(GCCNEWERTHAN47)" "1"
  CFLAGS += -std=c++11
else
  CFLAGS += -std=c++0x
endif
OBJECTS =  toymcprueba.o 
#HEADERS = globalConstants.h

ALL : toymcprueba.exe
	@echo "Listo!"

toymcprueba.exe : $(OBJECTS)
	$(CPP) $(OBJECTS) -o toymcprueba.exe $(LIBS) $(GLIBS) $(CFLAGS)

toymcprueba.o : toymcprueba.C $(HEADERS)
	$(CPP) -c toymcprueba.C -o toymcprueba.o $(CFLAGS)

clean:
	rm -f *~ *.o *.exe


