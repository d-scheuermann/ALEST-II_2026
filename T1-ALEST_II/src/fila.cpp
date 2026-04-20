/*O reinflador quântico redundante
Você está irritado com toda essa tecnologia para comprimir textos pois acha que os textos ficam
muito apertados e sofrem com isso. Por este motivo você resolveu fazer um reinflador ! Seu reinflador funciona baseado nas letrinhas minúsculas do alfabeto e cada letrinha deve ser transformada
em uma nova sequencia de letrinhas e cada uma destas em mais uma sequencia, e assim por diante
até nada mais poder ser transformado. Desse jeito, uma entrada bem pequena pode se transformar
em algo gigantesco! Um exemplo bem simples está abaixo: ao receber a entrada
a memimomu
e mimomu
i mooo
u mimimi
o // Opcional! Podia não estar aqui!
m // Opcional! Podia não estar aqui!
você já tem a tabela de substituições para cada letrinha. Por exemplo, a letra "i" deve ser sempre
transformada em "mooo" (devido a uma limitação de software as substituições associadas a cada
letrinha tem no máximo 1024 caracteres). Agora você precisa:
1. Determinar a letra inicial que dá origem a todo o arquivo a ser reinflado. Neste exemplo a
letra inicial é "a" mas poderia ser qualquer outra letra. Identificá-la faz parte do problema
(seus amigos da rede social acham que é impossível).
2. Informar quantas letras terá o arquivo final reinflado. Neste exemplo, teremos um arquivo
final com 47 caracteres, que conteria o texto abaixo:
mmmooomommmooommooommooommooomommmooommooommooo
Agora você deve processar várias entradas disponibilizadas na página da disciplina e dizer, para
cada uma delas, qual o tamanho final do arquivo reinflado.*/

// Implementação usando Fila (BFS / Ordenação Topológica de Kahn) para calcular
// o tamanho final do arquivo reinflado, processando as letras em ordem de dependência.

//RESULTADOS:
/* casos_11/t11_01.txt
'g': 207760
==============
casos_11/t11_02.txt
'g': 100897558
==============
casos_11/t11_03.txt
'g': 5973056973
==============
casos_11/t11_04.txt
'g': 25570697376
==============
casos_11/t11_05.txt
'g': 732053647169
==============
casos_11/t11_06.txt
'g': 3212546228360
==============
casos_11/t11_07.txt
'g': 17970337196998
==============
casos_11/t11_08.txt
'g': 129580201445915
==============
casos_11/t11_09.txt
'g': 653129623073193
==============
casos_11/t11_10.txt
'g': 7204742496512011
==============*/

/* Exemplo do conteudo em casos_11/t11_01.txt que precisa ser processado:
v jiiibjeibaiiwjbjjqaaebm
b fmamafm
w cic
c ffef
x effe
d iaaaix
y fqffff
e 
z 
f 
g pmwvqiqiwpnmmnjjaamuam
h 
i xqeqcex
j adeeeiyaqaiciaaqc
k 
l 
m ffeiaaeae
n ybtmabmqbaqijqiraxaxyyxjxx
o 
p jjatafatyf
q cffccccf
r vaxjmtxaavaawm
s 
t dd
u jfppxxxpfjff
a qqiqqi
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <filesystem>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

/**
 * Classe responsável pela lógica do Reinflador Quântico.
 * Utiliza Ordenação Topológica com Fila (algoritmo de Kahn) para calcular
 * o tamanho final sem recursão, processando cada letra apenas quando todas
 * as suas dependências já foram resolvidas.
 */
class Reinflador {
private:
    // Mapeia cada letra para sua sequência de substituição
    std::unordered_map<char, std::string> regras;

    // Tamanho calculado de cada letra após a expansão completa
    std::unordered_map<char, unsigned long long> tamanho;

    // Conjunto de letras que existem como LHS (definem uma regra)
    std::unordered_map<char, bool> existe;

    // Função auxiliar para limpar espaços e caracteres de controle (\r, \n)
    void limpar_string(std::string& s) {
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        size_t first = s.find_first_not_of(" \t");
        if (std::string::npos == first) {
            s = "";
            return;
        }
        size_t last = s.find_last_not_of(" \t");
        s = s.substr(first, (last - first + 1));
    }

public:
    /**
     * Processa o conteúdo bruto de um arquivo e constrói a tabela de substituições.
     */
    void carregar_conteudo(const std::string& conteudo) {
        regras.clear();
        tamanho.clear();
        existe.clear();

        std::stringstream ss(conteudo);
        std::string linha;

        while (std::getline(ss, linha)) {
            if (linha.empty() || linha == "\r") continue;

            std::stringstream line_stream(linha);
            char lhs_char;
            if (!(line_stream >> lhs_char)) continue;

            std::string rhs_part;
            std::getline(line_stream, rhs_part);
            limpar_string(rhs_part);

            regras[lhs_char] = rhs_part;
            existe[lhs_char] = true;
        }
    }

    /**
     * Identifica a letra raiz: está no LHS mas nunca aparece no RHS de nenhuma regra.
     */
    char identificar_raiz() {
        // Conta quantas vezes cada letra aparece como dependência (RHS)
        std::unordered_map<char, int> cont_inicial;
        for (auto& [letra, _] : existe) {
            cont_inicial[letra] = 0;
        }
        for (auto& [_, rhs] : regras) {
            for (char c : rhs) {
                if (existe.count(c)) {
                    cont_inicial[c]++;
                }
            }
        }
        // A raiz é a letra que existe mas nunca é dependência de outra.
        // Iterar em ordem alfabética (a-z) garante resultado determinístico.
        for (char letra = 'a'; letra <= 'z'; letra++) {
            if (existe.count(letra) && cont_inicial.count(letra) && cont_inicial[letra] == 0) {
                return letra;
            }
        }
        return '\0';
    }

    /**
     * Calcula o tamanho expandido de todas as letras usando ordenação topológica
     * com fila (algoritmo de Kahn). Processa letras sem dependências primeiro,
     * depois libera quem dependia delas — igual ao BFS clássico de grafo acíclico.
     */
    unsigned long long calcular_com_fila(char raiz) {
        // Calcula dependências reais (apenas letras que existem no LHS)
        std::unordered_map<char, int> dependencias;
        for (auto& [letra, _] : existe) {
            dependencias[letra] = 0;
        }
        for (auto& [letra, rhs] : regras) {
            if (!existe.count(letra)) continue;
            for (char c : rhs) {
                if (existe.count(c)) {
                    dependencias[letra]++;
                }
            }
        }

        // Enfileira todas as letras sem dependências (terminais)
        std::queue<char> fila;
        for (auto& [letra, dep] : dependencias) {
            if (dep == 0) {
                fila.push(letra);
            }
        }

        // Processa a fila: calcula tamanho de cada letra e libera seus pais
        while (!fila.empty()) {
            char atual = fila.front();
            fila.pop();

            // Calcula o tamanho desta letra somando os tamanhos de sua expansão
            unsigned long long soma = 0;
            for (char filho : regras[atual]) {
                if (existe.count(filho)) {
                    soma += tamanho[filho];
                } else {
                    soma += 1; // letra terminal sem regra conta como 1
                }
            }
            // Se a própria regra estava vazia, a letra é terminal (tamanho 1)
            tamanho[atual] = (regras[atual].empty()) ? 1 : soma;

            // Atualiza dependências dos pais e enfileira quem ficou livre.
            // Decrementa uma vez por CADA ocorrência de "atual" na regra do pai.
            for (auto& [pai, rhs] : regras) {
                if (!existe.count(pai)) continue;
                bool enfileirado = false;
                for (char c : rhs) {
                    if (c == atual) {
                        dependencias[pai]--;
                        if (dependencias[pai] == 0 && !enfileirado) {
                            fila.push(pai);
                            enfileirado = true;
                        }
                    }
                }
            }
        }

        return tamanho.count(raiz) ? tamanho[raiz] : 0;
    }
};

/**
 * Abre um arquivo, lê seu conteúdo e executa o processo de reinflação.
 */
void processar_arquivo_teste(const std::string& caminho_arquivo, Reinflador& reinflador) {
    std::ifstream arquivo(caminho_arquivo);
    if (!arquivo.is_open()) {
        return;
    }

    std::string conteudo;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        conteudo += linha + "\n";
    }
    arquivo.close();

    reinflador.carregar_conteudo(conteudo);
    char raiz = reinflador.identificar_raiz();

    if (raiz != '\0') {
        unsigned long long resultado = reinflador.calcular_com_fila(raiz);
        std::cout << caminho_arquivo << "\n";
        std::cout << "'" << raiz << "': " << resultado << "\n";
        std::cout << "==============" << std::endl;
    } else {
        std::cout << caminho_arquivo << "\n" << "Sem raiz identificável.\n==============" << std::endl;
    }
}

int main() {
    Reinflador reinflador;

    std::string pasta_de_testes = "casos_11";

    try {
        if (fs::exists(pasta_de_testes) && fs::is_directory(pasta_de_testes)) {
            // Coleta e ordena os arquivos para garantir ordem consistente
            std::vector<std::string> arquivos;
            for (const auto& entrada : fs::directory_iterator(pasta_de_testes)) {
                if (entrada.path().extension() == ".txt") {
                    arquivos.push_back(entrada.path().string());
                }
            }
            std::sort(arquivos.begin(), arquivos.end());

            for (const auto& caminho : arquivos) {
                processar_arquivo_teste(caminho, reinflador);
            }
        } else {
            std::cerr << "Diretório '" << pasta_de_testes << "' não encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
