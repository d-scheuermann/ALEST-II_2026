import java.util.Random;

public class AppSorts {

    public static void main(String args[]) {
        Random r = new Random();
        final int MAX = 100000;

        for (int max = 500; max <= MAX; max += 500) {
            Integer[] data = new Integer[max];
            for (int i = 0; i < data.length; i++)
                data[i] = r.nextInt(data.length * 10);

            //Mergesort<Integer> s = new Mergesort<>();
            Quicksort<Integer> s = new Quicksort<>();
            // MaxHeap<Integer> s = new MaxHeap<data.length>();

            long start = System.nanoTime();
            s.sort(data);
            long end = System.nanoTime();

            double tempo = (end - start) / 1e9; // 1.000.000 (para transformar em ms)
            System.out.printf("%d %.7f\n", max, tempo);
        }
    }
}
