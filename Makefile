FITSIOROOT = /home/dario/CCD/Datos_Fe55/cfitsio/
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
OBJECTS =  toyMC10.o 
#HEADERS = globalConstants.h

ALL : toyMC10.exe
	@echo "Listo!"

toyMC10.exe : $(OBJECTS)
	$(CPP) $(OBJECTS) -o toyMC10.exe $(LIBS) $(GLIBS) $(CFLAGS)

toyMC10.o : toyMC10.C $(HEADERS)
	$(CPP) -c toyMC10.C -o toyMC10.o $(CFLAGS)

clean:
	rm -f *~ *.o *.exe


