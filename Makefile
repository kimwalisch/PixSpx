CFLAGS = -O3 -Wall
LIBS =  -lgmpxx -lgmp

UNAME :=$(shell uname)
ifeq ($(UNAME),Darwin)
	LFLAGS+=-stdlib=libstdc++
	LPATH=-L/opt/local/lib		
else
	LPATH=
endif

SOURCES = S2.h f64.2.h sieve.h sqf.h arith_tools.h longgmp.h sieve_dyn_methodes.h typedefs.64.gmp.h\
	functionId.h longreal.h sieve_dynamic.h typedefs.64.h btable.h globals.h p2xy.h sieveext.h\
	typedefs.gmp.h chrono.h int64.h presieve30.h data.h inv64.h primes.h sievelng.h vector.h f64.1.h\
	long64.h read_data.h sommeV2.h


OBJ =	arith_tools.o  btable.o p2xy.o data.o  primes.o\
	little_primes.o	read_data.o int64.o longgmp.o sqf.o fixy.o\
	special_leaves.o S1.o S2.o S3.o sommeV.o sommeV1.o ordinary_leaves.o\
	sommesW.o  chrono.o Li.o sfx.o F.o 

CXX =  g++ 

%.o: %.cc *.h
	$(CXX) $(CFLAGS) -c $<

objs:$(OBJ)

all:
	make cleanexec
	echo "Make pi64"
	make pi64
	echo "Make sump64"	
	make sump64
	echo "Make prime64"	
	make prime64
	echo "Make invsump64"	
	make invsump64

main: $(OBJ)
	$(CXX) $(CFLAGS) $(LFLAGS) -o main -L/opt/local/lib   main.cc $(OBJ)  $(LIBS)
	rm -f typedefs.h longint.h longval.h f.h F.h F.cc	

pi64:	$(SOURCES)
	echo $(UNAME)
	./configure pi64
	make main
	cp main pi64
	make prime64

pi:	$(SOURCES)
	./configure pi
	make main
	cp main pi
	make clean

sump64:	$(SOURCES)
	./configure sump64
	make main
	cp main sump64
	make clean


sump:	$(SOURCES)
	./configure sump
	make main
	cp main sump
	make clean


prime64:$(SOURCES)
	./configure prime64
	make objs
	$(CXX) $(LFLAGS) $(CFLAGS) -o prime64 prime.cc $(OBJ) $(LIBS)
	make clean

prime:	$(SOURCES)
	./configure prime
	make objs
	$(CXX) $(LFLAGS) $(CFLAGS) -L/opt/local/lib  -o prime prime.cc $(OBJ)  $(LIBS) 	
	make clean

invsump64: $(SOURCES)
	make clean
	./configure invsump64
	make objs
	$(CXX) $(LFLAGS) $(CFLAGS) -L/opt/local/lib  -o invsump64 invsump.cc $(OBJ) $(LIBS)	
	make clean



invsump	: $(SOURCES) invsump.cc
	./configure invsump
	make objs
	$(CXX) $(LFLAGS) $(LPATH) $(CFLAGS) -o invsump invsump.cc $(OBJ) $(LIBS)	
	make clean

#################################################################################################################


clean:
	rm -f *~ *.o longint.* longval.* f.h F.h F.cc typedefs.h p

cleanexec:
	rm -rf  pi64 sump64 sump invsump invsump64 prime64 prime pi main

tags:
	etags *.cc *.h Makefile

