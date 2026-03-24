#!/usr/bin/python3

from maxheap import MaxHeap

if __name__ == "__main__":
    myheap = MaxHeap()
    el = "A"
    print("Digite um número/string ou 'get' para retirar o maior elemento, 'quit' para sair")
    while el != "quit":
        el = input("Element: ")
        if el == "get":
            print("get: ",myheap.get())
        else:
            myheap.add(el)
        myheap.printh()
  
