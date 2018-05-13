#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

int num_char(vector <string> palavras) {
    int cont = 0, j = 0;
    for (int i = 0; i < palavras.size(); ++i){
        for (j = 0; j < palavras[i].size(); ++j)
        cont +=j;
    }
    return cont;
}

int main()
{
    int num_bites = 0;
    cout << "Digite o numero de bits que voce deseja ter em memoria" << endl;
    cin >> num_bites;
    
    
    ifstream arqEntrada ("entrada1.txt");

    if (!arqEntrada.is_open()){
        cout << "Erro ao ler o Arquivo" << endl;
    }
    else {

        string str;
        vector <string> palavras;
        bool continuar = true;
        int num_arq = 0;
        char saida;

        // separa os blocos em arquivos
        while (!arqEntrada.eof()) {
            arqEntrada >> saida >> noskipws;

            // separa em palavras
            while (((tolower(saida) >= 'a' && tolower(saida) <= 'z') || (saida >= '0' && saida <= '9')) && continuar) {
                str.push_back(saida);
                arqEntrada >> saida >> noskipws;
                if(str.size() >= num_bites) {
                    str.clear();
                    continuar = false;
                }
            }

            if (continuar && str.size() > 0){
                if (str.size() + num_char(palavras) > num_bites){
                    //cria um arquivo
                    num_arq+=1;
                    string aux = "Temp";
                    aux += to_string(num_arq);
                    aux += ".txt";
                    ofstream mandar (aux);

                    //manda para um arquivo as palavras
                    sort(palavras.begin(), palavras.end());
                    for (int i = 0; i < palavras.size(); ++i) 
                        mandar << palavras[i];
                    mandar.close();

                    //apaganos as palavras
                    palavras.clear();

                    //alimentamos o vector de palavras
                    if(str.size() < num_bites-1)
                        str.push_back(' ');
                    palavras.push_back(str);
                    str.clear();
                }
                else if (str.size() + num_char(palavras) == num_bites){
                    //cria um arquivo
                    num_arq+=1;
                    string aux = "Temp";
                    aux += to_string(num_arq);
                    aux += ".txt";
                    ofstream mandar (aux);

                    //alimentamos o vector de palavras
                    if(str.size() < num_bites-1)
                        str.push_back(' ');
                    palavras.push_back(str);
                    str.clear();

                    //manda para um arquivo as palavras
                    sort(palavras.begin(), palavras.end());
                    for (int i = 0; i < palavras.size(); ++i)
                        mandar << palavras[i];
                    mandar.close();

                    //apaganos as palavras
                    palavras.clear();
                }
                else {
                    //alimentamos o vector de palavras
                    if(str.size() < num_bites-1)
                        str.push_back(' ');
                    palavras.push_back(str);
                    str.clear();
                }
            }
            continuar = true;
        }
    }



    arqEntrada.close();

    return 0;
}

// remove("arquivo.txt");
// criar uma string onde concatena os nomes