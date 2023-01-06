/**
 * Name: Manu Konnur
 * ID: 1178498
 * Date: 12/11/22
 * Assignment #3 - Binary Expression Tree
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

//a structure to represent the stack
struct stack
{
int data;
struct stack* next;
};
// rename 'struct stack' to 'stack'
typedef struct stack stack;

//functions that are relevant to the stack structure
stack*newNode(char);
int isEmpty(stack*);
void push(stack**, char);
char pop(stack**);
char peek(stack*);
void infixToPrefix(char*, char*);
void prefixToPostfix(char*, char*, stack**);

//a structure to represent the tree
struct expTree
{
char* data;
struct expTree* left, *right;
};
// rename 'struct expTree' to 'expTree'
typedef struct expTree expTree;


//functions that are relevant to the tree structure
void constructTreeRight(expTree**, char*);
void constructTreeLeft(expTree **, char*);
char* flipExpression(char*);
int operator(char);
expTree* getNode(char*);
expTree* addBranch(expTree*, char*);
int rank(char);
void inorder(expTree*);
void preorder(expTree*);
void postorder(expTree*);
void printTree(expTree*,int);

static int tree = 0;

//function to add an item to the stack
void push(stack** top, char data){
    stack* stackNode =newNode(data);
    stackNode->next = *top;
    *top = stackNode;
}

//function to remove an item from stack
char pop(stack** top){
    if(isEmpty(*top)){
        return 0;
    }
    stack* temp = *top;
    *top = (*top)->next;
    char popped = temp->data;
    free(temp);

    return popped;
}

//function to return the top from stack
char peek(stack* top){
    if(isEmpty(top)){
        return 0;
    }
    return top->data;
}

//function to check if stack is empty
int isEmpty(stack* top){
    return !top;
}

//function to create a new node from stack
stack* newNode(char value){
    stack* newNode = (stack*)malloc(sizeof(stack));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

//function to convert from infix to prefix
void infixToPrefix(char* infix, char* prefix){
    char arr[100];
    int i = 0;
    int j = 0;
    int count = 0;
    stack* temp = NULL;
    char* postfix = (char*)malloc(sizeof(char)*strlen(infix));

    //reverse the expression to help convert array to postfix
    for(i = strlen(infix)-1, j = 0; i+1 != 0; i--, j++){
        arr[j] = infix[i];
    }
    arr[j] = '\0';
    strcpy(infix, arr);

    while(infix[count] != '\0'){
        if(infix[count] == '('){ 
            infix[count] = ')';
        }
        else if(infix[count] == ')'){
            infix[count] = '(';
        }
        count++;
    }
    prefixToPostfix(infix, postfix, &temp);
    strcpy(prefix, postfix);
    printf("\n");
}

//function to convert from prefix to postfix
void prefixToPostfix(char* infix, char*postfix, stack** root){
    int index = 0;
    char ch;
    
    strcat(infix, ")");
    push(root, '(');

    //pop and pop according to if infix[i] is equal to either brackets, operators, or operands
    for(int i = 0; i < strlen(infix); i++){
        if(infix[i] == '('){
            push(root, infix[i]);
        }
        else if(infix[i] == ')'){
            ch = pop(root);
            while(ch != '('){
                postfix[index] = ch;
                index++;
                ch = pop(root);
            }
        }
        else if(operator(infix[i]) && !isalnum(infix[i])){
            ch = pop(root);
            while(operator(infix[i]) && rank(ch) >= rank(infix[i])){
                postfix[index] = ch;
                index++;
                ch = pop(root);
            }
            push(root, ch);
            push(root, infix[i]);
        }
        else if((!operator(infix[i]) && isalnum(infix[i])) || infix[i] == '.'){
            postfix[index] = infix[i];
            index++;
        }
        else{
            printf("error\n");
            exit(0);
        }
    }
}

//function to construct the left side of the tree
void constructTreeLeft(expTree **root, char* value){
    while(*root == NULL){
        *root = getNode(value);
        return;
    }
    
    //checks to see if the data is equal to an operator, then recursively call the function
    if(strcmp((*root)->data, "*") == 0 || strcmp((*root)->data, "/") == 0 || strcmp((*root)->data, "+") == 0 || strcmp((*root)->data, "-") == 0){
        if((*root)->left != NULL){
            if(strstr((*root)->left->data, ".") || strstr((*root)->left->data, "x")){
                constructTreeLeft(&(*root)->right, value);
            }
            else {
                constructTreeLeft(&(*root)->left, value);
            }
        }
        else{
            constructTreeLeft(&(*root)->left, value);
        }
    }
    else{
        tree = 1;
        return;
    }
}

//function to construct the right side of the tree
void constructTreeRight(expTree** root, char* value){

    while(*root == NULL){
        *root = getNode(value);
        return;
    }
    
    //checks to see if the data is equal to an operator, then recursively call the function
    if(strcmp((*root)->data, "*") == 0 || strcmp((*root)->data, "/") == 0 || strcmp((*root)->data, "+") == 0 || strcmp((*root)->data, "-") == 0){
        if((*root)->right != NULL){
            if(strstr((*root)->left->data, ".")){
                constructTreeLeft(&(*root)->left, value);
            }
            else {
                constructTreeLeft(&(*root)->right, value);
            }
        } 
        else{
            constructTreeLeft(&(*root)->right, value);
        }
    }
    else{
        return;
    }
}

//function to flip the expression from prefix
char* flipExpression(char* prefix){
    char temp[1000];
    int i;
    int j;

    for(i = strlen(prefix)-1, j = 0; i+1 != 0; --i, ++j){
        temp[j] = prefix[i];
    }
    temp[j] = '\0';
    strcpy(prefix, temp);
    return prefix;
}

//function to return 1 if it is an operator
int operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/'){
        return 1;
    }
    return 0;
}

//function to check the priority of the operators
int rank(char ch)
{
	switch(ch)
	{
		case '^':
			return 3;
		case '/':
		case '*':
			return 2;
		case '-':
		case '+':
			return 1;
		default:
			return 0;
	}
}

//function to get a node from the tree
expTree* getNode(char* data){
    expTree* temp = (expTree*) malloc(sizeof(expTree));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

//function to add a branch to the tree
expTree* addBranch(expTree* root, char* data){
    if(root == NULL){
        root = getNode(data);
        return root;
    }

    if(tree == 0){
        constructTreeLeft(&root, data);
        if(tree == 1){
            constructTreeRight(&root, data);
        }
    }
    else{
        constructTreeRight(&root, data);
    }
    return root;
}

//function to print the preorder traversal
void preorder(expTree *root) {
  if(root != NULL) {
    printf("%s ", root->data);
    preorder(root->left);
    preorder(root->right);
  }
}

//function to print the inorder traversal
void inorder(expTree *root) {
  if(root != NULL) {
    inorder(root->left);
    printf("%s ", root->data);
    inorder(root->right);
  }
}

//function to print the postorder traversal
void postorder(expTree *root) {
  if(root != NULL) {
    postorder(root->left);
    postorder(root->right);
    printf("%s ", root->data);
  }
}

int rec[1000006];
//function to the print the binary tree expression in the tree format
void printTree(struct expTree *root,int depth)
{
    int i;
    if(root==NULL){
        return;
    }
    printf("\t");
    //printing tree using special indentation technique (found from external internet resources)
    for(i=0;i<depth;i++)
        if(i==depth-1){
            printf("%s\u2014\u2014\u2014",rec[depth-1]?"\u0371":"\u221F");
        }
        else{
            printf("%s   ",rec[i]?"\u23B8":"  ");
        }
    if(strstr(root->data,"x") != 0){
        printf("%s [0.00]\n",root->data);
        rec[depth]=1;
        printTree(root->left,depth+1);
        rec[depth]=0;
        printTree(root->right,depth+1);
    }
    else{
        printf("%s\n",root->data);
        rec[depth]=1;
        printTree(root->left,depth+1);
        rec[depth]=0;
        printTree(root->right,depth+1);
    }
}

int main(int argc, char *argv[]){
    int j = 0;
    int menuOption = 0;
    char* userExpression = argv[1];
    char* prefix = (char*)malloc(sizeof(char) * strlen(userExpression));
    char* temp = (char*)malloc(sizeof(char) * strlen(userExpression));
    expTree *root = NULL;

    if( argc == 2 ) {
      printf("The argument/inorder is %s\n", argv[1]);
    }

    //function call; convert from infix to prefix and flip expression
    infixToPrefix(userExpression, prefix);
    flipExpression(prefix);

    //iterate through the argument and check if the character is an operator, 'x', or '.'
    for(int i = 0; i < strlen(prefix)-1; i++){        
        if(operator(prefix[i])){
            strncpy(&temp[j], prefix+i, 1);
            temp[j+1] = '\0';
            root = addBranch(root, &temp[j]);
            j+=2;
        }
        else{
            if(prefix[i] == 'x'){
                strncpy(&temp[j], prefix+i, 2);
                temp[j+3] = '\0';
                root = addBranch(root, &temp[j]);
                j+=4;
            }
            else if(prefix[i+1] == '.'){
                strncpy(&temp[j], prefix+i, 4);
                temp[j+5] = '\0';
                root = addBranch(root, &temp[j]);
                j+=6;
            }
        }
    }

    //print menu options
	do{
        printf("\nMenu options: \n\n");
        printf("1. Display\n");
        printf("2. Preorder\n");
        printf("3. Inorder\n");
        printf("4. Postorder\n");
        printf("5. Exit Program\n\n");

        //ask user to choose menu options
        printf("Choose a menu option: ");
        scanf("%d", &menuOption);
        //switch statement that calls a function corresponding to user input
        switch(menuOption){
            case 1:
				printTree(root, 0);
                break;
			case 2:
				printf("PreOrder: ");
				preorder(root);
				printf("\n");
				break;
			case 3:
				printf("\nInOrder: ");
				inorder(root);
				printf("\n");
				break;
			case 4:
				printf("\nPostOrder: ");
				postorder(root);
				printf("\n");
				break;
            case 5:
				break;
			default: printf("Invalid menu option");
		}
	}while(menuOption != 5);

    return 0;
}
