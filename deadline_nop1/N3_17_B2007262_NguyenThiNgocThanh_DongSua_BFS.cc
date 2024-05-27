//=======THANH_B2007262=======\\ 

//3 binh : x - 5, y - 6 ~ empty, Z - 10 ~ full
// start = (0,0,10) ~ goal = (x,y,8) 
//hanh dong : Z->X,Y; Y->X,Z; X->Y,Z 


#include <stdio.h>
#include <stdlib.h> 
#include <queue>
#include <stack> 
#define tankcapacity_X 5//suc chua binh x 
#define tankcapacity_Y 6 //suc chua binh y 
#define tankcapacity_Z 10 //suc chua binh z 
#define goal 8
#define emptys 0
#define Maxlength 100

using namespace std; 
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
		result->z = max(cur_state.z - (tankcapacity_X - cur_state.x),emptys);
		return 1; 
	} 
	return 0; 
}

int pourWaterZY(State cur_state, State *result){
	if(cur_state.z > 0 &&  cur_state.y < tankcapacity_Y){
		result->x = cur_state.x;
		result->y = min(cur_state.z + cur_state.y, tankcapacity_Y);
		result->z = max(cur_state.z - (tankcapacity_Y - cur_state.y),emptys);
		return 1; 
	} 
	return 0; 
}

int pourWaterYX(State cur_state, State *result){
	if(cur_state.y > 0 &&  cur_state.x < tankcapacity_X){
		result->x = min(cur_state.x + cur_state.y, tankcapacity_X);
		result->y = max(cur_state.y - (tankcapacity_X - cur_state.x),emptys);
		result->z = cur_state.z;
		return 1; 
	} 
	return 0; 
}

int pourWaterYZ(State cur_state, State *result){
	if(cur_state.y > 0 &&  cur_state.z < tankcapacity_Z){
		result->x = cur_state.x;
		result->y = max(cur_state.y - (tankcapacity_Z - cur_state.z),emptys);
		result->z = cur_state.z + cur_state.y;
		return 1; 
	} 
	return 0; 
}

int pourWaterXY(State cur_state, State *result){
	if(cur_state.x > 0 &&  cur_state.y < tankcapacity_Y){
		result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y),emptys);
		result->y = min(cur_state.x + cur_state.y, tankcapacity_Y);
		result->z = cur_state.z;
		return 1; 
	} 
	return 0; 
}

int pourWaterXZ(State cur_state, State *result){
	if(cur_state.x > 0 &&  cur_state.z < tankcapacity_Z){
		result->x = max(cur_state.x - (tankcapacity_Z - cur_state.z),emptys);
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
 

//cau truc nut_cay tim kiem
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function; //thu tu phep toan duoc thuc hien tuong ung
}Node;

//so sanh 2 TT
int compareState(State state1, State state2){
	return (state1.x == state2.x && state1.y == state2.y && state1.z == state2.z);
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
				open_BFS.push(newNode);
			}
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
		printf("\nAction %d: %s", no_action, action[queuePrint.front()->no_function]);
		printState(queuePrint.front()->state);
		queuePrint.pop();
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



