//===========THANH_B2007262==========\\ 

#include <stdio.h>
#include <stdlib.h> 
#define tankcapacity_X 9 //suc chua binh X 
#define tankcapacity_Y 4 //suc chua binh Y 
#define empty 0
#define goal 6 // TT dich 
#define Maxlength 100

const char* action[] = {"Fisrt State","pour Water Full X","pour Water Full Y",
"pour Water Empty X","pour Water Empty Y","pour Water X to Y","pour Water Y to X"
};

typedef struct{
	int x, y;
}State;

void makenullState(State *state){
	state->x = 0;
	state->y = 0;
}

void printState(State state){
	printf("\nX:%d --- Y:%d",state.x,state.y);
}
//kt tt dich 
int goalcheck(State state){
	return (state.x == goal || state.y == goal);
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
	if(cur_state.x > empty){
		result->x = empty;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y > empty){
		result->x = cur_state.x;
		result->y = empty;
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
		result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y),empty);
		result->y = min(cur_state.x + cur_state.y,tankcapacity_Y);
		return 1;
	}
	return 0;
}

int pourWaterYX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X && cur_state.y > 0){
		result->x = min(cur_state.x + cur_state.y,tankcapacity_X);
		result->y = max(cur_state.y - (tankcapacity_X - cur_state.x),empty);
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
//----------------------------------------------------------------------------------------------------------//
//cau truc nut_cay tim kiem
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function; //thu tu phep toan duoc thuc hien tuong ung
}Node;

//stack
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
//-------------------------------------------------------------------------------------------------------//
//so sanh 2 TT
int compareState(State state1, State state2){
	return (state1.x == state2.x && state1.y == state2.y);
} 

//tim TT trong open/close 
int find_State(State state, Stack openStack){
	while(!empty_Stack(openStack)){
		if(compareState(top(openStack)->state,state)) //so sanh 2 TT 
			return 1;
		pop(&openStack); //xoa khoi open 
	}
	return 0;
}

//DFS
Node* DFS(State state){
	//khai bao 2 stack open-close + khoi tao
	Stack open_DFS;
	Stack close_DFS;
	makenullStack(&open_DFS);
	makenullStack(&close_DFS);
	
	//tao nut TT Parent
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state; //TT nut goc = TT dang xet 
	root->Parent = NULL; //nut goc k co cha 
	root->no_function = 0; //no_function: thu tu cac phep toan 
	push(root, &open_DFS); // them nut goc vao open 
	
	while(!empty_Stack(open_DFS)){
		
		//lay mot dinh trong stack
		Node* node = top(open_DFS); //lay dinh dau trong open 
		pop(&open_DFS); //xoa no 
		push(node, &close_DFS); //them vao closed 
		
		//kt dinh lay ra ~ goal
		if(goalcheck(node->state))
			return node;
			
		int opt;
		//goi cac phep toan TT
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
				push(newNode,&open_DFS);
			}
		}
	}
	return NULL;
}
//chuyen kq->TT dich 
void print_WaysToGetGoal(Node* node){
	Stack stackPrint;//ngan xep can in 
	makenullStack(&stackPrint);
	//duyet nguoc ve nut parent
	while(node->Parent != NULL){
		push(node, &stackPrint);
		node = node->Parent;
	}
	push(node, &stackPrint);
	//in thu tu hanh dong
	int no_action=0;
	while(!empty_Stack(stackPrint)){
		printf("\nAction %d: %s",no_action,action[top(stackPrint)->no_function]);
		printState(top(stackPrint)->state);
		pop(&stackPrint);
		no_action++;
	}
}
//==================================================================================================//
int main(){
	State cur_state = {0, 0};
	Node* p = DFS(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}

