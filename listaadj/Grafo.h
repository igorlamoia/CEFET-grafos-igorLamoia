#include "Lista.h"
#include "FPHeapMinIndireto.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>
#include <cstring>
#include <float.h>
using namespace std;

class Grafo
{
public:
  class Aresta
  {
  private:
    int v1, v2, peso;

  public:
    Aresta(int v1, int v2, int peso)
    {
      this->v1 = v1;
      this->v2 = v2;
      this->peso = peso;
    }
    int _peso() { return this->peso; }
    int _v1() { return this->v1; }
    int _v2() { return this->v2; }
    ~Aresta() {}
  };

private:
  class Celula
  {
    friend class Grafo;
    friend ostream &operator<<(ostream &out, const Celula &celula)
    {
      out << "vertice:" << celula.vertice << endl;
      out << "peso:" << celula.peso << endl;
      return out;
    }

  private:
    int vertice, peso;

  public:
    Celula(int v, int p)
    {
      this->vertice = v;
      this->peso = p;
    }
    Celula(const Celula &cel) { *this = cel; }
    bool operator==(const Celula &celula) const
    {
      return this->vertice == celula.vertice;
    }
    bool operator!=(const Celula &celula) const
    {
      return this->vertice != celula.vertice;
    }
    const Celula &operator=(const Celula &cel)
    {
      this->vertice = cel.vertice;
      this->peso = cel.peso;
      return *this; // @{\it permite atribui\c{c}\~oes encadeadas}@
    }
    ~Celula() {}
  };
  Lista<Celula> *adj;
  int numVertices;

public:
  Grafo(istream &in);
  Grafo(int numVertices);
  Grafo(int numVertices, int numArestas);
  void insereAresta(int v1, int v2, int peso);
  bool existeAresta(int v1, int v2) const;
  bool listaAdjVazia(int v) const;
  Aresta *lerAresta();
  Aresta *primeiroListaAdj(int v);
  Aresta *proxAdj(int v);
  Aresta *retiraAresta(int v1, int v2);
  void imprime() const;
  int _numVertices() const;
  Grafo *grafoTransposto();
  void buscaEmProfundidade();
  void visitaDfs(int u, int *cor, int *antecessor);
  // todos usando o buscaEmProfundidade
  bool aciclico(); // tomar cuidado pra n pegar o mesmo vertice antecessor (antecessor e proximo cinza TODOS OS ADJACENTES)
  bool visitaDfsCiclo(int u, int *cor, int *antecessor);
  int numComponentes();
  vector<int> ordemTopologica();
  void visitaDfsComOrdem(int u, int *cor, int *antecessor, vector<int> &ordem);
  // bfs
  void buscaEmLargura();
  void visitaBfs(int u, int *cor, int *antecessor, int *distancia);

  ~Grafo();
  // const para cor
  static const int BRANCO = 0;
  static const int CINZA = 1;
  static const int PRETO = 2;
};

Grafo::Grafo(istream &in)
{
  int v1, v2, peso, numVertices;
  in >> numVertices;

  this->adj = new Lista<Celula>[numVertices];
  this->numVertices = numVertices;

  while (in >> v1 >> v2 >> peso)
  {
    Grafo::Aresta *a = new Grafo::Aresta(v1, v2, peso);
    this->insereAresta(a->_v1(), a->_v2(), a->_peso());
    delete a;
  }
}

Grafo::Grafo(int numVertices)
{
  this->adj = new Lista<Celula>[numVertices];
  this->numVertices = numVertices;
}
Grafo::Grafo(int numVertices, int numArestas)
{
  this->adj = new Lista<Celula>[numVertices];
  this->numVertices = numVertices;
}

Grafo::Aresta *lerAresta()
{
  cout << "Aresta:" << endl;
  cout << "  V1:";
  int v1 = 0;
  cin >> v1;
  cout << "  V2:";
  int v2 = 0;
  cin >> v2;
  cout << "  Peso:";
  int peso = 0;
  cin >> peso;
  return new Grafo::Aresta(v1, v2, peso);
}

void Grafo::insereAresta(int v1, int v2, int peso)
{
  Celula item(v2, peso);
  this->adj[v1].insere(item);
}
bool Grafo::existeAresta(int v1, int v2) const
{
  Celula item(v2, 0);
  return (this->adj[v1].pesquisa(item) != NULL);
}
bool Grafo::listaAdjVazia(int v) const
{
  return this->adj[v].vazia();
}
Grafo::Aresta *Grafo::primeiroListaAdj(int v)
{
  // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@
  // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@
  Celula *item = this->adj[v]._primeiro();
  return item != NULL ? new Aresta(v, item->vertice, item->peso) : NULL;
}
Grafo::Aresta *Grafo::proxAdj(int v)
{
  // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@
  // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@
  Celula *item = this->adj[v].proximo();
  return item != NULL ? new Aresta(v, item->vertice, item->peso) : NULL;
}
Grafo::Aresta *Grafo::retiraAresta(int v1, int v2)
{
  Celula chave(v2, 0);
  Celula *item = this->adj[v1].retira(chave);
  Aresta *aresta = item != NULL ? new Aresta(v1, v2, item->peso) : NULL;
  delete item;
  return aresta;
}
void Grafo::imprime() const
{
  for (int i = 0; i < this->numVertices; i++)
  {
    cout << i << ":";
    Celula *item = this->adj[i]._primeiro();
    while (item != NULL)
    {
      cout << "  " << item->vertice << " (" << item->peso << ")";
      item = this->adj[i].proximo();
    }
    cout << endl;
  }
}
int Grafo::_numVertices() const { return this->numVertices; }
Grafo *Grafo::grafoTransposto()
{
  Grafo *grafoT = new Grafo(this->numVertices);
  for (int v = 0; v < this->numVertices; v++)
    if (!this->listaAdjVazia(v))
    {
      Aresta *adj = this->primeiroListaAdj(v);
      while (adj != NULL)
      {
        grafoT->insereAresta(adj->_v2(), adj->_v1(), adj->_peso());
        delete adj;
        adj = this->proxAdj(v);
      }
    }
  return grafoT;
}
Grafo::~Grafo()
{
  delete[] this->adj;
}

void Grafo::buscaEmProfundidade()
{
  int *cor = new int[this->numVertices];
  int *antecessor = new int[this->numVertices];

  for (int u = 0; u < this->numVertices; u++)
  {
    cor[u] = BRANCO;
    antecessor[u] = -1;
  }
  for (int u = 0; u < this->numVertices; u++)
    if (cor[u] == BRANCO)
      this->visitaDfs(u, cor, antecessor);
  delete[] cor;
  delete[] antecessor;
}

void Grafo::visitaDfs(int u, int *cor, int *antecessor)
{
  cor[u] = CINZA;
  // cout << "cinza: " << u << endl;
  if (!this->listaAdjVazia(u))
  {
    Aresta *adj = this->primeiroListaAdj(u);
    while (adj != NULL)
    {
      int v = adj->_v2();
      if (cor[v] == BRANCO)
      {
        antecessor[v] = u;
        this->visitaDfs(v, cor, antecessor);
      }
      delete adj;
      adj = this->proxAdj(u); // próxima aresta de u
    }
  }
  // cout << "preto: " << u << endl;

  cor[u] = PRETO;
}

// verificar se grafo é aciclico
bool Grafo::aciclico() // tomar cuidado pra n pegar o mesmo vertice antecessor (antecessor e proximo cinza TODOS OS ADJACENTES)
{
  int *cor = new int[this->numVertices];
  int *antecessor = new int[this->numVertices];

  bool aciclico = false;

  for (int u = 0; u < this->numVertices; u++)
  {
    cor[u] = BRANCO;
    antecessor[u] = -1;
  }
  for (int u = 0; u < this->numVertices; u++)
    if (cor[u] == BRANCO)
    {
      aciclico = !this->visitaDfsCiclo(u, cor, antecessor);
      // if (aciclico)
      //   return true;
    }
  delete[] cor;
  delete[] antecessor;
  return aciclico;
}

bool Grafo::visitaDfsCiclo(int u, int *cor, int *antecessor)
{
  cor[u] = CINZA;
  if (!this->listaAdjVazia(u))
  {
    Aresta *adj = this->primeiroListaAdj(u);
    while (adj != NULL)
    {
      int v = adj->_v2();
      if (cor[v] == CINZA)
        return true;
      if (cor[v] == BRANCO)
      {
        antecessor[v] = u;
        this->visitaDfsCiclo(v, cor, antecessor);
      }
      delete adj;
      adj = this->proxAdj(u); // próxima aresta de u
    }
  }
  cor[u] = PRETO;
}

int Grafo::numComponentes()
{
  int *cor = new int[this->numVertices];
  int *antecessor = new int[this->numVertices];
  int numComponentes = 0;

  for (int u = 0; u < this->numVertices; u++)
  {
    cor[u] = BRANCO;
    antecessor[u] = -1;
  }
  for (int u = 0; u < this->numVertices; u++)
  {
    if (cor[u] == BRANCO)
    {
      numComponentes++;
      this->visitaDfs(u, cor, antecessor);
    }
  }
  delete[] cor;
  delete[] antecessor;
  return numComponentes;
}

vector<int> Grafo::ordemTopologica()
{
  vector<int> ordem;
  int *cor = new int[this->numVertices];
  int *antecessor = new int[this->numVertices];

  for (int u = 0; u < this->numVertices; u++)
  {
    cor[u] = BRANCO;
    antecessor[u] = -1;
  }
  for (int u = 0; u < this->numVertices; u++)
    if (cor[u] == BRANCO)
      this->visitaDfsComOrdem(u, cor, antecessor, ordem);
  delete[] cor;
  delete[] antecessor;
  reverse(ordem.begin(), ordem.end()); // inverte o vetor para ficar na ordem correta de prioridade
  return ordem;
}
void Grafo::visitaDfsComOrdem(int u, int *cor, int *antecessor, vector<int> &ordem)
{
  cor[u] = CINZA;
  if (!this->listaAdjVazia(u))
  {
    Aresta *adj = this->primeiroListaAdj(u);
    while (adj != NULL)
    {
      int v = adj->_v2();
      if (cor[v] == BRANCO)
      {
        antecessor[v] = u;
        this->visitaDfsComOrdem(v, cor, antecessor, ordem);
      }
      delete adj;
      adj = this->proxAdj(u); // próxima aresta de u
    }
  }

  cor[u] = PRETO;
  ordem.push_back(u);
}

void Grafo::buscaEmLargura()
{
  int *cor = new int[this->numVertices];
  int *antecessor = new int[this->numVertices];
  int *distancia = new int[this->numVertices];
  // vector<int> distancia;

  for (int u = 0; u < this->numVertices; u++)
  {
    cor[u] = BRANCO;
    antecessor[u] = -1;
    distancia[u] = -1;
  }
  for (int u = 0; u < this->numVertices; u++)
    if (cor[u] == BRANCO)
      this->visitaBfs(u, cor, antecessor, distancia);
  delete[] cor;
  delete[] antecessor;

  // printa distancia
  // for (int i = 0; i < this->numVertices; i++)
  //   cout << "Distancia de " << i << ": " << distancia[i] << endl;
}

void Grafo::visitaBfs(int u, int *cor, int *antecessor, int *distancia)
{
  queue<int> fila;
  cor[u] = CINZA;
  fila.push(u);
  while (!fila.empty())
  {
    int u = fila.front();
    fila.pop();
    if (!this->listaAdjVazia(u))
    {
      Aresta *adj = this->primeiroListaAdj(u);
      while (adj != NULL)
      {
        int v = adj->_v2();
        if (cor[v] == BRANCO)
        {
          cor[v] = CINZA;
          cout << "Visitou: " << v << endl;
          antecessor[v] = u;
          distancia[v] = distancia[u] + 1;
          fila.push(v);
        }
        delete adj;
        adj = this->proxAdj(u); // próxima aresta de u
      }
    }
    cor[u] = PRETO;
  }
}

// create a struct to store the edge information
