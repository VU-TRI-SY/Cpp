#ifndef LIST342_H_
#define LIST342_H_

#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

template<class ObjectType>
class List342
{
//attributes, methods
public:
	//Constructor and destructor
	List342();
	virtual ~List342();
	List342(const List342& source);// copy constructor

	//Action
	bool BuildList(string file_name);
	bool Insert(ObjectType* obj);
	bool Remove(ObjectType target, ObjectType& result);
	bool Peek(ObjectType target, ObjectType& result) const;
	int Size() const;
	void DeleteList();
	bool Merge(List342<ObjectType>& list1);

	// Overloading Operator 
	List342<ObjectType>& operator=(const List342<ObjectType>& source);
	List342<ObjectType> operator+(const List342<ObjectType>& rhs) ;
	List342<ObjectType>& operator+=(const List342<ObjectType>& rhs);
	bool operator == (const List342<ObjectType>& rhs); // just return true or false
	bool operator != (const List342<ObjectType>& rhs);
	// template<class ObjectType>
	friend ostream& operator<<(ostream& stream, const List342<ObjectType> &rhs){
		Node* temp = rhs.head_;
		while(temp != nullptr){
			stream << *(temp->data);
			temp = temp->next;
		}
		return stream;
	};
private:
	struct Node
	{
		ObjectType* data;
		Node* next;

		Node(ObjectType* d){
			data = d;
			next = nullptr;
		}
	};
	Node* head_;
};
#endif

template<class ObjectType>
List342<ObjectType>::List342() : head_(nullptr) {}

template<class ObjectType>
List342<ObjectType>::List342(const List342& source)
{
	//source must be a sorted list

	//copy all nodes of source to this
	Node* temp = source.head_;
	this->head_ = nullptr; // initialize -> head pointer must be null
	Node* tail = nullptr; // pointer that points to the tail of current list
	while(temp != nullptr){
		Node* newNode = new Node(temp->data); //creat new node to insert to this
		if(head_ == nullptr){
			//insert to head
			head_ = newNode;
			tail = head_;
		}else{
			//just insert to tail
			tail->next = newNode; //link tail to new node
			tail = newNode; //update pointer tail to new tail
		}
		temp = temp->next; //move temp on source
	}

}

template<class ObjectType>
List342<ObjectType>::~List342()
{
	DeleteList();
}

// BuildList is open the file, read the objects and build an ordered list in the file
template<class ObjectType>
bool List342<ObjectType>::BuildList(string file_name)
{
	ifstream infile; //input file stream and read its contents
	infile.open(file_name); //open the file stream
	if (!infile.is_open())
	{
		return false;
	}
	Node*tail = nullptr;
	ObjectType *item;
	while (!infile.eof()) //if haven't read to the end of the file
	{
		//voi moi lan lap, se tao ra 1 item moi de luu data doc duoc tu file
		// ObjectType item; //static declaration - on stack
		// cout << "Address: " << &tp << endl;
		item =  new ObjectType; // item is a pointer to dynamic memory on heap
		infile >> *item;
		Insert(item);
	}
	infile.close();	
	return true;
}
// Insert an object in a correct place, find a correct place, create a node
// prenode point to new node, new node point to the next node
template<class ObjectType>
bool List342<ObjectType>::Insert(ObjectType* obj)
{
	Node* node1 = new Node(obj); //dynamic allocate a new node
	
	if(head_ == nullptr){
		head_ = node1;
		return true;
	}else{
		Node* temp = head_;
		while(temp != nullptr){
			if(*obj == *(temp->data)){
				delete node1; //delete new node because not insert -> must deallocate
				node1 = nullptr;
				return false;
			}
			temp = temp->next;
		}

		temp = head_;
		Node* prev = nullptr;
		
		while(temp != nullptr){
			if(*(temp->data) > *obj){
				break;
			}
			prev = temp;
			temp = temp->next;
		}
		if(prev == nullptr){ // insert to head
			node1->next = head_;
			head_ = node1;
		}else{
			// insert to any position(not is head)
			node1->next = prev->next;
			prev->next = node1;
		}
		
		return true;
	}
}

template<class ObjectType>
bool List342<ObjectType>::Remove(ObjectType target, ObjectType& result){
	Node* temp = head_;
	Node* prev = nullptr;
	while(temp != nullptr){
		if(*(temp->data) == target){
			result = target;
			if(temp == head_){
				head_ = temp->next;
				
			}else{
				prev->next = temp->next;
			}
			delete temp;
			return true;
		}
		prev = temp;
		temp = temp->next;
	}

	return false;
}

template<class ObjectType>
bool List342<ObjectType>::Peek(ObjectType target, ObjectType& result) const{// function read only: only read data, cannot change any thing
	Node *temp = head_;
	while(temp != nullptr){
		if(*(temp->data) == target){
			result = target;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

template<class ObjectType>
int List342<ObjectType>::Size() const{
	int count = 0;
	Node* temp = head_;
	while(temp != nullptr){
		count++;
		temp->next;
	}
	return count;
}

template<class ObjectType>
void List342<ObjectType>::DeleteList(){
	Node* temp = nullptr;
	while(head_ != nullptr){
		temp = head_;
		head_ = head_->next;
		delete temp;
	}
}

template<class ObjectType>
bool List342<ObjectType>::Merge(List342<ObjectType>& list1){
	if(*this == list1){
		//merge itself
		return false;
	}
	//not use more new memory
	if(head_ == nullptr){
		//copy all nodes of list1 to this and set list = empty
		head_ = list1.head_;
		list1.head_ = nullptr;
		return true;
	}

	if(list1.head_ == nullptr){
		return true;
	}

	Node* prev1 = nullptr; Node* cur1 = head_; // 2 pointers to move on this list
	Node* prev2 = nullptr; Node* cur2 = list1.head_; //pointers to move on list1
	while(cur1 != nullptr && cur2 != nullptr){
		if(*(cur1->data) == *(cur2->data)){
			prev1 = cur1;
			cur1 = cur1->next;

			prev2 = cur2;
			cur2 = cur2->next;

			delete prev2;
			prev2 = nullptr;
		}else{
			if(*(cur1->data) > *(cur2->data)){
				//insert cur2 to this list
				prev2 = cur2;
				cur2 = cur2->next;
				//insert prev2 to this
				if(prev1 == nullptr){
					prev2->next = head_;
					head_ = prev2;
					prev1 = head_;
				}
			}else{
				//*(cur1->data) < *(cur2->data) -> move pointers on this
				prev1 = cur1;
				cur1 = cur1->next;
			}
		}
	}

	if(cur1 == nullptr && cur2 != nullptr){
		prev1->next = cur2;
		cur2 = nullptr;
	}

	list1.head_ = nullptr;//set list1 empty
	return true;
}

template<class ObjectType>
List342<ObjectType>& List342<ObjectType>::operator=(const List342<ObjectType>& source){
	//same as copy constructor
	//return the reference to current linked list
	DeleteList(); // delete old list;
	Node* temp = source.head_;
	Node* tail = nullptr; // pointer that points to the tail of current list
	while(temp != nullptr){
		Node* newNode = new Node(temp->data); //creat new node to insert to this
		if(head_ == nullptr){
			//insert to head
			head_ = newNode;
			tail = head_;
		}else{
			//just insert to tail
			tail->next = newNode; //link tail to new node
			tail = newNode; //update pointer tail to new tail
		}
		temp = temp->next; //move temp on source
	}
	return *this;
}
template<class ObjectType>
List342<ObjectType> List342<ObjectType>::operator+(const List342<ObjectType>& rhs){
	List342<ObjectType> result;
	Node* tail = nullptr; //this pointer points to the tail of result
	Node* cur1 = this->head_; // 2 pointers to move on this list
	Node* cur2 = rhs.head_; //pointers to move on list1
	while(cur1 != nullptr && cur2 != nullptr){
		if(*(cur1->data) == *(cur2->data)){
			
			//creat new node with data -> insert to result
			Node* newNode = new Node(cur1->data);
			if(result.head_ == nullptr){
				//insert to head of result
				newNode->next = result.head_;
				result.head_ = newNode;
				tail = result.head_;
			}else{
				//insert after tail -> link tail with new node
				tail->next = newNode;
				tail = newNode;
			}
			cur1 = cur1->next;
			cur2 = cur2->next;
			
		}else{
			if(*(cur1->data) > *(cur2->data)){
				//creat new node with data of cur2 -> insert to this
				Node* newNode = new Node(cur2->data);
				//insert newNode to this
				if(result.head_ == nullptr){
				//insert to head of result
					newNode->next = result.head_;
					result.head_ = newNode;
					tail = result.head_;
				}else{
					//insert after tail -> link tail with new node
					tail->next = newNode;
					tail = newNode;
				}

				//moving pointers on rhs list
				cur2 = cur2->next;

			}else{
				//*(cur1->data) < *(cur2->data) -> move pointers on this
				//creat new node with data of cur1 and insert it to result
				Node* newNode = new Node(cur1->data);
				//insert newNode to this
				if(result.head_ == nullptr){
				//insert to head of result
					newNode->next = result.head_;
					result.head_ = newNode;
					tail = result.head_;
				}else{
					//insert after tail -> link tail with new node
					tail->next = newNode;
					tail = newNode;
				}

				//moving pointers on list
				cur1 = cur1->next;
			}
		}
	}

	while(cur2 != nullptr){ //cur1 = null, cur2 != null
		//rhs list remains nodes
		Node* newNode = new Node(cur2->data);
		//insert newNode to this
		if(result.head_ == nullptr){
		//insert to head of result
			newNode->next = result.head_;
			result.head_ = newNode;
			tail = result.head_;
		}else{
			//insert after tail -> link tail with new node
			tail->next = newNode;
			tail = newNode;
		}

		//moving pointers on list
		cur2 = cur2->next;
	}

	while(cur1 != nullptr){ //cur1 != null, cur2 == null
		//rhs list remains nodes
		Node* newNode = new Node(cur1->data);
		//insert newNode to this
		if(result.head_ == nullptr){
		//insert to head of result
			newNode->next = result.head_;
			result.head_ = newNode;
			tail = result.head_;
		}else{
			//insert after tail -> link tail with new node
			tail->next = newNode;
			tail = newNode;
		}

		//moving pointers on list
		cur1 = cur1->next;
	}

	return result;
};
// a = 10
// b = 20
// a += b;
template<class ObjectType>//list1 += list2 : 2 operands: left(this object) and right (object passed(rsh))
List342<ObjectType>& List342<ObjectType>::operator+=(const List342<ObjectType>& rhs) 
{
	Node* prev1 = nullptr; Node* cur1 = head_; // 2 pointers to move on this list
	Node* prev2 = nullptr; Node* cur2 = rhs.head_; //pointers to move on list1
	while(cur1 != nullptr && cur2 != nullptr){
		if(*(cur1->data) == *(cur2->data)){
			prev1 = cur1;
			cur1 = cur1->next;

			prev2 = cur2;
			cur2 = cur2->next;
			//just moving pointers -> no delete
		}else{
			if(*(cur1->data) > *(cur2->data)){
				//creat new node with data of cur2 -> insert to this
				Node* newNode = new Node(cur2->data);
				//insert newNode to this
				if(prev1 == nullptr){
					//insert to head
					newNode->next = head_;
					head_ = newNode;
					prev1 = head_;
				}else{
					//insert after prev1 and before cur1
					newNode->next = cur1;
					prev1->next = newNode;
					prev1 = newNode;
				}

				//moving pointers on rhs list
				prev2 = cur2;
				cur2 = cur2->next;

			}else{
				//*(cur1->data) < *(cur2->data) -> move pointers on this
				prev1 = cur1;
				cur1 = cur1->next;
			}
		}
	}

	while(cur2 != nullptr){
		//rhs list remains nodes
		Node* newNode = new Node(cur2->data);
		//insert newNode to this
		if(prev1 == nullptr){
			//insert to head
			newNode->next = head_;
			head_ = newNode;
			prev1 = head_;
		}else{
			//insert after prev1 and before cur1
			newNode->next = cur1;
			prev1->next = newNode;
			prev1 = newNode;
		}

		cur2 = cur2->next; //move cur2
	}

	return *this;
}

template<class ObjectType>
bool List342<ObjectType>::operator == (const List342<ObjectType>& rhs) // list1 == list2 (compare two empty lists)
{
	if ((this->head_ == nullptr) && (rhs.head_ == nullptr))
	{
		return true;
	}

	if ((this->head_ != nullptr) && (rhs.head_ == nullptr))
	{
		return false;
	}

	if ((this->head_ == nullptr) && (rhs.head_ != nullptr))
	{
		return false;
	}
	Node* temp1 = this->head_;
	Node* temp2 = rhs.head_;
	while(temp1 != nullptr && temp2 != nullptr){
		if(*(temp1->data) != *(temp2->data)){
			return false;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	//case 1: temp1 == nullptr
	if(temp2 != nullptr){ // lils2 van con node -> list2 is longer than list1
		return false;
	}

	//case 2: temp2 == nullptr
	if(temp1 != nullptr){
		return false;
	}

	return true;
}

template<class ObjectType>
bool List342<ObjectType>::operator != (const List342<ObjectType>& rhs)
{
	return !(*this == rhs);
}

// template<class ObjectType>
// ostream& operator<<(ostream& stream, const List342<ObjectType> &rhs){
// 	Node* temp = rhs.head_;
// 	while(temp != nullptr){
// 		stream << *(temp->data);
// 		temp = temp->next;
// 	}
// }
