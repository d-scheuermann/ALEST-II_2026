from bubblesort import Bubblesort
from mergesort import Mergesort
from quicksort import Quicksort
from time import process_time

import random

if __name__ == "__main__":

    MAX = 100000

    data = [random.randint(1,n*10) for x in range(n)]
    #print(data)

    #bs = Bubblesort()
    #qs = Quicksort()
    ms = Mergesort()

    start = process_time()

    #qs.sort(data)
    ms.sort(data)

    end = process_time()

    t = end-start
    print(f"{n} {t}")

