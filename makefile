
output: Assignment1.o
	gcc Assignment1.o -o output	

Assignment1.o:Assignment1.c
	gcc -c Assignment1.c

clean:
	rm *.o output
