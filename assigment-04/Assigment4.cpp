//                                          ASSIGMENT 4
//
//  Info:
//
//  AF(2023/2024)
//  Student: Francesco Maxim(grupa 30224)
//  Task : Merge K Sorted Lists
//         
//  Surse de documentatie : 
// 
//  YouTube: https://www.youtube.com/@abdul_bari -> Pentru Analizare A Algoritmilor
//           https://www.youtube.com/@cypryoprisa -> Pentru Analizare A Algoritmilor
//  ChatGPT: https://chat.openai.com -> Pentru Realizarea Algoritmilor
//  GeeksForGeeks: https://www.geeksforgeeks.org -> Pentru Aprofundarea Algoritmilor
// 
// Concluzii si lucruri invatate dupa Assigmentul 4:
//      Eficienta N log k
//      O metoda foarte eficienta pentru interclasarea a k liste ordonate, fata de
//      abordarea clasica.

#include "Profiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define demoArray 5
#define step_size 100
#define max_limit 1000
#define nr_tests 500

char stringuri[3][20];
int string_index = 0;

Profiler p("Assigment4");

typedef struct node_type{
    int key;
    struct node_type* next;
}node;

typedef struct{
    node* first;
    node* last;
}list;

typedef struct{
    int key;
    int index;
}forHeap;

void initList(list** myList){
    (*myList)->first = NULL;
    (*myList)->last = NULL;
}

void initLists(list* myList[], int size){
    for(int i = 0; i < size; i++){
        myList[i] = (list*)malloc(sizeof(list));
        myList[i]->first = NULL;
        myList[i]->last = NULL;
    }
}

void swap(int* a, int* b){
    int buffer = *a;
    (*a) = (*b);
    (*b) = buffer;
}

void swap1(forHeap* a, forHeap* b){
    forHeap buffer = (*a);
    (*a) = (*b);
    (*b) = buffer;
}

void printList(node* first){
    while(first != NULL){
        printf("%d->",first->key);
        first = first->next;
    }
    printf("NULL\n"); 
}

void printLists(list* myList[], int size){
    for(int i = 0; i < size; i++){
        printList(myList[i]->first);
    }
}

void printStruct(forHeap array[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i].key);
    }
    printf("\n");
}

void printArray(int array[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

node* create_new_node(int key){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void insertFirst(node** first, node** last, int key){
    node* new_node = create_new_node(key);
    if((*first) == NULL){
        (*first) = new_node;
        (*last) = new_node;
    }else{
        new_node->next = (*first);
        (*first) = new_node;
    }
}

void insertLast(node** first, node** last, int key){
    if((*first) == NULL){
        insertFirst(first, last, key);
    }else{
        node* new_node = create_new_node(key);
        (*last)->next = new_node;
        (*last) = new_node;
    }
}

void deleteFirst(node** first,node** last){
    if((*first) == NULL){
        perror("u can't delete more budy :(\n");
        exit(-1);
    }else{
            node* buffer = (*first);
            (*first) = (*first)->next;
            free(buffer);
            if((*first) == NULL){
                (*last) = NULL;
            }
        }
}

list* insertFromArray(int array[], int sizeOfArray){
    list* new_list = (list*)malloc(sizeof(list));
    initList(&new_list);
    for(int i = sizeOfArray - 1; i >= 0; i--){
        insertFirst(&new_list->first, &new_list->last, array[i]);
    }
    return new_list;
}

void heapify(forHeap array[], int size, int index, int fixed_size){
    int current_index = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    if(left < size){
        p.countOperation(stringuri[string_index], fixed_size);
        if(array[left].key < array[current_index].key){
            current_index = left;
        }
    }
    if(right < size){
        p.countOperation(stringuri[string_index], fixed_size);
        if(array[right].key < array[current_index].key){
            current_index = right;
        }
    }
    if(current_index != index){
        swap1(&array[current_index],&array[index]); p.countOperation(stringuri[string_index], fixed_size, 3);
        heapify(array, size, current_index, fixed_size);
    }
}

void build_heap(forHeap array[], int size, int fixed_size){
    for(int i = (size - 1); i >= 0; i--){
        heapify(array, size, i, fixed_size);
    }
}

forHeap extractMin(forHeap array[], int *size, int fixed_size){
    if((*size) <= 0){
        perror("u can't extract more buddy :(");
        exit(-1);
    }
    if((*size) == 1){
        (*size)--;
        return array[0];
    }
    forHeap root = array[0];
    array[0] = array[(*size) - 1]; p.countOperation(stringuri[string_index], fixed_size);
    (*size)--;
    heapify(array, *size, 0, fixed_size);

    return root;
}

void insertIntoHeap(forHeap array[], int *size, int fixed_size, forHeap newElement){
    (*size)++;
    int i = (*size) - 1;
    array[i] = newElement; 
    p.countOperation(stringuri[string_index], fixed_size);
    while(i > 0 && array[i].key < array[(i - 1) / 2].key){
        swap1(&array[i], &array[(i - 1) / 2]);
        i = (i - 1) / 2;
        p.countOperation(stringuri[string_index], fixed_size);
    }
}

list* mergeKSortedLists(list* myList[], int size, int N, int fixed_size){

    int q = size;
    list* final_list = (list*)malloc(sizeof(list));
    initList(&final_list);

    forHeap array_buffer[size];
    for(int i = 0; i < size; i++){
        array_buffer[i].key = myList[i]->first->key; 
        array_buffer[i].index = i;
        deleteFirst(&myList[i]->first,&myList[i]->last);
    }

    build_heap(array_buffer, size, fixed_size);
    //int i = 1;
    while(N > 0){
        forHeap buffer = extractMin(array_buffer, &size, fixed_size);
        insertLast(&final_list->first, &final_list->last, buffer.key);
        if(myList[buffer.index]->first != NULL){
            forHeap newElement;
            newElement.key = myList[buffer.index]->first->key; 
            newElement.index =  buffer.index;
            deleteFirst(&myList[buffer.index]->first,&myList[buffer.index]->last);
            insertIntoHeap(array_buffer, &size, fixed_size, newElement);
        }
        N--;
    }
    return final_list;
}

void demo(){

    int size = 5;
    list* myList[size]; 
    initLists(myList, size);

    int N = 0;
    
    for(int i = 0; i < size; i++){
        int minRange = 1;
        int maxRange = 5;
        int randomInRange = (rand() % (maxRange - minRange + 1)) + minRange;
        int array[randomInRange];
        FillRandomArray(array, randomInRange, 0, 100, false, 1);
        myList[i] = insertFromArray(array, randomInRange);
        N += randomInRange;
    }

    printLists(myList, size);

    list* final_list = mergeKSortedLists(myList, size, N, N);

    printList(final_list->first);

}

void performanceN(){

    strcpy(stringuri[0],"K_este_5");
    strcpy(stringuri[1],"K_este_10");
    strcpy(stringuri[2],"K_este_100");

    int index_k = 0;
    while(index_k < 3){
        int k;
        if(index_k == 0){
            k = 5;
        }
        if(index_k == 1){
            k = 10;
        }
        if(index_k == 2){
            k = 100;
        }
    for(int N = 100; N <= 10000; N += 100){
        list* myList[k];
        initLists(myList, k);
        int buf = 0;
        for(int i = 0; i < k; i++){
            int randomInRange;
            if(i != (k - 1)){
                int minRange = 1;
                int maxRange = (N / k);
                randomInRange = (rand() % (maxRange - minRange + 1)) + minRange;
                buf += randomInRange;
            }else{
                randomInRange = (N - buf);
            }
            int array[randomInRange];
            FillRandomArray(array, randomInRange, 0, 100000, true, 1);
            myList[i] = insertFromArray(array, randomInRange);
        }
        list* final_list = mergeKSortedLists(myList, k, N, N);
   }
   index_k++;
   string_index++;
}

    p.createGroup("Tabel1",stringuri[0],stringuri[1],stringuri[2]);
    p.showReport();

}

void performanceK(){
    strcpy(stringuri[0],"Tabel2");
    string_index = 0;
    int N = 10000;
    for(int k = 10; k <= 500; k+=10){
        for(int q = 0; q < nr_tests; q++){
                list* myList[k];
                int buf = 0;
                for(int i = 0; i < k; i++){
                    int randomInRange;
                        if(i != (k - 1)){
                            int minRange = 1;
                            int maxRange = (N / k);
                            randomInRange = (rand() % (maxRange - minRange + 1)) + minRange;
                            buf += randomInRange;
                        }else{
                            randomInRange = (N - buf);
                        }
                        int array[randomInRange];
                        FillRandomArray(array, randomInRange, 0, 100000, true, 1);
                        myList[i] = insertFromArray(array, randomInRange);
                }
                list* final_list = mergeKSortedLists(myList, k, N, k);
                }
                p.divideValues(stringuri[string_index], nr_tests);
    }
    p.showReport();
}

int main(void){
    srand(time(NULL));
    demo();
    //performanceN();
    //performanceK();
    return(0);
}