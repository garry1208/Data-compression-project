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
	FILE *inputfp /*outputfp*/;
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
	//printf("%d", argc);
	if(argc != 2) {
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
	//outputfp = fopen(argv[2], "w+");
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
	free(str);
	return 0;
}
