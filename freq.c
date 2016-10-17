#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include "huff_encode.h"


int main(int argc, char *argv[]) {
	FILE *inputfp, *outputfp;
	char *str, ch;
	long int c = 0;
	str = (char *)malloc(sizeof(char) * 100000000);
	if(str == NULL) {
		printf("malloc failed");
		return 1;
	}
	inputfp = fopen(argv[1], "r");
	if(inputfp == NULL) {
		perror("E:cannot open file");
		return 1;
	}
	outputfp = fopen(argv[2], "w");
	if(outputfp == NULL) {
		perror("E:cannot create file");
		return 1;
	}
	//printf("%d", argc);
	if(argc != 4) {
		perror("usage: <a.out> <input file> <destination file> -c | -dc");
		return 1;
	}
	int i = 0;
	while(!feof(inputfp)) {
		str[i] = fgetc(inputfp);
		i++;
	}
	str[i] = '\0';
	int counts[256] = { 0 };
	for (i = 0; str[i] != '\0'; i++) {
	    counts[(int)(str[i])]++;
	}
	for(i = 0; i < 256; i++) {
		if(counts[i] > 0)
			c++;
	}
	printf("%ld\n", c);
	Minheap = createminheap(c);
	for (i = 0; i < 256; i++) {
		if(counts[i] > 0) {
			ch = i;
			printf("The %c character has %d occurrences\n", ch, counts[i]);
			struct node *temp = createnode(ch, counts[i]);
			//printf("node created\n");
			inserttoheap(temp);
			// printf("inserted\n");
		}
	}
	heapify();
	printf("heapified\n");
	for(i = 0; i < Minheap->heapsize; i++) {
		printf("%c\t%d\n", Minheap->array[i]->ch, Minheap->array[i]->freq);
	}
	root = buildhuffmantree();
	if(root != NULL)
		printf("huffman tree built\n");
	printhufftree(root);
	
	void writecodetofile(char *codearr) {
		unsigned char bit = 0;
		int bitswritten = 0, j, i;
		for ( i = 0; codearr[i] != '\0'; i++ ) {
			if(i == 8)
				break;
			bit |= (codearr[i] == '1') << (7 - i);
		}
		fputc(bit, outputfp);
		bit = 0;
		if(codearr[i] != '\0' && i == 8) {
			j = 0;
			while(codearr[i] != '\0') {
				if(bitswritten == 8) {
					fputc(bit, outputfp);
					bit = 0;
					continue;
				}
				else {
					bit |= (codearr[i] == '1') << (7 - j);
					i++;
					j++;
					bitswritten++;
				}
			}
		}
		//printf("code written\n");
	}
	void encode(FILE *outputfp, tree t, char *codearr, int in) {
		//printf("in encode:\n");
		if(in == 0)
			codearr = (char *)malloc(sizeof(char) * 1000);
		if(t->left) {
			//printf("0 stored\n");
			codearr[in] = '0';
			encode(outputfp, t->left, codearr, in + 1);
		}
		if(t->right) {
			//printf("1 stored\n");
			codearr[in] = '1';
			encode(outputfp, t->right, codearr, in + 1);
		}
		if(t->left == NULL && t->right == NULL) { //it is a leaf node
			//printf("leaf found\n");
			in++;
			codearr[in] = '\0';
			printf("%c : %s\n",t->ch, codearr);
			//int j = 0;
			//while(codearr[j] != '\0') {
			//	printf("%c", codearr[j]);
			//	j++;
			//}
			//printf("\n");
			writecodetofile(codearr);
			//free(codearr);
		}
	}
	encode(outputfp, root, codearr, 0);
	fprintf(outputfp, "EOF");
	free(str);
	return 0;
}
