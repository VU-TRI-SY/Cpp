#include<bits/stdc++.h>
using namespace std;
int partition(vector<int>& vec, int first, int last)
{
    int pivot = vec[last]; // pivot
    int id_pivot;
    vector<int> left;
    vector<int> right;
    for(int i = first; i <= last-1; i++){
        if(vec[i] > pivot){
            right.push_back(vec[i]);
        }else{
            left.push_back(vec[i]);
        }
    }
    int id = first; // index in vec, start from first
    for(int i = 0; i < left.size(); i++){
        vec[id] = left[i];
        id++;
    }

    vec[id] = pivot;
    id_pivot = id;
    id++;
    
    for(int i = 0; i <= right.size(); i++){
        vec[id] = right[i];
        id++;
    }

    return id_pivot;

}
int main(){
    vector<int> v;
    v.push_back(10);
    v.push_back(80);
    v.push_back(30);
    v.push_back(90);
    v.push_back(40);
    v.push_back(50);
    v.push_back(70);
    v.push_back(20);
    v.push_back(60);
    int pi = partition(v, 0, v.size()-1);
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    cout << pi << endl;
}