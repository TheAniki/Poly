# default command, builds an executable called "newton".
# executable can be called with ./newton 49 4
NewtonTargets = newton

all: $(NewtonTargets)

CC = gcc

LINKERFLAG = -lm


# link the object files into the executable.
# the -lm option is to tell the linker to include math libraries.
$(NewtonTargets): main.o newton.o comparison.o
	$(CC) -o $@ $^ $(LINKERFLAG)
# 	$(CC) -o newton main.o newton.o comparison.o -lm

# compile the main.c file into the main.o object file.
main.o: main.c newton.h comparison.h
	@echo "Compiling main files ..."
	$(CC) -o $@ -c $< 
#	gcc -o main.o -c main.c

# compile the newton.c file into the newton.o object file.
newton.o: newton.c newton.h
	@echo "Compiling newton files ..."
	$(CC) -o $@ -c $< 
#	$(CC) -o newton.o -c newton.c

# compile the comparison.c file into the comparison.o object file.
comparison.o: comparison.c comparison.h
	@echo "Compiling comparison files ..."
	$(CC) -o $@ -c $< 
#	gcc -o comparison.o -c comparison.c

# remove the executable and intermediary object files.
clean:
	rm -rf newton main.o newton.o comparison.o

install:
	mkdir install
	make 
	cp newton instal

