#include<bits/stdc++.h>
using namespace std;

// xay dung 1 liked list
// add, remove, read, search

struct Node{
    int data;
    Node* next; // vi next link toi Node tiep theo -> Node*

    Node(int d){
        data = d;
        next = nullptr;
    }
};

struct LinkedList{
    Node* head; // pointer point to the first node of liked list
    LinkedList(){
        head = nullptr;
    }
    void add(int d){
        Node* newnode = new Node(d); // tao ra mot Node moi
        if(head == nullptr){
            head = newnode;
        }else{
            Node* temp = head;
            Node* prev = nullptr; // neu temp chi vao mot Node nao do, thi prev point vao Node dung truoc temp
            while(temp != nullptr){
                prev = temp;
                temp = temp -> next; // di chuyen temp sang Node tiep theo
            }
            prev->next = newnode;
        }
    }; // add vao cuoi list
    void add(int d, int poisition);
    bool remove(int d){
        Node* temp = head;
        Node* prev = NULL;
        while(temp != NULL){
            if(temp->data == d){
                prev->next = temp->next;
                delete temp;
                return true;
            }else{
                prev = temp;
                temp = temp->next;
            }
        }
        return false;
    }; // xoa Node ma co data = d -> neu xoa thanh cong -> return true, nguoc lai false
    bool removeAtIndex(int index);
    void read(){
        Node * temp = head;
        while(temp != NULL){
            cout << temp->data << " ";
            temp = temp ->next;
        }
        cout << endl;
    }
    bool search(int d);
};

int main(){
    LinkedList l;
    l.add(10);
    l.add(100);
    l.add(101);
    l.add(102);
    l.read();
    if(l.remove(100)){
        cout << "Removed 1000 from list\n";
    }else{
        cout << "Nothing to remove\n";
    }
    l.read();
}