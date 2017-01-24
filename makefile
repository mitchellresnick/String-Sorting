all: pointersorter

pointersorter: pointersorter.c
	gcc -Wall -g -o pointersorter pointersorter.c
	#Use ./pointersorter [args]

test:
	./pointersorter Apple Bear
	./pointersorter apple Apple
	./pointersorter Apple apple
	./pointersorter aNd and
	./pointersorter and aNd
	./pointersorter Apple bear
	./pointersorter apple Bear
	#Test Complete - Results Above

clean:
	rm -f pointersorter
	#Cleaned
