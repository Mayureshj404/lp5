#include <omp.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Display Array
void displayArray(int nums[], int length)
{
    cout << "Nums: [";
    for (int i = 0; i < length; i++) {
        cout << nums[i];
        if (i != length - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

// Parallel Min Operation
void minOperation(int nums[], int length)
{
    int minValue = nums[0];
#pragma omp parallel for reduction(min : minValue)
    for (int i = 0; i < length; i++) {
        if (nums[i] < minValue)
        {
            minValue = nums[i];
        }
    }
    cout << "Min value: " << minValue << endl;
}

// Parallel Max Operation
void maxOperation(int nums[], int length)
{
    int maxValue = nums[0];
#pragma omp parallel for reduction(max : maxValue)
    for (int i = 0; i < length; i++) {
        if (nums[i] > maxValue)
        {
            maxValue = nums[i];
        }
    }
    cout << "Max value: " << maxValue << endl;
}

// Parallel Sum Operation
void sumOperation(int nums[], int length)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++) {
        sum += nums[i];
    }
    cout << "Sum: " << sum << endl;
}

// Parallel Average Operation
void avgOperation(int nums[], int length)
{
    float sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++) {
        sum += nums[i];
    }
    cout << "Average: " << (sum / length) << endl;
}

// Main Function
int main()
{

    srand(time(0)); // Seed for random number generator

    int length;
    cout << "Enter number of random elements to generate: ";
    cin >> length;

    int nums[length];

    for (int i = 0; i < length; ++i) {
        nums[i] = rand() % 100 + 1; 
    }

    displayArray(nums, length);

    auto start = high_resolution_clock::now();

    minOperation(nums, length);
    maxOperation(nums, length);
    sumOperation(nums, length);
    avgOperation(nums, length);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nParallel Execution time: " << duration.count() << " ms" << endl;

    return 0;
}
