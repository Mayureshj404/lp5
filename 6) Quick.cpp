#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;


int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }

        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void sequentialQuickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pIndex = partition(arr, low, high);
        sequentialQuickSort(arr, low, pIndex - 1);
        sequentialQuickSort(arr, pIndex + 1, high);
    }
}

void parallelQuickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pIndex = partition(arr, low, high);

#pragma omp task shared(arr)
        {
            parallelQuickSort(arr, low, pIndex - 1);
        }

#pragma omp task shared(arr)
        {
            parallelQuickSort(arr, pIndex + 1, high);
        }
    }
}

int main() {
    int n;
    cout<<"Enter the no of elemets in the array:";
    cin>>n;
    // Initialize random seed
    srand(time(nullptr));

    // Generate a random array
    vector<int> arr(n);
    for (int& num : arr) {
        num = rand() % 10000; // Generate random numbers between 0 and 9999
    }

    // Make a copy of the array for parallel sorting
    vector<int> arr_parallel = arr;
    
    //Print
    cout<<"Before Merge Sort :- \n[";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
        if (i != n - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    // Measure the execution time of sequential quick sort
    auto start1 = high_resolution_clock::now();
    sequentialQuickSort(arr, 0, arr.size() - 1);
    auto end1 = high_resolution_clock::now();
    auto sequential_time = duration_cast<microseconds>(end1 - start1);

    // Measure the execution time of parallel quick sort
    auto start2 = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        parallelQuickSort(arr_parallel, 0, arr_parallel.size() - 1);
    }
    auto end2 = high_resolution_clock::now();
    auto parallel_time = duration_cast<microseconds>(end2 - start2);
    
    cout<<"After Merge Sort :- \n[";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
        if (i != n - 1)
            cout << ", ";
    }
    cout << "]" << endl;
    
    // Print the sorted arrays
    cout << "Sequential Quick Sort: " << sequential_time.count() << "\n";
    cout << "Parallel Quick Sort: " << parallel_time.count() << "\n";

    return 0;
}
