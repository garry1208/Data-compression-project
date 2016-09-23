/*

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;
*/
void decode_huff(node * root,string s)
{
 char ch;
    int i = 0;
    node *tmp;
    tmp = root;
 while(s[i] != '\0') {
     ch = s[i];
     if(ch == '0')
         root = root->left;
     else if(ch == '1')
         root = root->right;
     if(root->left == NULL && root->right == NULL) {
         printf("%c", root->data);
         root = tmp; // reset root
     }
     i++;
 }   
}

