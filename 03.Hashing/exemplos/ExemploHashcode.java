public class ExemploHashcode
{
    public static void main(String[] args) {
        double v = 0.0;
        System.out.println("Double:");
        for(int i=0; i<10; i++) {
            System.out.println(v+" -> "+new Double(v).hashCode());
            v += 1;
        }
        System.out.println(1.1+" -> "+new Double(1.1).hashCode());
        System.out.println();
        String a = "Algoritmo";
        System.out.println(a + " -> "+a.hashCode());
        a = a + "s";
        System.out.println(a + " -> "+a.hashCode());
    }
}

