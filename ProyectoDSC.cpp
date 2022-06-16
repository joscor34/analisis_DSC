#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <math.h>
#define N 5

using namespace std;
void gJ(float[200][200], float[200], float[200], int);

float integra(float[], float, float[], float, float);

int number_of_lines = 0, tam, contador, contadorf;
float n = 0, x;

float resultados[N];

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

  cout << endl
       << endl
       << endl
       << "TABLA DE VALORES COMPLETA\nx\t\ty" << endl;

  for (int i = 0; i < tam; i++)
  {
    cout << endl;
    for (int j = 0; j < 2; j++)
    {
      cout << tabla[i][j];
      cout << "\t";
    }
  }

  for (int i = 0; i < tam - 1; i++)
  {
    contadorf++;
    if (tabla[i][1] - tabla[i + 1][1] < 1)
    {
      contador = i;
      // cout << "Dato normal: " << tabla[i][1] << " | ";
      // cout << "Dato siguiente: " << tabla[i + 1][1] << " | ";
      // cout << "Resta: " << tabla[i][1] - tabla[i + 1][1] << endl;
      // cout << "Contador final  " << contadorf << endl;
      if (tabla[i][1] - tabla[i + 1][1] > 0.7)
      {
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

  float valoresX[9];

  for (int i = 0; i < tamcurva + 1; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      curva[i][j] = tabla[contador + i][j];
    }
  }
  datos.close();

  ofstream outfile;
  outfile.open("Datos_DSC.txt");

  for (int i = 0; i < tamcurva + 1; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      valoresX[i] = curva[i][0];
      outfile << curva[i][j] << "\t";
    }
    // cout << endl;
    outfile << endl;
  }
  outfile.close();

  int n = 0, pol;

  float x[200][200], a[200], error[200];

  ifstream inf;
  inf.open("Datos_DSC.txt");

  int ii = 0, jj = 0;
  while (inf >> x[ii][jj] >> x[ii][jj + 1])
  {
    ii++;
    n++;
  }
  inf.close();
  cout << endl
       << endl
       << endl
       << "TABLA DE VALORES ESPECIFICOS\nx\t\ty";
  cout << endl;
  for (int i = 0; i < n; i++)
  {
    cout << "\n";
    for (int j = 0; j < 2; j++)
    {
      cout << x[i][j];
      cout << "\t";
    }
  }

  //Tamanio polinomio
  pol = 4;
  float X[200][200], Y[200][1], Xt[200][200], YX[200], Xk[200][200];
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < (pol + 1); j++)
    {
      if (j == 0)
        X[i][j] = 1;
      else if (j == 1)
        X[i][j] = x[i][0];
      else
        X[i][j] = X[i][j - 1] * x[i][0];
    }
  }

  //matriz Y
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < 2; j++)
      Y[i][j] = x[i][1];
  }

  //tranpuesta Xt
  for (int i = 0; i < pol + 1; i++)
    for (int j = 0; j < n; j++)
    {
      Xt[i][j] = X[j][i];
    }

  //Matriz sumatoria X^k
  for (int i = 0; i < pol + 1; i++)
    for (int j = 0; j < pol + 1; j++)
    {
      Xk[i][j] = 0;
      for (int k = 0; k < n; k++)
      {
        Xk[i][j] += Xt[i][k] * X[k][j];
      }
    }

  //Matriz sumatoria YX^2
  for (int i = 0; i < pol + 1; i++)
    for (int j = 0; j < 1; j++)
    {
      YX[i] = 0;
      for (int k = 0; k < n; k++)
      {
        YX[i] += Xt[i][k] * Y[k][j];
      }
    }

  gJ(Xk, YX, a, pol + 1);
  float yAjustada[200];
  for (int i = 0; i < 200; i++)
  {
    yAjustada[i] = 0;
    error[i] = 0;
  }
  float errorCuadratico = 0, promy = 0, promyAj = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < pol + 1; j++)
    {
      yAjustada[i] = yAjustada[i] + a[j] * pow(x[i][0], j);
    }
    errorCuadratico = errorCuadratico + pow(x[i][1] - yAjustada[i], 2);
    promy += x[i][1];
    promyAj += yAjustada[i];
  }
  promy = promy / n;
  promyAj = promyAj / n;
  float num = 0, den1 = 0, den2 = 0;
  for (int i = 0; i < n; i++)
  {
    num += (x[i][1] - promy) * (yAjustada[i] - promyAj);
    den1 += pow(x[i][1] - promy, 2);
    den2 += pow(yAjustada[i] - promyAj, 2);
  }
  float r;
  r = (num) / sqrt(den1 * den2);
  cout << endl
       << endl
       << "el valor de r= " << r << endl;

  int integrales = sizeof(valoresX) / sizeof(valoresX[0]);
  float valorX1 = valoresX[0];
  float valorXF = valoresX[integrales + 1];
  cout << "El resultado de integrar es: " << -1 * integra(a, pol + 1, resultados, valorX1, valorXF) << " J" << endl;

  return 0;
}
void gJ(float A[200][200], float b[200], float x[200], int n)
{

  for (int i = 0; i < n; i++)
  {
    A[i][n] = b[i];
  }

  for (int k = 0; k < n; k++)
  {
    for (int j = n; j >= k; j--)
    {
      A[k][j] = A[k][j] / A[k][k];
    }

    //proceso de reduccion
    for (int i = 0; i <= n; i++)
    {
      if (i != k)
      {
        for (int j = n; j >= k; j--)
          A[i][j] = A[i][j] - A[i][k] * A[k][j];
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    x[i] = A[i][n];
  }

  cout << endl
       << endl
       << "Solucion del sistema:" << endl;

  for (int i = 0; i < n; i++)
  {
    cout << "x[" << i << "]=" << x[i] << " x^" << i << endl;
  }
}

float integra(float a[], float n, float integral[], float val1, float val2)
{

  float resultado1 = 0;
  float resultado2 = 0;
  cout << "Evaluar en X1: " << val1 << endl;
  cout << "Evaluar en XF: " << val2 << endl;
  cout << endl
       << endl
       << "Ecuacion integrada: " << endl;
  for (int i = 0; i < n; i++)
  {
    float exp = 1 / (i + 1.0);
    cout << "a[" << i << "]=" << a[i] << " * " << exp << " = " << a[i] * exp << "  x^" << i + 1 << endl;
    integral[i] = a[i] * exp;
  }
  for (int i = 0; i < n; i++)
  {
    resultado1 += integral[i] * pow(val1, i + 1);
  }

  for (int i = 0; i < n; i++)
  {
    resultado2 += integral[i] * pow(val2, i + 1);
  }
  cout << endl
       << "El valor de evaluar el lim 1 es: " << resultado1 << endl;
  cout << "El valor de evaluar el lim 2 es: " << resultado2 << endl
       << endl;

  return resultado2 - resultado1;
}
