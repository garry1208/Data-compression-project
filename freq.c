#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char *str;
	str = (char *)malloc(sizeof(char) * 1000000000);
	if(str == NULL) {
		printf("malloc failed");
		return 1;
	}
	fp = fopen(argv[1], "r");
	if(fp == NULL) {
		perror("E:cannot open file");
		return 1;
	}
	int i = 0;
	while(!feof(fp)) {
		str[i] = fgetc(fp);
		i++;
	}
	str[i] = '\0';
	int counts[256] = { 0 };
	for (i = 0; str[i] != '\0'; i++) {
	    counts[(int)(str[i])]++;
	}
	for (i = 0; i < 256; i++) {
		if(counts[i] > 0)
			printf("The %c character has %d occurrences\n", i, counts[i]);
	}
	free(str);
	return 0;
}
