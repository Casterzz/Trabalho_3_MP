GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

IDIR =../include
CC=gcc
CCPLUS=g++	
CFLAGS=-I $(IDIR) -g
G_FLAGS=-I $(IDIR) -I $(GOOGLE_TEST_INCLUDE) -g -ftest-coverage -fprofile-arcs
LD_FLAGS=-I $(IDIR) -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread -g -ftest-coverage -fprofile-arcs

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = conta_linha.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o conta_linha.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJT = testa_contador.o conta_linha.o
OBJT = $(patsubst %,$(ODIR)/%,$(_OBJT))

all: conta_linha testa_contador

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CCPLUS) -c -o $@ $< $(G_FLAGS)

conta_linha: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

testa_contador: $(OBJT)
	$(CCPLUS) -o $@ $^ $(LD_FLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
