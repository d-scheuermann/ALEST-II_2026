#!/usr/bin/python3
#
# Bubblesort
#

import random
from time import process_time

class Bubblesort:

    def sort(self, alist):

        for i in range(len(alist)):
            trocou = False
            for j in range(len(alist)-i-1):
                if alist[j] > alist[j+1]:
                    alist[j], alist[j+1] = alist[j+1], alist[j]
                    trocou = True
            if not trocou:
                break

if __name__ == "__main__":

    MAX = 10000
    data = [random.randint(0,MAX*10) for x in range(MAX)]

    bs = Bubblesort()
    start = process_time()

    bs.sort(data)

    end = process_time()
    t = end-start

    #print(data)
    print(f"Tempo para ordenar {MAX} elementos: {t} s")

