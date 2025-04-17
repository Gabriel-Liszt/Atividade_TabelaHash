#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Objeto a ser armazenado
struct Objeto {
    int chave;
    string dado;

    Objeto(int c, string d) : chave(c), dado(d) {}
};

// Função hash 1 - para o primeiro nível
int hash1(int chave) {
    return chave % 10;
}

// Função hash 2 - para o segundo nível
int hash2(int chave, int tamanho_segundo_nivel) {
    return (chave / 10) % tamanho_segundo_nivel;
}

class HashDuplo {
private:
    int n;
    int tamanho_segundo_nivel;
    // Primeiro nível: vetor de 10 ponteiros para vetores
    vector<vector<list<Objeto>>> tabela;

public:
    HashDuplo(int total_objetos) : n(total_objetos) {
        tamanho_segundo_nivel = n / 10;
        tabela.resize(10);

        // Inicializa os vetores do segundo nível
        for (int i = 0; i < 10; i++) {
            tabela[i].resize(tamanho_segundo_nivel);
        }
    }

    void inserir(int chave, string dado) {
        int idx1 = hash1(chave); // nível 1
        int idx2 = hash2(chave, tamanho_segundo_nivel); // nível 2

        // Verifica se já existe
        for (const auto& obj : tabela[idx1][idx2]) {
            if (obj.chave == chave) {
                cout << "Chave " << chave << " já cadastrada.\n";
                return;
            }
        }

        tabela[idx1][idx2].push_back(Objeto(chave, dado));
        cout << "Inserido com sucesso: chave = " << chave << ", dado = " << dado << endl;
    }

    Objeto* buscar(int chave) {
        int idx1 = hash1(chave);
        int idx2 = hash2(chave, tamanho_segundo_nivel);

        for (auto& obj : tabela[idx1][idx2]) {
            if (obj.chave == chave) {
                return &obj;
            }
        }
        return nullptr;
    }
};
