CC=gcc
AR=ar
MAIN=main.o
FUNC=functions.o
FLAGS=-Wall -g

all: stringProg
stringProg: $(MAIN) $(FUNC)
	$(CC) $(FLAGS) -o stringProg $(MAIN) $(FUNC)
$(MAIN): main.c funcs.h
	$(CC) $(FLAGS) -c main.c 
$(FUNC): functions.c funcs.h
	$(CC) $(FLAGS) -c functions.c  

.PHONY: clean all
clean:
	rm -f *.o connections