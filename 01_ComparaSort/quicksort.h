#ifndef _QUICK_SORT_H
#define _QUICK_SORT_H

#include <algorithm>

template <typename T>
class QuickSort {
private:

    void sort(T data[], int p, int r) {
        if(p < r) {
            int q = partition(data,p, r);
            sort(data, p, q-1);
            sort(data, q+1, r);
        }
    }

    T partition(T data[], int p, int r) {
        int q = p;
        for(int j=p; j<r; j++) {
            if(data[j] <= data[r]) {
                //T tmp = data[j];
                //data[j] = data[q];
                //data[q] = tmp;
                std::swap(data[j], data[q]);
                q++;
            }
        }
        //T tmp = data[r];
        //data[r] = data[q];
        //data[q] = tmp;
        std::swap(data[r], data[q]);
        return q;
    }

public:
    void sort(T values[], int total) {
        sort(values, 0, total-1);
    }
};
#endif

