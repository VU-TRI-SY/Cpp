#include<bits/stdc++.h>
using namespace std;
struct Queue{
    int *data; // data là 1 con trỏ, trỏ tới 1 array nằm trên bộ nhớ Heap(dynamic allocate)
    int capacity;
    int q_front; //index của element ở đầu queue
    int q_back; //index của element ở cuối queue

    Queue(int s){
        capacity = s;
        data = new int[s]; //cho data trỏ tới 1 array với size là s nằm trên Heap
        q_front = -1;//khởi tạo với giá trị -1 - invalid index -> font và back không trỏ tới đâu cả -> queue empty
        q_back = -1;
    }

    bool empty(){
    	return q_front == -1;
	};

    bool full(){
    	return (q_back - q_front + 1) == capacity;
	};

    bool enqueue(int d){ // insert vao back, return true if insert successfully
    	if(full()){
    		return false;
		}else{
			if(q_back == capacity-1){ // các elements nằm tràn về cuối, ở đầu bị bỏ trống -> shift left tất cả các elements về đầu
                int n = (q_back - q_front + 1); // n = số elements
                for(int i = 0; i < n; i++){ //i: 0 -> 3
                    data[i] = data[q_front + i];
                }
                q_front = 0;
                q_back = n-1;

                //enqueue
                q_back++;
                data[q_back] = d;
            }else{
                q_back++;
                data[q_back] = d;
            }
            return true;
		}
	};
    int dequeue(); //NOTED
    //todo
    int front();//return value of element at head of queue
    //todo
    int back();
    //todo
    void display(){
        if(empty()){
            cout << "Queue is empty" << endl;
        }else{
            cout << "Queue' elements: " << endl;
            for(int i = q_front; i <= q_back; i++){ //chay tu dau ve cuoi va in ra
                cout << data[i] << " ";
            }
            cout << endl;
        }
    }
};