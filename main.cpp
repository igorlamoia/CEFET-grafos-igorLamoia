// #include "matrizadj/Grafo.h"
#include "listaadj/Grafo.h"
#include <fstream>
using namespace std;
// link para o grafo
// https://csacademy.com/app/graph_editor/
int main(int argc, char **argv)
{
    // ifstream in("input.txt");
    // ifstream in("input-busca-profundidade.txt");
    // ifstream in("input-nao-direcionado.txt");
    ifstream in("input-min.txt");

    cout << "Grafo: " << endl;
    Grafo *grafo = new Grafo(in);
    grafo->imprime();
    cout << endl;
    // Grafo *arvoreKruskal = grafo->kruskal();
    // cout << "Arvore de Kruskal: " << endl;
    // arvoreKruskal->imprime();

    // Grafo::PrimResult algResult = grafo->prim(0);
    Grafo::DijkstraResult algResult = grafo->dijkstra(0);
    cout << "Algoritimo: " << endl;
    int pesoTotal = 0;
    for (int i = 0; i < algResult.numVertices; i++)
    {
        cout << i << " : ";
        cout << algResult.antecessor[i] << " (" << algResult.peso[i] << ")" << endl;
        pesoTotal += algResult.peso[i];
    }
    cout << "Peso total: " << pesoTotal << endl;
    delete algResult.antecessor;
    delete algResult.peso;
    // // grafo->buscaEmProfundidade();
    // grafo->aciclico() ? (cout << "Grafo aciclico!") : (cout << "Grafo nao aciclico!");
    // cout << endl;
    // cout << "Numero de componentes: " << grafo->numComponentes() << endl;
    // cout << "Ordem topologica: ";
    // vector<int> ordem = grafo->ordemTopologica();
    // for (int i = 0; i < ordem.size(); i++)
    //     cout << ordem[i] << " ";
    // cout << endl;

    // Grafo::ResultadoBusca resultado = grafo->buscaEmLargura();
    // cout << "Caminho mais curto: " << endl;
    // grafo->imprimeCaminho(0, 7, resultado.antecessor);
    // for (int i = 0; i < grafo->_numVertices(); i++)
    // {
    //     cout << "Vertice: " << i << endl;
    //     cout << "  Distancia: " << resultado.distancia[i] << endl;
    //     cout << "  Antecessor: " << resultado.antecessor[i] << endl;
    // }
    // delete resultado.antecessor;
    // delete resultado.distancia;
    cout << endl;

    // Ex1: criar e imprimir grafo transposto.
    // cout << endl;
    // cout << "Grafo transposto: " << endl;
    // Grafo *grafoTransposto = grafo->grafoTransposto();
    // grafoTransposto->imprime();

    // Ex2: Criar e imprimir um grafo não orientado.
    // cout << endl;
    // cout << "Grafo nao direcionado: " << endl;
    // Grafo *grafoNaoDirecionado = grafo->grafoNaoDirecionado();
    // grafoNaoDirecionado->imprime();

    // Ex3: Ler e inserir nova aresta, verificando se ela já existe.
    // cout << endl;
    // Grafo::Aresta *aresta = grafo->lerAresta();
    // cout << "Antes de inserir: " << endl; // "Antes de inserir:
    // grafo->imprime();
    // if (grafo->existeAresta(aresta->_v1(), aresta->_v2()))
    //     cout << "Aresta ja existe!" << endl;
    // else
    //     grafo->insereAresta(aresta->_v1(), aresta->_v2(), aresta->_peso());
    // cout << "Apos inserir: " << endl; // "Antes de inserir:
    // grafo->imprime();

    // Ex4: Ler e remover uma aresta, verificando se ela já existe.
    // cout << endl;
    // cout << "Remover aresta: " << endl;
    // cout << "Aresta:" << endl;
    // cout << "  V1:";
    // int v1 = 0;
    // cin >> v1;
    // cout << "  V2:";
    // int v2 = 0;
    // cin >> v2;
    // cout << "Antes de excluir: " << endl; // "Antes de inserir:
    // grafo->imprime();
    // if (!grafo->existeAresta(v1, v2))
    //     cout << "Aresta ao existe!" << endl;
    // else
    //     grafo->retiraAresta(v1, v2);
    // cout << "Apos Retirar: " << endl; // "Antes de inserir:
    // grafo->imprime();
    // // Ex5: Imprimir uma lista adjacente de um determinado vértices.
    // cout << endl
    //      << "Lista adjacentes:: " << endl; // "Antes de inserir:

    // cout << endl;
    // grafo->listaAdj(0);
    // cout << endl
    //      << "Grau Vertice: " << grafo->grauVertice(0);
    // Ex6: Verificar se um grafo é completo.
    // cout << endl;
    // cout << endl;
    // if (!grafo->naoDirecionado())
    //     return 0;
    // grafo->completo() ? (cout << "Grafo completo!") : (cout << "Grafo nao completo!");

    // // Ex7: Verificar se um grafo é regular.
    // cout << endl;
    // grafo->regular() ? (cout << "Grafo regular!") : (cout << "Grafo nao regular!");

    // // Ex8: Verificar se um grafo é Euleriano (Grau par em todos os vertices)
    // cout << endl;
    // grafo->euleriano() ? (cout << "Grafo euleriano!") : (cout << "Grafo nao euleriano!");

    // // Ex9: Verificar SubEuleriano
    // cout << endl;
    // grafo->subEuleriano() ? (cout << "Grafo SubEuleriano!") : (cout << "Grafo nao SubEuleriano!");
    // cout << endl;
}

// Regular é todos os vertices tendo o mesmo grau
// Completo é todos os vertices se ligarem (n-1) n sendo o número total de vertices
// Euleriano (Grau par em todos os vertices)
// SubEuleriano (Somente 2 impares) (Grau par em todos os vertices menos 2)

// ordem topologica Para resumir: a ordenação topológica é um conceito que se aplica a grafos direcionados. Se um grafo é não direcionado, esse conceito não se aplica diretamente.
// No entanto, podemos transformar um grafo não direcionado em um grafo direcionado, adicionando uma aresta direcionada entre cada par de vértices que já estão conectados por uma aresta não direcionada. O grafo resultante é chamado de grafo direcionado de linha. A ordenação topológica pode ser aplicada a este grafo direcionado de linha. A ordem topológica resultante é uma ordem de visitação dos vértices do grafo não direcionado original.

// https://csacademy.com/app/graph_editor/