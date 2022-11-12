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
	// head_ = nullptr;
	// *this = source;
	//source is another linked list
	// copy all nodes from source to this list
	Node* temp = source.head_;
	while(temp != nullptr){
		this->Insert((temp->data));
		temp = temp->next;
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
	ObjectType item;
	while (infile.eof()) //if haven't read to the end of the file
	{
		infile >> item;
		Insert(&item);
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
	
	if(head_ == nullptr){
		head_ = list1.head_;
		list1.head_ = nullptr;
		return true;
	}

	if(list1.head_ == nullptr){
		return true;
	}

	Node* prev1 = nullptr; 
	Node* cur1 = this->head_;
	Node* prev2 = nullptr;
	Node *cur2 = list1.head_; //list = rhs
	
	while(cur1 != nullptr && cur2 != nullptr){
		if(*(cur1->data) == *(cur2->data)){
			prev1 = cur1;
			cur1 = cur1->next;

			prev2 = cur2;
			cur2 = cur2->next;
			delete prev2;
		}else{
			if(*(cur1->data) > *(cur2->data)){
				prev2 = cur2;
				cur2 = cur2->next;
				// cout << (prev1 == nullptr) << endl;
				if(prev1 == nullptr){
					prev2->next = cur1;
					this->head_ = prev2;
					prev1 = prev2; 
				}
			}else{
				prev1 = cur1;
				cur1 = cur1->next;
			}
		}
	}

	if(cur1 == nullptr && cur2 != nullptr){
		prev1->next = cur2;
		cur2 = nullptr;
	}
	list1.head_ == nullptr;
	return true;
}

template<class ObjectType>
List342<ObjectType>& List342<ObjectType>::operator=(const List342<ObjectType>& source){
	//return the reference to current linked list
	DeleteList(); // delete old list;
	Node* temp = source.head_;
	while(temp != nullptr){
		Insert(temp->data);
	}
	return *this;
}
template<class ObjectType>
List342<ObjectType> List342<ObjectType>::operator+(const List342<ObjectType>& rhs){
	List342<ObjectType> result;
	result = *this;

	if(result.head_ == nullptr){ // this block is run is this is null -> head_ of result is null -> just result = rhs;
		result = rhs;
		return result;
	}

	if(rhs.head_ == nullptr){
		return result;
	}

	Node* prev1 = nullptr; Node* cur1 = result.head_;
	Node* prev2 = nullptr; Node* cur2 = rhs.head_;
	while(cur1 != nullptr && cur2 != nullptr){
		if(*(cur1->data) == *(cur2->data)){
			prev1 = cur1;
			cur1 = cur1->next;
			prev2 = cur2;
			cur2 = cur2->next;
			result.Insert(prev1->data); // insert 1 trong 2 nodes
		}else{
			if(*(cur1->data) > *(cur2->data)){
				prev2 = cur2;
				cur2 = cur2->next;
				result.Insert(prev2->data);
				
			}else{
				prev1 = cur1;
				cur1 = cur1->next;
				result.Insert(prev1->data);
			}
		}
	}

	//case 1: cur1 is null
	while(cur2 != nullptr){
		result.Insert(cur2->data);
		cur2 = cur2->next;
	}

	//case 2: cur2 is null
	while(cur1 != nullptr){
		result.Insert(cur1->data);
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
	if ((this->head_ == nullptr) && (rhs.head_ == nullptr))
	{
		return *this;
	}
	//if list 1 empty -> traverse through list2 and insert each node to list 1
	
	if (this->head_ == nullptr)
	{
		Node* temp = rhs.head_;
		while(temp != nullptr){
			this->Insert(temp->data);
			temp = temp->next;
		}
		return *this;
	}

	//if list 2 empty, result will be list 1 only
	if (rhs.head_ == nullptr)
	{
		return *this;
	}
	
	Node* prev1 = nullptr; Node* cur1 = this->head_;
	Node* prev2 = nullptr; Node* cur2 = rhs.head_;
	while (cur1 != nullptr && cur2 != nullptr) {
		if (*(cur1->data) == *(cur2->data)) {
			prev1 = cur1;
			cur1 = cur1->next;
			prev2 = cur2;
			cur2 = cur2->next;
			//ignore cur2 and cur1 -> update cur1 and cur2
			//neu nhu 2 cur bang nhau, vay minh giu lai 1 cur->data?
		}
		else {
			if (*(cur1->data) > *(cur2->data)) {
				prev2 = cur2;
				cur2 = cur2->next;
				this->Insert(prev2->data); // insert this node of list2 to list1
			}
			else { // current node of list1 has data > list2
			//case: cur1->data < cur2->data
				prev1 = cur1;
				cur1 = cur1->next;
				// this->Insert(*(prev1->data)); // insert current node of list1 to list1
				//just move cur1 and prev1
			}
		}
	}

	//case 1: cur1 is null
	while (cur2 != nullptr) {
		this->Insert(cur2->data);
		cur2 = cur2->next;
	}

	// //case 2: cur2 is null -> return 

	// while (cur1 != nullptr) {
	// 	this->Insert(*(cur1->data));
	// 	cur1 = cur1->next;
	// }
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
