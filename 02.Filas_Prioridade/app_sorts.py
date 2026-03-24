from mergesort import Mergesort
from quicksort import Quicksort
from maxheap import MaxHeap
from time import process_time

import random

if __name__ == "__main__":

    MAX = 50000

    for n in range(500,MAX,500):
        data = [random.randint(1,n*10) for x in range(n)]
        #print(data)

        s = Quicksort()
        #s = Mergesort()
        #s = MaxHeap()

        start = process_time()

        s.sort(data)

        end = process_time()

        t = end-start
        print(f"{n} {t}")

