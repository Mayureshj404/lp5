#include <omp.h>
#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;

void displayArray(string message, int nums[], int length)
{
    cout << "\t" << message << ": [";
    for (int i = 0; i < length; i++)
    {
        cout << nums[i];
        if (i != length - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

void merge(int nums[], int leftStart, int leftEnd, int rightStart, int rightEnd)
{
    int n = (rightEnd - leftStart) + 1; // Size of both arrays
    int tempArray[n];

    int t = 0;           // Index for temporary array
    int l = leftStart;   // Index for left array
    int r = rightStart;  // Index for right array

    // Merge both arrays into tempArray
    while (l <= leftEnd && r <= rightEnd)
    {
        if (nums[l] <= nums[r])
            tempArray[t++] = nums[l++];
        else
            tempArray[t++] = nums[r++];
    }

    // Copy remaining elements from left array
    while (l <= leftEnd)
        tempArray[t++] = nums[l++];

    // Copy remaining elements from right array
    while (r <= rightEnd)
        tempArray[t++] = nums[r++];

    // Copy back to original array
    for (int i = 0; i < n; i++)
        nums[leftStart + i] = tempArray[i];
}

void mergeSort(int nums[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
#pragma omp parallel sections num_threads(2)
        {
#pragma omp section
            mergeSort(nums, start, mid);
#pragma omp section
            mergeSort(nums, mid + 1, end);
        }
        merge(nums, start, mid, mid + 1, end);
    }
}

int main()
{
    srand(time(0)); // Seed for random number generator

    int n;
    cout << "Enter number of random elements to generate: ";
    cin >> n;

    int arr[n];

    for (int i = 0; i < n; ++i) {
        int val = rand() % 100 + 1; // Random numbers between 1 and 100
        arr[i] = val;
    }
    
    cout << "\nMerge Sort:" << endl;
    displayArray("Before", arr, n);

    auto start_merge = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end_merge = high_resolution_clock::now();

    displayArray("After", arr, n);
    auto duration_merge = duration_cast<microseconds>(end_merge - start_merge);
    cout << "\nExecution time for Merge Sort: " << duration_merge.count() << " microseconds" << endl;

    return 0;
}