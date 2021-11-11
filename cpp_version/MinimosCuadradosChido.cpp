#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {
	int tam, k = 1, pol;
	float n = 0, x, a;
	ifstream datos;
	//Crear un archivo txt con los datos experimentales y nombrarlo tabla.
	datos.open("tabla.txt");
	if (!datos) {
		cerr << "could not open file!" << endl;
		return EXIT_FAILURE;
	}
	while (datos >> x) {
		n++;
	}
	tam = n / 2;
	datos.close();
	
	float**tabla = new float*[tam];
    for (int i = 0; i<tam; i++)
        tabla[i] = new float[tam];
        
	datos.open("tabla.txt");
	if (!datos) {
		cerr << "could not open file!" << endl;
		return EXIT_FAILURE;
	}
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < 2; j++)
			datos >> tabla[i][j];
	}

	//Tamanio polinomio
	cout << "\nDe que tamanio desea su polinomio?\n";
	cin >> pol;
	
	float**X = new float*[tam];
    for (int i = 0; i<tam; i++)
        X[i] = new float[tam];
        
    float**Xt = new float*[tam];
    for (int i = 0; i<tam; i++)
        Xt[i] = new float[tam];
    
    float**Xk = new float*[tam];
    for (int i = 0; i<tam; i++)
        Xk[i] = new float[tam];
        
    float**Y = new float *[tam];
    for (int i = 0; i<tam; i++)
        Y[i] = new float[tam];
        
    float**YX = new float *[tam];
    for (int i = 0; i<tam; i++)
        YX[i] = new float[tam];
        
    float**A = new float *[tam];
    for (int i = 0; i<tam; i++)
        A[i] = new float[tam];
        
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < (pol + 1); j++) {
			if (j == 0)X[i][j] = 1;
			else if (j == 1)X[i][j] = tabla[i][0];
			else X[i][j] = X[i][j - 1] * tabla[i][0];
		}
	}

	//Matriz Y
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < 2; j++)
			Y[i][j] = tabla[i][1];
	}

	//tranpuesta Xt
	for (int i = 0; i < pol + 1; i++)
		for (int j = 0; j < tam; j++) {
			Xt[i][j] = X[j][i];
		}

	//Matriz sumatoria X^k
	for (int i = 0; i < pol + 1; i++)
		for (int j = 0; j < pol + 1; j++) {
			Xk[i][j] = 0;
			for (int k = 0; k < tam; k++) {
				Xk[i][j] += Xt[i][k] * X[k][j];
			}
		}
		
	//Matriz sumatoria YX^2
	for (int i = 0; i < pol + 1; i++)
		for (int j = 0; j < 1; j++) {
			YX[i][j] = 0;
			for (int k = 0; k < tam; k++) {
				YX[i][j] += Xt[i][k] * Y[k][j];
			}
		}
		
	//inversa de Xk
	float**Xkinver = new float*[tam];
    for (int i = 0; i<tam; i++)
        Xkinver[i] = new float[tam];
        
	for (int i = 0; i < pol + 1; i++) {
		for (int j = (pol); j < ((pol + 1) * 2); j++) {
			if (j == (i + pol + 1))Xkinver[i][j] = 1;
			else Xkinver[i][j] = 0;
		}
	}
	
	for (int i = 0; i < pol + 1; i++) {
		for (int j = 0; j < pol + 1; j++)
			Xkinver[i][j] = Xk[i][j];
	}
	
	n = 0;
	for (int k = n; k < pol + 1; k++) {
		for (int i = k; i < pol + 1; i++) {
			a = Xkinver[i][k];
			for (int j = k; j < (2 * (pol + 1)); j++) {
				if (i == k) {
					Xkinver[i][j] = Xkinver[i][j] / a;
				}
				else {
					Xkinver[i][j] = Xkinver[i][j] - (Xkinver[k][j] * a);
				}
			}
		}
	}
	n++;
	
	for (int k = n; k < (pol + 1); k++) {
		for (int i = 0; i < pol + 1; i++) {
			a = Xkinver[i][k];
			for (int j = k; j < (2 * (pol + 1)); j++) {
				if (i == k) {
					Xkinver[i][j] = Xkinver[i][j] / a;
				}
				else {
					Xkinver[i][j] = Xkinver[i][j] - (Xkinver[k][j] * a);
				}
			}
		}
	}
	
	float**Xki = new float*[pol+1];
    for (int i = 0; i<tam; i++)
        Xki[i] = new float[pol+1];
        
	for (int i = 0; i < pol + 1; i++) {
		for (int j = pol + 1; j < ((pol + 1) * 2); j++)
			Xki[i][j - (pol + 1)] = Xkinver[i][j];

	}

	//Vector A de resultados
	for (int i = 0; i < pol + 1; i++)
		for (int j = 0; j < 1; j++) {
			A[i][j] = 0;
			for (int k = 0; k < pol + 1; k++) {
				A[i][j] += Xki[i][k] * YX[k][j];
			}
		}
		
	cout << "\n\nLa ecuacion es: \n";
	for (int i = 0; i < pol + 1; i++) {
		cout << endl;
		for (int j = 0; j < 1; j++) {
			cout << A[i][j];
			cout << "\t";
			cout << "x^" << i;
		}
	}
	return 0;
}
