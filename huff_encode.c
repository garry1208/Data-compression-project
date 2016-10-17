#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "huff_encode.h"

void treeinit(tree root) {
	root->left = root->right = NULL;
}

struct node *createnode(char data, int freq) { //create a node for the tree
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp->left = temp->right = NULL;
	temp->ch = data;
	temp->freq = freq;
	return temp;
}

struct minheap *createminheap(long int capacity) {  //create and initialise min heap
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

void inserttoheap( struct node *temp) { //insert to heap without sorting
		//Minheap->array[Minheap->heapsize] = (node *)malloc(sizeof(struct node));
		//printf("in insert function\n");
		Minheap->array[Minheap->heapsize] = temp;
		/*Minheap->array[Minheap->heapsize]->ch = temp->ch;
		printf("1\n");
		Minheap->array[Minheap->heapsize]->freq = temp->freq;
		printf("2\n");
		Minheap->array[Minheap->heapsize]->left = temp->left;
		printf("3\n");
		Minheap->array[Minheap->heapsize]->right = temp->right;
		printf("4\n");*/
		Minheap->heapsize++;
		//printf("inserted\n");
}

void heapify() { //sort in ascending order
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
		
int issizeone() {
	return Minheap->heapsize == 1;
}

struct node* deletemin() { //extract min node from minheap
	int i;
	node *temp = (struct node *)malloc(sizeof(node)); 
	if(!issizeone()) {
		temp = Minheap->array[0];
		/*Minheap->array[0]->ch = temp->ch;
		Minheap->array[0]->freq = temp->freq;
		Minheap->array[0]->left = temp->left;
		Minheap->array[0]->right = temp->right;*/
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

node *buildhuffmantree() {
	int newfreq, i = 0;
	char newch = '$';
	while(!issizeone()) {
		node1 = deletemin();
		printf("%c %d\n", node1->ch, node1->freq);
		node2 = deletemin();
		printf("%c %d\n", node2->ch, node2->freq);
		newfreq = node1->freq + node2->freq;
		printf("%d\n", newfreq);
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

void printhufftree(tree t) {
	if(t == NULL)
		return;
	printhufftree(t->left);
	printf("%c  %d\n", t->ch, t->freq);
	printhufftree(t->right);
}


