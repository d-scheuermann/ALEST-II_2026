#include <string>
#include <iostream>
#include "separatechaining_hashtable.h"
#include "linearprobing_hashtable.h"

using namespace std;

int main() {
    // Inicializa a tabela hash
    SeparateChainingHashTable<string, string> ht;
    //LinearProbingHashTable<string, string> ht;

    // Insere alguns itens chave-valor
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");

    // Recupera e exibe os valores
    cout << ht.get("key1") << endl;
    cout << ht.get("key2") << endl;
    cout << ht.get("key3") << endl;

    // Verifica se uma chave existe
    cout << ht.contains("key1") << endl;

    return 0;
}
