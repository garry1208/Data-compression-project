
					/********************************************************************************
					 *	DSA 2016 MINI PROJECT : DATA COMPRESSION				*
					 *										*
					 *	ALGORITHMS IMPLEMENTED : 1) HUFFMAN COMPRESSION				*
					 *				 2) LEMPEL ZIV WELCH (LZW) ALGORITHM		*
					 *				 3) RUN LENGTH ENCODING (RLE) ALGORITHM		*
					 *										*
					 ********************************************************************************/

/********************************************************************************
 * Copyright (C) ROHIT KHOLE , MIS: 111503034 rohitkhole5@gmail.com 		*
 *										*
 * This program is free software; you can redistribute it and/or modify it	*
 * under the terms of the GNU Lesser General Public License as published by	*
 * the Free Software Foundation; either version 2.1 of the License, or		*
 * (at your option) any later version.						*
 *										*
 * This program is distributed in the hope that it will be useful,		*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of		*
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the			*
 * GNU Lesser General Public License for more details.				*
 *										*
 * You should have received a copy of the GNU Lesser General Public License	*
 * along with this program; if not, write to the Free Software Foundation,	*
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.		*
 *										*
 ********************************************************************************/



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
#include <math.h>
#include "huff_encode.h"

/******************************  HUFFMAN ALGORITHM UTILITY FUNCTIONS  ***************************/

void treeinit(tree root) {
	
	root->left = root->right = NULL;
}

struct node *createnode(char data, int freq) {				//create a node for the tree
	
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp->left = temp->right = NULL;
	temp->ch = data;
	temp->freq = freq;
	return temp;
}

struct minheap *createminheap(long int capacity) { 			 //create and initialise min heap
	int i;
	struct minheap *Minheap1 = (struct minheap *) malloc(sizeof(struct minheap));
	Minheap1->heapsize = 0;  // current size is 0
	Minheap1->capacity = capacity;
	Minheap1->array = (struct node**)malloc(Minheap1->capacity * sizeof(struct node*));
	for(i = 0; i < capacity; i++) {
	
		Minheap1->array[i] = (struct node *)malloc(sizeof(node));
	}
	Minheap1->array[0]->freq = INT_MAX;
	return Minheap1;
}

void inserttoheap( struct node *temp) {					 //insert to heap without sorting
		Minheap->array[Minheap->heapsize] = temp;
		Minheap->heapsize++;
}

void heapify() { 		//sort in ascending order
	int i, j;
	node *temp;
	for(i = 0; i < Minheap->heapsize; i++) {
		for(j = i; j < Minheap->heapsize; j++) {
			if(Minheap->array[i]->freq > Minheap->array[j]->freq) {
			
				temp = (struct node *)malloc(sizeof(struct node));
				temp = Minheap->array[i];
				Minheap->array[i] = Minheap->array[j];
				Minheap->array[j] = temp;
			}
		}
	}
}
		
int issizeone() {		// CHECK IF THE SIZE IS ONE OR NOT
	return Minheap->heapsize == 1;
}

struct node* deletemin() {			 //extract min node from minheap
	int i;
	node *temp = (struct node *)malloc(sizeof(node)); 
	if(!issizeone()) {
		temp = Minheap->array[0];
		for(i = 0; i < Minheap->heapsize; i++) {
			Minheap->array[i] = Minheap->array[i + 1];
		}
		Minheap->heapsize--;
		return temp;
	}
	else {
		Minheap->heapsize--;
		return Minheap->array[0];
	}
	
}

/* build huffman tree
 * the internal node has char as '$' and freq as the sum of freq of its child nodes.
 */
 
node *buildhuffmantree() {
	int newfreq, i = 0;
	char newch = '$';
	while(!issizeone()) {
		node1 = deletemin();
		node2 = deletemin();
		newfreq = node1->freq + node2->freq;
		intnode[i] = createnode(newch, newfreq);
		intnode[i]->left = node1;
		intnode[i]->right = node2;
		inserttoheap(intnode[i]);
		i++;
		heapify();
	}
	if(issizeone())
		return Minheap->array[0];
	else
		return NULL;
}


typedef struct codetable {
	char codestr[1000];
	char ch;
}codetable;

int struct_index = 0;

struct codetable codestructarr[1000], tempstruct;

/********************************   LZW UTILITY FUNCIONS   *******************************/

typedef struct dict {
	char word[1000];
	int index;
}dict;

dict dictionary_arr[5000];	//dictionary that contains word and its corresponding index.

/***********  linear search function that searches for a substring in dictionary  ********/

int search_in_dict(char *str, int dict_len) {
	int i;
	for(i = 0; i < dict_len; i++) {
		if(strcmp(str, dictionary_arr[i].word) == 0)
			return i;
	}
	//NOT FOUND
	return -1;
}

int search_index_dict(int index, int dict_len) {
	int i;
	for(i = 0; i < dict_len; i++) {
		if((dictionary_arr[i].index) == index)
			return i;
	}
	//NOT FOUND
	return -1;
}

/****************  ENCODE FUNCTION   *************************/

/*  convert the index to binary representation and store it in 12 byte string
 *  if int is directly stored it would take sizeof(int) * 12 bytes so that 
 *  compression ratio increases significantly.                              */

char *encode_index(int in) {
	char *code = (char *)malloc(sizeof(char) * 13);
	int bit;
	int j;
	j = 0;
	while(j < 12) {
		bit = (in >> j) & 1;
		if(bit == 1)
			code[12 - j - 1] = '1';
		else
			code[12 - j - 1] = '0';
		j++;
	}
	code[12] = '\0';
	return code;
}

/*****************  TO OBTAIN DECIMAL INDEX FROM BINARY STRING READ FROM FILE   *******************/
 
int obtain_index(char *codestr1) {
	long n;
	int decimalNumber = 0, i = 0, remainder;
	n = atol(codestr1);
	while (n != 0)	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder* pow(2, i);
		++i;
	}
	return decimalNumber;
}

/**************************    MAIN    ***************************/	

int main(int argc, char *argv[]) {

	FILE *inputfp, *outputfp;
	int headersize = 0, readmagicnumber;
	char *str, ch, *inputstr;
	char codestr[1000];
	strcpy(codestr, "\0");
	int bit_val, bitsread = 0;
	long long bitswritten = 0;
	int bitsinbuffer = 0, magicnumber = 111;
	long int c = 0, charcount = 0;
	long long filesize = 0, encodesize = 0;
	unsigned char bit = 0;
	int j, i, k;
	int structsize, codelen = 0;
	char nextchar, tempstr[2], wstr[100], comparestr[100], *codestr1, decodestr[13], entry[100], tmpstr[3];
	int dict_len = 0, currcode, prevcode, idx;
	
	str = (char *)malloc(sizeof(char) * 100000000);
	
	
	if(argc != 5 && argc != 2) {
		perror("usage: <./project> <input file> <destination file> -c | -dc <huffman | rle | lzw>\n Type ./project -h for help\n");
		return 1;
	}
	
	
	if(strcmp(argv[1], "-h") == 0) {
		printf("  USAGE : <./project> <input filename> <destination filename> <-c | -dc> <huffman | rle | lzw \n");
		printf("          File to be compressed is the <input file name> \n");
		printf("          Compressed or decompressed file is stored at <destination filename>\n");
		printf("          -c : to compress a file\n");
		printf("          -dc : to decompress a file\n");
		printf("          huffman : to compress or decompress using huffman algorithm\n");
		printf("          rle : to compress or decompress using rle algorithm\n");
		printf("          lzw : to compress or decompress using lzw algorithm\n");
		
		return 0;
	}
	
	
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
	

/**********************   HUFFMAN COMPRESSION  ***********************/

	
	if(strcmp(argv[4], "huffman") == 0) {
		if(strcmp(argv[3], "-c") == 0) {
		
			//write the detection number to detect if the file is compressed or not
			
			fwrite(&magicnumber, sizeof(int), 1, outputfp);
			i = 0;
			
			/**************  Calculate the frequency of each character in file ***********/
			
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
			Minheap = createminheap(c);
			for (i = 0; i < 256; i++) {
				if(counts[i] > 0) {
					ch = i;
					struct node *temp = createnode(ch, counts[i]);
					inserttoheap(temp);
				}
			}
			heapify();
			root = buildhuffmantree();

		/************  write the character and its corresponding code as huffman header  **********/
		
			void writehuffheader(FILE *outputfp, tree t, char *codearr, int in) {
				int j = 0;
				if(in == 0)
					codearr = (char *)malloc(sizeof(char) * 1000);
				if(t->left) {
					codearr[in] = '0';
					writehuffheader(outputfp, t->left, codearr, in + 1);
				}
				if(t->right) {
					codearr[in] = '1';
					writehuffheader(outputfp, t->right, codearr, in + 1);
				}
				if(t->left == NULL && t->right == NULL) { //it is a leaf node
					in++;
					codearr[in] = '\0';
					strcpy(tempstruct.codestr, codearr);
					tempstruct.ch = t->ch;
					codestructarr[struct_index].ch = tempstruct.ch;
					strcpy(codestructarr[struct_index].codestr , tempstruct.codestr);
					struct_index++;
					fwrite(&tempstruct.ch, sizeof(char), 1, outputfp);
					filesize += sizeof(char);
					while(j < strlen(tempstruct.codestr)) {
						fwrite(&tempstruct.codestr[j], sizeof(char), 1, outputfp);
						filesize += sizeof(char);
						j++;
					}
					fputc('\0', outputfp);
					filesize += sizeof(char);
				}
				
			}
			
		/*********  write the binary code to file such that for 00 it uses only 2 bits
			    and store it in byte array in continuos way   ************/
			    	
			void writecodetofile(char *codearr1) {
				for ( j = 0; codearr1[j] != '\0'; j++ ) {
					bit |= (codearr1[j] == '1') << (7 - bitsinbuffer);
					bitsinbuffer++;
					if(bitsinbuffer == 8) {
						fputc(bit, outputfp);
						filesize += sizeof(char);
						bit = 0;
						bitsinbuffer = 0;
					}
				}
			}
			
		/*************  generate the huffman code for the corresponding character and write it to file **********/
		
			void encode() {
				while((fread(&ch, sizeof(char), 1, inputfp)) != 0) {
					for(i = 0; i < headersize; i++) {
						if(codestructarr[i].ch == ch) {
							writecodetofile(codestructarr[i].codestr);
							break;
						}
					}
				}
				if(bitsinbuffer < 8 && bitsinbuffer > 0) {
					fputc(bit, outputfp);
				}
			}
			fseek(inputfp, 0l, 0);
			headersize = sizeof(char) * c;
			fwrite(&headersize, sizeof(int), 1, outputfp);
			writehuffheader(outputfp, root, codearr, 0);
			for(i = 0; i < struct_index; i++) {
				encodesize = encodesize + (strlen(codestructarr[i].codestr) * counts[(int)codestructarr[i].ch]) ;
			}
			fwrite(&encodesize, sizeof(long long), 1, outputfp);
			fseek(inputfp, 0l, 0);
			encode();
			printf("file compressed to %s successfully !!\nsize :%lld\n", argv[2], filesize);
		}
		
		
	/*******************   HUFFMAN DECOMPRESSION   *************************/
	
	
		else if(strcmp(argv[3], "-dc") == 0) {
		
			fread(&readmagicnumber, sizeof(int), 1, inputfp);
			
			if(readmagicnumber != 111) {
				printf("E : the file is not in compressed format :: INVALID FILENAME\n");
				return 1;
			}
			 
			i = 0;
			j = 0;
			codelen = 0;
			strcpy(codestr, "\0");
			bitsread = 0;
			fread(&headersize, sizeof(int), 1, inputfp);
			structsize = headersize;
			
			// this loop reads the header and stores in struct header
			
			do {
				if(headersize == 0)
					break;

				fread(&ch, sizeof(char), 1, inputfp);

				codestructarr[i].ch = ch;

				while(1) {
					fread(&codestructarr[i].codestr[j++], sizeof(char), 1, inputfp);
					if(codestructarr[i].codestr[j - 1] == '\0') {
						i++;
						j = 0;
						break;
					}
				}
			}while(headersize--);		//header is read.
			
			//read total bits written in file
					
			fread(&bitswritten, sizeof(long long), 1, inputfp);
			i = 1;
			
			/* read the actual compressed bits 
			 * and retrieve the encoded character
			 * and write to file */
			
			while(bitsread < bitswritten) {
				fread(&bit, sizeof(char), 1, inputfp);
				i = 1;
				while(i <= 8) {
					bit_val = (bit & (1 << 8 - i)) != 0;
					if(bit_val == 1)
						strcat(codestr, "1");
					if(bit_val == 0)
						strcat(codestr, "0");
					bitsread++;
					codelen++;
					
					for(j = 0; j < structsize; j++) {
							if(strcmp(codestructarr[j].codestr, codestr) == 0) {
								//printf("MATCH: %c : %s\n", codestructarr[j].ch, codestructarr[j].codestr);
								fwrite(&codestructarr[j].ch, sizeof(char), 1, outputfp); 
								codelen = 0;
								strcpy(codestr, "\0");
								break;
							}
					}
					i++;
					if(bitsread == bitswritten)
						break;
			
				}
				//printf("\n");
			}
			printf("file decompressed to %s successfully !!\n ", argv[2]);
		}
		
		else {
			printf("enter valid argument: [ -c | -dc ] \n");
			exit(1);
		}
	}
	
	/*************  RLE COMPRESSION AND DECOMPRESSION   *****************/
	
	else if(strcmp(argv[4], "rle") == 0) {
		i = 0;
		inputstr = (char *)malloc(sizeof(char) * 1000000);
	
		
	/***************  RLE COMRPESS  **************************/
		
		if(strcmp(argv[3], "-c") == 0) {
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
		}
	
		
	/*****************   RLE DECOMPRESS   ******************/
	
		else if(strcmp(argv[3], "-dc") == 0) {
			fread(&readmagicnumber, sizeof(int), 1, inputfp);
			if(readmagicnumber != 111) {
				printf("! invalid file ::the file is not in compressed form\n");
				return 1;
			}
			while(!feof(inputfp)) {
				fread(&ch, sizeof(char), 1, inputfp);
				fwrite(&ch, sizeof(char), 1, outputfp);
				fread(&charcount, sizeof(long int), 1, inputfp);
				charcount--;
				while(charcount > 0) {
					fwrite(&ch, sizeof(char), 1, outputfp);
					charcount--;
				}
			}
			printf("file decompressed to %s successfully!\n" , argv[2]);
		}
		
		else {
			printf("enter valid argument: [ -c | -dc ] \n");
			exit(1);
		}
	}
	
	/********************   LEMPEL ZIV WELCH (LZW) COMPRESSION AND DECOMPRESSION  ********************/
	
	else if(strcmp(argv[4], "lzw") == 0) {
		
		/**********  create and initialise dictionary with first 256 ascii characters  ********/
	
		for(i = 0; i < 256; i++) {
			ch = i;
			tempstr[0] = ch;
			tempstr[1] = '\0';
			strcpy(dictionary_arr[i].word, tempstr);	//write the character and its index in dictionary.
			dictionary_arr[i].index = i;
			//printf("%s : %d\n", dictionary_arr[i].word, dictionary_arr[i].index);
		}
	
		dict_len = 256;
	
	
	/************************   LZW COMPRESSION   *******************/
	
	
		if(strcmp(argv[3], "-c") == 0) {
		
			//write the detection number to detect if the file is compressed or not
			
			fwrite(&magicnumber, sizeof(int), 1, outputfp);
			
			/***********   read from file and encode   ***************/
		
			strcpy(wstr, "\0");	//first wstr is empty
			while(fread(&nextchar, sizeof(char), 1, inputfp)) {
				strcpy(comparestr, wstr);
				tempstr[0] = nextchar;
				tempstr[1] = '\0';
				
				//comparestr = wstr + nextchar
				strcat(comparestr, tempstr);					
				
				//if w + ch is present in dictionary
				if((search_in_dict(comparestr, dict_len)) != -1) {		
					strcat(wstr, tempstr);					//wstr = wstr + nextchar
				}
				
				else {		//not found in dictionary
					
					//encode wstr to file
					idx = search_in_dict(wstr, dict_len);
					if(idx != -1) {
						codestr1 = encode_index(idx);		//obtain index in binary form
						i = 0;
						while(codestr1[i] != '\0') {
							fwrite(&codestr1[i++], sizeof(char), 1, outputfp);	//write index(code) to file
						}
						fputc('\0', outputfp);
					}
					
					//add wstr + ch to dictionary
					strcpy(dictionary_arr[dict_len].word, comparestr);
					dictionary_arr[dict_len].index = dict_len;
					dict_len++;
					
					//wstr becomes nextchar
					strcpy(wstr, tempstr);
				}
			}
		
			//encode wstr to file i.e. the last substring.
		
			if(strcmp(wstr, "\0") != 0) {
				idx = search_in_dict(wstr, dict_len);
				if(idx != -1) {
					codestr1 = encode_index(idx);
					i = 0;
					while(codestr1[i] != '\0') {
						fwrite(&codestr1[i++], sizeof(char), 1, outputfp);	//write index(code) to file
					}
					fputc('\0', outputfp);
				}
			}
			printf("file compressed to %s successfully !! \n", argv[2]);
		}
		
	/************************   LZW DECOMPRESSION   *****************/
	
	
		else if(strcmp(argv[3], "-dc") == 0) {
		
			fread(&readmagicnumber, sizeof(int), 1, inputfp);
			
			if(readmagicnumber != 111) {
				printf("E : the file is not in compressed format :: INVALID FILENAME\n");
				return 1;
			}
			
			strcpy(decodestr, "\0");
			i = 0;

			/********   read in the first code   **********/
			
			while(fread(&ch, sizeof(char), 1, inputfp)) {
				if(ch == '\0') {
					decodestr[i++] = '\0';
					prevcode = obtain_index(decodestr);
					fwrite(dictionary_arr[prevcode].word, sizeof(char), strlen(dictionary_arr[prevcode].word), outputfp);
					strcpy(decodestr, "\0");
					i = 0;
					break;
				}
				else
					decodestr[i++] = ch;
			}
		
			/************   read remaining codes till EOF   ************/
		
			strcpy(decodestr, "\0");
			i = 0;
		
			while(fread(&ch, sizeof(char), 1, inputfp)) {
				if(ch == '\0') {		//code is read.
					decodestr[i++] = '\0';
					currcode = obtain_index(decodestr);
					if(search_index_dict(currcode, dict_len) != -1) {	//if currcode exists in dictionary 
						//entry is translation of currcode from dictionary
						strcpy(entry, dictionary_arr[currcode].word);
						
						fwrite(dictionary_arr[currcode].word, sizeof(char), strlen(dictionary_arr[currcode].word),outputfp);
						strcpy(entry, dictionary_arr[prevcode].word);
						//ch = first char of currcode
						ch = dictionary_arr[currcode].word[0];
						
						//make a string of this ch
						tmpstr[0] = ch;	//this is a single char string.
						tmpstr[1] = '\0';
						
						//add (translation of prevcode + ch) to dictionary
						strcpy(comparestr, dictionary_arr[prevcode].word);
						strcat(comparestr, tmpstr);
						strcpy(dictionary_arr[dict_len].word, comparestr);
						dictionary_arr[dict_len].index = dict_len;
						dict_len++;
					}
					//if currcode is not in dictionary
					else {
						strcpy(entry, dictionary_arr[prevcode].word);
						ch = dictionary_arr[prevcode].word[0];
						tmpstr[0] = ch;
						tmpstr[1] = '\0';
						strcat(entry, tmpstr);
						fwrite(entry, sizeof(char), strlen(entry), outputfp);
						strcpy(dictionary_arr[dict_len].word, entry);
						dictionary_arr[dict_len].index = dict_len;
						dict_len++;
					}
					strcpy(entry, "\0");
					strcpy(decodestr, "\0");
					strcpy(comparestr, "\0");
					prevcode = currcode;
					i = 0;
				}
				else
					decodestr[i++] = ch;
			}
			printf("file decompressed to %s successfully !! \n", argv[2]);
		}
		
		
		else {
			printf("enter valid argument: [ -c | -dc ] \n");
			exit(1);
		}
	}
	fclose(inputfp);
	fclose(outputfp);
	return 0;
}
