
import java.util.Scanner;

public class HeapTest {

  public static void main( String[] args ) {
    MaxHeap<Integer> H = new MaxHeap<Integer>(100);

    System.out.println("Digite um numero para inserir na fila, get para retirar o primeiro elemento ou quit para sair");
    try (Scanner input = new Scanner( System.in )) {
      // 3 entradas possiveis:
      //
      // numero: coloca o numero na fila
      // quit: sai
      // get: retira elemento do inicio da fila
      //
      while ( input.hasNext() ) {
        String temp = input.next();

        if ( temp.equals( "quit" ) ) System.exit(0);
        if ( temp.equals( "get" ) )  System.out.println( H.get() );
        if ( temp.matches( "[0-9]+" ) ) H.put( Integer.parseInt( temp ) );

        H.print();
      }
    } catch (NumberFormatException e) {
      e.printStackTrace();
    }
  }
}
