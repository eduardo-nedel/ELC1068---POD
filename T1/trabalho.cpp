#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Função que retorna o número de char em um vector de strings
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

    // Pede ao usuário para informar o tamanho da memória
    
    // Arquivo de entrada
    fstream arqEntrada ("entrada.txt");

    // Testa se o arquivos está aberto
    if (!arqEntrada.is_open()){
        cout << "Erro ao ler o Arquivo" << endl;
    }
    else {

        cout << "Digite o numero de bits que voce deseja ter em memoria" << endl;
        cin >> num_bites;
        
        string str;
        char saida;
        vector <string> palavras;
        bool continuar = true;
        int num_arq = 0;

        // Separa os blocos em arquivos
        while (!arqEntrada.eof()) {
            arqEntrada >> saida >> noskipws;
            // Separa em palavras e verifica se a memória irá estourar
            while (((tolower(saida) >= 'a' && tolower(saida) <= 'z') || (saida >= '0' && saida <= '9')) && continuar) {
                str.push_back(tolower(saida));
                arqEntrada >> saida >> noskipws;
                cout << saida  << "teste"<< endl;
            }

            if(str.size() > num_bites || str.size() <= 0) {
                str.clear();
                continuar = false;
            }

            if (continuar) {

                if (str.size() + num_char(palavras) > num_bites){
                    // Cria um arquivo
                    num_arq+=1;
                    string aux = "Temp";
                    aux += to_string(num_arq);
                    aux += ".txt";
                    ofstream mandar (aux);

                    // Manda para um arquivo as palavras
                    sort(palavras.begin(), palavras.end());
                    for (int i = 0; i < palavras.size(); ++i) {
                        mandar << palavras[i];
                        mandar << ' ';
                    }
                    mandar.close();

                    // Apaga as palavras
                    palavras.clear();

                    // Alimenta o vector de palavras
                    palavras.push_back(str);
                    str.clear();
                }
                else if (str.size() + num_char(palavras) == num_bites){
                    // Cria um arquivo
                    num_arq+=1;
                    string aux = "Temp";
                    aux += to_string(num_arq);
                    aux += ".txt";
                    ofstream mandar (aux);

                    // Alimenta o vector de palavras
                    palavras.push_back(str);
                    str.clear();

                    // Manda para um arquivo as palavras
                    sort(palavras.begin(), palavras.end());
                    for (int i = 0; i < palavras.size(); ++i) {
                        mandar << palavras[i];
                        mandar << ' ';
                    }
                    mandar.close();

                    // Apaga as palavras
                    palavras.clear();
                }
                else {
                    // Alimenta o vector de palavras
                    palavras.push_back(str);
                    str.clear();
                }
            }
            continuar = true;
        }

        // Caso o vector de palavras contenha algo após todas iterações, devemos adicionar ao arquivo
        if (palavras.size() > 0) {

            // Cria um arquivo
            num_arq+=1;
            string aux = "Temp";
            aux += to_string(num_arq);
            aux += ".txt";
            ofstream mandar (aux);

            // Manda para um arquivo as palavras
            sort(palavras.begin(), palavras.end());
            for (int i = 0; i < palavras.size(); ++i) {
                mandar << palavras[i];
                mandar << ' ';
            }
            mandar.close();
        }


        // Ordena os arquivos
        for (int j = num_arq; j > 1 ; j = ceil(j/2.0)) {
            int num_arq_escrita = 1;
            for (int i = 1; i <= j; i++) {
                // Cria um arquivo auxiliar
                ofstream arq_aux ("auxiliar.txt");

                // Abertura dos arquivos
                string aux = "Temp";
                aux += to_string(i);
                aux += ".txt";
                ifstream ler1 (aux);

                i++;

                string aux2 = "Temp";
                aux2 += to_string(i);
                aux2 += ".txt";
                ifstream ler2 (aux2);

                string str1, str2;
                if (ler1.is_open()) 
                    ler1 >> str1;
                if (ler2.is_open())
                    ler2 >> str2;

                // Enquanto não acabar um dos arquivos, le palavras, compara as palavras e adiciona no arquivo auxiliar
                while(ler1.is_open() && ler2.is_open() && !ler1.eof() && !ler2.eof()){
                    // Encontra a menor palavra e a adiciona no arquivo auxiliar, além disso, organiza os espaços
                    if(str1.compare(str2) >=0) {
                        arq_aux << str2;
                        arq_aux << ' ';
                        ler2 >> str2;
                    }
                    else {
                        arq_aux << str1;
                        arq_aux << ' ';
                        ler1 >> str1;
                    }
                }
                // Se um dos arquivos não tiver acabado, adiciona no arquivo auxiliar até chegar ao fim
                while(ler1.is_open() && !ler1.eof()) {
                    arq_aux << str1;
                    arq_aux << ' ';
                    ler1 >> str1;
                }
                while(ler2.is_open() && !ler2.eof()) {
                    arq_aux << str2;
                    arq_aux << ' ';
                    ler2 >> str2;
                }

                // Fecha os arquivos
                ler1.close();
                ler2.close();
                arq_aux.close();

                // Abre o arquivo a ser escrito em modo de escrita
                string aux3 = "Temp";
                aux3 += to_string(num_arq_escrita);
                aux3 += ".txt";
                ofstream ler (aux3);
                num_arq_escrita++;

                // Abre o arquivo auxiliar em modo de leitura
                ifstream arq ("auxiliar.txt");

                // Copia o arquivo auxiliar para o primeiro arquivo
                char c = arq.get();

                while (arq.good()) {
                    ler << c;
                    c = arq.get();
                }

                // Fecha os arquivos e limpa o auxiliar
                ler.close();
                arq.close();
                remove("auxiliar.txt");
            }

        }
        // Copia a resposta para um arquivo chamado "Respostas.txt"
        ofstream resp ("Resposta.txt");
        ifstream arq ("Temp1.txt");

        char c = arq.get();

        while (arq.good()) {
            resp << c;
            c = arq.get();
        }

        // Fecha os arquivos
        resp.close();
        arq.close();

        // Remove todos arquivos temporarios
        for (int i = 1; i <= num_arq; ++i) {
            string aux = "Temp";
            aux += to_string(i);
            aux += ".txt";
            remove(aux.c_str());
        }

        cout << "Verifique o arquivo ""Resposta.txt"" na pasta do programa, nele está contida a resposta." << endl;

    }

    arqEntrada.close();
    return 0;
}