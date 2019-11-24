CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)

randomtest1: randomtest1.c dominion.o rngs.o
	gcc -o randomtest1 -g randomtest1.c dominion.o rngs.o $(CFLAGS)

randomtest2: randomtest2.c dominion.o rngs.o
	gcc -o randomtest2 -g randomtest2.c dominion.o rngs.o $(CFLAGS)

randomtest3: randomtest3.c dominion.o rngs.o
	gcc -o randomtest3 -g randomtest3.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: unittest1 unittest2 unittest3 unittest4 randomtest1 randomtest2 randomtest3
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	./randomtest1 >> unittestresults.out
	./randomtest2 >> unittestresults.out
	./randomtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
#above 7 lines of code referenced from Piazza discussion post for class 362 author
#John Hash from assignment 3 makefile discussion
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unittest1 unittest2 unittest3 unittest4 unittest5 randomtest1 randomtest2 randomtest3 unittestresults

clean:
	rm -f *.o playdom.exe playdom player unittest1 unittest2 unittest3 unittest4 unittest5 randomtest1 randomtest2 randomtest3  player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
