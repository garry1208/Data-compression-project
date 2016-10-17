typedef struct node {
	char ch;
	int freq;
	int code;
	struct node *left, *right;
}node;

typedef struct node *tree;

tree root;

node *node1, *node2, *intnode[1000000];

typedef struct minheap {
	long int heapsize;
	long int capacity;
	struct node **array;
}minheap;

struct minheap *Minheap;

char *codearr;

struct node* createnode(char ch, int freq);

void treeinit(tree t);

void inserttoheap( struct node *tmp); // insert the temp node created by createnode()

struct node* deletemin();

struct minheap *createminheap(long int capacity);

int issizeone();

void heapify();

node *buildhuffmantree();

void printhufftree(tree t);

void encode(FILE *,tree t, char *, int);

void writecodetofile(char *);
