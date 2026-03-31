public class AppCompara {
   public static void main(String[] args) {

    In arq = new In("DomCasmurro_utf8.txt");
    SeparateChainingHashST<String, Integer> dic = new SeparateChainingHashST<>();
    //LinearProbingHashST<String, Integer> dic = new LinearProbingHashST<>();

    long inicial = System.nanoTime();
    while(arq.hasNextLine()) {
        String linha = arq.readLine();
        for(String pal: linha.split(" ")) {
            pal = pal.toLowerCase();
            //System.out.println(pal);
            if(!dic.containsKey(pal)) {
                dic.put(pal, 1); // primeira vez
            }
            else {
                int freq = dic.get(pal);
                dic.put(pal, freq+1); // conta mais uma ocorrência
            }
        }
    }
    long fim = System.nanoTime();
    double tempo = (fim - inicial)/1e9;
    System.out.println("Total de palavras: "+dic.size());
    String[] palavras = new String[dic.size()];
    int cont = 0;
    for(String pal: dic.keySet()) {
        System.out.println(pal + " -> " + dic.get(pal));
        palavras[cont] = pal;
        cont++;
    }
    System.out.println("Tempo para criação: "+tempo+" s");
    // Repetir muitas vezes (1 milhão ou mais):
    // - Sortear uma posição no vetor (0...tamanho-1)
    // - Faz get daquela palavra
   } 
}