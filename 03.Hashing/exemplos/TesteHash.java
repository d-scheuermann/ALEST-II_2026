import java.util.HashMap;
import java.util.Map;

public class TesteHash {
    public static void main(String[] args) {

        Map<String, Integer> dic = new HashMap<>();
        // Problema da implementação padrão de
        // hashCode: retorna um endereço de memória
        // do objeto, que não tem relação com o 
        // CONTEÚDO do objeto
        Object x = new Object();
        Object y = new Object();

        // Observe que os dois objetos são IGUAIS,
        // mas os hashCode são diferentes!
        System.out.println("x: "+x.hashCode());
        System.out.println("y: "+y.hashCode());

        // Isso não acontece com strings, por exemplo
        System.out.println("Fulano".hashCode());        
        System.out.println("Ana".hashCode());        
        System.out.println("José".hashCode());        
        System.out.println("ABC: "+"ABC".hashCode());
        System.out.println("BAC: "+"BAC".hashCode());

        // Dicionário de strings -> inteiros
        dic.put("Fulano", 12);
        dic.put("Ana", 56);
        dic.put("José", 78);
    }
}
