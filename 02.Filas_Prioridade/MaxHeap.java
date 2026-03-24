// MaxHeap.java
public class MaxHeap<T extends Comparable<T>> {

  private T v[];
  private int size;

  @SuppressWarnings("unchecked")
  public MaxHeap(int tam) {
    size = 1;
    v = (T[]) new Comparable[tam];
  }

  public MaxHeap(T values[]) {
    v = values;
    size = values.length;
  }

  private void swim(int k) {
    while (k > 1 && v[k / 2].compareTo(v[k]) < 0) {
      System.out.println("Swap " + v[k] + " with " + v[k / 2] + " " + k);
      T tmp = v[k];
      v[k] = v[k / 2];
      v[k / 2] = tmp;
      k = k / 2;
    }
  }

  public void put(T data) {
    v[size] = data;
    swim(size);
    size++;
  }

  private void sink(int k, int n) {
    while (2 * k <= n) {
      int j = 2 * k;
      if (j < n && v[j].compareTo(v[j + 1]) < 0)
        j++;
      if (v[k].compareTo(v[j])>=0)
        break;
      T tmp = v[k];
      v[k] = v[j];
      v[j] = tmp;
      k = j;
    }
  }

  public T get() {
    if (size == 1)
      throw new UnsupportedOperationException("MaxHeap vazio!");
    T res = v[1];
    v[1] = v[--size];
    sink(1,size);
    return res;
  }

  private void print(int b, int elem, int sp) {
    int i, j;

    System.out.println("");
    for (j = 0; j < size; j++)
      System.out.print(v[j] + " ");
    System.out.println("");

    while (true) {
      for (j = 0; j <= sp / 2; j++)
        System.out.print(" ");
      for (i = b; i < b + elem; i++) {
        if (i == size)
          return;
        System.out.print(v[i]);
        for (j = 0; j < sp; j++)
          System.out.print(" ");
      }
      System.out.println("");
      b = b + elem;
      elem = 2 * elem;
      sp = sp / 2;
    }
  }

  public void print() {
    System.out.println("");
    print(1, 1, 32);
    System.out.println("");
  }

  public void printArray() {
    for (int i = 0; i < size; i++)
      System.out.print(v[i] + " ");
    System.out.println();
  }

  // Implemente heapsort!
  void sort(T[] data) {
  }
}
