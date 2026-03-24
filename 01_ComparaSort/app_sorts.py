from bubblesort import Bubblesort
from mergesort import Mergesort
from quicksort import Quicksort
from time import process_time

import random

if __name__ == "__main__":

    MAX = 50000

    for n in range(500,MAX,500):
        data = [random.randint(1,n*10) for x in range(n)]
        #print(data)

        #s = Bubblesort()
        s = Quicksort()
        #s = Mergesort()

        start = process_time()

        s.sort(data)

        end = process_time()

        t = end-start
        print(f"{n} {t}")

