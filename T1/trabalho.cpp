# include <iostream>
#include<fstream>

using namespace std;

int main()
{
    ifstream leitorArquivo;

    leitorArquivo.open("entrada1.txt");

    if (!leitorArquivo.is_open()){
        cout << "Erro ao ler o Arquivo" << endl;
    }

    char saida;

    if (leitorArquivo.is_open()) {
        while (!leitorArquivo.eof()) {
            leitorArquivo >> saida >> noskipws;
            cout << saida;
        }
    }

    leitorArquivo.close();

    return 0;
}