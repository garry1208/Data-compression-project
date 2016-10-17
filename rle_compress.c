#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *inputfp, *outputfp;
	char *inputstr, *outputstr, ch;
	int i = 0, j = 0, k;
	long int charcount = 0;
	inputstr = (char *)malloc(sizeof(char) * 1000000);
	outputstr = (char *)malloc(sizeof(char) * 10000);
	inputfp = fopen(argv[1], "r");
	if(inputfp == NULL) {
		perror("E:cannot open file");
		return 1;
	}
	if(argc != 2) {
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
	while(inputstr[i] != '\0') {
		outputstr[j++] = inputstr[i];
		charcount++;
		for(k = i + 1; inputstr[k] == inputstr[k - 1]; k++) {
			charcount++;
			i++;
		}
		outputstr[j++] = charcount + '0';
		i++;
		charcount = 0;
	}
	outputstr[j] = '\0';
	printf("%s\n", inputstr);
	printf("%s\n", outputstr);
	return 0;
}
