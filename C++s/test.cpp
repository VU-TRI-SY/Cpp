#include<bits/stdc++.h>
using namespace std;

struct Node{
	int data;
	Node* next;
	
	Node(int d){
		data = d;
		next = NULL;
	}
};
struct Stack{
	Node* head;
	int size;
	Stack(int s){
		head = NULL;
		size = s;
	}
	bool push(int d){
		if(isFull()){
			return false;
		}else{
			Node* newnode = new Node(d);
			if(head == NULL){
				head = newnode;
			}else{
				newnode->next = head;
				head = newnode;
			}
			return true;
		}
		
    }

	
	int pop(){
		if(isEmpty()){
			return -1;
		}else{
			Node* temp = head;
			int d = head->data;
			head = head -> next;
			delete temp;
			temp = NULL;
			return d;
	    }    
	}
	bool isEmpty(){
		if(head == NULL){
			return true;
		}else{
			return false;
		}
	}
	bool isFull(){
		int count = 0;
		Node* temp = head;
		while(temp != NULL){
			count++;
			temp = temp -> next;
		}
		return count == size;
    }
	int peek(){
		if(head == NULL){
			return -1;
		}else{
            return head -> data;
		}
	}
	void displayStack(){
		if(isEmpty()){
			cout << "stack is empty";
		}else{
			cout << "top to bottom: ";
			Node* temp = head;
			while(temp->next != NULL){
				cout << temp->data << "->";
				temp = temp -> next;
			}
            cout << temp->data;
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
    stack.displayStack(); //in ra stack
}
