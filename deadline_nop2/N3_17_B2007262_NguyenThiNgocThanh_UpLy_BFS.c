//=======THANH_B2007262=======\\ 

#include <stdio.h>
#include <stdlib.h> 
#define U 0 
#define N 1 
#define soly 6 
#define empty -1 
#define Maxlength 100

//================================TT============================// 
const char* action[]={"First State","1-2-3","2-3-4",
						"3-4-5","4-5-6"} ;

typedef struct{
	int ly[soly]; 
}State;

void makenullState(State *state){
	int i;
	for(i=0; i<soly ; i++)
		state->ly[i] = empty; 
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
//so sanh 2 TT
int compareState(State state1, State state2){
	int i;
	for(i=0; i<soly; i++)
		if(state1.ly[i] != state2.ly[i])
			return 0; 
	return 1; 
} 

//==============================QUEUE============================//
typedef struct{
	Node* Elements[Maxlength];
	int front, rear;
}Queue;

void makenullQueue(Queue *Q){
	Q->front = -1;
	Q->rear = -1;
}

int emptyQ(Queue Q){
	return Q.front == -1;
}

int fullQ(Queue Q){
	return ((Q.rear-Q.front)+1)%Maxlength == 0;
}

//tra ve phan tu hang doi
Node* get_front(Queue Q){
	if(emptyQ(Q)) 
		printf("Queue is empty !");
	else return Q.Elements[Q.front];
}

//them phan tu vao hang doi
void pushQ(Node* x, Queue *Q){
	if(!fullQ(*Q)){
		if(emptyQ(*Q))
			Q->front = 0;
		Q->rear = (Q->rear+1)%Maxlength;
		Q->Elements[Q->rear] = x;
	}
	else printf("Error , Push!");
}
//xoa phan tu
void delete_Q(Queue *Q){
	if(!emptyQ(*Q)){
		if(Q->front == Q->rear)
			makenullQueue(Q);
		else Q->front = (Q->front+1) % Maxlength;
	}
	else printf("Error , delete !");
}
int find_State_Queue(State state, Queue openQueue){
	while(!emptyQ(openQueue)){
		if(compareState(get_front(openQueue)->state,state)) //so sanh 2 TT 
			return 1;
		delete_Q(&openQueue); //xoa khoi open 
	}
	return 0;
}

Node* BFS(State state){
	
	//khai bao 2 hang doi
	Queue open_BFS;
	Queue close_BFS;
	makenullQueue(&open_BFS);
	makenullQueue(&close_BFS);
	
	//tao trang thai nut cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state; 
	root->Parent = NULL;
	root->no_function = 0;
	//them nut goc vao open
	pushQ(root,&open_BFS);
	
	
	while(!emptyQ(open_BFS)){
		//lay mot dinh o dau hang doi
		Node* node = get_front(open_BFS);
		delete_Q(&open_BFS);
		pushQ(node, &close_BFS);
		
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
			pushQ(newNode,&open_BFS);
			
		}
	}
	return NULL;
}
void print_WaysToGetGoal(Node* node){
	Queue queuePrint;//hang doi can in 
	makenullQueue(&queuePrint);
	//duyet nguoc ve nut parent
	while(node->Parent != NULL){
		pushQ(node, &queuePrint);
		node = node->Parent;
	}
	pushQ(node, &queuePrint);
//-----------------------------------------//
	
	Stack s;
	makenullStack(&s);
	//chuyen phan tu QUEUE => STACK 
	while(!emptyQ(queuePrint)){
		node = get_front(queuePrint);
		delete_Q(&queuePrint); 
		push(node,&s);
	} 

	//chuyen phan tu STACK => QUEUE 
	while(!empty_Stack(s)){
		node = top(s);
		pop(&s); 
		pushQ(node,&queuePrint); 
	} 
//------------------------------------------//
	//in thu tu thanh dong
	int no_action=0;
	while(!emptyQ(queuePrint)){
		printf("\nAction %d: %s\n\n", no_action, action[get_front(queuePrint)->no_function]);
		printState(get_front(queuePrint)->state);
		delete_Q(&queuePrint);
		no_action++;
	}
}

int main(){
	State cur_state = {1,0,1,0,1,0};
	Node* p = BFS(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}



