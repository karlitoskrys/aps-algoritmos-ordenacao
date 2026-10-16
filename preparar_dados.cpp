#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Selection Sort
void selectionSort(vector<int>& dados) {

    int tamanho = dados.size();

    for (int i = 0; i < tamanho - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < tamanho; j++) {

            if (dados[j] < dados[menor]) {
                menor = j;
            }
        }

        if (menor != i) {

            int temp = dados[i];
            dados[i] = dados[menor];
            dados[menor] = temp;
        }
    }
}


// Le os dados do arquivo original
vector<int> lerDados() {

    vector<int> dados;

    ifstream arquivo("dados.txt");

    int numero;

    while (arquivo >> numero) {
        dados.push_back(numero);
    }

    arquivo.close();

    return dados;
}


// Salva os dados em um arquivo
void salvarDados(string nomeArquivo, vector<int> dados) {

    ofstream arquivo(nomeArquivo);

    for (int i = 0; i < dados.size(); i++) {
        arquivo << dados[i] << endl;
    }

    arquivo.close();
}


int main() {

    vector<int> dados = lerDados();

    cout << "Dados lidos: " << dados.size() << endl;


    // DADOS ORDENADOS

    vector<int> ordenados = dados;

    selectionSort(ordenados);

    salvarDados("dados_ordenados.txt", ordenados);

    cout << "dados_ordenados.txt criado!" << endl;


    // DADOS SEMIORDENADOS

    vector<int> semiordenados = dados;

    int metade = semiordenados.size() / 2;

    vector<int> primeiraMetade;

    for (int i = 0; i < metade; i++) {
        primeiraMetade.push_back(semiordenados[i]);
    }

    selectionSort(primeiraMetade);

    for (int i = 0; i < metade; i++) {
        semiordenados[i] = primeiraMetade[i];
    }

    salvarDados("dados_semiordenados.txt", semiordenados);

    cout << "dados_semiordenados.txt criado!" << endl;


    return 0;
}