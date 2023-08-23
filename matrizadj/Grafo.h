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
  int **mat; // @{\it pesos do tipo inteiro}@
  int numVertices;
  int *pos; // @{\it posi\c{c}\~ao atual ao se percorrer os adjs de um v\'ertice v}@

public:
  Grafo(int numVertices);
  Grafo(istream &in);
  Grafo(int numVertices, int numArestas);
  void insereAresta(int v1, int v2, int peso);
  // void insereArestaPorReferencia(int v1, int v2, int peso);
  bool existeAresta(int v1, int v2) const;
  bool listaAdjVazia(int v) const;
  Aresta *lerAresta();
  Aresta *primeiroListaAdj(int v);
  Aresta *proxAdj(int v);
  Aresta *retiraAresta(int v1, int v2);
  void imprime() const;
  int _numVertices() const;
  Grafo *grafoTransposto();
  Grafo *grafoNaoDirecionado();
  void listaAdj(int v);
  bool completo();
  bool regular();
  int grauVertice(int v);
  ~Grafo();
};

Grafo::Grafo(istream &in)
{
  int v1, v2, peso;
  in >> this->numVertices;
  this->mat = new int *[numVertices];
  for (int i = 0; i < numVertices; i++)
    this->mat[i] = new int[numVertices];
  this->pos = new int[numVertices];

  for (int i = 0; i < this->numVertices; i++)
  {
    for (int j = 0; j < this->numVertices; j++)
      this->mat[i][j] = 0;
    this->pos[i] = -1;
  }

  while (in >> v1 >> v2 >> peso)
  {
    Grafo::Aresta *a = new Grafo::Aresta(v1, v2, peso);
    this->insereAresta(a->_v1(), a->_v2(), a->_peso());
    delete a;
  }
}

Grafo::Grafo(int numVertices)
{
  this->mat = new int *[numVertices];
  for (int i = 0; i < numVertices; i++)
    this->mat[i] = new int[numVertices];
  this->pos = new int[numVertices];
  this->numVertices = numVertices;
  for (int i = 0; i < this->numVertices; i++)
  {
    for (int j = 0; j < this->numVertices; j++)
      this->mat[i][j] = 0;
    this->pos[i] = -1;
  }
}

Grafo::Grafo(int numVertices, int numArestas)
{
  this->mat = new int *[numVertices];
  for (int i = 0; i < numVertices; i++)
    this->mat[i] = new int[numVertices];
  this->pos = new int[numVertices];
  this->numVertices = numVertices;
  for (int i = 0; i < this->numVertices; i++)
  {
    for (int j = 0; j < this->numVertices; j++)
      this->mat[i][j] = 0;
    this->pos[i] = -1;
  }
}

void Grafo::insereAresta(int v1, int v2, int peso)
{
  this->mat[v1][v2] = peso;
}
// receaving an Aresta object
// void insereArestaPorReferencia(Aresta *a)
// {
//   this->mat[a->_v1()][a->_v2()] = a->_peso();
// }
bool Grafo::existeAresta(int v1, int v2) const
{
  return (this->mat[v1][v2] > 0);
}
bool Grafo::listaAdjVazia(int v) const
{
  for (int i = 0; i < this->numVertices; i++)
    if (this->mat[v][i] > 0)
      return false;
  return true;
}

Grafo::Aresta *Grafo::lerAresta()
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
  return new Aresta(v1, v2, peso);
}

Grafo::Aresta *Grafo::primeiroListaAdj(int v)
{
  // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@
  // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@
  this->pos[v] = -1;
  return this->proxAdj(v);
}

Grafo::Aresta *Grafo::proxAdj(int v)
{
  // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@
  // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@
  this->pos[v]++;
  while ((this->pos[v] < this->numVertices) &&
         (this->mat[v][this->pos[v]] == 0))
    this->pos[v]++;
  if (this->pos[v] == this->numVertices)
    return NULL;
  else
    return new Aresta(v, this->pos[v], this->mat[v][this->pos[v]]);
}

Grafo::Aresta *Grafo::retiraAresta(int v1, int v2)
{
  if (this->mat[v1][v2] == 0)
    return NULL; // @{\it Aresta n\~ao existe}@
  else
  {
    Aresta *aresta = new Aresta(v1, v2, this->mat[v1][v2]);
    this->mat[v1][v2] = 0;
    return aresta;
  }
}

void Grafo::imprime() const
{
  cout << "   ";
  for (int i = 0; i < this->numVertices; i++)
    cout << i << "   ";
  cout << endl;
  for (int i = 0; i < this->numVertices; i++)
  {
    cout << i << "  ";
    for (int j = 0; j < this->numVertices; j++)
      cout << this->mat[i][j] << "   ";
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

Grafo *Grafo::grafoNaoDirecionado()
{
  Grafo *grafoND = new Grafo(this->numVertices);
  for (int v = 0; v < this->numVertices; v++)
    if (!this->listaAdjVazia(v))
    {
      Aresta *adj = this->primeiroListaAdj(v);
      while (adj != NULL)
      {
        grafoND->insereAresta(adj->_v1(), adj->_v2(), adj->_peso());
        grafoND->insereAresta(adj->_v2(), adj->_v1(), adj->_peso());
        delete adj;
        adj = this->proxAdj(v);
      }
    }
  // Ex5: Implementar o grafo não direcionado
  return grafoND;
}

Grafo::~Grafo()
{
  for (int i = 0; i < numVertices; i++)
    delete[] this->mat[i];
  delete[] this->mat;
  delete[] this->pos;
}

void Grafo::listaAdj(int v)
{
  for (int j = 0; j < this->numVertices; j++)
  {
    // if (this->mat[v][j] > 0)
    if (this->existeAresta(v, j))
      cout << j << " ";
  }
  //  funciona também
  // if (!this->listaAdjVazia(v))
  // {
  //   Aresta *adj = this->primeiroListaAdj(v);
  //   while (adj != NULL)
  //   {
  //     cout << adj->_v2() << " ";
  //     delete adj;
  //     adj = this->proxAdj(v);
  //   }
  // }
}

int Grafo::grauVertice(int v)
{
  int grau = 0;
  for (int j = 0; j < this->numVertices; j++)
  {
    if (this->existeAresta(v, j))
      grau++;
  }
  return grau;
}

bool Grafo::completo()
{
  // n - 1
  for (int i = 0; i < this->numVertices; i++)
  {
    if (this->grauVertice(i) < this->numVertices - 1)
      return false;
  }
  return true;
  // for (int i = 0; i < this->numVertices; i++)
  // {
  //   for (int j = 0; j < this->numVertices; j++)
  //   {
  //     if (i != j)
  //     {
  //       if (!this->existeAresta(i, j))
  //       {
  //         return false;
  //       }
  //     }
  //   }
  // }
  // return true;
}

// bool Grafo::regular()
// {
//   int grau = 0;
//   int grauAnterior = 0;
//   for (int i = 0; i < this->numVertices; i++)
//   {
//     for (int j = 0; j < this->numVertices; j++)
//     {
//       if (i != j)
//       {
//         if (this->existeAresta(i, j))
//         {
//           grau++;
//         }
//       }
//     }
//     if (i == 0)
//     {
//       grauAnterior = grau;
//     }
//     else
//     {
//       if (grau != grauAnterior)
//       {
//         return false;
//       }
//     }
//     grau = 0;
//   }
//   return true;
// }

bool Grafo::regular()
{
  int grau = 0;
  int grauAnterior = this->grauVertice(0);
  for (int i = 1; i < this->numVertices; i++)
  {
    grau = this->grauVertice(i);
    if (grau != grauAnterior)
      return false;
    grauAnterior = grau;
  }
  return true;
}