PNM = ../sylence

IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR) -g -lm

ODIR = obj
LDIR = ../lib

LIBS = 

_DEPS = cordic.h universe.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = sylence.o cordic.o universe.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PNM) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all : $(PNM)
	echo $(PNM) Compile complete

.PHONY : clean

clean :
	rm -f $(ODIR)/*.o $(PNM)

#sylence: sylence.c cordic.c cordic.h universe.c universe.h
#	$(CC) -o sylence sylence.c cordic.c cordic.h universe.c universe.h
