# include <iostream>
#include<fstream>

using namespace std;

int main()
{
    ifstream leitorArquivo;

    leitorArquivo.open("entrada1.txt");

    char saida[100];

    if (leitorArquivo.is_open()) {
        while (!leitorArquivo.eof()) {
            leitorArquivo >> saida;
            cout << saida;
        }
    }
    leitorArquivo.close();
    return 0;
}