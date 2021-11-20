#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
using namespace std;

int number_of_lines = 0, tam, contador, contadorf;
float n = 0, x;

int main()
{
  ifstream datos;
  datos.open("Datos_DSC.txt");
  if (!datos)
  {
    cerr << "could not open file!" << endl;
    return EXIT_FAILURE;
  }
  while (datos >> x)
  {
    n++;
  }
  tam = n / 2;
  datos.close();

  float **tabla = new float *[tam];
  for (int i = 0; i < tam; i++)
    tabla[i] = new float[tam];

  datos.open("Datos_DSC.txt");
  if (!datos)
  {
    cerr << "could not open file!" << endl;
    return EXIT_FAILURE;
  }

  for (int i = 0; i < tam; i++)
  {
    for (int j = 0; j < 2; j++)
      datos >> tabla[i][j];
  }

  for (int i = 0; i < tam; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      cout << tabla[i][j] << endl;
    }
  }

  for (int i = 0; i < tam - 1; i++)
  {
    contadorf++;
    if (tabla[i][1] - tabla[i + 1][1] < 1)
    {
      contador = i;
      cout << "Dato normal: " << tabla[i][1] << " | ";
      cout << "Dato siguiente: " << tabla[i + 1][1] << " | ";
      cout << "Resta: " << tabla[i][1] - tabla[i + 1][1] << endl;
      cout << "Contador final  " << contadorf << endl;
      if (tabla[i][1] - tabla[i + 1][1] > 0.7)
      {
        cout << "FINAL DE ADEVERAS = " << -1 * (contador - tam - 1) << endl;
        break;
      }
    }
  }
  contador = -1 * (contador - tam - 1);
  int tamcurva = contadorf - contador;

  float **curva = new float *[tamcurva];
  for (int i = 0; i <= tamcurva; i++)
  {
    curva[i] = new float[tamcurva];
  }
  cout << "Curva: " << endl;

  for (int i = 0; i < tamcurva; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      curva[i][j] = tabla[(contador + 1) + i][j];
    }
  }
  for (int i = 0; i < tamcurva; i++)
  {
    cout << "tabla final alv: " << endl;
    for (int j = 0; j < 2; j++)
    {
      cout << curva[i][j] << endl;
    }
  }

  // for (int i = contador + 1; i <= contadorf + 1; i++)
  // {
  //   cout << "-------" << endl;
  //   cout << "valor de i: " << i << endl;
  //   cout << "-------" << endl;
  //   for (int q = 0; q < tamcurva; q++)
  //   {
  //     cout << "-------" << endl;
  //     cout << "valor de q: " << q << endl;
  //     cout << "-------" << endl;
  //     for (int j = 0; j < 2; j++)
  //     {
  //       cout << "-------" << endl;
  //       cout << "valor de j: " << j << endl;
  //       cout << "-------" << endl;
  //       curva[q][j] = tabla[i][j];
  //       //cout << curva[q][j] << "\t\n";
  //     }
  //   }
  // }

  return 0;
}
