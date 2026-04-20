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

class Reinflador {
private:
    std::unordered_map<char, std::string> regras;
    
    std::unordered_map<char, unsigned long long> memo;
    
    std::set<char> lhs_nodes;
    std::set<char> rhs_nodes;

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
            
            if (!(line_stream >> lhs_char)) continue;

            std::string rhs_part;
            std::getline(line_stream, rhs_part);
            
            limpar_string(rhs_part);

            regras[lhs_char] = rhs_part;
            lhs_nodes.insert(lhs_char);

            if (!rhs_part.empty()) {
                for (char c : rhs_part) {
                    rhs_nodes.insert(c);
                }
            }
        }
    }

    char identificar_raiz() {
        for (char c : lhs_nodes) {
            if (rhs_nodes.find(c) == rhs_nodes.end()) {
                return c;
            }
        }
        return '\0';
    }

    unsigned long long calcular_tamanho_expandido(char c) {
        if (memo.count(c)) {
            return memo[c];
        }

        if (regras.find(c) == regras.end() || regras[c].empty()) {
            return memo[c] = 1;
        }

        unsigned long long total = 0;
        for (char filho : regras[c]) {
            total += calcular_tamanho_expandido(filho);
        }

        return memo[c] = total;
    }
};

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
        unsigned long long resultado = reinflador.calcular_tamanho_expandido(raiz);
        std::cout << caminho_arquivo << "\n";
        std::cout << "'" << raiz << "': " << resultado << "\n";
        std::cout << "=============" << std::endl;
    }
 else {
        std::cout << caminho_arquivo << "\n" << "Sem raiz identificável.\n=============" << std::endl;
    }
}

int main() {
    Reinflador reinflador;
    
    std::string pasta_de_testes = "casos_11";

    try {
        if (fs::exists(pasta_de_testes) && fs::is_directory(pasta_de_testes)) {
            
            for (const auto& entrada : fs::directory_iterator(pasta_de_testes)) {
                if (entrada.path().extension() == ".txt") {
                    processar_arquivo_teste(entrada.path().string(), reinflador);
                }
            }
        } else {
            std::cerr << "Diretório '" << pasta_de_testes << "' não encontrado." << std::endl;
        }
    } catch (const std::set<char, std::allocator<char>>& e) {
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}