#include "matrizadj/Grafo.h"
// #include "listaadj/Grafo.h"
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
    ifstream in("input.txt");
    cout << "Grafo: " << endl;
    Grafo *grafo = new Grafo(in);
    grafo->imprime();

    // Ex1: criar e imprimir grafo transposto.
    cout << endl;
    cout << "Grafo transposto: " << endl;
    Grafo *grafoTransposto = grafo->grafoTransposto();
    grafoTransposto->imprime();

    // Ex2: Criar e imprimir um grafo não orientado.
    cout << endl;
    cout << "Grafo nao direcionado: " << endl;
    Grafo *grafoNaoDirecionado = grafo->grafoNaoDirecionado();
    grafoNaoDirecionado->imprime();
    // Ex3: Ler e inserir nova aresta, verificando se ela já existe.

    // Ex4: Ler e remover uma aresta, verificando se ela já existe.

    // Ex5: Imprimir uma lista adjacente de um determinado vértices.
}
