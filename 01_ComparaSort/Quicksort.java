import java.util.Random;

public class Quicksort<T extends Comparable<T>> {
    private T data[];

    public void sort(T[] data) {
        this.data = data;
        sort(0, data.length-1);
    }

    public void sort(int p, int r) {
        if(p < r) {
            int q = partition(p, r);
            sort(p, q-1);
            sort(q+1, r);
        }
    }

    private int partition(int p, int r) {
        int q = p;
        for(int j=p; j<r; j++) {
            if(data[j].compareTo(data[r]) < 0) {
                swap(j,q);
                q++;
            }
        }
        swap(r,q);
        return q;
    }

    private void swap(int p1, int p2) {
        T tmp = data[p1];
        data[p1] = data[p2];
        data[p2] = tmp;
    }

    public static void main(String args[]) {
        Random r = new Random();
        int MAX = 100000;
        Integer[] data = new Integer[MAX];
        for(int i=0; i<data.length; i++)
            data[i] = r.nextInt(data.length*10);

        Quicksort<Integer> qs = new Quicksort<>();

        long start = System.nanoTime();
        qs.sort(data);
        long end = System.nanoTime();

        double tempo = (end-start)/1e9;
        System.out.printf("%d %f\n",MAX,tempo);

        //for(int i=0; i<data.length; i++)
        //    System.out.print(data[i]+" ");
        //System.out.println();
    }
}

