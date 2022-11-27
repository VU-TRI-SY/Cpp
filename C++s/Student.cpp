#include <bits/stdc++.h>
using namespace std;
struct Student{
	string id;
	string name;
	string clss;
	int age;
	
	Student(string id_, string name_, string clss_, int age_){
		id = id_;
		age = age_;
		name = name_;
		clss = clss_;
	}

	Student(){
		id = "";
		name = "";
		clss = "";
		age = 0;
	}
	
};
struct Node{
	Student st;
	Node* next;
    Node(Student std){
    	st = std;
    	next = NULL;
	}//ok
};


//add sv - add
//in thong tin sv - read
//tim kiem sv theo msv - search 
//sua thong tin 1 sv theo msv
//xoa sv theo msv - remove
//ghi thong tin cac sinh vien vao file student_out.txt
//thoat ctrinh


struct LinkedList{
    Node* head; 
    LinkedList(){ //tao empty linked list
        head = NULL;
    } //ok
    void addSt(Student st){
        Node* newnode = new Node(st);
        if (head == NULL){
            head = newnode;
        }else{
            Node* temp = head;
            Node* prev = NULL;
            while (temp != NULL){
                prev = temp;
                temp = temp -> next;
            }
            prev -> next = newnode;
        }

    }; //ok

	bool addSt(){
		//1. Yeu cau nhap vao thong tin cho student do
		//2. Tao ra mot Node moi dua theo student tren
		//3. Add
		string id, name, clss;
		int age;
		cout << "ID: "; cin >> id;
		cout << "Name: "; cin >> name;
		cout << "Class: "; cin >> clss;
		cout << "Age: "; cin >> age;
		cin.ignore(1000, '\n'); // vi sau khi nhap vao age va an enter -> buffer se chua '\n -> clear buffer
		Student st(id, name, clss, age);

		// tao Node moi
		Node* newNode = new Node(st);
		// insert Node do vao trong list
		if (head == NULL){
            head = newNode;
			return true;
        }else{
            Node* temp = head;
            Node* prev = NULL;
            while (temp != NULL){
                prev = temp;
                temp = temp -> next;
            }
            prev -> next = newNode;
			return true;
        }
		return false;
	}

    bool addSt(Student st, int position){ // add thanh cong -> return true; add fail -> return false
    	if (head == NULL){ //list is empty
    		if(position == 0){ // add newNode thanh header
    			Node* newnode = new Node(st);
    			head = newnode;
                return true; //add vao head thanh cong
            }else{
                return false; //vi list rong ma position != 0 -> position khong hop le
            }
		}else{
			Node* prev = NULL;
			Node* curr = head;
			int index = 0;
			while (curr != NULL && index != position){
				prev = curr;
				curr = curr -> next;
				index++;
			}
			Node* newnode = new Node(st);
			if(index < position){
				return false; // add fail
			}

			if(prev == NULL){ //add vao dau
				newnode -> next = head;
				head = newnode;
				prev = newnode;
			}else{
				newnode -> next = curr;
				prev -> next = newnode;
			}
            return true; // add thanh cong
		}
 
	};
    bool removeStu(string id){ //xoa sinh vien theo ID
		Node* temp = head;
		Node* prev = NULL;
		while (temp != NULL){
			if (temp->st.id == id){ //xoa hoc sinh nay
				if(prev == NULL){//cur = head - phai xoa head
                    head = head->next;
                    delete temp;
                    temp = NULL;
                    return true;
                }else{
                    prev->next = temp->next;
                    delete prev;
                    prev = NULL;
                    return true;
                }
			}else{
				prev = temp;
				temp = temp -> next; 
			}
		}
		return false;
	}; 
    bool removeAtIndex(int position){
    	if (head == NULL){
    		return false;
		}else{
			Node* curr = head;
			Node* prev = NULL;
			int index = 0;
			while(curr != NULL && index != position){
				prev = curr;
				curr = curr -> next;
				index++;
			}
			if (index < position){
				return false;
			}
			if (index == position && curr == NULL){
				return false;
			}

			if (prev == NULL){ //xoa head
				head = curr -> next;
				delete curr;
				curr = NULL;
				return true;
			}
			else{
				prev -> next = curr -> next;
				delete curr;
				curr = NULL;
				return true;
			}
			
		}
	};//ok

    void readStu(){
        Node* temp = head;
        int i = 1;
        while (temp != NULL){
            cout << i << "." << endl;
            cout << "ID: " << temp->st.id << endl;
            cout << "Name: " << temp->st.name << endl;
            cout << "Class: " << temp->st.clss << endl;
            cout << "Age: " << temp->st.age << endl; 
            temp = temp -> next;
            i++;
        }
    };

    bool searchStu(string id){ 
    	if(head == NULL){
    		return false;
		}
		else{
			Node* prev = head;
			while(prev != NULL){
				if (prev->st.id == id){
					return true;
				}
				prev = prev -> next;
			}
			return false;
		}
	};//ok

    bool updateStu(string id, string name_, string class_, int age_){ // return true neu update thanh cong va false neu khong update
        //1.search
        //2. neu search thay trung -> update
		if(head == NULL){
    		return false;
		}
		else{
			Node* prev = head;
			while(prev != NULL){
				if (prev->st.id == id){
					//prev la Node ma minh can phai update thong tin cho Student
					prev->st.name = name_;
					prev->st.clss = class_;
					prev->st.age = age_;
					return true;
				}
				prev = prev -> next;
			}
			return false;
		}
    }
};

int main(){

	//viet menu
    LinkedList stu;
	int choice;
	string id;
	string name;
	string clss;
	int age;
	int index;
	while(true){
		cout << "1. Add student" << endl;
		cout << "2. Remove student" << endl;
		cout << "3. Remove student at index" << endl;
		cout << "4. Search student" << endl;
		cout << "5. Update student" << endl;
		cout << "6. Display student" << endl;
		cout << "7. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore(1000, '\n'); //clear buffer
		switch(choice){
			case 1:
				stu.addSt();
				break;
			case 2:
				cout << "Enter ID of student to remove: "; cin >> id;
				cin.ignore(1000, '\n');
				if(stu.removeStu(id)){
					cout << "Student with ID " << id << "has been removed" << endl;
				}
				else{
					cout << "Not found student with ID " << id << endl;
				}
				break;
			case 3:
				cout << "Enter index of student to remove: "; cin >> index;
				cin.ignore(1000, '\n');
				if(stu.removeAtIndex(index)){
					cout << "Remove successfully" << endl;
				}else{
					cout << "Cannot remove" << endl;
				}
				break;
			case 4:
				cout << "Enter ID of student to search: " ; cin >> id;
				cin.ignore(1000, '\n');
				if(stu.searchStu(id)){
					cout << "Found" << endl;
				}else{
					cout << "Not found" << endl;
				}
				break;
			case 5:
				cout << "Enter information of student to update: " << endl;
				cout << "ID: "; cin >> id;
				cout << "Name: "; cin >> name;
				cout << "Class: "; cin >> clss;
				cout << "Age: "; cin >> age;
				cin.ignore(1000, '\n');
				if(stu.updateStu(id, name, clss, age)){
					cout << "Update successfully" << endl;
				}else{
					cout << "Update fail" << endl;
				}
				break;
			case 6:
				cout << "All students:" << endl;
				stu.readStu();
				break;
			case 7:
				cout << "Good bye!" << endl;
				exit(0); //thoat chuong trinh
				break;
			default:
				cout << "Invalid choice!" << endl;
				break;
		}
	}

}
