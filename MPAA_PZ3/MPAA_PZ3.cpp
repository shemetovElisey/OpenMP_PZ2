// MPAA_PZ3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>

const int n = 10;

void upperTriangleMatrix()
{
	int a[n][n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				a[i][j] = 9;
			else if (i < j)
				a[i][j] = 3;
			else
				a[i][j] = 0;
		}
		
	int x[n];
	int b[n];
	int y[n];
	int i;
	int j;

	for (int i = 0; i < n; i++)
		x[i] = rand() % 10;

	for (int i = 0; i < n; i++)
		printf_s("%d", x[i]);

	int threads = omp_get_max_threads();
//#pragma omp parallel for private(i, j) num_threads(threads)
	for (i = 0; i < n; i++)
	{
		int c = 0;
		for (j = 0; j < n; j++)
			c += a[i][j] * x[j];
		b[i] = c;
	}

	for (i = 0; i < n; i++)
	{
		int c = 0;
		for (j = 0; j < n; j++)
			c += a[j][i] * b[j];
		y[i] = c;
	}

	printf_s("\n b =");
	for (int i = 0; i < n; i++)
		printf_s(" %d", b[i]);

	printf_s("\n y =");

	for (int i = 0; i < n; i++)
		printf_s(" %d", y[i]);
}

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

	//matrix(a, b, res);
	//matrixNorm(res);
	upperTriangleMatrix();
}
