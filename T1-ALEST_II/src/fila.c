#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char regra[1025];    
    long long tamanho;  
    int existe;          
    int cont_inicial;    
} Alfabeto;

Alfabeto lista[26];

void iniciar() {
    for(int i = 0; i < 26; i++) {
        lista[i].tamanho = 0;
        lista[i].existe = 0;
        lista[i].cont_inicial = 0;
        strcpy(lista[i].regra, "");
    }
}


void ler_regras(FILE *f) {
    char linha[2048];
    

    while (fgets(linha, sizeof(linha), f)) {
        char origem;
        char destino[1025] = ""; 
        

        int lidos = sscanf(linha, " %c %1024s", &origem, destino);


        if (lidos == 2) {
            int idx = origem - 'a';
            if (idx >= 0 && idx < 26) {
                lista[idx].existe = 1;
                strcpy(lista[idx].regra, destino);

                for (int i = 0; destino[i] != '\0'; i++) {
                    int filho = destino[i] - 'a';
                    if (filho >= 0 && filho < 26) {
                        lista[filho].cont_inicial++;
                    }
                }
            }
        }
    }
}

int achar_letra_inicial() {
    for(int i = 0; i < 26; i++) {
        if(lista[i].existe && lista[i].cont_inicial == 0) {
            return i;
        }
    }
    return -1;
}

void solucao() {
    int fila[26], inicio = 0, fim = 0;
    int dependencias_reais[26] = {0};


    for(int i = 0; i < 26; i++) {
        if(lista[i].existe) {
            for(int j = 0; lista[i].regra[j] != '\0'; j++) {
                int filho = lista[i].regra[j] - 'a';
                if(filho >= 0 && filho < 26 && lista[filho].existe) {
                    dependencias_reais[i]++;
                }
            }
        }
    }


    for(int i = 0; i < 26; i++) {
        if(lista[i].existe && dependencias_reais[i] == 0) {
            fila[fim++] = i;
        }
    }


    while(inicio < fim) {
        int atual = fila[inicio++];
        long long soma = 0;

        for(int j = 0; lista[atual].regra[j] != '\0'; j++) {
            int filho = lista[atual].regra[j] - 'a';
            if(filho >= 0 && filho < 26 && lista[filho].existe) {
                soma += lista[filho].tamanho;
            } else {
                soma += 1;
            }
        }
        lista[atual].tamanho = soma;


        for(int pai = 0; pai < 26; pai++) {
            if(lista[pai].existe) {
                for(int k = 0; lista[pai].regra[k] != '\0'; k++) {
                    if(lista[pai].regra[k] == (atual + 'a')) {
                        dependencias_reais[pai]--;
                        if(dependencias_reais[pai] == 0) {
                            fila[fim++] = pai;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    char *arquivos[] = {"t11_01.txt", "t11_02.txt", "t11_03.txt", "t11_04.txt", "t11_05.txt", 
                        "t11_06.txt", "t11_07.txt", "t11_08.txt", "t11_09.txt", "t11_10.txt"};
    
    for (int i = 0; i < 10; i++) {
        iniciar();
        FILE *f = NULL;
        char caminho[200];
        
        
        char *tentativas[] = {
            "%s",                    
            "src/%s",                 
            "T1-ALEST_II/src/%s",     
            "casos_11/%s"             
        };

        for (int j = 0; j < 4; j++) {
            sprintf(caminho, tentativas[j], arquivos[i]);
            f = fopen(caminho, "r");
            if (f != NULL) break; 
        }

        if (f == NULL) {
            printf("Erro: Nao achei o arquivo %s nas pastas.\n", arquivos[i]);
            continue; 
        }

        ler_regras(f);
        solucao();

        int inicial = achar_letra_inicial();
        if (inicial != -1) {
            printf("casos_11/%s\n", arquivos[i]);
            printf("'%c': %lld\n", inicial + 'a', lista[inicial].tamanho);
            printf("==============\n");
        }
        fclose(f);
    }
    return 0;
}