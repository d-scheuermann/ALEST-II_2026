#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

void bubblesort(int values[], int total);

void bubblesort(int values[], int total)
{
    for(int i=0; i<total; i++) {
        char trocou = 0;
        for(int j=0; j<total-i-1; j++) {
            if(values[j] > values[j+1]) {
               int temp = values[j];
               values[j] = values[j+1];
               values[j+1] = temp;
               trocou = 1;
            }
        }
        if(!trocou) break;
    }
}

int main()
{
    int data[MAX];
    for(int i=0; i<MAX; i++)
        data[i] = rand()%(MAX*10);
    long start = clock();
    bubblesort(data, MAX);
    long end = clock();
    //for(int i=0; i<MAX; i++)
    //    printf("%d ", data[i]);
    //printf("\n");
    printf("Tempo para %d elementos: %ld ns\n", MAX,(end-start));
}
