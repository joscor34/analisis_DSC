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

  // for (int i = 0; i < tam; i++)
  // {
  //   for (int j = 0; j < 2; j++)
  //   {
  //     cout << tabla[i][j] << endl;
  //   }
  // }

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
        // cout << "FINAL DE ADEVERAS = " << -1 * (contador - tam - 1) << endl;
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
      // cout << "el primer valor de i: " << i << endl;
      // cout << "El valor de valoresX[" << i << "] " << valoresX[i] << endl;
      valoresX[i] = curva[i][0];
      // cout << curva[i][j] << "\t";
      outfile << curva[i][j] << "\t";
    }
    // cout << endl;
    outfile << endl;
  }
  outfile.close();

  int n = 0, pol; // n es el numero de puntos coordenados, funcion tabular

  float x[200][200], a[200], error[200];

  ifstream inf;
  inf.open("Datos_DSC.txt");

  int ii = 0, jj = 0;
  while (inf >> x[ii][jj] >> x[ii][jj + 1])
  {
    cout << x[ii][jj] << " " << x[ii][jj + 1] << endl;
    ii++;

    n++;
  }
  inf.close();
  cout << "TABLA DE VALORES\nx\ty";
  cout << endl;
  for (int i = 0; i < n; i++)
  {
    cout << "\n";
    for (int j = 0; j < 2; j++)
    {
      cout << x[i][j];
      cout << "\t";

      //			cout<<x[i]<<"\t"   <<y[i]<<endl;
    }
  }

  //Tamaño polinomio
  cout << "\nDe que tamanio desea su polinomio?\n";
  cin >> pol;
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
  //matriz X
  cout << "\nLa matriz X es: \n";
  for (int i = 0; i < n; i++)
  {
    cout << endl;
    for (int j = 0; j < pol + 1; j++)
    {
      cout << X[i][j];
      cout << "\t";
    }
  }
  //matriz Y
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < 2; j++)
      Y[i][j] = x[i][1];
  }
  cout << "\n\nLa matriz Y es: \n";
  for (int i = 0; i < n; i++)
  {
    cout << endl;
    for (int j = 0; j < 1; j++)
    {
      cout << Y[i][j];
      cout << "\t";
    }
  }
  //tranpuesta Xt
  for (int i = 0; i < pol + 1; i++)
    for (int j = 0; j < n; j++)
    {
      Xt[i][j] = X[j][i];
    }
  cout << "\n\nTranspuesta X=Xt\n";
  for (int i = 0; i < pol + 1; i++)
  {
    cout << endl;
    for (int j = 0; j < n; j++)
    {
      cout << Xt[i][j];
      cout << "\t";
    }
  }
  //
  ofstream onf;
  onf.open("gg.txt");
  cout << "\n"
       << "\n";
  cout << "--------------------------------------------------------------------------------------------------";
  cout << "\n"
       << " Donde el sistema de ecuaciones normales esta dado por [Xt*X]*A=[Xt*Y]";
  cout << "\n";
  cout << " Tomando en cuenta que:"
       << "\n"
       << " [Xt*X]=[S X^k]"
       << "\n"
       << " [Xt*Y]=[S YX^2]"
       << "\n"
       << " Dando la forma -> [S X^k][A]=[S YX^2] "
       << "\n";
  cout << "--------------------------------------------------------------------------------------------------";
  cout << "\n";
  onf << pol + 1 << endl;
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
  cout << "\n La matriz Xk es: \n"
       << endl;
  for (int i = 0; i < pol + 1; i++)
  {
    cout << endl;
    onf << endl;
    for (int j = 0; j < pol + 1; j++)
    {
      cout << Xk[i][j];
      cout << "\t";
      onf << Xk[i][j];
      onf << "\t";
    }
  }
  cout << "\n";
  onf << "\n";
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
  cout << "\nLa matriz YX es: \n";
  for (int i = 0; i < pol + 1; i++)
  {
    cout << endl;
    onf << endl;
    for (int j = 0; j < 1; j++)
    {
      cout << YX[i];
      cout << "\t";
      onf << YX[i];
      onf << "\t";
    }
  }

  cout << "\n"
       << "\n";
  onf << "\n"
      << "\n";
  onf.close();
  cout << "------------------------------------------------------------------------";
  cout << endl;
  cout << "Para sacar A= matriz de coeficientes"
       << "\n"
       << "[A]=invX^k * YX^2 "
       << "\n";
  cout << "------------------------------------------------------------------------";
  cout << endl;
  cout << "\n"
       << " Para sacar matriz inversa(invX^k) = AdjA/detA"
       << "\n";

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
    cout << "x[" << i << "]= " << x[i][0] << "y[" << i << "]= " << x[i][1] << "y ajustada[" << i << "]=" << yAjustada[i] << endl;
    promy += x[i][1];
    promyAj += yAjustada[i];
  }
  cout << "La suma de los errores al cuadrado = " << errorCuadratico << endl;
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
  cout << "el valor de r= " << r << endl;

  //for(int i=0;i<n;i++){

  //error=error+powf(x[i][1]-f(x[i][0]),2.0)

  //}

  // matriz inversa de X^2
  // integra(a, n, resultados, valoresX);

  for (int i = 0; i < tamcurva + 1; i++)
  {
    cout << "Valores de X: " << valoresX[i] << endl;
  }
  int integrales = sizeof(valoresX) / sizeof(valoresX[0]);
  float valorX1 = valoresX[0];
  float valorXF = valoresX[integrales + 1];
  cout << "El resultado de integrar es: " << integra(a, pol + 1, resultados, valorX1, valorXF) << endl;

  return 0;
}
void gJ(float A[200][200], float b[200], float x[200], int n)
{

  for (int i = 0; i < n; i++)
  {
    A[i][n] = b[i];
  }

  cout << "desplegando la matriz aumentada desde gauss jordan" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      cout << A[i][j] << "  ";
    }
    cout << endl;
  }

  for (int k = 0; k < n; k++)
  {
    for (int j = n; j >= k; j--)
    {
      A[k][j] = A[k][j] / A[k][k];
    }
    //proceso de reducci�n
    for (int i = 0; i <= n; i++)
    {
      if (i != k)
      {
        for (int j = n; j >= k; j--)
          A[i][j] = A[i][j] - A[i][k] * A[k][j];
      }
    }
  }
  cout << "----Matriz normalizada----" << endl;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      cout << A[i][j] << "  ";
    }
    cout << endl;
  }

  for (int i = 0; i < n; i++)
  {
    x[i] = A[i][n];
  }

  ofstream onf;
  onf.open("gg.txt");

  onf << "Matriz inicial" << endl;

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n + 1; j++)
    {
      onf << A[i][j] << "  ";
    }
    onf << endl;
  }
  onf << "solucion del sistema:" << endl;

  for (int i = 1; i <= n; i++)
  {
    onf << "x[" << i << "]=" << x[i] << endl;
  }
  onf.close();
  cout << "retornando desde Gauss Jordan" << endl;

  cout << "Valores resultantes: " << endl;
}

float integra(float a[], float n, float integral[], float val1, float val2)
{

  float resultado1 = 0;
  float resultado2 = 0;
  cout << "Evaluar en X1: " << val1 << endl;
  cout << "Evaluar en XF: " << val2 << endl;
  for (int i = 0; i < n; i++)
  {
    float exp = 1 / (i + 1.0);
    cout << "----------------------" << endl;
    cout << "a[" << i << "]=" << a[i] << " * " << exp << " = " << a[i] * exp << "  x^" << i + 1 << endl;
    cout << "----------------------" << endl;
    integral[i] = a[i] * exp;
    // cout << da[i - 1] << " ";
  }
  for (int i = 0; i < n; i++)
  {
    resultado1 += integral[i] * pow(val1, i + 1);
  }

  for (int i = 0; i < n; i++)
  {
    resultado2 += integral[i] * pow(val2, i + 1);
  }
  cout << "El valor de evaluar el lim 1 es: " << resultado1 << endl;
  cout << "El valor de evaluar el lim 2 es: " << resultado2 << endl;

  return resultado2 - resultado1;
  /*cout << "------ Segunda derivada -------";
  for (int i = 1; i < n; i++)
  {

    cout << "----------------------" << endl;
    cout << "a[" << i << "]=" << da[i] << " * " << i - 1 << " = " << da[i] * (i - 1) << endl;
    cout << "----------------------" << endl;
    // cout << da[i] << endl;
  }*/
}
