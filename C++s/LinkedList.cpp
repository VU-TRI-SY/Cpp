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
    void add(int d, int position){
        if(head == nullptr){
            Node* newNode = new Node(d);
            head = newNode; // insert new node to empty list
        }else{
            Node* prev = nullptr;
            Node* cur = head; // khoi tao cur bang head -> di tu dau cua list
            int index = 0;
            while(cur != nullptr && index != position){ // loop: lap den khi nao ma cur != null va index < position
                prev = cur;
                cur = cur->next;
                index++;            
            }
            //vong while ket thuc -> index = position -> prev se chi vao Node ma can phai insert new Node vao sau no
            if(index < position){
                cout << "Position out of index" << endl;
                return; // dung lai luon
            }

            Node* newNode = new Node(d);
            if(prev == nullptr){ // insert vao index 0 -> new node tro thanh header
                newNode->next = head;
                head = newNode;
                prev = newNode;
            }else{
                //insert vao giua cur va prev
                newNode->next = cur;
                prev->next = newNode;
            }

        }
    }

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
    bool removeAtIndex(int index){

    }

    void read(){
        Node * temp = head;
        while(temp != NULL){
            cout << temp->data << " ";
            temp = temp ->next;
        }
        cout << endl;
    }

    bool search(int d){
        if(head == nullptr){
            return false;
        }else{
            Node* temp = head;
            while(temp != nullptr){
                if(temp->data == d){
                    return true;
                }

                temp = temp->next;
            }
            return false;
        }
    }
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