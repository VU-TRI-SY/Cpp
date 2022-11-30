#ifndef SORTS_H_
#define SORTS_H_
#include <iostream>
#include <vector>

using namespace std;
class Sorts
{
public:
    void InsertionSort(vector<int>& vec, int size);
    void BubbleSort(int arr[], int n);
    void MergeSort(vector<int>& vec, int first, int last);
    void IterativeMergeSort(vector<int>& vec, int first, int last);
    void Merge(vector<int>& vec, int first, int mid, int last);
    void QuickSort(vector<int>& vec, int first, int last);
    void ShellSort(vector<int>& vec, int first, int last);
private:
    vector<int>& vec;
    // int first_;
    // int mid_;
    // int last_;
    // int pivot_;
};
#endif

void InsertionSort(vector<int>& vec, int first, int last)
{
    for (int place = first + 1; place <= last; place++)
    {
        int tmp = vec[place];
        int i = place;
        while ((i > 0) && (vec[i - 1] > tmp))
        {
            vec[i] = vec[i - 1];
            i--;
        }
        vec[i] = tmp;
    }
}

void BubbleSort(int arr[], int n)
{
    int check = 1; // check that has 2 elements a[i] and a[i+1] that a[i] > a[i+1]
    while (check) {
        check = 0; // assume that has no adjcent elements that a[i] > a[i+1]
        for (int i = 0; i <= n - 2; i++) {
            if (arr[i] > arr[i + 1]) {
                // swap(arr[i], arr[i+1]);
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                check = 1;
            }
        }
    }
}

void BubbleSort(vector<int>& vec, int first, int last)
{
    int check = 1; // check that has 2 elements a[i] and a[i+1] that a[i] > a[i+1]
    while (check) {
        check = 0; // assume that has no adjcent elements that a[i] > a[i+1]
        for (int i = first; i <= last-1; i++) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i+1]);
                check = 1;
            }
        }
    }
}
void Merge(vector<int>& vec, int first, int mid, int last) //we want reference, not copy
{
    int size = last - first + 1;
    int* tmp_arr;
    tmp_arr = new int[size];

    //set indexes for beginning and end of each subarray
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = 0;

    while ((first1 <= last1) && (first2 <= last2))
    {
        if (vec[first1] < vec[first2])
        {
            tmp_arr[index] = vec[first1];
            first1++;//move first1 forward
        }
        else
        {
            tmp_arr[index] = vec[first2];
            first2++;//move first2 forward
        }
        index++;

    }
    //when the second array is shorter than then first
    while (first1 <= last1)
    {
        tmp_arr[index] = vec[first1];
        first1++;
        index++;
    }
    //when the first array is shorter than then second
    while (first2 <= last2)
    {
        tmp_arr[index] = vec[first2];
        first2++;
        index++;
    }

    for (index = 0; index < size; index++)
    {
        vec[first] = tmp_arr[index];
        first++;
    }
    delete[] tmp_arr;
}

void MergeSort(vector<int>& vec, int first, int last)
{
    if (first == last)
    {
        return;
    }
    else
    {
        //So the mergesort handles the lower half and 
        //then the next call of merge sort handles the upper half
        //Once those are done, they are combined in merge
        int mid = (first + last) / 2;
        MergeSort(vec, first, mid);
        MergeSort(vec, mid + 1, last);
        Merge(vec, first, mid, last);
    }
}

// void IterativeMergeSort(vector<int>& vec, int first, int last)
// {
//     int mid = 
// }

// void QuickSort(vector<int>& vec, int first, int last) 
// {
//     //base case
//     if (last - first < 5) //last <= first
//     {
//         InsertionSort(vec, first, last); 
//         return;
//     }
//     //do partitions
//     int mid = (first + last) / 2;
//     //sort first, mid, last values
//     if (vec[first] > vec[last])
//     {
//         swap(vec[first], vec[last]);
//     }
//     if (vec[first] > vec[mid])
//     {
//         swap(vec[first], vec[mid]);
//     }
//     if (vec[mid] > vec[last])
//     {
//         swap(vec[mid], vec[last]);
//     }
//     int pivot = vec[mid];
//     swap(vec[mid], vec[last - 1]);// vec[last-1] hold the value of pivot
//     int left = first + 1;
//     int right = last - 2;
//     bool done = false;
//     while (!done)
//     {
//         while (vec[left] < pivot)
//         {
//             left++;
//         }//vec[left] >= pivot
//         while (vec[right] > pivot)
//         {
//             right--;
//         }//vec[right] <= pivot
//         if (right > left)
//         {
//             swap(vec[left], vec[right]);
//             right--;
//             left++;
//         }
//         else
//         {
//             done = true;
//         }
//         if(vec[left] > vec[last-1]){
//             swap(vec[left], vec[last - 1]);
//         }
//     QuickSort(vec, first, left - 1);
//     QuickSort(vec, left + 1, last);
//     }
// }

// int partition(vector<int>& vec, int first, int last)
// {
//     int pivot = vec[last]; // pivot
//     int i = (first - 1); // Index of smaller element and indicates
//     // the right position of pivot found so far
  
//     for (int j = first; j <= last - 1; j++) {
//         // If current element is smaller than the pivot
//         if (vec[j] < pivot) {
//             i++; // increment index of smaller element
//             swap(vec[i], vec[j]);
//         }
//     }
//     swap(vec[i + 1], vec[last]);
//     return (i + 1);
// }

int partition(vector<int>& vec, int first, int last)
{
    int pivot = vec[last]; // pivot
    int j = first-1;
    for(int i = first; i < last; i++){
        if(pivot >= vec[i]){
            j++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[j+1], vec[last]);
    return j+1;

}
  
void QuickSort(vector<int>& vec, int first, int last)
{
    if(last - first < 5){
        InsertionSort(vec, first, last);
        return;
    }
    /* pi is partitioning index, arr[p] is now
    at right place */
    int pi = partition(vec, first, last); //pi is index of pivot

    // Separately sort elements before
    // partition and after partition
    QuickSort(vec, first, pi - 1);
    QuickSort(vec, pi + 1, last);
}

void ShellSort(vector<int>& vec, int first, int last)
{
    int size = last - first + 1;
    for (int gap = size / 2; gap > 0; gap = (gap == 2) ? 1 : int(gap / 2.2))
    {
        for (int i = gap; i < size; i++)
        {
            int tmp = vec[i];
            int j = i;
            for (; (j >= gap) && (tmp < vec[j - gap]); j -= gap)
            {
                vec[j] = vec[j - gap];
            }
            vec[j] = tmp;
        }
    }

}

void SelectionSort(vector<int>& vec, int first, int last){ //sorted | unsorted
    for(int i = first; i <= last; i++){
        //unsorted begin at i
        int id_min = i;
        for(int j = i+1; j <= last; j++){
            if(vec[id_min] > vec[j]){
                id_min = j;
            }
        }
        swap(vec[id_min], vec[i]);
    }
}
