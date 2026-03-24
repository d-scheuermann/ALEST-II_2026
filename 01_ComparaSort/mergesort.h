#ifndef _MERGE_SORT_H
#define _MERGE_SORT_H

template <typename T>
class MergeSort {
private:

    T* helper;

    void sort(T values[], int low, int high) {
        // Check if low is smaller then high, if not then the array is sorted
        if (low < high) {
            // Get the index of the element which is in the middle
            int middle = (low + high) / 2;
            // Sort the left side of the array
            sort(values, low, middle);
            // Sort the right side of the array
            sort(values, middle + 1, high);
            // Combine them both
            merge(values, low, middle, high);
        }
    }

    void merge(T values[], int low, int middle, int high) {
        // Copy both parts into the helper array
        for (int i = low; i <= high; i++) {
            helper[i] = values[i];
        }

        int i = low;
        int j = middle + 1;
        int k = low;
        // Copy the smallest values from either the left or the right side back
        // to the original array
        while (i <= middle && j <= high) {
            if (helper[i] <= helper[j]) {
                values[k] = helper[i];
                i++;
            } else {
                values[k] = helper[j];
                j++;
            }
            k++;
        }
        // Copy the rest of the left side of the array into the target array
        while (i <= middle) {
            values[k] = helper[i];
            k++;
            i++;
        }
    }

public:
    void sort(T values[], int total) {
        helper = new int[total];
        sort(values, 0, total-1);
        delete helper;
    }
};
#endif

