#include <stdio.h>
#include <stdlib.h>

#define stackMaxSize 100
#define stepSize 100
#define maxSize 10000

typedef struct nodeType {
    int key;
    struct nodeType *left;
    struct nodeType *right;
}node;

node* createNewNode(int key) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node* insertNewNode(node* root, int key){
    if(root == NULL){
        return createNewNode(key);
    }else{
        if(key < root->key){
            root->left = insertNewNode(root->left, key);
        }else{
            root->right = insertNewNode(root->right, key);
        }
    }
    return root;
}

void buildTree(node** root, int left, int right){
    if(left > right){
        return;
    }
    int mid = (left + right) / 2;
    (*root) = insertNewNode(*root, mid);
    buildTree(root, left, mid - 1);
    buildTree(root, mid + 1, right);
}

void inorder(node* root, int fixedSize){
    if(root != NULL){
        inorder(root->left, fixedSize);
        //printf("%d ", root->key);
        inorder(root->right, fixedSize);
    }
}

void push(node stack[], int *size, node* element){
    stack[(*size)] = *element;
    (*size)++;
}

node* pop(node stack[], int *size){
    node* buffer = &stack[(*size) - 1];
    (*size)--;
    return buffer;
}

void printStack(node stack[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", stack[i].key);
    }
}

void iterativeInorder(node* root, int fixedSize) {
    node stack[stackMaxSize];
    int size = 0;
    node *cover = root;
    while (1) {
        if (cover != NULL) {
            push(stack, &size, cover);
            cover = cover->left;
        } else {
            if (size == 0)
                break;
            cover = pop(stack, &size);
            //printf("%d ", cover->key);
            cover = cover->right;
        }
    }
}

void demo(){
    node* root = NULL;
    buildTree(&root,1,30);
    node stack[stackMaxSize];
    int size = 0;
    iterativeInorder(root, 30);
    //inorder(root);
}

int main(void){
    demo();
    return(0);
}