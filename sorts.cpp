#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

void maxHeapify(vector<float> &arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(vector<float> &arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void heapSortDesc(vector<float> &arr)
{
    int n = arr.size();

    buildMaxHeap(arr);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

void minHeapify(vector<float> &arr, int n, int i)
{
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] < arr[smallest])
        smallest = l;

    if (r < n && arr[r] < arr[smallest])
        smallest = r;

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(vector<float> &arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

void heapSortAsc(vector<float> &arr)
{
    int n = arr.size();

    buildMinHeap(arr);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }
}

void quickSortAsc(vector<float> &arr, int left, int right)
{
    int i = left, j = right;
    float pivot = arr[(left + right) / 2];
    while (i <= j)
    {
        while (arr[i] < pivot) 
            i++;
        while (arr[j] > pivot) 
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j)
        quickSortAsc(arr, left, j);
    if (i < right)
        quickSortAsc(arr, i, right);
}


void quickSortDesc(vector<float> &arr, int left, int right)
{
    int i = left, j = right;
    float pivot = arr[(left + right) / 2];
    while (i <= j)
    {
        while (arr[i] > pivot)
            i++;
        while (arr[j] < pivot)
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j)
        quickSortDesc(arr, left, j);
    if (i < right)
        quickSortDesc(arr, i, right);
}

void mergeAsc(vector<float> &arr, int left, int mid, int right)
{
    vector<float> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] > arr[j])  
        {
            temp[k] = arr[j];
            j++;
        }
        else
        {
            temp[k] = arr[i];
            i++;
        }
        k++;
    }
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i - left];
    }
}

void mergeSortAsc(vector<float> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSortAsc(arr, left, mid);
        mergeSortAsc(arr, mid + 1, right);
        mergeAsc(arr, left, mid, right);
    }
}


void mergeDesc(vector<float> &arr, int left, int mid, int right)
{
    vector<float> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
        {
            temp[k] = arr[j];
            j++;
        }
        else
        {
            temp[k] = arr[i];
            i++;
        }
        k++;
    }
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i - left];
    }
}

void mergeSortDesc(vector<float> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSortDesc(arr, left, mid);
        mergeSortDesc(arr, mid + 1, right);
        mergeDesc(arr, left, mid, right);
    }
}

int main()
{
    vector<vector<float>> numbers(10, vector<float>(1000000));
    vector<vector<float>> original_numbers(10, vector<float>(1000000));

    ifstream input("10bodulieu.txt");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 1000000; j++)
        {
            input >> original_numbers[i][j];
            numbers[i][j] = original_numbers[i][j];
        }
    }
    input.close();

    vector<string> output(10);

    for (int i = 0; i < 10; i++)
    {
        string filename = "sorted_numbers_" + to_string(i) + ".txt";
        ofstream output_file(filename);

        if (i == 0) {
            // sort in descending order
            auto start = high_resolution_clock::now();
            heapSortAsc(numbers[i]);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count()) + " ";

            //output_file << "HeapSort: "; 
            for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;

            start = high_resolution_clock::now();
            quickSortDesc(numbers[i], 0, 999999);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count()) + " ";

            //output_file << "quickSortDesc: "; 
            for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;

            start = high_resolution_clock::now();
            mergeSortDesc(numbers[i], 0, 999999);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count()) + " ";

            //output_file << "MergeSort: "; 
            for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;

            start = high_resolution_clock::now();
            sort(numbers[i].begin(), numbers[i].end(), greater<float>());
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count());

            //output_file << "Built-inSort: "; 
             for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;
        }
        else {
            // sort in ascending order
            auto start = high_resolution_clock::now();
            heapSortDesc(numbers[i]);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count()) + " ";

            //output_file << "HeapSort: "; 
            for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;

            start = high_resolution_clock::now();
            quickSortAsc(numbers[i], 0, 999999);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count()) + " ";

            //output_file << "quickSortDesc: "; 
            for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;

            start = high_resolution_clock::now();
            mergeSortAsc(numbers[i], 0, 999999);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count()) + " ";

            //output_file << "MergeSort: "; 
            for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;

            start = high_resolution_clock::now();
            sort(numbers[i].begin(), numbers[i].end());
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            output[i] += to_string(duration.count());

            //output_file << "Built-inSort: "; 
             for (int j = 0; j < 1000000; j++)
            {
                //output_file << numbers[i][j] << " ";
                numbers[i][j] = original_numbers[i][j];
            }
            //output_file << endl;

        }
    }
    
    ofstream output_file("sorting_times.txt");
    for (int i = 0; i < 10; i++)
    {
        output_file << output[i] << endl;
    }
    output_file.close();

    return 0;
}
