#include <stdlib.h>
#include <string.h>
#include "bfs.h"
#include <time.h>
using namespace std;

int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4

    int numberOfElements = 0;
    Point qq = p;

    qq.col--;
    if(grid->mat[qq.row][qq.col] != 1){
        neighb[numberOfElements] = qq;
        numberOfElements++;
    }

    qq = p;
    qq.col++;
    if(grid->mat[qq.row][qq.col] != 1){
        neighb[numberOfElements] = qq;
        numberOfElements++;
    }

    qq = p;
    qq.row++;
    if(grid->mat[qq.row][qq.col] != 1){
        neighb[numberOfElements] = qq;
        numberOfElements++;
    }

    qq = p;
    qq.row--;
    if(grid->mat[qq.row][qq.col]!= 1){
        neighb[numberOfElements] = qq;
        numberOfElements++;
    }

    return numberOfElements;

//-------------CAL
//
//    int numberOfElements = 0;
//    Point qq = p;
//
//    qq.row++;
//    qq.col += 2;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row++;
//    qq.col -= 2;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row--;
//    qq.col -= 2;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row--;
//    qq.col += 2;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row--;
//    qq.col += 2;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row -= 2;
//    qq.col++;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row -= 2;
//    qq.col--;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row += 2;
//    qq.col++;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    qq = p;
//    qq.row += 2;
//    qq.col--;
//    if(qq.row >= 0 && qq.row < grid->rows && qq.col >= 0 && qq.col < grid->cols){
//        neighb[numberOfElements++] = qq;
//    }
//
//    return numberOfElements;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[8];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void bfs(Graph *graph, Node *s, Operation *op) {

    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();

    for (int i = 0; i < graph->nrNodes; i++) {

        if (op != NULL) op->count(3);
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = INT_MAX;
        graph->v[i]->parent = NULL;

    }

    if (op != NULL) op->count(3);
    s->color = COLOR_GRAY;
    s->dist = 0;
    s->parent = NULL;

    Node *queue[1000];
    int start = 0;
    int stop = 0;

    queue[stop++] = s;
    if (op != NULL) op->count();

    while (start != stop) {

        if (op != NULL) op->count();
        s = queue[start++];

        for (int i = 0; i < s->adjSize; i++) {

            if (op != NULL) op->count();
            if (s->adj[i]->color == COLOR_WHITE) {

                if (op != NULL) op->count(4);

                s->adj[i]->color = COLOR_GRAY;
                s->adj[i]->dist = s->dist + 1;
                s->adj[i]->parent = s;

                queue[stop++] = s->adj[i];

            }

        }

        if (op != NULL) op->count();
        s->color = COLOR_BLACK;

    }

}



void printSpaces(int heightOfNode) {

    printf("\n");

    for (int i = 0; i < heightOfNode; i++) {

        printf("      ");

    }

}

void prettyPrintForR1(int R1[], int sizeOfR1, int currentNode, int heightOfNode, Point repr[]) {
    if(heightOfNode == 0){
        printf("Afisare R1:");
    }
    for (int i = 0; i < sizeOfR1; i++) {
        if (R1[i] == currentNode) {
            printSpaces(heightOfNode);
//            printf("%d", i);
            printf("(%d,%d)",repr[i].row, repr[i].col);
            prettyPrintForR1(R1, sizeOfR1, i, heightOfNode + 1, repr);
        }
    }
}

void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if(!err){
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs

        prettyPrintForR1(p, n, -1, 0, repr);

        printf("\n");

    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{

    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000


    for(int i = 0; i < graph->nrNodes; i++){
        graph->v[i]->dist = INT_MAX;
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->parent = NULL;
    }

    start->dist = 0;
    start->color = COLOR_GRAY;
    start->parent = NULL;

    Node* queue[1000];
    int start1 = 0;
    int final1 = 0;

    queue[final1++] = start;

    while(start1 != final1){
        start = queue[start1++];
        for(int k = 0; k < start->adjSize;k++){
            Node* buffer = start->adj[k];
            if(buffer->color == COLOR_WHITE){
                buffer->dist = start->dist + 1;
                buffer->color = COLOR_GRAY;
                buffer->parent = start;
                queue[final1++] = buffer;
            }
        }

        start->color = COLOR_BLACK;

        if(start == end){
            if(path != NULL){
                Node* buffer3 = start;
                for(int k = start->dist; k >= 0; k--){
                    path[k] = buffer3;
                    buffer3 = buffer3->parent;
                }
            }
            return start->dist;
        }
    }

    return -1;
}

bool findExistingNode(Graph graph, int x, int y){
    for(int i = 0; i < graph.v[x]->adjSize; i++){
        if(graph.v[x]->adj[i] == graph.v[y]){
            return true;
        }
    }
    for(int i = 0; i < graph.v[y]->adjSize; i++){
        if(graph.v[y]->adj[i] == graph.v[x]){
            return true;
        }
    }
    return false;
}

void performance()
{
    srand(time(NULL));
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for(n=1000; n<=4500; n+=100){
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected

        int k = 0;
        while(k != graph.nrNodes - 1){
            graph.v[k]->adjSize = 1;
            graph.v[k]->adj = (Node **) malloc(sizeof(Node *) * graph.v[k]->adjSize);
            graph.v[k]->adj[0] = graph.v[k + 1];
            k++;
        }

        k = 0;
        while(k!=n-graph.nrNodes){
            int x1 = rand()%graph.nrNodes;
            int x2 = rand()%graph.nrNodes;
            while(findExistingNode(graph, x1, x2)){
                x1 = rand()%graph.nrNodes;
                x2 = rand()%graph.nrNodes;
            }
            graph.v[x1]->adjSize++;
            graph.v[x1]->adj = (Node**) realloc(graph.v[x1]->adj,graph.v[x1]->adjSize * sizeof(Node*));
            graph.v[x1]->adj[graph.v[x1]->adjSize - 1] = graph.v[x2];
            k++;
        }
        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    // vary the number of vertices
    for(n=100; n<=200; n+=10){
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected

        int k = 0;
        while(k != graph.nrNodes - 1){
            graph.v[k]->adjSize = 1;
            graph.v[k]->adj = (Node **) malloc(sizeof(Node *) * graph.v[k]->adjSize);
            graph.v[k]->adj[0] = graph.v[k + 1];
            k++;
        }

        k = 0;
        while(k!=4500-graph.nrNodes){
            int x1 = rand()%graph.nrNodes;
            int x2 = rand()%graph.nrNodes;
            while(findExistingNode(graph, x1, x2)){
                x1 = rand()%graph.nrNodes;
                x2 = rand()%graph.nrNodes;
            }
            graph.v[x1]->adjSize++;
            graph.v[x1]->adj = (Node**) realloc(graph.v[x1]->adj,graph.v[x1]->adjSize * sizeof(Node*));
            graph.v[x1]->adj[graph.v[x1]->adjSize - 1] = graph.v[x2];
            k++;
        }

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    p.showReport();
}
