#!/usr/bin/python3
#
# Quicksort
#

import random
from time import process_time

class Quicksort:

    def partition(self, data, p, r):

        q = p
        for j in range(p,r):
            if data[j] <= data[r]:
                data[j], data[q] = data[q], data[j]
                q += 1
        data[r], data[q] = data[q], data[r]
        return q


    def sort(self, data):
        self.__quicksort(data, 0, len(data)-1)

    def __quicksort(self, data, p, r):
        if p < r:
            q = self.partition(data, p, r)
            self.__quicksort(data, p, q-1)
            self.__quicksort(data, q+1, r)


if __name__ == "__main__":
    MAX = 100000
    data = [random.randint(0,MAX*10) for x in range(MAX)]

    qs = Quicksort()
    start = process_time()

    qs.sort(data)

    end = process_time()
    t = end-start

    print(f"{MAX} {t}")

    #print(f"Tempo para ordenar {MAX} elementos: {t} s")

