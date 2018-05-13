#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
 
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
        string palavras;
        bool continuar = true;
        int num_arq = 0;
        char saida;
 
        // separa os blocos em arquivos
        while (!arqEntrada.eof()) {
            arqEntrada >> saida >> noskipws;
 
            // separa em palavras
            while (saida >= '!' && saida <= '~' && continuar) {
                str.push_back(saida);
                arqEntrada >> saida >> noskipws;
                if(str.size() >= num_bites) {
                    str.clear();
                    continuar = false;
                }
            }
 
            if (continuar && str.size() > 0){
                if (str.size() + palavras.size() > num_bites){
                    //cria arq
                    num_arq+=1;
                    string aux = "Temp";
                    aux += to_string(num_arq);
                    aux += ".txt";
                    ofstream mandar (aux);
 
                    //manda palavras
                    mandar << palavras;
                    mandar.close();
 
                    //erase palavras
                    palavras.clear();
 
                    //insert
                    palavras.insert(palavras.end(), str.begin(), str.end());
                    if (palavras.size() < num_bites)
                        palavras.push_back(' ');
                    str.clear();
                }
                else if (str.size() + palavras.size() == num_bites){
                    //cria arq
                    num_arq+=1;
                    string aux = "Temp";
                    aux += to_string(num_arq);
                    aux += ".txt";
                    ofstream mandar (aux);
 
                    //insert
                    palavras.insert(palavras.end(), str.begin(), str.end());
                    if (palavras.size() < num_bites)
                        palavras.push_back(' ');
                    str.clear();
 
                    //manda palavras
                    mandar << palavras;
                    mandar.close();
 
                    //erase palavras
                    palavras.clear();
                }
                else {
                    //insert
                    palavras.insert(palavras.end(), str.begin(), str.end());
                    if (palavras.size() < num_bites)
                        palavras.push_back(' ');
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