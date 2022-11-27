#include<bits/stdc++.h>
using namespace std;
struct Car{
    string id; //bien so
    string name; //volve, mazda
};

struct Node{
    Car c;
    Node* next;

    Node(Car c_){
        c = c_;
        next = nullptr;
    }
};

struct Queue{
    Node* head;
    Node* tail;
    int capacity;

    Queue(){
        head = nullptr;
        tail = nullptr;
        capacity = 5;
    }

    
    bool empty(){
    	return head == NULL;
	};
    bool full(){
    	int count = 0;
		Node* temp = head;
		while(temp != NULL){
			count++;
			temp = temp -> next;
		}
		return count == capacity;
    }
	bool enqueueCar(Car c){
        if(full()){
            return false;
        }else{
            Node* newnode = new Node(c); 
            if(head == NULL){ 
                head = newnode;
                tail = newnode;
            }else{ 
                tail -> next = newnode; 
                tail = newnode;
            }
            return true;
        }
    }
    Node* dequeueCar(){
        Node* res = nullptr;
        if(empty()){
            return nullptr; 
        }else{
            if(head == tail){ 
                delete head;
                head = NULL;
                tail = NULL;
            }else{
                Node* temp = head;
                head = head->next;
                res = temp;
                delete temp;
                temp = NULL;
            }
            return res;
        }
    }
    Node* front(){
        return head;
	};
    Node* back(){
	    return tail;
	}; 
	void display(){
		if(empty()){
			cout << "Queue is empty";
		}else{
			cout << "Car's info: " << endl;
			Node* temp = head;
            int i = 1;
			while(temp != NULL){ // in ra n node
                cout << "Car number " << i << ": " << endl;
				cout << "Car id: " << temp->c.id << endl;
				cout << "Car name: " << temp->c.name << endl;
				temp = temp -> next;
                i++;
			} 
            
		}
	}
};

int main(){
	Queue cars;
	string id;
	string name;
    int choice;
    Car c;	
	while(true){
		cout << "1. Car entered" << endl;
		cout << "2. Car removed" << endl;
		cout << "3. Car in parking" << endl;
		cout << "4. First car" << endl;
		cout << "5. Last car" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore(1000, '\n');  //clear buffer
		switch(choice){
			case 1:
                cout << "Enter car's id: ";
                getline(cin, c.id);
                cout << "Enter car's name: ";
                getline(cin, c.name); //getline -> '\n' sẽ được đọc -> k cần clear buffer
                // cin.ignore(1000, '\n'); 
				if(cars.enqueueCar(c)){
                    cout << "Add car's info successfully" << endl;
                }
                else{
                    cout << "Add car's info failed" << endl;
                }
				break;
			case 2:
                if(cars.dequeueCar()){
                    cout << "This car is removed" << endl;
                }else{
                    cout << "No car is removed" << endl;
                }
				break;
			case 3:
				cars.display();
				break;
			case 4:
				if(cars.front() == NULL){
					cout << "Queue is empty";
				}else{
					cout << cars.front()->c.id << " " <<  cars.front()->c.name;
				}
				break;
			case 5:
				if(cars.back() == NULL){
					cout << "Queue is empty";
				}else{
					cout << cars.back()->c.id << " " <<  cars.back()->c.name;
				}
				break;	
			case 6:
				cout << "Good bye!" << endl;
				exit(0); 
				break;
			default:
				cout << "Invalid choice!" << endl;
				break;
		}
	}    
}
