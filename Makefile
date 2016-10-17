try : freq.o huff_encode.o
	cc freq.o huff_encode.o -o try 
freq.o : freq.c huff_encode.h
	cc -c -Wall freq.c
huff_encode.o : huff_encode.c huff_encode.h
	cc -c -Wall huff_encode.c
  
