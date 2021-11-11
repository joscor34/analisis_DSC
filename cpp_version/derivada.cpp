#include <iostream>

void deriva(float a[], int n, float da[])
{
  for (int i = 1; i < n; i++)
  {
    da[i - 1] = a[i] * i;
    cout << da[i - 1] << " ";
  }
}
