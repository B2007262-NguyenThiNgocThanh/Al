//============THANH_B2007262============\\ 

#include <stdio.h>
#include <stdlib.h>
#include <stack> 

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define emptys 0
#define goal 6
#define Maxlength 100

using namespace std;

const char* action[] = {"Fisrt State","pour Water Full X","pour Water Full Y",
"pour Water Empty X","pour Water Empty Y","pour Water X to Y","pour Water Y to X"
};

typedef struct{
	int x,y; 
}State;

void makenullState(State *state){
	state->x = 0;
	state->y = 0; 
} 

int goalcheck(State state){
	return (state.x == goal || state.y == goal); 
} 

void print_state(State state){
	printf("\n X:%d --- Y:%d", state.x, state.y); 
} 

//ham cac TT
int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X){
		result->x = tankcapacity_X;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y < tankcapacity_Y){
		result->x = cur_state.x;
		result->y = tankcapacity_Y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x > emptys){
		result->x = emptys;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y > emptys){
		result->x = cur_state.x;
		result->y = emptys;
		return 1;
	}
	return 0;
}

int max(int a, int b){
	return a>b? a:b;
}

int min(int a, int b){
	return a<b? a:b;
}

int pourWaterXY(State cur_state, State *result){
	if(cur_state.x > 0 && cur_state.y < tankcapacity_Y){
		result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y),emptys);
		result->y = min(cur_state.x + cur_state.y,tankcapacity_Y);
		return 1;
	}
	return 0;
}

int pourWaterYX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X && cur_state.y > 0){
		result->x = min(cur_state.x + cur_state.y,tankcapacity_X);
		result->y = max(cur_state.y - (tankcapacity_X - cur_state.x),emptys);
		return 1;
	}
	return 0;
}

int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourWaterFullX(cur_state, result);
		case 2: return pourWaterFullY(cur_state, result);
		case 3: return pourWaterEmptyX(cur_state, result);
		case 4: return pourWaterEmptyY(cur_state, result);
		case 5: return pourWaterXY(cur_state, result);
		case 6: return pourWaterYX(cur_state, result);
		default: printf("Error !");
			return 0;
	}
} 

//=================================================================//
//cau truc nut_cay tim kiem
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function; //thu tu phep toan duoc thuc hien tuong ung
}Node;

//so sanh 2 TT
int compareState(State state1, State state2){
	return (state1.x == state2.x && state1.y == state2.y);
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
//-------------------DFS-----------------//

Node* DFS(State state){
	stack<Node*> open_DFS;
	stack<Node*> close_DFS;
	
	//tao nut TT parent
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state; //TT nut goc = TT dang xet 
	root->Parent = NULL; //nut goc k co cha 
	root->no_function = 0; //no_function: thu tu cac phep toan 
	open_DFS.push(root);
	
	while(!open_DFS.empty()){
		//lay 1 dinh trong stack
		Node *node = open_DFS.top();
		open_DFS.pop();
		close_DFS.push(node);
		
		//kt 
		if(goalcheck(node->state))
			return node;
			
		int opt;
		//goi phep toan
		for(opt=1;opt<=6;opt++){
			State newstate;//tt moi 
			makenullState(&newstate);
			if(call_operator(node->state, &newstate, opt)){
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
		printf("\nAction %d: %s",no_action, action[stackPrint.top()->no_function]);
		print_state(stackPrint.top()->state);
		stackPrint.pop();
		no_action++;
	}
}

int main(){
	State cur_state = {0, 0};
	Node* p = DFS(cur_state);
	print_WaysToGetGoal(p);
	return 0; 
} 












