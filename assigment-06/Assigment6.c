#include <stdio.h>
#include <stdlib.h>

void printSpaces(int heightOfNode) {
    printf("\n");
    for (int i = 0; i < heightOfNode; i++) {
        printf("   ");
    }
}

void prettyPrintForR1(int R1[], int sizeOfR1, int currentNode, int heightOfNode) {
    if(heightOfNode == 0){
        printf("Afisare R1:");
    }
    for (int i = 0; i < sizeOfR1; i++) {
        if (R1[i] == currentNode) {
            printSpaces(heightOfNode);
            printf("%d", i);
            prettyPrintForR1(R1, sizeOfR1, i, heightOfNode + 1);
        }
    }
}

typedef struct nodeType{
    int key;
    int numberOfChildrens;
    struct nodeType** childrens;
}nodeType2;

nodeType2* convertFromR1ToR2(const int R1[], int sizeOfR1) {
    nodeType2 *buffer = (nodeType2 *) malloc(sizeof(nodeType2) * sizeOfR1);
    for (int i = 0; i < sizeOfR1; i++) {
        buffer[i].key = i;
        buffer[i].numberOfChildrens = 0;
        buffer[i].childrens = NULL;
    }
    nodeType2 *R2 = NULL;
    for (int i = 0; i < sizeOfR1; i++) {
        if (R1[i] != -1) {
            nodeType2 *buffer2 = &buffer[R1[i]];
            buffer2->numberOfChildrens++;
            buffer2->childrens = realloc(buffer2->childrens, sizeof(nodeType2) * buffer2->numberOfChildrens);
            buffer2->childrens[buffer2->numberOfChildrens - 1] = &buffer[i];
        } else {
            R2 = &buffer[i];
        }
    }
    return R2;
}

void prettyPrintForR2(nodeType2* R2, int heightOfNode) {
    if(heightOfNode == 0){
        printf("\nAfisare R2:");
    }
    printSpaces(heightOfNode);
    printf("%d", R2->key);
    for (int i = 0; i < R2->numberOfChildrens; i++) {
        prettyPrintForR2(R2->childrens[i], heightOfNode + 1);
    }
}

typedef struct nodeTypeR3{
    int key;
    struct nodeTypeR3* left;
    struct nodeTypeR3* right;
}nodeType3;

nodeType3* convertR2toR3(nodeType2* R2){
    if(!R2){
        return NULL;
    }
    nodeType3* R3 = (nodeType3*)malloc(sizeof(nodeType3));
    R3->key = R2->key;
    R3->left = R3->right = NULL;
    if(R2->numberOfChildrens != 0){
        R3->left = convertR2toR3(R2->childrens[0]);
        nodeType3* buffer = R3->left;
        for(int i = 1; i < R2->numberOfChildrens; i++){
            nodeType3* buffer2 = convertR2toR3(R2->childrens[i]);
            buffer->right = buffer2;
            buffer = buffer2;
        }
    }
    return R3;
}

void prettyPrintForR3(nodeType3* R3, int heightOfNode){
    if(heightOfNode == 0){
        printf("\nAfisare R3:");
    }
    if(!R3){
        return;
    }
    printSpaces(heightOfNode);
    printf("%d",R3->key);
    if(R3->left){
        prettyPrintForR3(R3->left, heightOfNode + 1);
    }
    if(R3->right){
        prettyPrintForR3(R3->right, heightOfNode);
    }
}


void demo() {
    int R1[] = { 10, 0, 10, 10, 7, 3, 5, 3, 3, 10, -1, 0 };
    int sizeOfR1 = sizeof(R1) / sizeof(R1[0]);
    prettyPrintForR1(R1, sizeOfR1, -1, 0);
    nodeType2* p = convertFromR1ToR2(R1, sizeOfR1);
    //printf("%d",p->childrens[2]->childrens[0]->childrens[0]->key); debugging
    prettyPrintForR2(p,0);
    nodeType3* q = convertR2toR3(p);
    prettyPrintForR3(q, 0);
}

int main(void) {
    demo();
    return(0);
}