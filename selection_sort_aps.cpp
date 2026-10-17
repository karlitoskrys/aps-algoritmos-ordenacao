
#include <iostream>
#include <vector>
// Permite criar um vetor que pode aumentar ou diminuir de tamanho durante a execução
#include <fstream>
// Permite trabalhar com arquivos .txt, .csv e outros
#include <sstream>
// Permite tratar uma sting como um fluxo de dados, facilitando a separação e conversão de informações
#include <string>
#include <chrono>
// Serve para medicao de tempo
#include <iomanip>
// Permite controlar a apresentação de números e textos na tela
#include <algorithm>
// Oferece funções para ordenar, pesquisar, comparar e maniplar dados
#include <random>
// geração de numeros aleatorios

using namespace std;

// Dados aleatorios
struct DadoAleatorio {
    int id;
    double latitude;
    double longitude;
    int altitude;
    int nuvens;
    int tamanho;
};

// Dados reais do INPE
struct DadoReal {
    string area;
    string ano;
    string data;
    string satelite;
    int scene_id;
    string estado;
    string longitude;
    string latitude;
};

// Le os dados aleatorios
vector<DadoAleatorio> lerAleatorios() {
    vector<DadoAleatorio> dados;
    ifstream arquivo("metadados.txt");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir metadados.txt" << endl;
        return dados;
    }

    DadoAleatorio registro;

    while (arquivo >> registro.id
                   >> registro.latitude
                   >> registro.longitude
                   >> registro.altitude
                   >> registro.nuvens
                   >> registro.tamanho) {
        dados.push_back(registro);
    }

    return dados;
}

// Le os dados reais do INPE
vector<DadoReal> lerReais() {
    vector<DadoReal> dados;
    ifstream arquivo("dados_inpe_corrigidos_500000.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir dados_inpe_corrigidos_500000.csv" << endl;
        return dados;
    }

    string linha;
    getline(arquivo, linha); // Pula o cabecalho

    int ignorados = 0;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        DadoReal registro;
        string identificador;

        getline(ss, registro.area, ';');
        getline(ss, registro.ano, ';');
        getline(ss, registro.data, ';');
        getline(ss, registro.satelite, ';');
        getline(ss, identificador, ';');
        getline(ss, registro.estado, ';');
        getline(ss, registro.longitude, ';');
        getline(ss, registro.latitude, ';');

        // Converte o scene_id para numero
        try {
            size_t posicao = 0;
            long valor = stol(identificador, &posicao);

            if (posicao != identificador.size() ||
                valor < 0 || valor > 2147483647L) {
                ignorados++;
                continue;
            }

            registro.scene_id = (int)valor;
        }
        catch (...) {
            ignorados++;
            continue;
        }

        dados.push_back(registro);
    }

    cout << "Registros reais lidos: "
         << dados.size() << endl;

    if (ignorados > 0) {
        cout << "Registros ignorados: "
             << ignorados << endl;
    }

    return dados;
}

// Selection Sort dos dados aleatorios pelo tamanho
void selectionAleatorio(vector<DadoAleatorio>& dados) {
    int tamanho = dados.size();

    for (int i = 0; i < tamanho - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < tamanho; j++) {
            if (dados[j].tamanho < dados[menor].tamanho) {
                menor = j;
            }
        }

        if (menor != i) {
            DadoAleatorio temp = dados[i];
            dados[i] = dados[menor];
            dados[menor] = temp;
        }
    }
}

// Selection Sort dos dados reais pelo scene_id numerico
void selectionReal(vector<DadoReal>& dados) {
    int tamanho = dados.size();

    for (int i = 0; i < tamanho - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < tamanho; j++) {
            if (dados[j].scene_id < dados[menor].scene_id) {
                menor = j;
            }
        }

        if (menor != i) {
            DadoReal temp = dados[i];
            dados[i] = dados[menor];
            dados[menor] = temp;
        }
    }
}

// Mostra um registro aleatorio
void mostrarAleatorio(const DadoAleatorio& d) {
    cout << d.id << " ; "
         << d.latitude << " ; "
         << d.longitude << " ; "
         << d.altitude << " ; "
         << d.nuvens << " ; "
         << d.tamanho << endl;
}

// Mostra um registro real
void mostrarReal(const DadoReal& d) {
    cout << d.area << " ; "
         << d.ano << " ; "
         << d.data << " ; "
         << d.satelite << " ; "
         << d.scene_id << " ; "
         << d.estado << " ; "
         << d.longitude << " ; "
         << d.latitude << endl;
}

// Prepara os dados e mede o tempo do Selection Sort
template <typename T, typename Comparar>
void executarTeste(
    vector<T> dados,
    int situacao,
    void (*ordenar)(vector<T>&),
    void (*mostrar)(const T&),
    Comparar comparar
) {
    mt19937 gerador(42);

    // Coloca os dados inicialmente em ordem
    sort(dados.begin(), dados.end(), comparar);

    if (situacao == 2) {
        // Primeira metade embaralhada e segunda ordenada
        shuffle(
            dados.begin(),
            dados.begin() + dados.size() / 2,
            gerador
        );
    }

    if (situacao == 3) {
        // Todos os registros embaralhados
        shuffle(dados.begin(), dados.end(), gerador);
    }

    cout << "\nAMOSTRA ANTES DA ORDENACAO:\n";

    if (situacao == 2) {
        cout << "\n5 LINHAS DESORDENADAS:\n";

        for (int i = 0; i < 5; i++) {
            mostrar(dados[i]);
        }

        cout << "\n5 LINHAS ORDENADAS:\n";

        int metade = dados.size() / 2;

        for (int i = metade; i < metade + 5; i++) {
            mostrar(dados[i]);
        }

    } else {
        for (int i = 0; i < 10; i++) {
            mostrar(dados[i]);
        }
    }

    cout << "\nIniciando Selection Sort...\n";

    // Inicia a contagem do tempo
    auto inicio = chrono::steady_clock::now();

    ordenar(dados);

    // Finaliza a contagem do tempo
    auto fim = chrono::steady_clock::now();

    chrono::duration<double> tempo = fim - inicio;

    cout << "\nTEMPO DE ORDENACAO: "
         << tempo.count() << " segundos\n";

    cout << "\n10 LINHAS APOS A ORDENACAO:\n";

    for (int i = 0; i < 10; i++) {
        mostrar(dados[i]);
    }

    // Verifica se os dados ficaram ordenados
    bool correto = is_sorted(
        dados.begin(),
        dados.end(),
        comparar
    );

    cout << "\nOrdenacao correta: "
         << (correto ? "SIM" : "NAO") << endl;
}

int main() {
    cout << fixed << setprecision(3);

    int opcao;
    int quantidade;
    int situacao;

    cout << "SELECTION SORT - APS\n";
    cout << "1 - Dados aleatorios\n";
    cout << "2 - Dados reais do INPE\n";
    cout << "Escolha: ";
    cin >> opcao;

    cout << "\nQuantidade de registros:\n";
    cout << "1 - 250000\n";
    cout << "2 - 500000\n";
    cout << "Escolha: ";

    int escolhaQuantidade;
    cin >> escolhaQuantidade;

    if (escolhaQuantidade == 1) {
        quantidade = 250000;
    }
    else if (escolhaQuantidade == 2) {
        quantidade = 500000;
    }
    else {
        cout << "Quantidade invalida!\n";
        return 1;
    }

    cout << "\nSituacao dos dados:\n";
    cout << "1 - Ordenados\n";
    cout << "2 - Semiordenados\n";
    cout << "3 - Desordenados\n";
    cout << "Escolha: ";
    cin >> situacao;

    if (situacao < 1 || situacao > 3) {
        cout << "Situacao invalida!\n";
        return 1;
    }

    if (opcao == 1) {
        vector<DadoAleatorio> dados = lerAleatorios();

        if ((int)dados.size() < quantidade) {
            cout << "Registros insuficientes em metadados.txt.\n";
            cout << "Disponiveis: " << dados.size() << endl;
            return 1;
        }

        dados.resize(quantidade);

        executarTeste(
            dados,
            situacao,
            selectionAleatorio,
            mostrarAleatorio,
            [](const DadoAleatorio& a,
               const DadoAleatorio& b) {
                return a.tamanho < b.tamanho;
            }
        );

    }
    else if (opcao == 2) {
        vector<DadoReal> dados = lerReais();

        if ((int)dados.size() < quantidade) {
            cout << "Registros insuficientes no CSV.\n";
            cout << "Disponiveis: " << dados.size() << endl;
            return 1;
        }

        dados.resize(quantidade);

        executarTeste(
            dados,
            situacao,
            selectionReal,
            mostrarReal,
            [](const DadoReal& a,
               const DadoReal& b) {
                return a.scene_id < b.scene_id;
            }
        );

    }
    else {
        cout << "Opcao invalida!\n";
        return 1;
    }

    return 0;
}
