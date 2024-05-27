//=======THANH_B2007262=======\\ 

#include <stdio.h>
#include <stdlib.h> 
#include <stack>
#include <queue> 
#define U 0 
#define N 1 
#define soly 6 
#define emptys -1 
#define Maxlength 100
using namespace std; 

//================================TT============================// 
const char* action[]={"First State","1-2-3","2-3-4",
						"3-4-5","4-5-6"} ;

typedef struct{
	int ly[soly]; 
}State;

void makenullState(State *state){
	int i;
	for(i=0; i<soly ; i++)
		state->ly[i] = emptys; 
} 

int goalcheck(State state){
	int i;
	for(i=0; i<soly; i++)
		if(state.ly[i] != N)
			return 0; 
	return 1; 
} 

void operators(State state, State *result, int pos){
	int i;
	for(i=0; i<soly ; i++){
		if(i>=pos-1 && i<=pos+1)
			result->ly[i] = 1 - state.ly[i];
		else result->ly[i] = state.ly[i]; 
	} 
	 
} 


void printState(State state){
	int i;
	for(i=0; i<soly; i++)
		printf(" %d ", state.ly[i]); 
	printf("\n"); 
} 

//=================================STACK=========================// 

//cau truc nut_cay tim kiem
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function; //thu tu phep toan duoc thuc hien tuong ung
}Node;


//so sanh 2 TT
int compareState(State state1, State state2){
	int i;
	for(i=0; i<soly; i++)
		if(state1.ly[i] != state2.ly[i])
			return 0; 
	return 1; 
} 

int find_State_Queue(State state, queue<Node*> openQueue){
	while(!openQueue.empty()){
		if(compareState(openQueue.front()->state,state)) //so sanh 2 TT 
			return 1;
		openQueue.pop(); //xoa khoi open 
	}
	return 0;
}

Node* BFS(State state){
	
	//khai bao 2 hang doi
	queue<Node*> open_BFS;
	queue<Node*> close_BFS;
	
	//tao trang thai nut cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state; 
	root->Parent = NULL;
	root->no_function = 0;
	//them nut goc vao open
	open_BFS.push(root);
	
	
	while(!open_BFS.empty()){
		//lay mot dinh o dau hang doi
		Node* node = open_BFS.front();
		open_BFS.pop();
		close_BFS.push(node);
		
		//kt no co phai TT dich
		if(goalcheck(node->state))
			return node;
			
		int opt;
		for(opt=1; opt<=4; opt++){
			State newstate ;
			makenullState(&newstate);
			operators(node->state, &newstate, opt); 
			//neu TT moi da ton tai thi bo qua
			if(find_State_Queue(newstate,close_BFS) || find_State_Queue(newstate,open_BFS))
				continue;
			//neu chua ton tai thi dua vao hang doi
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->state = newstate;
			newNode->Parent = node;
			newNode->no_function = opt;
			open_BFS.push(newNode);
			
		}
	}
	return NULL;
}
void print_WaysToGetGoal(Node* node){
	queue<Node*> queuePrint;//hang doi can in 
	
	//duyet nguoc ve nut parent
	while(node->Parent != NULL){
		queuePrint.push(node);
		node = node->Parent;
	}
	queuePrint.push(node);
//-----------------------------------------//
	
	stack<Node*> s;
	//chuyen phan tu QUEUE => STACK 
	while(!queuePrint.empty()){
		node = queuePrint.front();
		queuePrint.pop(); 
		s.push(node);
	} 

	//chuyen phan tu STACK => QUEUE 
	while(!s.empty()){
		node = s.top();
		s.pop(); 
		queuePrint.push(node); 
	} 
//------------------------------------------//
	//in thu tu thanh dong
	int no_action=0;
	while(!queuePrint.empty()){
		printf("\nAction %d: %s\n\n", no_action, action[queuePrint.front()->no_function]);
		printState(queuePrint.front()->state);
		queuePrint.pop();
		no_action++;
	}
}

int main(){
	State cur_state = {1,0,1,0,1,0};
	Node* p = BFS(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}



