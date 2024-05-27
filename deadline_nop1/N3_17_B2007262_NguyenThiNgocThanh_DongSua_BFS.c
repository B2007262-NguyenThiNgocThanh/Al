//=======THANH_B2007262=======\\ 

//3 binh : x - 5, y - 6 ~ empty, Z - 10 ~ full
// start = (0,0,10) ~ goal = (x,y,8) 
//hanh dong : Z->X,Y; Y->X,Z; X->Y,Z 


#include <stdio.h>
#include <stdlib.h> 
#define tankcapacity_X 5//suc chua binh x 
#define tankcapacity_Y 6 //suc chua binh y 
#define tankcapacity_Z 10 //suc chua binh z 
#define goal 8
#define empty 0
#define Maxlength 100
//================================TT============================// 
const char* action[]={"First State","pour Water Z to X","pour Water Z to Y",
"pour Water Y to X","pour Water Y to Z","pour Water X to Y","pour Water X to Z"
} ;

typedef struct{
	int x,y,z; 
}State;

void makenullState(State *state){
	state->x = 0;
	state->y = 0;
	state->z = 0; 
} 

int goalcheck(State state){
	return (state.z == goal || state.x == goal ||state.y == goal); 
} 
int max(int a, int b){
	return a>b? a:b; 
} 
int min(int a, int b){
	return a<b? a:b; 
} 

void printState(State state){
	printf("\nX:%d --- Y:%d --- Z:%d", state.x, state.y, state.z); 
} 

int pourWaterZX(State cur_state, State *result){
	if(cur_state.z > 0 &&  cur_state.x < tankcapacity_X){
		result->x = min(cur_state.z + cur_state.x, tankcapacity_X);
		result->y = cur_state.y;
		result->z = max(cur_state.z - (tankcapacity_X - cur_state.x),empty);
		return 1; 
	} 
	return 0; 
}

int pourWaterZY(State cur_state, State *result){
	if(cur_state.z > 0 &&  cur_state.y < tankcapacity_Y){
		result->x = cur_state.x;
		result->y = min(cur_state.z + cur_state.y, tankcapacity_Y);
		result->z = max(cur_state.z - (tankcapacity_Y - cur_state.y),empty);
		return 1; 
	} 
	return 0; 
}

int pourWaterYX(State cur_state, State *result){
	if(cur_state.y > 0 &&  cur_state.x < tankcapacity_X){
		result->x = min(cur_state.x + cur_state.y, tankcapacity_X);
		result->y = max(cur_state.y - (tankcapacity_X - cur_state.x),empty);
		result->z = cur_state.z;
		return 1; 
	} 
	return 0; 
}

int pourWaterYZ(State cur_state, State *result){
	if(cur_state.y > 0 &&  cur_state.z < tankcapacity_Z){
		result->x = cur_state.x;
		result->y = max(cur_state.y - (tankcapacity_Z - cur_state.z),empty);
		result->z = cur_state.z + cur_state.y;
		return 1; 
	} 
	return 0; 
}

int pourWaterXY(State cur_state, State *result){
	if(cur_state.x > 0 &&  cur_state.y < tankcapacity_Y){
		result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y),empty);
		result->y = min(cur_state.x + cur_state.y, tankcapacity_Y);
		result->z = cur_state.z;
		return 1; 
	} 
	return 0; 
}

int pourWaterXZ(State cur_state, State *result){
	if(cur_state.x > 0 &&  cur_state.z < tankcapacity_Z){
		result->x = max(cur_state.x - (tankcapacity_Z - cur_state.z),empty);
		result->y = cur_state.y;
		result->z = cur_state.z + cur_state.x;
		return 1; 
	} 
	return 0; 
}

int call_operator(State cur_state, State *result, int opt){
	switch(opt){
		case 1: return pourWaterZX(cur_state,result);
		case 2: return pourWaterZY(cur_state,result); 
		case 3: return pourWaterYX(cur_state,result); 
		case 4: return pourWaterZY(cur_state,result); 
		case 5: return pourWaterXY(cur_state,result); 
		case 6: return pourWaterXZ(cur_state,result); 
		default: printf("Error !");
			return 0; 
	} 
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
	return (state1.x == state2.x && state1.y == state2.y && state1.z == state2.z);
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
		for(opt=1; opt<=6; opt++){
			State newstate ;
			makenullState(&newstate);
			if(call_operator(node->state,&newstate,opt)){
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
		printf("\nAction %d: %s", no_action, action[get_front(queuePrint)->no_function]);
		printState(get_front(queuePrint)->state);
		delete_Q(&queuePrint);
		no_action++;
	}
}

int main(){
	State cur_state = {0, 0, 10};
	Node* p = BFS(cur_state);
	printf("\n=================BFS===================//\n"); 
	print_WaysToGetGoal(p);
	return 0;
}



