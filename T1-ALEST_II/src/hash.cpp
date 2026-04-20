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
você já tem a tabela de substituições para cada letrinha. Por exemplo, a letra “i” deve ser sempre
transformada em “mooo” (devido a uma limitação de software as substituições associadas a cada
letrinha tem no máximo 1024 caracteres). Agora você precisa:
1. Determinar a letra inicial que dá origem a todo o arquivo a ser reinflado. Neste exemplo a
letra inicial é “a” mas poderia ser qualquer outra letra. Identificá-la faz parte do problema
(seus amigos da rede social acham que é impossível).
2. Informar quantas letras terá o arquivo final reinflado. Neste exemplo, teremos um arquivo
final com 47 caracteres, que conteria o texto abaixo:
mmmooomommmooommooommooommooomommmooommooommooo
Agora você deve processar várias entradas disponibilizadas na página da disciplina e dizer, para
cada uma delas, qual o tamanho final do arquivo reinflado.*/

//implementar estrutura hash de dados para o reinflador que pegue os arquivos txt e os armazene em uma tabela hash, onde a chave seja o nome do arquivo e o valor seja o conteúdo do arquivo. A estrutura deve permitir a inserção, remoção e busca de arquivos de forma eficiente.

//RESULTADOS:
/* casos_11/t11_01.txt
'g': 207760
=============
casos_11/t11_02.txt
'g': 100897558
=============
casos_11/t11_03.txt
'g': 5973056973
=============
casos_11/t11_04.txt
'g': 25570697376
=============
casos_11/t11_05.txt
'g': 732053647169
=============
casos_11/t11_06.txt
'g': 3212546228360
=============
casos_11/t11_07.txt
'g': 17970337196998
=============
casos_11/t11_08.txt
'g': 129580201445915
=============
casos_11/t11_09.txt
'g': 653129623073193
=============
casos_11/t11_10.txt
'g': 7204742496512011
=============*/

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
#include <unordered_map>
#include <set>
#include <filesystem>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

/**
 * Classe responsável pela lógica do Reinflador Quântico.
 * Utiliza Programação Dinâmica (Memoização) para calcular o tamanho final.
 */
class Reinflador {
private:
    // Mapeia uma letra para sua sequência de substituição
    std::unordered_map<char, std::string> regras;
    
    // Memoização: armazena o tamanho já calculado de cada letra para evitar recursão infinita/repetitiva
    std::unordered_map<char, unsigned long long> memo;
    
    // Conjuntos para identificar a letra raiz (LHS: quem expande, RHS: quem é expandido)
    std::set<char> lhs_nodes;
    std::set<char> rhs_nodes;

    // Função auxiliar para limpar espaços e caracteres de controle (\r, \n) de strings
    void limpar_string(std::string& s) {
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        // Remove espaços em branco no início e no fim
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
     * Processa o conteúdo bruto de um arquivo de texto e constrói a tabela de substituições.
     */
    void carregar_conteudo(const std::string& conteudo) {
        regras.clear();
        memo.clear();
        lhs_nodes.clear();
        rhs_nodes.clear();

        std::stringstream ss(conteudo);
        std::string linha;

        while (std::getline(ss, linha)) {
            if (linha.empty() || linha == "\r") continue;

            std::stringstream line_stream(linha);
            char lhs_char;
            
            // Tenta ler o primeiro caractere (a letra que expande)
            if (!(line_stream >> lhs_char)) continue;

            // O resto da linha é a expansão
            std::string rhs_part;
            std::getline(line_stream, rhs_part);
            
            limpar_string(rhs_part);

            // Registra a regra
            regras[lhs_char] = rhs_part;
            lhs_nodes.insert(lhs_char);

            // Se houver expansão, registra os dependentes
            if (!rhs_part.empty()) {
                for (char c : rhs_part) {
                    rhs_nodes.insert(c);
                }
            }
        }
    }

    /**
     * Identifica a letra inicial (raiz). 
     * É a letra que está no LHS mas nunca aparece no RHS de nenhuma regra.
     */
    char identificar_raiz() {
        for (char c : lhs_nodes) {
            if (rhs_nodes.find(c) == rhs_nodes.end()) {
                return c;
            }
        }
        return '\0';
    }

    /**
     * Função recursiva com memoização para calcular o tamanho final da expansão.
     */
    unsigned long long calcular_tamanho_expandido(char c) {
        // 1. Se já calculamos este caractere, retorna o valor salvo
        if (memo.count(c)) {
            return memo[c];
        }

        // 2. Se o caractere não possui regra ou a regra é uma string vazia,
        // ele é um terminal (tamanho 1). Isso evita o erro de retornar 0.
        if (regras.find(c) == regras.end() || regras[c].empty()) {
            return memo[c] = 1;
        }

        // 3. Se possui regra, o tamanho é a soma dos tamanhos de cada letra da sequência
        unsigned long long total = 0;
        for (char filho : regras[c]) {
            total += calcular_tamanho_expandido(filho);
        }

        return memo[c] = total;
    }
};

/**
 * Função que abre um arquivo, lê seu conteúdo e comanda o processo de expansão.
 */
void processar_arquivo_teste(const std::string& caminho_arquivo, Reinflador& reinflador) {
    std::ifstream arquivo(caminho_arquivo);
    if (!arquivo.is_open()) {
        return;
    }

    // Lê todo o conteúdo do arquivo para uma string de forma segura
    std::string conteudo;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        conteudo += linha + "\n";
    }
    arquivo.close();

    reinflador.carregar_conteudo(conteudo);
    char raiz = reinflador.identificar_raiz();

    if (raiz != '\0') {
        unsigned long long resultado = reinflador.calcular_tamanho_expandido(raiz);
        std::cout << caminho_arquivo << "\n";
        std::cout << "'" << raiz << "': " << resultado << "\n";
        std::cout << "=============" << std::endl;
    }
 else {
        // Se não encontrar raiz, mas o arquivo tem conteúdo, imprimimos o arquivo
        std::cout << caminho_arquivo << "\n" << "Sem raiz identificável.\n=============" << std::endl;
    }
}

int main() {
    Reinflador reinflador;
    
    // Caminho para a pasta de testes (relativo ao local de execução)
    std::string pasta_de_testes = "casos_11";

    try {
        if (fs::exists(pasta_de_testes) && fs::is_directory(pasta_de_testes)) {
            
            // Itera por todos os arquivos dentro da pasta casos_11
            for (const auto& entrada : fs::directory_iterator(pasta_de_testes)) {
                // Processa apenas arquivos .txt
                if (entrada.path().extension() == ".txt") {
                    processar_arquivo_teste(entrada.path().string(), reinflador);
                }
            }
        } else {
            std::cerr << "Diretório '" << pasta_de_testes << "' não encontrado." << std::endl;
        }
    } catch (const std::set<char, std::allocator<char>>& e) {
        // Erros de permissão ou de sistema de arquivos
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}