#include<bits/stdc++.h> 
using namespace std;
//Build a stack with the of linked list
struct Node{
    int data;
    Node* next;

    Node(int d){
        data = d;
        next = nullptr;
    }
};

struct Stack{
    Node* head; // head la pointer tro toi Top cua Stack
    int size; // Maximum elements that Stack can holds
    Stack(int s){//constructor - hàm dựng; Buil Stack with max size (s)
        head = nullptr; // empty stack 
        size = s;
    }

    bool push(int d){
        if(isFull()){
            return false;
        }else{
            Node* newNode = new Node(d); // create new node with data d
            if(head == nullptr){
                head = newNode;
            }else{
                newNode->next = head;
                head = newNode;
            }

            return true; //insert thanh cong
        }
    }

    int pop(){
		if(isEmpty()){
			return -1;
		}else{
            Node* temp = head;
            int d = head->data; // luu gia tri cua head vao d de return
            head = head->next;
            delete temp;
            temp = nullptr;
            return d;
		}	
	}

    bool isEmpty(){
        return head == nullptr;
    }

    bool isFull(){
        int ct = 0; //ct holds the number of nodes
        Node* temp = head;
        while(temp != nullptr){
            ct++;
            temp = temp->next;
        }
        return ct == size;
    }

    int peek(){
		if(head == NULL){
			return -1;
		}else{
			return head->data;
		}
	}

    void displayStack(){
        // Top->Bottom: 2->4->5->1
        if(isEmpty()){
            cout << "Stack is empty!";
        }else{
            cout << "Top->Bottom: ";
            Node* temp = head;
            while(temp->next != nullptr){ //neu temp la Node khong phai la node cuoi -> in ra theo format: data->
                cout << temp->data << "->";
                temp = temp->next;
            }
            cout << temp->data; // in ra data cuar Node cuoi cung.
            cout << endl;
        }
    }
};

int main(){
    Stack stack(5);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    if(stack.push(6) == false){
        cout << "Stack is full, cannot put new item" << endl;
    };
    stack.displayStack();
    cout << "Remove: " << stack.pop() << endl;
    cout << "Remove: " << stack.pop() << endl;
    cout << "Top after remove: " << stack.peek() << endl;
    stack.displayStack();

}
