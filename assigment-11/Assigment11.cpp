//              Assigment11
//
//  Student : Maxim Francesco
//  Grupa : 30224 (2023 / 2024)
//
//  Documentatie :
//      -> DFS : https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
//      -> TopologicalSort : https://www.geeksforgeeks.org/topological-sorting/
//      -> TarjanAlgorithm : https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
//


#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "Profiler.h"
using namespace std;

Profiler p("Assigment11");

typedef struct nodeType{
    int key;
    bool visited;
    nodeType* neighbours;
}node;

typedef struct {
    int numberOfNodes;
    bool* visited; //dfs graph
    node** nodes;
}graph;

graph* init(int n){
    graph* graph1 = (graph*)malloc(sizeof(graph));
    graph1->numberOfNodes = n;
    graph1->nodes = (node**)malloc(sizeof(node*) * graph1->numberOfNodes);
    for(int i = 0; i < graph1->numberOfNodes; i++){
        graph1->nodes[i] = (node*)malloc(sizeof(node));
        graph1->nodes[i]->key = i;
        graph1->nodes[i]->visited = false;
        graph1->nodes[i]->neighbours = NULL;
    }
    return graph1;
}

void printStruct(graph* graph1){
    for(int i = 0; i < graph1->numberOfNodes; i++){
        printf("%d : ", graph1->nodes[i]->key);
        node* buffer = graph1->nodes[i]->neighbours;
        while(buffer != NULL){
            printf("%d",buffer->key);
            if(buffer->neighbours != NULL){
                printf("->");
            }
            buffer = buffer->neighbours;
        }
        printf("\n");
    }
}


void createEdge(graph* graph1, int key1, int key2){
    node* newEdge = (node*)malloc(sizeof(node));
    newEdge->key = key2;
    newEdge->visited = false;
    newEdge->neighbours = graph1->nodes[key1]->neighbours;
    graph1->nodes[key1]->neighbours = newEdge;
}

void dfs(graph* graph1, int start, int fixedSize, int result[]){
    printf("%d ", graph1->nodes[start]->key);
    p.countOperation("PERFORMANCE", fixedSize, 3);
    graph1->nodes[start]->visited = true;
    node* buffer = graph1->nodes[start]->neighbours;
    while (buffer != NULL){
        p.countOperation("PERFORMANCE", fixedSize);
        if(graph1->nodes[buffer->key]->visited != true){
            result[buffer->key] = graph1->nodes[start]->key;
            dfs(graph1, buffer->key, fixedSize, result);
        }
        p.countOperation("PERFORMANCE", fixedSize,2);
        buffer = buffer->neighbours;
    }
}

void topologicalSortUtil(graph* graph1, int index, stack<node*> &stack1){
    graph1->nodes[index]->visited = true;
    node* buffer = graph1->nodes[index]->neighbours;
    while(buffer != NULL){
        if(graph1->nodes[buffer->key]->visited != true){
            topologicalSortUtil(graph1, buffer->key, stack1);
        }
        buffer = buffer->neighbours;
    }
    stack1.push(graph1->nodes[index]);
}

void topologicalSort(graph* graph1){
    stack<node*> stack1;
    for(int i = 0; i < graph1->numberOfNodes; i++){
        if(graph1->nodes[i]->visited != true){
            topologicalSortUtil(graph1, i, stack1);
        }
    }
    while (stack1.empty() != true){
        printf("%d ", stack1.top()->key);
        stack1.pop();
    }
}

void tarjanUtil(graph* graph1, int u, int disc[], int low[], stack<int>& st, int *time){
    disc[u] = low[u] = ++(*time);
    st.push(u);

    graph1->nodes[u]->visited = true;

    node* buffer =  graph1->nodes[u]->neighbours;
    while(buffer != NULL){

        int v = buffer->key;

        if (disc[buffer->key] == -1) {
            tarjanUtil(graph1, buffer->key, disc, low, st, time);
            low[u] = min(low[u], low[buffer->key]);
        }
        else {
            if (graph1->nodes[v]->visited == true) {
                low[u] = min(low[u], disc[buffer->key]);
            }
        }
        buffer = buffer->neighbours;
    }

    int w = 0;
    if (low[u] == disc[u]) {
        while (st.top() != u) {
            w = st.top();
            printf("%d ", w);
            graph1->nodes[w]->visited = false;
            st.pop();
        }
        w = st.top();
        printf("%d\n", w);
        graph1->nodes[w]->visited = false;
        st.pop();
    }
}

void initArray(int array[], int sizeOfArray){
    for(int i = 0; i < sizeOfArray; i++){
        array[i] = -1;
    }
}

void printArray(int array[], int sizeOfArray){
    for(int i = 0; i < sizeOfArray; i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

void tarjan(graph* graph1)
{
    int disc[graph1->numberOfNodes];
    int low[graph1->numberOfNodes];
    stack<int> st;
    int time = 0;

    initArray(disc, graph1->numberOfNodes);
    initArray(low, graph1->numberOfNodes);

    for (int i = 0; i < graph1->numberOfNodes; i++) {
        if (disc[i] == -1) {
            tarjanUtil(graph1, i, disc, low, st, &time);
        }
    }

}

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

void demo(){

    // GRAF LUAT DE PE GEEKFORGEEKS !!!

    graph* graph1 = init(6);
    createEdge(graph1, 5,0);
    createEdge(graph1, 5,2);
    createEdge(graph1, 4,1);
    createEdge(graph1, 4,0);
    createEdge(graph1, 3,1);
    createEdge(graph1, 2,3);
    createEdge(graph1, 3,2);
    printStruct(graph1);
//    topologicalSort(graph1);
int array[6];
    initArray(array, 6);
    array[5] = -99;
    dfs(graph1, 5,0,array);
    printf("\n");
//    printArray(array, 6);
    prettyPrintForR1(array, 6, -99, 0);
//    printf("\n");
//    printStruct(graph1);
}

void demo2(){

    // TESTE LUATE DE PE GEEKFORGEEKS !!!

//    graph* graph1 = init(5); // 1
//    createEdge(graph1, 1, 0);
//    createEdge(graph1, 0, 2);
//    createEdge(graph1, 2, 1);
//    createEdge(graph1, 0, 3);
//    createEdge(graph1, 3, 4);

//    graph* graph1 = init(5); // 5
//    createEdge(graph1, 0, 1);
//    createEdge(graph1, 1, 2);
//    createEdge(graph1, 2, 3);
//    createEdge(graph1, 2, 4);
//    createEdge(graph1, 3, 0);
//    createEdge(graph1, 4, 2);

    graph* graph1 = init(7); //3
    createEdge(graph1, 0, 1);
    createEdge(graph1, 1, 2);
    createEdge(graph1, 2, 0);
    createEdge(graph1, 1, 3);
    createEdge(graph1, 1, 4);
    createEdge(graph1, 1, 6);
    createEdge(graph1, 3, 5);
    createEdge(graph1, 4, 5);

    tarjan(graph1);

}

bool findExistingNode(graph* graph1, int x, int y){
    node* buffer = graph1->nodes[x]->neighbours;
    while(buffer != NULL){
        if(buffer->key == y){
            return true;
        }
        buffer = buffer->neighbours;
    }
    return false;
}

void perf1() {
//    srand(time(NULL));
    for (int i = 1000; i <= 4500; i += 100) {
        graph *graph1 = init(100);
        int k = 0;
        while (k <= i) {
            int x1 = rand() % (graph1->numberOfNodes -1);
            int x2 = rand() % (graph1->numberOfNodes -1);
            while (findExistingNode(graph1, x1, x2) == true) {
                x1 = rand() % (graph1->numberOfNodes -1);
                x2 = rand() % (graph1->numberOfNodes -1);
            }
            createEdge(graph1, x1, x2);
            k++;
        }
        int array[100];
        initArray(array, 100);
        dfs(graph1, 0, i, array);
    }
    p.showReport();
//    p.showReport();
}

void perf2(){
    for(int i = 100; i <= 200; i += 10){
        graph *graph1 = init(i);
        int k = 0;
        while (k <= 4500) {
            int x1 = rand() % graph1->numberOfNodes;
            int x2 = rand() % graph1->numberOfNodes;
            while (findExistingNode(graph1, x1, x2) == true && (x1 != x2)) {
                x1 = rand() % graph1->numberOfNodes;
                x2 = rand() % graph1->numberOfNodes;
            }
            createEdge(graph1, x1, x2);
            k++;
        }
        int array[i];
        initArray(array, i);
        dfs(graph1, 1, i, array);
    }
    p.showReport();
}

int main(void){
//    demo();
    demo2();
//    perf1();
//    perf2();
    return(0);
}