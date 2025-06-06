//                                          ASSIGMENT 3
//
//  Info:
//
//  AF(2023/2024)
//  Student: Francesco Maxim(grupa 30224)
//  Task : QuickSort -> Analiza Average,Best and Worst Case
//         BubbleSort -> Analiza Iterativ vs Recursiv (Timp si Nr Operatii)
//         QuickSort Vs HeapSort
//         QuickSelect
//         
//  Surse de documentatie : 
// 
//  YouTube: https://www.youtube.com/@abdul_bari -> Pentru Analizare A Algoritmilor
//           https://www.youtube.com/@cypryoprisa -> Pentru Analizare A Algoritmilor
//  ChatGPT: https://chat.openai.com -> Pentru Realizarea Algoritmilor
//  GeeksForGeeks: https://www.geeksforgeeks.org -> Pentru Aprofundarea Algoritmilor
// 
// Concluzii si lucruri invatate dupa Assigmentul 3:
//
//  QuickSort: ->Foarte optim in cazul unui array care este foarte random
//             ->Foarte prost in BestCase si Worst Case(deoarece mi am ales Pivotul ca fiind ultimul element)
//  Concluzie Generala pentru Pivotul Primul/Ultimul element 
//             ->Daca avem un vector sortat (cresc/desc) alegerea pivotului fiind primul/ultimul este foarte neoptima
// 
// Iterativ Sau Recursiv?
//              Recursivul o sa ia mai mult timp deoarece se foloseste de stiva 
// 


#include <stdio.h>

#include "Profiler.h"
Profiler p("Assigment3");

#define demo_size 10

#define performance_size 1000
#define step_size 100
#define nr_tests 3

void swap(int *a, int *b){

    int temp = *a;
    *a = *b;
    *b = temp; 

}

int partition(int array[], int left, int right, int size){

    p.countOperation("QuickSort", size);

    int pivot = array[right]; 
    int i = left - 1;

    for(int j = left; j <= (right - 1); j++){

        p.countOperation("QuickSort", size);
        if(array[j] < pivot){

            i++;
            swap(&array[i],&array[j]); p.countOperation("QuickSort", size, 3);

        }

    }

    i++;
    swap(&array[i],&array[right]); p.countOperation("QuickSort", size, 3);

    return i;

}

void quicksort(int array[], int left, int right, int size){

    if(right <= left){

        return;

    }

    int pivot = partition(array, left, right, size); //p.countOperation("QuickSort", size);
    //int pivot = quickselect(array,left,right,size);
    quicksort(array, left, pivot - 1, size);
    quicksort(array, pivot + 1, right, size);

}

void print(char s[], int array[], int size){

    printf("%s:",s);

    for(int i = 0; i < size; i++){

        printf("%d ", array[i]);

    }

    printf("\n");

}

void heapify_bottom_up(int array[], int size, int index, int fix_size){

    int current_index = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    p.countOperation("HeapSort", fix_size);
    if(left < size && (array[left] > array[current_index])){

        current_index = left;

    }

    p.countOperation("HeapSort", fix_size);
    if(right < size && (array[right] > array[current_index])){

        current_index = right;

    }

    if(current_index != index){

        swap(&array[current_index],&array[index]); p.countOperation("HeapSort", fix_size, 3);

        heapify_bottom_up(array, size, current_index, fix_size);

    }

}

void build_with_bottom_up(int array[], int size, int fix_size){

    for(int index = ( (size / 2) - 1); index >= 0; index--){

        heapify_bottom_up(array, size, index, fix_size);

    }

}

void heapsort(int array[], int size, int fix_size){

    build_with_bottom_up(array, size, fix_size);

    for(int i = (size - 1); i >=0; i--){

        swap(&array[0],&array[i]); p.countOperation("HeapSort", fix_size, 3);

        heapify_bottom_up(array, i, 0, fix_size);

    }

}

void bubble_sort(int array[],int array_lenght){

    for(int i = 0; i < array_lenght - 1; i++){

        //iterativ.count();
        int swap = 0;

        for(int j = 0; j < array_lenght - i - 1; j++){

            p.countOperation("Bubble_Sort",array_lenght);
            if(array[j] > array[j + 1]){

                p.countOperation("Bubble_Sort",array_lenght,3);
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swap = 1;
            }

        }

        //iterativ.count();
        if(swap == 0){
            break;
        }

    }

}

void bubble_sort_recursive(int array[], int size, int fixed_size){

    

    if(size == 1){

        return; 

    }

    for(int i = 0; i < size - 1; i++){

        p.countOperation("Recursive_Bubble_Sort", fixed_size);
        if(array[i + 1] < array[i]){
            
            swap(&array[i],&array[i + 1]); p.countOperation("Recursive_Bubble_Sort", fixed_size, 3);

        }

    }

    bubble_sort_recursive(array, size - 1,fixed_size);

}

void demo(){

    int array[demo_size];
    FillRandomArray(array, demo_size, 0, 100, true);
    print("Initial Array", array, demo_size);
    //printf("Quick Select:%d\n",quickselect(array,0,demo_size,demo_size/2));
    quicksort(array, 0, demo_size - 1, demo_size);
    //bubble_sort_recursive(array, demo_size);
    print("After QuickSort", array, demo_size);

}

void performance_iterative_vs_recursive(){

    int array[performance_size];
    int array_copy[performance_size];

    for(int i = step_size; i <= performance_size; i += step_size){

        //p.startTimer("Bubble_Sort_Timer",i);
        // p.startTimer("BubbleTimerRecursiv",i);
        for(int j = 0; j < nr_tests; j++){

            FillRandomArray(array, i);
            memcpy(array_copy, array, i * sizeof(array[0]));
            //p.startTimer("Bubble_Sort_Timer",i);
            bubble_sort(array, i);
            // p.stopTimer("Bubble_Sort_Timer",i);
            // p.startTimer("BubbleTimerRecursiv",i);
            bubble_sort_recursive(array_copy, i,i);
            //p.stopTimer("BubbleTimerRecursiv",i);

       }
        // p.stopTimer("Bubble_Sort_Timer",i);
        // p.stopTimer("BubbleTimerRecursiv",i);
    }


    p.divideValues("Bubble_Sort", nr_tests);
    p.divideValues("Recursive_Bubble_Sort", nr_tests);

    p.createGroup("Iterative vs Recursive","Bubble_Sort","Recursive_Bubble_Sort");
    //p.createGroup("Timer","BubbleTimerRecursiv","Bubble_Sort_Timer");

    p.showReport();    

}


void performance(){

    int array[performance_size];
    int array_copy[performance_size];

    for(int i = step_size; i <= performance_size; i += step_size){

        for(int j = 0; j < nr_tests; j++){

            FillRandomArray(array, i);
            memcpy(array_copy, array, i * sizeof(array[0]));
            quicksort(array, 0, i - 1, i);
            heapsort(array_copy, i, i);

        }

    }

    p.divideValues("QuickSort", nr_tests);
    p.divideValues("HeapSort", nr_tests);

    p.createGroup("Average","QuickSort","HeapSort");

    p.showReport();

}

void performance_best_case(){

    int best_array[performance_size];
    int best_array_copy[performance_size];

    for(int i = step_size; i < performance_size; i += step_size){

        FillRandomArray(best_array, i, 0, i, true, 1);
        memcpy(best_array_copy, best_array, i * sizeof(best_array[0]));
        quicksort(best_array, 0, i - 1, i);
        heapsort(best_array_copy, i, i);

    }

    p.createGroup("BestCase","QuickSort","HeapSort");

    p.showReport();

}

void performance_worst_case(){

    int worst_array[performance_size];
    int worst_array_copy[performance_size];

    for(int i = step_size; i < performance_size; i += step_size){

        FillRandomArray(worst_array, i, 0, i, true, 2);
        memcpy(worst_array_copy, worst_array, i * sizeof(worst_array[0]));
        quicksort(worst_array, 0, i - 1, i);
        heapsort(worst_array_copy, i, i);

    }

    p.createGroup("WorstCase","QuickSort","HeapSort");

    p.showReport();

}

int main(void){

    demo();

    //demo_quick_select();

    //performance_iterative_vs_recursive();

    //performance();

    //performance_best_case();

    //performance_worst_case();


    return(0);
}