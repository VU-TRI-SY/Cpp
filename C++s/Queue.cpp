#include<bits/stdc++.h>
using namespace std;
struct Node{
    int data;
    Node* next;

    Node(int d){
        data = d;
        next = nullptr;
    }
};
struct Queue{
    //head to delete
    //tail to insert
    Node* head;
    Node* tail; 
    int capacity; //maximum elements that queue can holds
    Queue(int s){
        capacity = s;
        head = nullptr;
        tail = nullptr;
    }

    bool enqueue(int d){
        if(full()){
            return false;
        }else{
            Node* newnode = new Node(d); //ok
            if(head == NULL){ 
                head = newnode;
                //tail????
                tail = newnode;
            }else{ 
                tail -> next = newnode; //ok
                // ??update tail????
                tail = newnode;
            }
            return true;
        }
    }
    bool dequeue(){
        //1. check empty or not
        //2. if not empty -> delete head
        //2.1: head and tail point to a Node (Queue has only 1 element) -> delete head -> tail must point to null
        //2.2: head != tail -> queue has mor than 1 elements -> delete head normally
        if(empty()){
            return false; //ok
        }else{
            if(head == tail){ //has 1 element
                delete head;
                head = NULL;
                tail = NULL;
            }else{
                Node* temp = head;
                head = head->next;
                delete temp;
                temp = NULL;
            }
            return true;
        }
    }
    bool empty(){
    	return head == NULL;
	}; //ok

    bool full(){
    	int count = 0;
		Node* temp = head;
		while(temp != NULL){
			count++;
			temp = temp -> next;
		}
		return count == capacity;
    } //ok

    Node* front(){
        return head;
	};// return the address of Node at head
    Node* back(){
        return tail;
    } //return the address of Node at tail

    void display(){
		if(empty()){
			cout << "queue is empty";
		}else{
			cout << "queue: ";
			Node* temp = head;
			while(temp->next != NULL){ // n-1
				cout << temp->data << "->";
				temp = temp -> next;
			}
			cout << temp->data; //node thu n
			cout << endl;
		}
	}
};

int main(){
    Queue queue(5);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.display();
    queue.dequeue();
    queue.display();


    Node* tp = queue.back();
    if(tp == NULL){
        cout << "queue is empty";
    }else{
        cout << "back: " << tp->data << endl;
    }
}

// áp dụng build queue với linked list để làm 1 bài tập khác(lớn hơn)
// build queue với mảng
