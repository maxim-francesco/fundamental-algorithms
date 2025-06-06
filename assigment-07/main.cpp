//          Assigment 7
//
//  Documentatie : GeeksForGeeks
//                 Laborator SDA
//                 ChatGBT
//
//  Concluzii : Am observat ca complexitatea este in intervalul (log n , n) -> Select / Delete
//                                           *mai mult spre n in interval*

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Profiler.h"

#define stepSize 100
#define nrTests 5
#define maxSize 10000

Profiler p("Assigment7");

//functia asta e luata copy paste
int generateRandomInt(int min, int max) {
    // Ensure that the random number generator is seeded only once
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    // Generate a random number in the range [min, max]
    return min + rand() % (max - min + 1);
}

typedef struct nodeType {
    int key;
    int size;
    struct nodeType *left;
    struct nodeType *right;
}node;

node* createNewNode(int key) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = key;
    newNode->size = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node* insertNewNode(node* root, int key){
    if(root == NULL){
        return createNewNode(key);
    }else{
        root->size++;
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

node* osSelect(node* root, int i, int fixedSize){
    int r; p.countOperation("osSelect",fixedSize);
    if(root->left != NULL){
        r = root->left->size + 1; p.countOperation("osSelect",fixedSize);
    }else{
        r = 1; p.countOperation("osSelect",fixedSize);
    } p.countOperation("osSelect",fixedSize);
    if(r == i){
        return root;
    }else{ p.countOperation("osSelect",fixedSize);
        if(i < r){
            return osSelect(root->left, i, fixedSize);
        }else{
            return osSelect(root->right, i - r, fixedSize);
        }
    }

}

node* osDelete(node* root, int key, int fixedSize) {
    p.countOperation("osDelete",fixedSize);
    if (root == NULL) {
        return NULL;
    } p.countOperation("osDelete",fixedSize);
    if (key < root->key) {
        root->size--; p.countOperation("osDelete",fixedSize);
        root->left = osDelete(root->left, key, fixedSize); p.countOperation("osDelete",fixedSize);
        return root;
    } else { p.countOperation("osDelete",fixedSize);
        if (key > root->key) {
            root->size--; p.countOperation("osDelete",fixedSize);
            root->right = osDelete(root->right, key, fixedSize); p.countOperation("osDelete",fixedSize);
            return root;
        }
    } p.countOperation("osDelete",fixedSize);
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    } else { p.countOperation("osDelete",fixedSize);
        if (root->left == NULL) {
            node *buffer = root; p.countOperation("osDelete",fixedSize, 2);
            root = root->right;
            free(buffer);
            return root;
        } else { p.countOperation("osDelete",fixedSize);
            if (root->right == NULL) {
                node *buffer = root; p.countOperation("osDelete",fixedSize, 2);
                root = root->left;
                free(buffer);
                return root;
            } else {
                node *succesorParent = root; p.countOperation("osDelete",fixedSize, 3);
                node *succesor = root->right;
                while (succesor->left != NULL) {
                    succesor->size--; p.countOperation("osDelete",fixedSize, 4);
                    succesorParent = succesor;
                    succesor = succesor->left;
                } p.countOperation("osDelete",fixedSize);
                if (succesorParent != root) {
                    succesorParent->left = succesor->right; p.countOperation("osDelete",fixedSize, 4);
//                    root->key = succesor->key;
                    succesor->size = root->size - 1;
                    succesor->left = root->left;
                    succesor->right = root->right;
                    free(root);
                    return succesor;
                } else {
                    succesor->left = succesorParent->left; p.countOperation("osDelete",fixedSize, 2);
                    succesor->size = root->size - 1;
                    free(root);
                    return succesor;
                }
            }
        }
    }
    //return root;
}

void printSpaces(int heightOfNode) {
    printf("\n");
    for (int i = 0; i < heightOfNode; i++) {
        printf("    ");
    }
}

void prettyPrint(node* root, int heightOfNode){
    if(root == NULL){
        return;
    }
    prettyPrint(root->right, heightOfNode + 1);
    printSpaces(heightOfNode);
    printf("%d(%d)", root->key, root->size);
    prettyPrint(root->left, heightOfNode + 1);
}

void demo(void){
    node* root = NULL;
    buildTree(&root, 1, 10);

    prettyPrint(root, 0);
    root = osDelete(root, 5, 10);
    printf("\n-------------------------Stergem radacina\n");
    prettyPrint(root,0);
    node* q = osSelect(root,5,10);
    printf("\nSize-ul radacinii:%d",q->size);
    printf("\nSize-ul lui 7:%d\n-----------------Stergem Din Nou Radacina\n", osSelect(root,6,20)->size);
    root = osDelete(root,6,10);
    prettyPrint(root,0);
//    printf("%d",root->size);
//
//    root = osDelete(root, 5, 10);
//    printf("\n%d",root->left->size);
//    //prettyPrint(root, 0);
//    printf("\n%d",root->size);
//    printf("\n%d",root->right->size);
}

void performance(){

    for(int k = stepSize; k < maxSize; k += stepSize) {

        for (int j = 0; j < nrTests; j++) {

            node *root = NULL;
            buildTree(&root, 1, k);
            int randomArray[k];
            FillRandomArray(randomArray, k, 1, k, true);

            for (int i = 0; i < k; i++) {
                int r = generateRandomInt(1, root->size);
                node *q = osSelect(root, r, k);
                //root = osDelete(root, randomArray[i], k);
                root = osDelete(root,q->key,k);
            }

        }

    }

    p.divideValues("osDelete", nrTests);
    p.divideValues("osSelect", nrTests);
    p.createGroup("OS", "osDelete", "osSelect");

    p.showReport();

}

int main(void){
    //demo();
    performance();
    return(0);
}