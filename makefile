CC=gcc
CCFLAGS=-g -Wall
LIBS=-lm -lSDL
ALL= background.o collisionDetection.o init.o main.o mergeOverlapped.o \
		 movementBoundCheck.o objectBlit.o objectStore.o playermovement.o \
		 random.o sdlstore.o vectorMath.o velIntoPos.o
all: $(ALL)
		 $(CC) $(CCFLAGS) -o xOsmosClone $(LIBS) $(ALL)

clean:
			rm $(ALL) xOsmosClone

background.o: background.c sdlstore.o 
							$(CC) $(CCFLAGS) -c background.c

collisionDetection.o: collisionDetection.c
											$(CC) $(CCFLAGS) -c collisionDetection.c

init.o: init.c objectStore.o sdlstore.o collisionDetection.o random.o
				$(CC) $(CCFLAGS) -c init.c

main.o: main.c init.o sdlstore.o playermovement.o velIntoPos.o \
				movementBoundCheck.o mergeOverlapped.o background.o objectBlit.o
				$(CC) $(CCFLAGS) -c main.c

mergeOverlapped.o: mergeOverlapped.c objectStore.o
									 $(CC) $(CCFLAGS) -c mergeOverlapped.c

movementBoundCheck.o: movementBoundCheck.c objectStore.o
											$(CC) $(CCFLAGS) -c movementBoundCheck.c

objectBlit.o: objectBlit.c objectStore.o sdlstore.o
							$(CC) $(CCFLAGS) -c objectBlit.c

objectStore.o: objectStore.c
							 $(CC) $(CCFLAGS) -c objectStore.c

playermovement.o: playermovement.c objectStore.o sdlstore.o
								 $(CC) $(CCFLAGS) -c playermovement.c

random.o: random.c
					$(CC) $(CCFLAGS) -c random.c

sdlstore.o: sdlstore.c
						$(CC) $(CCFLAGS) -c sdlstore.c

vectorMath.o: vectorMath.c
							$(CC) $(CCFLAGS) -c vectorMath.c

velIntoPos.o: velIntoPos.c sdlstore.o objectStore.o
							$(CC) $(CCFLAGS) -c velIntoPos.c
