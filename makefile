
output: PixelArrangement.o
	gcc Assignment1.o -o output	

PixelArrangement.o:PixelArrangement.c
	gcc -c PixelArrangement.c

clean:
	rm *.o output
