#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

int main(int argc, char *argv[]) {
	FILE *inputfp, *outputfp;
	char *inputstr, ch;
	int i = 0, k, magicnumber = 111;
	long int charcount = 0;
	inputstr = (char *)malloc(sizeof(char) * 1000000);
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
	if(argc != 3) {
		perror("usage: <a.out> <input file> <output file>");
		return 1;
	} 
	while(fscanf(inputfp, "%c", &ch) != -1) {
		inputstr[i] = ch;
		i++;
		if(i == 1000000)
			inputstr = realloc(inputstr, sizeof(char) * 1000000 * 2);
	}
	inputstr[i] = '\0';
	i = 0;
	fwrite(&magicnumber, sizeof(int), 1, outputfp);
	while(inputstr[i] != '\0') {
		fwrite(&inputstr[i], sizeof(char), 1, outputfp);
		charcount++;
		for(k = i + 1; inputstr[k] == inputstr[k - 1]; k++) {
			charcount++;
			i++;
		}
		fwrite(&charcount, sizeof(long int), 1, outputfp);
		charcount = 0;
		i++;
	}
	i = 0;
	printf("file compressed to %s successfully !! \n", argv[2]);
	fclose(inputfp);
	fclose(outputfp);
	return 0;
}
