//Concluzii
// 
// ->Quadratic Probing este foarte bun din cauza ca evitam sa avem zone cu o densitate foarte mare la un factor 
//   de umplere mic
// 


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Profiler.h"
#define SIZE_H_TABLE 10
#define M 1500
#define NR_TESTS 5

int hashFunction(int key, int i){
    return (key + 4 * i + 5 * i * i) % SIZE_H_TABLE;
    //return (key + i)% SIZE_H_TABLE;
}

void initHashTable(int hashTable[]){
    for(int i = 0; i < SIZE_H_TABLE; i++){
        hashTable[i] = -2;
    }
}

void printHashTable(int hashTable[]){
    for(int i = 0; i < SIZE_H_TABLE; i++){
        printf("%d ",hashTable[i]);
    }
    printf("\n");
}

bool isHashTableFull(int hashTable[]){
    for(int i = 0; i < SIZE_H_TABLE; i++){
        if(hashTable[i] == -2){
            return false;
        }
    }
    return true;
}

void insertIntoHashTable(int hashTable[], int key){
    if(isHashTableFull(hashTable) == true){
        perror("is full already");
        exit(-1);
    }
    int i = 0;
    while(((hashTable[hashFunction(key, i)] != -2) && (hashTable[hashFunction(key, i)] != -1))){
        i++;
    }
    hashTable[hashFunction(key, i)] = key;
    if(isHashTableFull(hashTable) == true){
        perror("be carefull, is full now");
    }
}

// int searchInFullHashTable(int hashTable[], int key){
//     for(int i = 0; i < SIZE_H_TABLE; i++){
//         if(hashTable[i] == key){
//             return i;
//         }
//     }
//     return -1;
// }
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DACA E PLINA ?!

int searchInHashTable(int hashTable[], int key, int *buffer){
    int i = 0;
    while(hashTable[hashFunction(key, i)] != -2){
        if(hashTable[hashFunction(key, i)] == key){
            (*buffer) = i + 1;
            return hashFunction(key, i);
        }else{
            i++;
        }
    }
    (*buffer) = i + 1;
    return -1;
}

void deleteInHashTable(int hashTable[], int key){
    int buf; //inutil aici
    int keyToDelete = searchInHashTable(hashTable, key, &buf);
    if(keyToDelete == -1){
        perror("key not found");
    }else{
        hashTable[keyToDelete] = -1;
    }
}

void demo(){
    int hashTable[SIZE_H_TABLE];
    initHashTable(hashTable);
    insertIntoHashTable(hashTable,22);
    insertIntoHashTable(hashTable,21);
    insertIntoHashTable(hashTable,23);
    insertIntoHashTable(hashTable,24);
    printHashTable(hashTable);
    printf("\n");
    //printf("%d",searchInHashTable(hashTable, 22));
    deleteInHashTable(hashTable,21);
    printHashTable(hashTable);
    insertIntoHashTable(hashTable,31);
    insertIntoHashTable(hashTable,41);
    printf("\n");
    printHashTable(hashTable);
    printf("\n");
    int q = 0;
    searchInHashTable(hashTable,61,&q);
    printf("%d ", q);
    //deleteInHashTable(hashTable,100);
}

void insertFromArrayToHashTable(int hashTable[], int array[], int sizeOfArray){
    while(sizeOfArray != 0){
        insertIntoHashTable(hashTable, array[sizeOfArray]);
        sizeOfArray--;
    }
}

void printArray(int array[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void performance(double x){

    double sumaCautariFinal = 0;
    int maximCautariFinal = 0;
    double sumaCautariFinal2 = 0;
    int maximCautariFinal2 = 0;

    int hashTable[SIZE_H_TABLE];
    int fillFactor = (int)(x * SIZE_H_TABLE);
    int randomArray[fillFactor + M];
    int randomIndices[M];

    for(int k = 0; k < NR_TESTS; k++){

        //int hashTable[SIZE_H_TABLE];
        initHashTable(hashTable);
        // int fillFactor = (int)(x * SIZE_H_TABLE);
        // int randomArray[fillFactor + M];
        FillRandomArray(randomArray, fillFactor + M, 0, 100000000, true);
        insertFromArrayToHashTable(hashTable, randomArray, fillFactor);
        //printHashTable(hashTable);
        // int randomIndices[M];
        FillRandomArray(randomIndices, M, 0, fillFactor - 1, true);
        // printHashTable(hashTable);
        // printArray(randomIndices,M);
        int sumaCautari = 0;
        int maximCautari = 0;
        for(int i = 0; i < M; i++){
            int cautari = 0;
            searchInHashTable(hashTable, randomArray[randomIndices[i]], &cautari);
            sumaCautari += cautari;
            if(cautari > maximCautari){
                maximCautari = cautari;
            }
        }
        //printf("Avg:%.2lf|Max:%d",(double)sumaCautari / M,maximCautari);

        sumaCautariFinal += (double)sumaCautari / M;
        maximCautariFinal += maximCautari;

        sumaCautari = 0;
        maximCautari = 0;
        for(int i = 0; i < M; i++){
            int cautari = 0;
            // printf("%d ", randomArray[fillFactor + i]);
            searchInHashTable(hashTable, randomArray[fillFactor + i],&cautari);
            sumaCautari += cautari;
            if(cautari > maximCautari){
                maximCautari = cautari;
            }
        }
        //printf(" | Avg:%.2lf|Max:%d",(double)sumaCautari / M,maximCautari);
        sumaCautariFinal2 += (double)sumaCautari / M;
        maximCautariFinal2 += maximCautari;

    }

        sumaCautariFinal /= NR_TESTS;
        maximCautariFinal /= NR_TESTS;
        sumaCautariFinal2 /= NR_TESTS;
        maximCautariFinal2 /= NR_TESTS;

        printf("Avg : %10.2lf | Max : %10d ",sumaCautariFinal, maximCautariFinal);
        printf(" | Avg : %10.2lf | Max : %10d ",sumaCautariFinal2, maximCautariFinal2);

        if(x == 0.99){

        sumaCautariFinal = 0;
        maximCautariFinal = 0;
        sumaCautariFinal2 = 0;
        maximCautariFinal2 = 0;


            printf("\n");
            printf("----DUPA STERGERI----------------------------------------------------------------------\n");
            int y = (int)0.2 * SIZE_H_TABLE;
            int y1 = 0;
            int y2 = 0;
            while(y1 <= y){
                if(hashTable[y2] != -2){
                    deleteInHashTable(hashTable,hashTable[y2]);
                    y1++;
                }
                y2++;
            }

            FillRandomArray(randomIndices, M, y + 1, fillFactor - 1, true);

        int sumaCautari = 0;
        int maximCautari = 0;
        for(int i = 0; i < M; i++){
            int cautari = 0;
            searchInHashTable(hashTable, randomArray[randomIndices[i]], &cautari);
            sumaCautari += cautari;
            if(cautari > maximCautari){
                maximCautari = cautari;
            }
        }
        //printf("Avg:%.2lf|Max:%d",(double)sumaCautari / M,maximCautari);

        sumaCautariFinal += (double)sumaCautari / M;
        maximCautariFinal += maximCautari;

        sumaCautari = 0;
        maximCautari = 0;
        for(int i = 0; i < M; i++){
            int cautari = 0;
            // printf("%d ", randomArray[fillFactor + i]);
            searchInHashTable(hashTable, randomArray[fillFactor + i],&cautari);
            sumaCautari += cautari;
            if(cautari > maximCautari){
                maximCautari = cautari;
            }
        }
        //printf(" | Avg:%.2lf|Max:%d",(double)sumaCautari / M,maximCautari);
        sumaCautariFinal2 += (double)sumaCautari / M;
        maximCautariFinal2 += maximCautari;

        printf("%.2lf-> 0.80 : ",x);
        printf("Avg : %10.2lf | Max : %10d ",sumaCautariFinal, maximCautariFinal);
        printf(" | Avg : %10.2lf | Max : %10d ",sumaCautariFinal2, maximCautariFinal2);

    }

}


void final_performance(){
    double fillFactor[] = {0.80, 0.85, 0.90, 0.95, 0.99};
    int size = sizeof(fillFactor) / sizeof(fillFactor[0]);
    printf("----ALPHA--------------------FOUND---------------------------------NOT FOUND-----------\n");
    for(int i = 0; i < size; i++){
        printf("pentru %.2lf : ",fillFactor[i]);
        performance(fillFactor[i]);
        printf("\n");
        // ????????
    }
}

int main(void){
    demo();
    //performance();
    //final_performance();
    return(0);
}