//============Thanh===========//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define rows 3 //so hang 
#define cols 3 //so cot 
#define empty 0 //tt o trong 
#define max_op 4 //hanh dong toi da 
#define Maxlength 500 

//ten cac tt hanh dong 
const char* action[]={"First State","Move cell EMPTY to UP",
				"Move cell EMPTY to DOWN","Move cell EMPTY to LEFT",
							"Move cell EMPTY to RIGHT"};
//cau truc tt 
typedef struct{
	int eightPuzzle[rows][cols]; //mang 2 chieu luu so hang so cot 
	int emptyRow; //vi tri hang o trong 
	int emptyCol; //vi tri cot o trong 
}State; 

//in tt
void printState(State state){
	printf("\n-------------\n");
	int row,col;
	for(row=0; row<rows; row++){
		for(col=0; col<cols; col++)
			printf("| %d ",state.eightPuzzle[row][col]);
		printf("|\n"); 
	}
		
	printf("-------------\n"); 
} 
//kt tt 
int goalcheck(State state, State goal){
	return compareStates(state, goal);
}
//di chuyen o trong len tren 1 o
int upOperator(State state, State *result){
	*result = state;
	int emptyRcur = state.emptyRow;
	int emptyCcur = state.emptyCol;
	
	if(emptyRcur > 0){
		result->emptyRow = emptyRcur - 1;
		result->emptyCol = emptyCcur;
		result->eightPuzzle[emptyRcur][emptyCcur] = state.eightPuzzle[emptyRcur - 1][emptyCcur];
		result->eightPuzzle[emptyRcur - 1][emptyCcur] = empty;
		return 1;
	}
	return 0;
}
//di chuyen o trong xuong duoi 1 o
int downOperator(State state, State *result){
	*result = state;
	int emptyRcur = state.emptyRow;
	int emptyCcur = state.emptyCol;
	
	if(emptyRcur < 2){
		result->emptyRow = emptyRcur + 1;
		result->emptyCol = emptyCcur;
		result->eightPuzzle[emptyRcur][emptyCcur] = state.eightPuzzle[emptyRcur+1][emptyCcur];
		result->eightPuzzle[emptyRcur+1][emptyCcur] = empty;
		return 1;
	}
	return 0;
}

//di chuyen o trong sang trai 1 o
int leftOperator(State state, State *result){
	*result = state;
	int emptyRcur = state.emptyRow;
	int emptyCcur = state.emptyCol;
	
	if(emptyCcur > 0){
		result->emptyRow = emptyRcur;
		result->emptyCol = emptyCcur - 1;
		result->eightPuzzle[emptyRcur][emptyCcur] = state.eightPuzzle[emptyRcur][emptyCcur - 1];
		result->eightPuzzle[emptyRcur][emptyCcur - 1] = empty;
		return 1;
	}
	return 0;
}
//di chuyen sang phai 1 o
int rightOperator(State state, State *result){
	*result = state;
	int emptyRcur = state.emptyRow;
	int emptyCcur = state.emptyCol;
	
	if(emptyCcur < 2){
		result->emptyRow = emptyRcur;
		result->emptyCol = emptyCcur + 1;
		result->eightPuzzle[emptyRcur][emptyCcur] = state.eightPuzzle[emptyRcur][emptyCcur + 1];
		result->eightPuzzle[emptyRcur][emptyCcur + 1] = empty;
		return 1;
	}
	return 0;
}
//goi cac hanh dong 
int callOperator(State state, State *result, int opt){
	switch(opt){
		case 1: return upOperator(state, result);
		case 2: return downOperator(state, result);
		case 3: return leftOperator(state, result);
		case 4: return rightOperator(state, result);
		default: printf("ERROR !");
			return 0;
	}
}
//======================== node + list ============================//
typedef struct Node{
	State state;
	struct Node* parent;
	int no_funct;
	int f,g,h;
}Node;

typedef struct{
	Node* ele[Maxlength];
	int size;
}List;

//khoi tao danh sach
void makenullList(List *L){
	L->size = 0;
}

//kt rong
int emptyList(List L){
	return L.size == 0;
}

//kt day
int fullList(List L){
	return L.size == Maxlength;
}

//tra ve phan tu
Node* ele_at(int p, List L){
	return L.ele[p-1];
}

void push(Node* x, int pos, List *L){
	if(fullList(*L))
		printf("List is full !\n");
	else{
		int q;
		for(q=L->size; q>=pos; q--)
			L->ele[q] = L->ele[q-1];
		L->ele[pos - 1] = x;
		L->size++; 
	}
}
void deleteL(int pos, List *L){
	if(emptyList(*L))
		printf("List is empty !");
	else if(pos < 1 || pos > L->size)
		printf("Position is not possible to Delete !");
	else{
		int i;
		for(i= pos-1; i<L->size; i++)
			L->ele[i] = L->ele[i+1];
		L->size--;
	}
}


//============================HEURISTIC========================//
//dem so o sai khac voi goal
int heuristic1(State state, State goal){
	int r,c, cnt=0;
	for(r=0; r<rows; r++)
		for(c=0; c<cols; c++)
			if(state.eightPuzzle[r][c] != goal.eightPuzzle[r][c])
				return cnt++;
	return cnt;
}
//====================================================//
//so sanh 2 tt 
int compareStates(State state1, State state2){
	if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol)
		return 0;
	int row, col;
	for(row=0; row<rows; row++)
		for(col=0; col<cols; col++)
			if(state1.eightPuzzle[row][col] != state2.eightPuzzle[row][col])
				return 0;
	return 1;
}

//tim  
Node* findState(State state, List L, int *pos){
	int i;
	for(i=1; i<=L.size; i++){
		if(compareStates(ele_at(i, L)->state, state)){
			*pos = i;
			return ele_at(i, L);
		}
	}
	return NULL;
}

//sap xep phan tu trong ds 
void sort_List(List *L){
	int i,j;
	for(i=0; i<L->size - 1; i++){
		for(j=i+1; j<L->size; j++){
			if(L->ele[i]->f > L->ele[j]->f){ 
				Node* node = L->ele[i];
				L->ele[i] = L->ele[j];
				L->ele[j] = node;
			}
		}
	}
}

//A_star_A Puzzle 
Node* Astar(State state, State goal){
	List open;
	List closed;
	makenullList(&open);
	makenullList(&closed);
	
	Node* root=(Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_funct = 0;
	root->g = 0;
	root->h = heuristic1(root->state, goal);
	root->f = root->g + root->h;
	
	push(root, open.size+1, &open);
	
	while(!emptyList(open)){
		Node* node = ele_at(1, open);
		deleteL(1, &open);
		push(node,closed.size+1,&closed);
		
		if(goalcheck(node->state, goal))
			return node;
		
		int opt;
		for(opt=1; opt<=max_op; opt++){
			State newstate ;
			//newstate = node->state;
			if(callOperator(node->state, &newstate, opt)){
				
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->parent = node;
				newNode->no_funct = opt;
				newNode->g = node->g + 1;
				newNode->h = heuristic1(newstate, goal);
				newNode->f = newNode->g + newNode->h;
				
				//kt tt moi co thuoc open/closed 
				int posopen, posclosed;
				Node* nodeFoundopen = findState(newstate, open, &posopen);
				Node* nodeFoundclosed = findState(newstate, closed, &posclosed);
				
				if(nodeFoundopen == NULL && nodeFoundclosed == NULL)
					push(newNode, open.size+1, &open);
					
				else if(nodeFoundopen != NULL && nodeFoundopen->g > newNode->g){
					deleteL(posopen, &open);
					push(newNode, posopen, &open);
				}
				
				else if(nodeFoundclosed != NULL && nodeFoundclosed->g > newNode->g){
					deleteL(posclosed, &closed);
					push(newNode, open.size+1, &open);
				}
			}
		}
		sort_List(&open);
	}
	return NULL;
}

//ham in kq cua thuat toan bestFS
void print_WaysToGetGoal(Node* node){
	List listPrint;
	makenullList(&listPrint);
	//duyet nguoc ve parent
	while(node->parent != NULL){
		push(node, listPrint.size+1, &listPrint);//them vao sau ds 
		node = node->parent; 
	} 
	push(node, listPrint.size+1, &listPrint);
	
	int no_action = 0, i;
	for(i=listPrint.size; i>0; i--){
		printf("\nAction %d: %s", no_action, action[ele_at(i,listPrint)->no_funct]);
		printState(ele_at(i,listPrint)->state);
		no_action++; 
	}
} 

int main(){
	State state;
	state.emptyRow = 1;
	state.emptyCol = 1;
	state.eightPuzzle[0][0] = 1;
	state.eightPuzzle[0][1] = 2;
	state.eightPuzzle[0][2] = 3;
	state.eightPuzzle[1][0] = 8;
	state.eightPuzzle[1][1] = 0;
	state.eightPuzzle[1][2] = 4;
	state.eightPuzzle[2][0] = 7;
	state.eightPuzzle[2][1] = 6;
	state.eightPuzzle[2][2] = 5;
	
	State goal;
	goal.emptyRow = 1;
	goal.emptyCol = 0;
	goal.eightPuzzle[0][0] = 2;
	goal.eightPuzzle[0][1] = 8;
	goal.eightPuzzle[0][2] = 1;
	goal.eightPuzzle[1][0] = 0;
	goal.eightPuzzle[1][1] = 4;
	goal.eightPuzzle[1][2] = 3;
	goal.eightPuzzle[2][0] = 7;
	goal.eightPuzzle[2][1] = 6;
	goal.eightPuzzle[2][2] = 5;
	
	Node* p =Astar(state, goal);
	print_WaysToGetGoal(p);
	return 0;
}







