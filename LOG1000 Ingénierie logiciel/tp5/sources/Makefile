
article: Emission.o main.o Chaine.o
	g++ -o Emission main.o Emission.o Chaine.o

Emission.o: Emission.cpp Emission.h Chaine.h
	g++ -o Emission.o -c Emission.cpp

Chaine.o: Chaine.cpp Chaine.h
	g++ -o Chaine.o -c Chaine.cpp

main.o: main.cpp Emission.h 
	g++ -o main.o -c main.cpp
 
clean: 
	rm *.o
	rm Emission
