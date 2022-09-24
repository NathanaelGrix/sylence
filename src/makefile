PNM = ../sylence

IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR) -g -lX11

ODIR = obj
LDIR = ../lib

LIBS = 

_DEPS = cord.h universe.h sound.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = sylence.o cord.o universe.o sound.o
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
