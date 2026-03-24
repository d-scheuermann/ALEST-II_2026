#ifndef _BUBBLE_SORT_H
#define _BUBBLE_SORT_H

#include <algorithm>

template <typename T>
class BubbleSort {
public:

    void sort(T data[], int total) {
        for(int i=0; i<total; i++) {
            char trocou = 0;
            for(int j=0; j<total-i-1; j++) {
                if(data[j] > data[j+1]) {
                   int temp = data[j];
                   data[j] = data[j+1];
                   data[j+1] = temp;
                   trocou = 1;
                }
            }
            if(!trocou) break;
        }
    }
};

#endif

