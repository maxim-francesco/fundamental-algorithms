#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <time.h>
#include "Profiler.h"
#define stepSize 100
#define maxSize 10000
using namespace std;

Profiler p("Assigment10");

typedef struct nodeType{
    int key;
    int rank;
    nodeType* parent;
}node;

typedef struct {
    int u;
    int v;
    int weight;
}edge;

void createSet(node* currentNode, int fixedSize){
    currentNode->parent = currentNode; p.countOperation("Operatii", fixedSize);
}

void makeSet(node* nodes[], int numberOfNodes, int fixedSize){
    for(int i = 0; i < numberOfNodes; i++){
        nodes[i] = (node*)malloc(sizeof(node));
        nodes[i]->key = i; p.countOperation("Operatii", fixedSize);
        nodes[i]->rank = 0; p.countOperation("Operatii", fixedSize);
        createSet(nodes[i], fixedSize);
    }
}

void printMyNodes(node* nodes[], int numberOfNodes){
    for(int i = 0; i < numberOfNodes; i++){
        printf("%d %d\n",nodes[i]->key,nodes[i]->rank);
    }
}

node* findSet(node* currentNode, int fixedSize){
    p.countOperation("Operatii", fixedSize);
    while(currentNode != currentNode->parent){
        currentNode = currentNode->parent; p.countOperation("Operatii", fixedSize,2);
    }
    return currentNode;
}

void unionSet(node* x, node* y, int fixedSize){
    node* a = findSet(x,fixedSize);
    node* b = findSet(y,fixedSize);

    p.countOperation("Operatii", fixedSize);
    if(a->rank <= b->rank){ p.countOperation("Operatii", fixedSize);
        if(a->rank == b->rank){
            b->rank++; p.countOperation("Operatii", fixedSize);
        }
        a->parent = b; p.countOperation("Operatii", fixedSize);
    }else{
        b->parent = a; p.countOperation("Operatii", fixedSize);
    }

}

int qq;

int comp(const void* a, const void* b){
    edge* a1 = (edge*)a; //p.countOperation("Operation",?)
    edge* b1 = (edge*)b;
    return a1->weight - b1->weight;
}

vector<vector<int>> kruskal(edge e[], int muchii, int noduri, int fixedSize){
    qsort(e,muchii,sizeof(edge),comp);
    node* nodes[noduri];
    makeSet(nodes, noduri, fixedSize);

    vector<vector<int>> rezultat;

    for(int i = 0; i < muchii; i++){
        node* a = findSet(nodes[e[i].u], fixedSize);
        node* b = findSet(nodes[e[i].v], fixedSize);
        if(a != b){
            vector<int> newLine = {e[i].u,e[i].v,e[i].weight};
            rezultat.push_back(newLine);
            unionSet(a,b, fixedSize);
        }
    }

    return rezultat;
}

void print(vector<vector<int>> minimumSpanningTree){
    for(auto & linie : minimumSpanningTree){
        printf("%d %d %d\n",linie[0],linie[1],linie[2]);
    }
}

void printEdges(edge e[], int m){
    for(int i = 0; i < m; i++){
        printf("%d %d %d\n",e[i].u,e[i].v,e[i].weight);
    }
}

bool existaDeja(edge e[], int m, int x, int y){

    for(int i = 0; i < m; i++){
        if((e[i].u == x && e[i].v == y) || (e[i].u == y && e[i].v == x)){
            return true;
        }
    }

    return false;
}

void generateRandom(edge e[], int numberOfNodes){

    for(int i = 0; i < numberOfNodes - 1; i++){
        e[i].u = i;
        e[i].v = i + 1;
        e[i].weight = rand();
    }

    for(int i = numberOfNodes - 1; i < numberOfNodes * 4 ; i++){
        e[i].u = rand()%(numberOfNodes-1);
        e[i].v = rand()%(numberOfNodes-1);
        while(existaDeja(e,i,e[i].u,e[i].v) || e[i].u == e[i].v){
            e[i].u = rand()%(numberOfNodes-1);
            e[i].v = rand()%(numberOfNodes-1);
        }
        e[i].weight = rand();
//        printf("%d %d\n",e[i].u,e[i].v);
    }

}

void demo(){
//    node* nodes[5];
//    makeSet(nodes, 5);
//    printMyNodes(nodes, 5);

//    unionSet(nodes[0],nodes[1]);
//    printMyNodes(nodes,5);

    edge e[] = {
            {0,1,4},
            {0,7,8},
            {1,7,11},
            {1,2,8},
            {7,6,1},
            {7,8,7},
            {6,8,6},
            {2,8,2},
            {2,3,7},
            {2,5,4},
            {6,5,2},
            {5,4,10},
            {5,3,14},
            {3,4,9}
    };
//
    vector<vector<int>> minimumSpanningTree = kruskal(e,14,9,14);
//
    print(minimumSpanningTree);

//    edge e[] = generateRandom(5);


//    printf("%d", e[1].u);

//    edge e[20];
//    generateRandom(e,5);
//    printEdges(e,20);

//    vector<edge> e = generateRandom(5);

//    int numberOfNodes = 10;
//    edge e[numberOfNodes * 4];
//    generateRandom(e,numberOfNodes);
//    generateRandomProst(e,numberOfNodes);

//    printEdges(e,numberOfNodes * 4);

}

void perf(){
    srand(time(NULL));
    for(int i = stepSize; i <= maxSize; i+=stepSize){

        edge e[i * 4];
        generateRandom(e,i);
        vector<vector<int>> minimumSpanningTree = kruskal(e,i*4,i,i);

    }

    p.showReport();

}

int main(void){
    demo();
//    perf();
    return(0);
}