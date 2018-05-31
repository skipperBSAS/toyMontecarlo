FITSIOROOT = /home/babieca/MEGA/MEGAsync/CCD/Datos_Fe55/cfitsio/
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
OBJECTS =  toyMC11.o 
#HEADERS = globalConstants.h

ALL : toyMC11.exe
	@echo "Listo!"

toyMC11.exe : $(OBJECTS)
	$(CPP) $(OBJECTS) -o toyMC11.exe $(LIBS) $(GLIBS) $(CFLAGS)

toyMC11.o : toyMC11.C $(HEADERS)
	$(CPP) -c toyMC11.C -o toyMC11.o $(CFLAGS)

clean:
	rm -f *~ *.o *.exe


