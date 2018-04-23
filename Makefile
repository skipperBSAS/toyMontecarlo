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
OBJECTS =  Mont.o 
#HEADERS = globalConstants.h

ALL : Mont.exe
	@echo "Listo!"

Mont.exe : $(OBJECTS)
	$(CPP) $(OBJECTS) -o Mont.exe $(LIBS) $(GLIBS) $(CFLAGS)

Mont.o : toyMont.C $(HEADERS)
	$(CPP) -c toyMont.C -o Mont.o $(CFLAGS)

clean:
	rm -f *~ *.o *.exe


