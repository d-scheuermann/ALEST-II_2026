import java.util.Random;

public class Bubblesort<T extends Comparable<T>> {

    public void sort(T[] values) {
        for(int i=0; i<values.length; i++) {
            boolean trocou = false;
            for(int j=0; j<values.length-i-1; j++) {
                if(values[j].compareTo(values[j+1]) > 0) {
                    T temp = values[j];
                    values[j] = values[j+1];
                    values[j+1] = temp;
                    trocou = true;
                }
            }
            if(!trocou) break;
        }
    }

    public static void main(String args[]) {
        Random r = new Random();
        int MAX = 30000;
        Integer[] data = new Integer[MAX];
        for(int i=0; i<data.length; i++)
            data[i] = r.nextInt(data.length*10);

        long start = System.nanoTime();
        Bubblesort<Integer> bs = new Bubblesort<>();
        bs.sort(data);
        long end = System.nanoTime();
        //for(int i=0; i<data.length; i++)
        //    System.out.print(data[i]+" ");
        //System.out.println();
        double tempo = (end-start)/1e9;
        System.out.printf("%d %f\n",MAX,tempo);
    }
}
