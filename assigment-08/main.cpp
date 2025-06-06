#include <stdio.h>
#include "Profiler.h"

#define stepSize 100
#define maxSize 50
#define nrTests 10
#define bestSize 22
#define bossSize 10000

Profiler p("Assigment8");

void swap(int* a, int* b) {
    int buffer = (*a);
    (*a) = (*b);
    (*b) = buffer;
}

void insertionsort(int array[], int start, int sizeOfArray, int fixedSize) {
    for (int i = start + 1; i < sizeOfArray; i++) {
        int buffer = array[i]; p.countOperation("Hybrid",fixedSize);
        int j = i - 1;
        p.countOperation("Hybrid",fixedSize);
        while (j >= 0 && array[j] > buffer) {
            array[j + 1] = array[j]; p.countOperation("Hybrid",fixedSize);
            j--;
            p.countOperation("Hybrid", fixedSize);
        }
        array[j + 1] = buffer; p.countOperation("Hybrid",fixedSize);
    }
}

int quicksortPartition(int array[], int left, int right, int fixedSize){
    int pivot = array[right]; p.countOperation("QuickSort",fixedSize);
    int i = left - 1;
    for(int j = left; j <= right - 1; j++){
        p.countOperation("QuickSort",fixedSize);
        if(array[j] < pivot){
            i++;
            swap(&array[i], &array[j]); p.countOperation("QuickSort",fixedSize, 3);
        }
    }
    i++;
    swap(&array[i], &array[right]); p.countOperation("QuickSort",fixedSize, 3);
    return i;
}

void quicksort(int array[], int left, int right, int fixedSize){
    if(right <= left){
        return;
    } p.countOperation("QuickSort",fixedSize);
    int pivot = quicksortPartition(array, left, right, fixedSize);
    quicksort(array, left, pivot - 1, fixedSize);
    quicksort(array, pivot + 1, right, fixedSize);
}

void printArray(int array[], int sizeOfArray){
    printf("My array is:");
    for(int i = 0; i < sizeOfArray; i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

int hybridQuicksortPartition(int array[], int left, int right, int fixedSize){
    int pivot = array[right]; p.countOperation("Hybrid",fixedSize);
    int i = left - 1;
    for(int j = left; j <= right - 1; j++){
        p.countOperation("Hybrid",fixedSize);
        if(array[j] < pivot){
            i++;
            swap(&array[i], &array[j]); p.countOperation("Hybrid",fixedSize, 3);
        }
    }
    i++;
    swap(&array[i], &array[right]); p.countOperation("Hybrid",fixedSize, 3);
    return i;
}

void hybridQuicksort(int array[], int left, int right, int fixedSize, int francesco){
    p.countOperation("Hybrid",fixedSize);
    if(right - left <= francesco){
        insertionsort(array, left, right, fixedSize);
        return;
    } p.countOperation("Hybrid",fixedSize);
    int pivot = hybridQuicksortPartition(array, left, right, fixedSize);
    hybridQuicksort(array, left, pivot - 1, fixedSize, francesco);
    hybridQuicksort(array, pivot + 1, right, fixedSize, francesco);
}

void demo(){
    //int array[] = {5,8,9,2,4,1,3,6};
    //int array[] = {9,8,7,6,5,4,3,2,1};
    int array[50];
    FillRandomArray(array, 50);
    int sizeOfArray = sizeof(array) / sizeof(array[0]);
    printArray(array, sizeOfArray);
    //quicksort(array, 0, sizeOfArray - 1);
    hybridQuicksort(array, 0, sizeOfArray, sizeOfArray, bestSize);
    printArray(array, sizeOfArray);
}

void QuicksortVSHybridQuickSort(){
    for(int k = stepSize; k <= bossSize; k += stepSize) {
        for (int i = 0; i < nrTests; i++) {
            int array[k];
            FillRandomArray(array, k);
            int arrayCopy[k];
            memcpy(arrayCopy, array, k * sizeof(int));
            quicksort(array, 0, k, k);
            hybridQuicksort(arrayCopy, 0, k, k, bestSize);
        }
    }
    p.divideValues("Hybrid", nrTests);
    p.divideValues("QuickSort", nrTests);
    p.createGroup("COMPARATION","Hybrid","QuickSort");
    p.showReport();
}

void timeChallenge(){

    for(int k = stepSize; k <= bossSize; k += stepSize) {

        p.startTimer("HYBRID-TIME", k);
        for (int i = 0; i < nrTests; i++) {
            int array[k];
            FillRandomArray(array, k);
            hybridQuicksort(array, 0, k, k, bestSize);
        }
        p.stopTimer("HYBRID-TIME", k);
        //p.divideValues("HYBRID-TIME", nrTests);

        p.startTimer("NORMAL-TIME", k);
        for (int i = 0; i < nrTests; i++) {
            int array[k];
            FillRandomArray(array, k);
            quicksort(array, 0, k, k);
        }
        p.stopTimer("NORMAL-TIME", k);
        //p.divideValues("NORMAL-TIME", nrTests);

    }

//    p.divideValues("HYBRID-TIME", nrTests);
//    p.divideValues("NORMAL-TIME", nrTests);

    p.createGroup("TIME_COMPARATION","NORMAL-TIME", "HYBRID-TIME");

    p.showReport();
}

void demonstratie(){
    for(int k = 0; k < 50; k++){
        for(int i = 0; i < nrTests; i++){
            int array[bossSize];
            FillRandomArray(array, bossSize);
            hybridQuicksort(array, 0, bossSize, k, k);
        }
    }
    p.divideValues("Hybrid", nrTests);
    p.showReport();
}

int main(void){
    //demonstratie();
    //demo();
    QuicksortVSHybridQuickSort();
    //timeChallenge();
    return(0);
}