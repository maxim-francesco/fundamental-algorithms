//                                          ASSIGMENT 1
//
//  Info:
//
//  AF(2023/2024)
//  Student: Francesco Maxim(grupa 30224)
//  Task : analiza pentru bubble sort, insertion sort si selection sort
//
//  Surse de documentatie : 
//                          
//     YouTube:  --> https://www.youtube.com/@BroCodez (Pentru Realizarea Algoritmilor)
//               --> https://www.youtube.com/@cypryoprisa (Pentru analizarea lor cu ajutorul bibliotecii Profiler)            
//                          
//  Concluzii dupa assigment : 
//
//  BEST CASE:
//      SELECTION SORT SE DUCE IN O(N^2)
//        
//  WORST:
//      TOATE SUNT LA FEL
//  AVARAGE:
//      BUBBLE SORT ARE CELE MAI MULTE COMPARATII SI ASIGNARI
//          ->NOT A GOOD CHOICE 
//

#include <stdio.h>
#include <stdlib.h>

#include "Profiler.h"

#define array_size1 10

#define array_max_size 10000
#define step_size 100
#define number_of_tests 3

Profiler p("Assigment1");

void insertion_sort(int array[],int array_lenght){

    Operation comp1 = p.createOperation("Comparatii_Insertion_Sort",array_lenght);
    Operation atr1 = p.createOperation("Atribuiri_Insertion_Sort",array_lenght);

    for(int i = 1; i < array_lenght; i++){

        atr1.count();
        int buffer = array[i];
        int j = i - 1;

        comp1.count();
        while(j >= 0 && array[j] > buffer){
            
            atr1.count();
            array[j + 1] = array[j];
            j--;
            comp1.count();

        }

        atr1.count();
        array[j + 1] = buffer;

    }

}

void selection_sort(int array[],int array_lenght){

    Operation comp2 = p.createOperation("Comparatii_Selection_Sort",array_lenght);
    Operation atr2 = p.createOperation("Atribuiri_Selection_Sort",array_lenght);

    for(int i = 0; i < array_lenght; i++){

        int pozition_of_min = i;

        for(int j = i + 1; j < array_lenght; j++){

            comp2.count();
            if(array[pozition_of_min] > array[j]){

                atr2.count();
                pozition_of_min = j;

            }

        }

        atr2.count(3);
        int buffer = array[i];
        array[i] = array[pozition_of_min];
        array[pozition_of_min] = buffer;

    }

}

void bubble_sort(int array[],int array_lenght){

    Operation comp3 = p.createOperation("Comparatii_Bubble_Sort",array_lenght);
    Operation atr3 = p.createOperation("Atribuiri_Bubble_Sort",array_lenght);

    for(int i = 0; i < array_lenght; i++){

        atr3.count();
        int swap = 0;

        for(int j = 0; j < array_lenght - i - 1; j++){

            comp3.count();
            if(array[j] > array[j + 1]){

                atr3.count(3);
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swap = 1;
            }

        }

        comp3.count();
        if(swap == 0){
            break;
        }

    }

}

void print(char s[],int array[],int array_lenght){

    printf("Vectorul %s:",s);
    for(int i = 0; i < array_lenght; i++){
        printf("%d ",array[i]);
    }

    printf("\n");

}

void demo(){

    int array1[array_size1];
    int array2[array_size1];
    int array3[array_size1];

    FillRandomArray(array1,array_size1);

    memcpy(array2,array1,array_size1 * sizeof(array1[0]));
    memcpy(array3,array1,array_size1 * sizeof(array1[0]));

    print("Inainte de Insertion Sort",array1,array_size1);
    insertion_sort(array1,array_size1);
    print("Dupa",array1,array_size1);

    printf("\n");

    print("Inainte de Selection Sort",array2,array_size1);
    selection_sort(array2,array_size1);
    print("Dupa",array2,array_size1);

    printf("\n");

    print("Inainte de Bubble Sort",array3,array_size1);
    bubble_sort(array3,array_size1);
    print("Dupa",array3,array_size1);

}

void performance_of_algorithms(){

    int array1[array_max_size];
    int array2[array_max_size];
    int array3[array_max_size];
    for(int i = step_size; i < array_max_size; i += step_size){

        for(int j = 0; j < number_of_tests; j++){

            FillRandomArray(array1,i);
            memcpy(array2,array1,i * sizeof(array1[0]));
            memcpy(array3,array1,i * sizeof(array1[0]));
            insertion_sort(array1,i);
            selection_sort(array2,i);
            bubble_sort(array3,i);

        }

    }

    p.divideValues("Comparatii_Insertion_Sort",number_of_tests);
    p.divideValues("Atribuiri_Insertion_Sort",number_of_tests);

    p.divideValues("Comparatii_Selection_Sort",number_of_tests);
    p.divideValues("Atribuiri_Selection_Sort",number_of_tests);

    p.divideValues("Comparatii_Bubble_Sort",number_of_tests);
    p.divideValues("Atribuiri_Bubble_Sort",number_of_tests);

    p.createGroup("Atribuiri","Atribuiri_Insertion_Sort","Atribuiri_Selection_Sort","Atribuiri_Bubble_Sort");
    p.createGroup("Comparatii","Comparatii_Insertion_Sort","Comparatii_Selection_Sort","Comparatii_Bubble_Sort");

    p.showReport();

}

void best_case(){

    int array1[array_max_size];
    int array2[array_max_size];
    int array3[array_max_size];
    for(int i = step_size; i < array_max_size; i += step_size){

            FillRandomArray(array1,i,10,array_max_size,false,1);
            memcpy(array2,array1,i * sizeof(array1[0]));
            memcpy(array3,array1,i * sizeof(array1[0]));
            insertion_sort(array1,i);
            selection_sort(array2,i);
            bubble_sort(array3,i);

    }

    p.createGroup("Atribuiri Best Case","Atribuiri_Insertion_Sort","Atribuiri_Selection_Sort","Atribuiri_Bubble_Sort");
    p.createGroup("Comparatii Best Case","Comparatii_Insertion_Sort","Comparatii_Selection_Sort","Comparatii_Bubble_Sort");

    p.showReport();

}

void worst_case(){

    int array1[array_max_size];
    int array2[array_max_size];
    int array3[array_max_size];
    for(int i = step_size; i < array_max_size; i += step_size){

            FillRandomArray(array1,i,10,array_max_size,false,2);
            memcpy(array2,array1,i * sizeof(array1[0]));
            memcpy(array3,array1,i * sizeof(array1[0]));
            insertion_sort(array1,i);
            selection_sort(array2,i);
            bubble_sort(array3,i);

    }

    p.divideValues("Comparatii_Insertion_Sort",number_of_tests);
    p.divideValues("Atribuiri_Insertion_Sort",number_of_tests);

    p.divideValues("Comparatii_Selection_Sort",number_of_tests);
    p.divideValues("Atribuiri_Selection_Sort",number_of_tests);

    p.divideValues("Comparatii_Bubble_Sort",number_of_tests);
    p.divideValues("Atribuiri_Bubble_Sort",number_of_tests);

    p.createGroup("Atribuiri Worst Case","Atribuiri_Insertion_Sort","Atribuiri_Selection_Sort","Atribuiri_Bubble_Sort");
    p.createGroup("Comparatii Worst Case","Comparatii_Insertion_Sort","Comparatii_Selection_Sort","Comparatii_Bubble_Sort");

    p.showReport();

}


int main(void){

    //demo();
    performance_of_algorithms();
    //best_case();
    //worst_case();

    return(0);
}