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

class Reinflador {
private:
    std::unordered_map<char, std::string> regras;

    std::unordered_map<char, unsigned long long> tamanho;

    std::unordered_map<char, bool> existe;

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

    char identificar_raiz() {
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
        for (char letra = 'a'; letra <= 'z'; letra++) {
            if (existe.count(letra) && cont_inicial.count(letra) && cont_inicial[letra] == 0) {
                return letra;
            }
        }
        return '\0';
    }

    unsigned long long calcular_com_fila(char raiz) {
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

        std::queue<char> fila;
        for (auto& [letra, dep] : dependencias) {
            if (dep == 0) {
                fila.push(letra);
            }
        }

        while (!fila.empty()) {
            char atual = fila.front();
            fila.pop();

            unsigned long long soma = 0;
            for (char filho : regras[atual]) {
                if (existe.count(filho)) {
                    soma += tamanho[filho];
                } else {
                    soma += 1;
                }
            }
            tamanho[atual] = (regras[atual].empty()) ? 1 : soma;

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