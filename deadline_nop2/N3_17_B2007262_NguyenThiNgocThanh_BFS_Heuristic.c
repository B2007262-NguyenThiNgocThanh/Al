#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define rows 3 //so hang 
#define cols 3 //so cot 
#define empty 0 //tt o trong 
#define max_op 4 // so hanh dong max = 4
#define Maxlength 500

const char* action[]={"First State","Move cell EMPTY to UP","Move cell EMPTY to DOWN",
"Move cell EMPTY to LEFT","Move cell EMPTY to RIGHT"
} ;

//khai bao cau truc state 8 puzzle
typedef struct{
	int eightPuzzle[rows][cols]; //mang 2 chieu rows - cols
	int emptyRow; //vi tri hang o trong
	int emptyCol; //vi tri cot o trong 
}State;

// in trang thai cua 8 puzzle
void printState(State state){
	int row, col;
	//tao khung + in tt 
	printf("\n----------\n");  
	for(row=0; row<rows ; row++){
		for(col=0; col<cols ;col++)
			printf("|%d ", state.eightPuzzle[row][col]);
		printf("|\n"); 
	}
	printf("----------\n"); 
} 
//ham so sanh 2 TT
int compareStates(State state1, State state2){
	//so sanh tt hang o trong & tt cot o trong 
	if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol)
		return 0;
	//so sanh o cac vi tri con lai 
	int row, col; 
	for(row=0 ; row<rows ; row++){
		for(col=0 ; col<cols ; col++)
			if(state1.eightPuzzle[row][col] != state2.eightPuzzle[row][col])
				return 0; 
	} 
	return 1; 
} 

// kt TT dich
int goalcheck(State state, State goal){
	return  compareStates(state, goal); 
} 

//==============================operators=========================//
 
//di chuyen o trong len tren mot o
int upOperator(State state, State *result){
	*result = state; //kq = tt htai
	int emptyR_cur = state.emptyRow; // vi tri hang o trong hien tai 
	int emptyC_cur = state.emptyCol; // vi tri cot o trong hien tai 
	//TH vi tri hang khac bien tren _ nam o hang 1,2 
	if(emptyR_cur > 0){
		result->emptyRow = emptyR_cur - 1; //hang o trong di chuyen len 1 o
		result->emptyCol = emptyC_cur; //giu nguyen vi tri cot
		//vi tri 2 o hoan doi cho nhau:  
		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur -1][emptyC_cur];
		result->eightPuzzle[emptyR_cur-1][emptyC_cur] =  empty;
		return 1; 
	}
	return 0; 
}
//di chuyen o trong xuong duoi mot o
int downOperator(State state, State *result){
	*result = state; //tt hien tai
	int emptyR_cur = state.emptyRow; //vi tri hang o trong htai 
	int emptyC_cur = state.emptyCol; //vi tri cot o trong htai 
	
	//Th vi tri hang khac bien duoi_nam o hang 0,1
	if(emptyR_cur < 2){
		result->emptyRow = emptyR_cur+1; 
		result->emptyCol = emptyC_cur;
		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur+1][emptyC_cur]; 
		result->eightPuzzle[emptyR_cur+1][emptyC_cur] = empty; 
		return 1; 
	} 
	return 0; 
} 

//di chuyen o trong sang trai mot o
int leftOperator(State state, State *result){
	*result = state;
	int emptyR_cur = state.emptyRow; //tt hang htai o trong 
	int emptyC_cur = state.emptyCol; //tt cot htai o trong
	//TH vi tri cot khac bien trai _ o cot 1,2 
	if(emptyC_cur > 0){
		result->emptyRow = emptyR_cur;
		result->emptyCol = emptyC_cur-1; 
		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur][emptyC_cur - 1];
		result->eightPuzzle[emptyR_cur][emptyC_cur - 1] = empty;
		return 1; 
	} 
	return 0; 
} 

// di chuyen o trong sang phai mot o
int rightOperator(State state, State *result){
	*result = state;
	int emptyR_cur = state.emptyRow;
	int emptyC_cur = state.emptyCol;
	
	//TH o trong khac bien phai - o cot 0,1
	if(emptyC_cur < 2){
		result->emptyRow = emptyR_cur;
		result->emptyCol = emptyC_cur + 1;
		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur][emptyC_cur+1];
		result->eightPuzzle[emptyR_cur][emptyC_cur+1] = empty;
		return 1; 
	} 
	return 0; 
} 

//goi cac hanh dong chuyen o trong cho state htai
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
//==========================================================//
//ham heuristic 1
//dem so o sai khac so voi goal
int heuristic1(State state, State goal){
	int row,col,cnt=0;
	for(row=0; row<rows; row++)
		for(col=0; col<cols; col++)
			if(state.eightPuzzle[row][col] != goal.eightPuzzle[row][col])
				cnt++;
	return cnt; 
} 

//ham heuristic 2
//dem so buoc chuyen sai ve o dung cua tt goal 
int heuristic2(State state, State goal){
	int cnt=0;
	int row, col, rowG, colG;
	for(row=0; row<rows; row++){ //dong tt htai 
		for(col=0; col<cols; col++){ //cot tt htai 
			if(state.eightPuzzle[row][col] != empty){ 
				for(rowG=0; rowG<rows; rowG++){
					for(colG=0; colG<rows; colG++){ 
						if(state.eightPuzzle[row][col] == goal.eightPuzzle[rowG][colG]){
							cnt += abs(row - rowG) + abs(col - colG); //so buoc chuyen 
							 colG = cols; 
							 rowG = rows; 
						}
					} 
				} 
			} 
		} 
	} 
	return cnt; 
} 
//==========================================================//
typedef struct Node{
	State state; // luu tt 8 puzzle
	struct Node* parent; // nut cha
	int no_funct; //thu tu cac phep toan
	int heuristic; 
} Node;

//----------------------List--------------------------------// 
typedef struct{
	Node* elements[Maxlength]; //mang
	int size; 
}List;
//khoi tao ds
void makenullList(List *L){
	L->size = 0; 
} 

//kt ds rong
int emptyList(List L){
	return L.size == 0; 
} 

//kt ds day
int fullList(List L){
	return  L.size == Maxlength; 
} 

//tra ve phan tu 
Node* element_at(int p, List L){
	return L.elements[p-1]; 
} 

//them phan tu x vao 1 vi tri pos trong ds L 
void push_List(Node *x, int pos, List *L){
	if(fullList(*L))
		printf("List is full !");
	else{
		int q;
		for(q=L->size; q>=pos; q--) 
			L->elements[q] = L->elements[q-1]; 
		L->elements[pos-1] = x; //them phan tu 
		L->size++; //tang kich thuoc danh sach 
	} 
} 

//xoa phan tu tai vi tri pos trong ds L
void delete_List(int pos, List *L){
	if(emptyList(*L)) 
		printf("List is empty !");
	else if(pos < 1 || pos >L->size)
		printf("Position is not possible to delete !"); // khong the xoa 
	else{
		int i;
		for(i = pos-1 ; i<L->size; i++)
			L->elements[i] = L->elements[i+1];
		L->size--;
	}
} 

// tim tt co thuoc open or closed  
// luu vi tri tim duoc vao bien pos
Node* findState(State state, List L, int *pos){
	int i;
	for(i=1; i<=L.size; i++){
		if(compareStates(element_at(i, L)->state, state)){
			*pos = i;
			return element_at(i,L); 
		}
	} 
	return NULL; 
}

//sx ds theo trong so heuristic
void sort_List(List *L){
	int i,j;
	for(i=0; i<L->size - 1; i++){
		for(j=i+1; j<L->size; j++){
			if(L->elements[i]->heuristic > L->elements[j]->heuristic){
				Node* node = L->elements[i];
				L->elements[i] = L->elements[j];
				L->elements[j] = node;
			}
		}
	}
}
//==========================================================//
//thuat toan tim kiem tot nhat dau tien
//f = h 
Node* best_FS(State state, State goal){
	List open;
	List closed;
	makenullList(&open);
	makenullList(&closed);
	//khoi tao tt nut cha 
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_funct = 0;
	root->heuristic = heuristic1(root->state, goal);
	push_List(root, open.size+1, &open);
	
	while(!emptyList(open)){
		Node* node = element_at(1,open);
		delete_List(1,&open); //xoa phan tu dau tien trong ds pen 
		push_List(node,closed.size+1,&closed) ; //them vao closed 
		//kt tt dich 
		if(goalcheck(node->state, goal))
			return node;
		int opt;
		for(opt=1; opt<=max_op; opt++){
			State newstate;
			newstate = node->state;
			//goi cac hanh dong 
			if(callOperator(node->state, &newstate, opt)){
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->state = newstate;
				newnode->parent = node;
				newnode->no_funct = opt;
				newnode->heuristic = heuristic1(newstate, goal);
				
				//kt tt moi co thuoc open / closed
				int pos_open, pos_closed;
				Node* nodeFoundopen = findState(newstate, open, &pos_open);
				Node* nodeFoundclosed = findState(newstate, closed, &pos_closed);
				if(nodeFoundopen == NULL && nodeFoundclosed == NULL){
					push_List(newnode, open.size+1, &open); 
				} 
				else if(nodeFoundopen!=NULL && nodeFoundopen->heuristic > newnode->heuristic){
					delete_List(pos_open, &open);
					push_List(newnode, pos_open, &open); 
				} 
				else if(nodeFoundclosed!=NULL && nodeFoundclosed->heuristic > newnode->heuristic){
					delete_List(pos_closed, &closed);
					push_List(newnode, open.size+1, &open); 
				} 
				sort_List(&open); 
			}
		} 
	} 
	return NULL; 
} 
 
//==========================================================//
//ham in kq cua thuat toan bestFS
void print_WaysToGetGoal(Node* node){
	List listPrint;
	makenullList(&listPrint);
	//duyet nguoc ve parent
	while(node->parent != NULL){
		push_List(node, listPrint.size+1, &listPrint);//them vao sau ds 
		node = node->parent; 
	} 
	push_List(node, listPrint.size+1, &listPrint);
	int no_action = 0, i;
	for(i=listPrint.size; i>0; i--){
		printf("\nAction %d: %s", no_action, action[element_at(i,listPrint)->no_funct]);
		printState(element_at(i,listPrint)->state);
		no_action++; 
	}
} 
//==========================================================//
int main(){
	State state;
	state.emptyRow = 1;
	state.emptyCol = 1;
	state.eightPuzzle[0][0] = 3;
	state.eightPuzzle[0][1] = 4;
	state.eightPuzzle[0][2] = 5;
	state.eightPuzzle[1][0] = 1;
	state.eightPuzzle[1][1] = 0;
	state.eightPuzzle[1][2] = 2;
	state.eightPuzzle[2][0] = 6;
	state.eightPuzzle[2][1] = 7;
	state.eightPuzzle[2][2] = 8;
	
	State goal;
	goal.emptyRow = 0;
	goal.emptyCol = 0;
	goal.eightPuzzle[0][0] = 0; 
	goal.eightPuzzle[0][1] = 1;
	goal.eightPuzzle[0][2] = 2;
	goal.eightPuzzle[1][0] = 3;
	goal.eightPuzzle[1][1] = 4;
	goal.eightPuzzle[1][2] = 5;
	goal.eightPuzzle[2][0] = 6;
	goal.eightPuzzle[2][1] = 7;
	goal.eightPuzzle[2][2] = 8;
	
	Node* p = best_FS(state, goal);
	print_WaysToGetGoal(p);	
	return 0; 
} 

