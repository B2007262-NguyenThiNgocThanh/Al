//==================THANH=================// 

#include <stdio.h>
#include <stdlib.h> 
#define X 3 //so tu si
#define Y 3 //so ke an thit
#define goal 0 //(0,0,B)
#define Maxlength 100

//=====================================================//

const char* action1[] = {"FIRST STATE","MOT TU SI","HAI TU SI","MOT KE AN THIT","HAI KE AN THIT","MOT TU SI & MOT KE AN THIT"};

typedef struct{
	int x,y; //so luong tu si, ke an thit
	int  z; //vi tri thuyen
}State;

void makenullState(State *state){
	state->x = 0;
	state->y = 0;
	state->z = 1;
}
//kt TT dich
int goalcheck(State state){
	return (state.x == goal && state.y == goal && state.z == 2);
}
void printState(State state){
	printf("\n\tX:%d ---- Y:%d ----Z:%d",state.x,state.y,state.z);
}
//TT chet o bo A va B 

int checkstate_die(State state){
//	if(state.z == 1)
//		return (state.x < state.y && state.x > 0) ;
//	else if(state.z == 2)
//		return (((3-state.x) > 0) && (3-state.x < 3-state.y) && state.x < state.y);
//	else return 0;

	return ((state.x < state.y && state.x > 0) || (3-state.x) > 0 && (3-state.x < 3-state.y));
}

//=======================di chuyen==================//

//cho 1 tu s
int one_X(State cur_state, State *result){
	if((cur_state.x-1 >= 0) && cur_state.z==1){
		result->x = cur_state.x-1;
		result->y = cur_state.y;
		result->z = 2;
		return 1;
	}
	else if((cur_state.x+1 <= 3) && cur_state.z==2 ){
		result->x = cur_state.x+1;
		result->y = cur_state.y;
		result->z = 1;
		return 1;
	}
	return 0;
}
//cho 2 tu si
int two_X(State cur_state, State *result){
	if(cur_state.z == 1 && (cur_state.x-2 >= 0)){
		result->x = cur_state.x-2;
		result->y = cur_state.y;
		result->z = 2;
		return 1;
	}
	else if(cur_state.z == 2 && (cur_state.x+2 <= 3)){
		result->x = cur_state.x+2;
		result->y = cur_state.y;
		result->z = 1;
		return 1;
	}
	return 0;
}
//cho 1 ke an thit
int one_Y(State cur_state, State *result){
	if(cur_state.z == 1 && (cur_state.y-1 >= 0)){
		result->x = cur_state.x;
		result->y = cur_state.y - 1;
		result->z = 2;
		return 1;
	}
	else if(cur_state.z == 2 && (cur_state.y+1<= 3)){
		result->x = cur_state.x;
		result->y = cur_state.y + 1;
		result->z = 1;
		return 1;
	}
	return 0;
}
//cho 2 ke an thit
int two_Y(State cur_state, State *result){
	if(cur_state.z==1 &&(cur_state.y-2 >= 0)){
		result->x = cur_state.x;
		result->y = cur_state.y - 2;
		result->z = 2;
		return 1;
	}
	else if(cur_state.z==2 && (cur_state.y + 2 <= 3)){
		result->x = cur_state.x;
		result->y = cur_state.y + 2;
		result->z = 1;
		return 1;
	}
	return 0;
}
//cho 1 tu si & 1 ke an thit
int one_XY(State cur_state, State *result){
	if((cur_state.x -1 >= 0)&& (cur_state.y-1 >= 0) && cur_state.z == 1){
		result->x = cur_state.x - 1;
		result->y = cur_state.y - 1;
		result->z = 2;
		return 1;
	}
	else if((cur_state.x+1 <= 3)&& (cur_state.y+1 <= 3) && cur_state.z == 2){
		result->x = cur_state.x + 1;
		result->y = cur_state.y + 1;
		result->z = 1;
		return 1;
	}
	return 0;
}

int call_operators(State cur_state, State *result, int opt){
	switch(opt){
		case 1: return one_X(cur_state, result);
		case 2: return two_X(cur_state, result);
		case 3: return one_Y(cur_state, result);			
		case 4: return two_Y(cur_state, result);
		case 5: return one_XY(cur_state, result);
		default: printf("Error !");
			return 0;
	}
}

//=========================node==========================//
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;
//=======================================================//
typedef struct{
	Node* Elements[Maxlength];
	int Top_idx;
}Stack;

//khoi tai stack
void makenullStack(Stack *pS){
	pS->Top_idx = Maxlength;
}

//kt rong
int empty_Stack(Stack S){
	return S.Top_idx == Maxlength;
}

//kt day
int full_Stack(Stack S){
	return S.Top_idx == 0;
}

//tra ve dinh ngan xep
Node* top(Stack S){
	if(!empty_Stack(S)) 
		return S.Elements[S.Top_idx];
	return NULL;
}
//them 1 phan tu vao Stack
void push(Node* x, Stack *pS){
	if(full_Stack(*pS)) printf("Stack is full !");
	else{
		pS->Top_idx -= 1;
		pS->Elements[pS->Top_idx] = x;
	}
}
//xoa phan tu kho Stack
void pop(Stack *pS){
	if(!empty_Stack(*pS))
		pS->Top_idx += 1;
	else printf("Stack is empty !");
}
//===========================================================================================//
int comparestate(State state1, State state2){
	return (state1.x == state2.x && state1.y == state2.y && state1.z == state2.z); 
} 

int find_state(State state, Stack open){
	while(!empty_Stack(open)){
		if(comparestate(top(open)->state, state))
			return 1;
		pop(&open); 
	} 
	return 0; 
} 


Node* DFS(State state){
	Stack open, closed;
	makenullStack(&open);
	makenullStack(&closed);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	
	push(root, &open);
	
	while(!empty_Stack(open)){
		Node* node = top(open);
		pop(&open);
		push(node, &closed);
		
		if(goalcheck(node->state))
			return node;
		int opt;
		for(opt = 1; opt <= 5; opt++){
			State newState;
			makenullState(&newState);

			if(call_operators(node->state, &newState, opt)){
				if(find_state(newState, closed)||find_state(newState,open)||checkstate_die(newState)) 
					continue;
					
				Node* newnode=(Node*)malloc(sizeof(Node));
				newnode->state = newState;
				newnode->Parent = node;
				newnode->no_function = opt;
				push(newnode, &open);
			}
		}		
	}
	return NULL;
}

void print_WaysToGetGoal(Node* node){
	Stack stackPrint;//hang doi can in 
	makenullStack(&stackPrint);
	//duyet nguoc ve nut parent
	while(node->Parent != NULL){
		push(node, &stackPrint);
		node = node->Parent;
	}
	push(node, &stackPrint);

	//in thu tu thanh dong
	int no_action=0;
	while(!empty_Stack(stackPrint)){
		printf("\nAction %d: %s", no_action, action1[top(stackPrint)->no_function]);
		printState(top(stackPrint)->state);
		pop(&stackPrint);
		no_action++;
	}
} 

int main(){
	State cur_state = {3,3,1};
	Node* p = DFS(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}

