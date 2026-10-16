
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {

    const int quantidade = 500000;

    // Cria o arquivo de metadados
    ofstream arquivo("metadados.txt");

    if (!arquivo.is_open()) {
        cout << "Erro ao criar o arquivo!" << endl;
        return 1;
    }

    // Inicia a geracao de numeros aleatorios
    srand(time(NULL));

    // Gera os 50 mil registros
    for (int i = 0; i < quantidade; i++) {

        // Gera o ID
        int algInicio = (rand() % 9) + 1;
        int algMeio1 = rand() % 100;
        int algMeio2 = rand() % 100;
        int algFim = rand() % 10;

        int id = (algInicio * 100000)
               + (algMeio1 * 1000)
               + (algMeio2 * 10)
               + algFim;

        // Gera os outros metadados
        double latitude = -90.0 + (rand() % 18000) / 100.0;
        double longitude = -180.0 + (rand() % 36000) / 100.0;

        int altitude = rand() % 501 + 500;
        int nuvens = rand() % 101;
        int tamanho = rand() % 5000 + 1;

        // Salva os dados no arquivo
        arquivo << id << " "
                << latitude << " "
                << longitude << " "
                << altitude << " "
                << nuvens << " "
                << tamanho << endl;
    }

    arquivo.close();

    cout << "Arquivo criado com sucesso!" << endl;
    cout << quantidade << " registros foram gerados." << endl;

    return 0;
}
