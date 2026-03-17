#!/usr/bin/python3
#
# Mergesort
#

import random
from time import process_time

class Mergesort:

    def sort(self, alist):

        #print("Splitting ",alist)
        if len(alist) > 1:

            mid = len(alist) // 2   # Div. inteira
            lefthalf = alist[:mid]  # slicing: lista até mid-1
            righthalf = alist[mid:] # slicing: lista de mid ao final

            self.sort(lefthalf)
            self.sort(righthalf)

            i = 0
            j = 0
            k = 0

            while i < len(lefthalf) and j < len(righthalf):

                if lefthalf[i] < righthalf[j]:
                    alist[k] = lefthalf[i]
                    i += 1
                else:
                    alist[k] = righthalf[j]
                    j += 1
                k += 1

            while i < len(lefthalf):
                alist[k] = lefthalf[i]
                i += 1
                k += 1

            while j < len(righthalf):
                alist[k] = righthalf[j]
                j += 1
                k += 1

if __name__ == "__main__":

    MAX = 100000
    data = [random.randint(0,MAX*10) for x in range(MAX)]

    ms = Mergesort()

    start = process_time()

    ms.sort(data)

    end = process_time()
    t = end-start

    print(f"{MAX} {t}")

    #print(f"Tempo para ordenar {MAX} elementos: {t} s")

