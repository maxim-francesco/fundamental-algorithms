//                                          ASSIGMENT 2
//
//  Info:
//
//  AF(2023/2024)
//  Student: Francesco Maxim(grupa 30224)
//  Task : Construire Heap prin metoda Bottom Up si Top Down si analizarea acestora
//         Analizare construire Heap in worst case
//         Realizare Heap Sort
//         
//  Surse de documentatie : 
// 
//  YouTube: https://www.youtube.com/@abdul_bari -> Pentru Analizare A Algoritmilor
//           https://www.youtube.com/@cypryoprisa -> Pentru Analizare A Algoritmilor
//  ChatGPT: https://chat.openai.com -> Pentru Realizarea Algoritmilor
//  GeeksForGeeks: https://www.geeksforgeeks.org -> Pentru Aprofundarea Algoritmilor
// 
// Concluzii si lucruri invatate dupa Assigmentul 2:
// 
//  De ce heap?
//      R: -> Insertie Eficienta : O(1) pana la O(log n)  
//         -> Stergere Eficienta : O(1) pana la O(log n) 
//         -> Acces la extrema in O(1)
// 
// Bottom Up sau Top Down?
//      R: -> Observam dupa analiza acestui assigment ca metoda Bottom Up
//            este mai eficienta, datorita numarului mult mai scazut de operatii
//            in construirea heap-ul
//
// De ce sa mai folosim si Top Down daca Bottom Up are o performanta mai buna?
// 
//      R: -> Intr-un caz mai special, unde ne intereseaza performanta insertiilor 
//            este mai eficient sa folosim metoda Top Down datorita numarului mai mic
//            de comparatii(la insertie) ->GeeksForGeeks + Analiza Assigmentului
// 
// De ce Heap Sort?
//      R: -> Performanta excelenta in orice caz, WORST, BASE SI AVERAGE
//             O(N LOG N) comparativ cu algoritmii din assigmentul 1
// 


#include <stdio.h>
#include <stdlib.h>

#include "Profiler.h"
Profiler p("Assigment2");

#define DEMO 5

#define step_size 100
#define max_limit 10000
#define tests 5

void swap(int *p1, int *p2){
    int p_buffer = *p1;
    *p1 = *p2;
    *p2 = p_buffer;
}

void heapify_bottom_up(int array[], int size, int index){

    Operation bottom_up_comp = p.createOperation("bottom_up_comp", size);
    Operation bottom_up_attr = p.createOperation("bottom_up_attr", size);

    int current_index = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    bottom_up_comp.count();
    if(left < size && (array[left] > array[current_index])){

        current_index = left;

    }

    bottom_up_comp.count();
    if(right < size && (array[right] > array[current_index])){

        current_index = right;

    }

    if(current_index != index){

        swap(&array[current_index],&array[index]); bottom_up_attr.count(3);

        heapify_bottom_up(array, size, current_index);

    }

}

void build_with_bottom_up(int array[], int size){

    for(int index = ( (size / 2) - 1); index >= 0; index--){

        heapify_bottom_up(array, size, index);

    }

}

void print_array(char text[],int array[], int size){

    printf("%s:",text);

    for(int i = 0; i < size; i++){

        printf("%d ", array[i]);

    }

    printf("\n");

}

void heapify_top_down(int array[], int index, int size){

    Operation top_down_comp = p.createOperation("top_down_comp", size);
    Operation top_down_attr = p.createOperation("top_down_attr", size);

    int parent = (index - 1) / 2;

    top_down_comp.count();
    while(index > 0 && (array[index] > array[parent])){

            swap(&array[index],&array[parent]); top_down_attr.count(3);
            index = parent;
            parent = (index - 1) / 2;

        top_down_comp.count();
    }

}

void build_with_top_down(int array[],int size){

    for(int index = 1; index < size; index++){

        heapify_top_down(array, index, size);

    }

}

void heapsort(int array[], int size){

    build_with_bottom_up(array, size);

    for(int i = (size - 1); i >=0; i--){

        swap(&array[0],&array[i]);

        heapify_bottom_up(array, i, 0);

    }

}

void demo(){

    int array[DEMO];
    FillRandomArray(array, DEMO, 0, 100, true);
    int size = sizeof(array) / sizeof(array[0]);

    int array_copy[DEMO];
    int array_for_heapsort[DEMO];

    memcpy(array_copy, array, DEMO * sizeof(array[0]));
    memcpy(array_for_heapsort, array, DEMO * sizeof(array[0]));

    print_array("Actual Array", array, size);

    build_with_bottom_up(array, size);

    print_array("Building with Bottom Up", array, size);

    build_with_top_down(array_copy, size);

    print_array("Building with Top Down",array_copy, size);

    heapsort(array_for_heapsort, size);

    print_array("Heap Sort", array_for_heapsort, size);

    //p.showReport();

}

void performance_of_algorithms(){

    int array[max_limit];
    int array_copy[max_limit];

    for(int i = step_size; i < max_limit; i++){

        // for(int j = 0; j < tests; j++){

            FillRandomArray(array, i);
            memcpy(array_copy, array, i * sizeof(array[0]));
            build_with_bottom_up(array, i);
            build_with_top_down(array_copy, i);

        // }

    }

    p.addSeries("Bottom_Up","bottom_up_comp","bottom_up_attr");
    p.addSeries("Top_Down","top_down_comp","top_down_attr");

    p.createGroup("Analysis","Bottom_Up","Top_Down");

    p.showReport();

}

void worst_case(){

    int array[max_limit];
    int array_copy[max_limit];

    for(int i = step_size; i < max_limit; i += step_size){

        FillRandomArray(array, i, 0, i, true, 1);
        memcpy(array_copy, array, sizeof(array[0]) * i);
        build_with_bottom_up(array, i);
        build_with_top_down(array_copy, i);

    }

    p.addSeries("Worst Case Bottom Up","bottom_up_comp","bottom_up_attr");
    p.addSeries("Worst Case Top Down","top_down_comp","top_down_attr");

    p.createGroup("Worst Case","Worst Case Bottom Up","Worst Case Top Down");

    p.showReport();

}

int main(void){

    demo();

    //performance_of_algorithms();

    //worst_case();

    return(0);
}