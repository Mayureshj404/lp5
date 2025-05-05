#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int m,n;
    cout << "Enter the size of the matrix (m x n): ";
    cin >> m >> n;
    
    int A[m][n], B[n]; // No zero initialization
    int C[n] = {0};
    
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
    
    cout << "\nVector B :\n";
    for (int i = 0; i < n; i++)
    {
        B[i] = rand() % 10;
        cout << B[i] << " ";
    }
    
    #pragma omp parallel for
    for(int i=0; i<m; i++)
    {
        #pragma omp parallel for
        for(int j=0; j<n; j++)
        {
            C[i]+= A[i][j] * B[i];
        }
    }
    
    cout << "\nResultant Vector C :\n";
    for (int i = 0; i < n; i++)
    {
        cout << C[i] << " ";
    }
    
}