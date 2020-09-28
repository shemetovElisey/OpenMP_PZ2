// MPAA_PZ3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>

const int n = 100;

void matrix(int a[n][n], int b[n][n], int r[n][n])
{
	int i, j, k;

	double start = omp_get_wtime();

#pragma omp parallel for shared(a, b, r) private(i, j, k)
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			r[i][j] = 0;
			for (k = 0; k < n; k++) 
				r[i][j] += (a[i][k] * b[k][j]);
		}
	printf("TimeOMP: \t %f \n", omp_get_wtime() - start);
}

void matrixNorm(int a[][n])
{
	int res = 0;

	for (int i = 0; i < n; i++)
		res += a[i][i] * a[i][i];

	printf_s("%lf", sqrt(res));
}

int main()
{
	int a[n][n];
	int b[n][n];
	int res[n][n];

	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
		{
			int j = rand() % 10;
			int g = rand() % 10;
			
			a[i][k] = j;
			b[i][k] = g;
		}

	matrix(a, b, res);
	matrixNorm(res);
}
