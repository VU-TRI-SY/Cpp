#include <bits/stdc++.h>
using namespace std;
template <class T>

int main(){
    int arr[100]; // static allocate -> take 4 * 100 = 400 bytes from stack memory for array
    int* parr;
    parr = new int[100]; // dynamic allocate -> take 4 * 100 = 400 bytes from heap memory for array
    //delete : de-allocate the memory that is allocated by new
}