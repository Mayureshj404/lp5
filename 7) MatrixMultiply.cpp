#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

int main()
{
    int m, n, o;
    cout << "Enter dimensions of Matrix A (m x n): ";
    cin >> m >> n;

    cout << "Enter number of columns for Matrix B (n x o): ";
    cin >> o;

    int A[m][n], B[n][o], C[m][o];

    srand(time(0));
   
    cout << "\nMatrix A (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % 10;
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatrix B (" << n << "x" << o << "):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < o; j++)
        {
            B[i][j] = rand() % 10;
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < m; i++)
        for (int j = 0; j < o; j++)
            C[i][j] = 0;

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < o; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "\nResultant Matrix C = A * B (" << m << "x" << o << "):\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < o; j++)
        {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
