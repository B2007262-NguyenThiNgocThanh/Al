//=======THANH_B2007262=======\\ 

#include <stdio.h>
#include <stdlib.h> 
#include <stack> 
#define U 0 
#define N 1 
#define soly 6 
#define emptys -1 

#define Maxlength 100

using namespace std; 
//================================TT============================// 
const char* action[]={"First State",
					"1-2-3","2-3-4",
					"3-4-5","4-5-6"};
//cau truc tt
typedef struct{
	int ly[soly]; //mang 1 chieu luu so ly 
}State;
//khoi tao tt
void makenullState(State *state){
	int i;
	for(i=0 ; i<soly ; i++)
		state->ly[i] = emptys; 
} 
//kt muc tieu
int goalcheck(State state){
	int i;
	for(i=0 ; i<soly ; i++)
		if(state.ly[i] != N)
			return 0;
	return 1; 
} 
//hanh dong
void operators(State state, State *result, int pos){
	int i;
	for(i=0; i<soly; i++){
		if(i>=pos-1 && i<=pos+1) 
			result->ly[i] = 1 - state.ly[i]; 
		else 
			result->ly[i] = state.ly[i]; 
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
	struct Node* Parent;//nut cha
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

//tim TT trong open/close 
int find_State(State state, stack<Node*> openStack){
	while(!openStack.empty()){
		if(compareState(openStack.top()->state,state)) //so sanh 2 TT 
			return 1;
		openStack.pop(); //xoa khoi open 
	}
	return 0;
}

//DFS
Node* DFS(State state){
	//khai bao 2 stack open-close + khoi tao
	stack<Node*> open_DFS;
	stack<Node*> close_DFS;
	
	//tao nut TT Parent
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state; //TT nut goc = TT dang xet 
	root->Parent = NULL; //nut goc k co cha 
	root->no_function = 0; //no_function: thu tu cac phep toan 
	open_DFS.push(root); // them nut goc vao open 
	
	while(!open_DFS.empty()){
		
		//lay mot dinh trong stack
		Node* node = open_DFS.top(); //lay dinh dau trong open 
		open_DFS.pop(); //xoa no 
		open_DFS.push(node); //them vao closed 
		
		//kt dinh lay ra ~ goal
		if(goalcheck(node->state))
			return node;
			
		int opt;
		//goi cac phep toan TT
		for(opt=1;opt<=4;opt++){
			State newstate;//tt moi 
			makenullState(&newstate);
			operators(node->state,&newstate,opt); 
			
			//neu TT new sinh ra da ton tai thi continue
			if(find_State(newstate, close_DFS) || find_State(newstate,open_DFS)) 
				continue;
			//neu TT moi chua ton tai thi dua vao ngan xep
			Node* newNode = (Node*)malloc(sizeof(Node));				
			newNode->state = newstate;
			newNode->Parent = node;
			newNode->no_function = opt;
			open_DFS.push(newNode);			
		}
	}
	return NULL;
}
//chuyen kq->TT dich 
void print_WaysToGetGoal(Node* node){
	stack<Node*> stackPrint;//ngan xep can in 

	//duyet nguoc ve nut parent
	while(node->Parent != NULL){
		stackPrint.push(node);
		node = node->Parent;
	}
	stackPrint.push(node);
	//in thu tu hanh dong
	int no_action=0;
	while(!stackPrint.empty()){
		printf("\nAction %d: %s\n\n",no_action, action[stackPrint.top()->no_function]);
		printState(stackPrint.top()->state);
		stackPrint.pop();
		no_action++;
	}
}

int main(){
	State cur_state = {1, 0, 1, 0, 1, 0};
	Node* p = DFS(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}
