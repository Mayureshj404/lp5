#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;


void bubble_sort(int n, vector <int>&arr)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallel_bubble_sort(int n, vector <int>&arr)
{
    for (int i = 0; i < n - 1; i++)
    {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    srand(time(0)); // Seed for random number generator

    int n;
    cout << "Enter number of random elements to generate: ";
    cin >> n;

    vector<int> arr1(n), arr2(n);

    for (int i = 0; i < n; ++i) {
        int val = rand() % 100 + 1; // Random numbers between 1 and 100
        arr1[i] = val;
        arr2[i] = val;
    }

    cout << "\nRandomly generated array:\n\n[";
    for (int i = 0; i < n; i++)
    {
        cout << arr1[i];
        if (i != n - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    
    // Sequential Bubble Sort
    auto start_bubble = high_resolution_clock::now();
    bubble_sort(n, arr1);
    auto end_bubble = high_resolution_clock::now();
    auto duration_bubble = duration_cast<microseconds>(end_bubble - start_bubble);
    
    cout << "\nSequential Bubble Sort Time: "<< duration_bubble.count() << " ms" << endl;

    // Parallel Bubble Sort
    auto start_bubble2 = high_resolution_clock::now();
    parallel_bubble_sort(n, arr2);
    auto end_bubble2 = high_resolution_clock::now();
    
    auto duration_bubble2 = duration_cast<microseconds>(end_bubble2 - start_bubble2);
    cout << "Parallel Bubble Sort Time: " << duration_bubble2.count() << " ms" << endl;

    return 0;
}