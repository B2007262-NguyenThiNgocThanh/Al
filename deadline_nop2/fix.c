#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 3
#define Maxlist 400
#define Hole 0

const char* act[] = {"first state", "move cell HOLE to UP", 
					 "move cell HOLE to DOWN", "move cell HOLE to LEFT",
					 "move cell HOLE to RIGHT"};

typedef struct {
	int holeRow, holeCol;
	int E[size][size];
} State;

typedef struct Node {
	State state;
	struct Node* parent;
	int no_func;
	int heuristic;
} Node;

//---------------- Array list ----------------
typedef struct {
	int lenght;
	Node* A[Maxlist];
} List;

void makenull_list(List *l) {
	l->lenght = 0;
}

int empty_list(List l) {
	return l.lenght == 0;
}

int full_list(List l) {
	return l.lenght == Maxlist;
}

Node* element_at(int pos, List l) {
	return l.A[pos - 1];
}

void insert_list(List *l, int pos, Node* x) {
	if (!full_list(*l)) {
		int q;
		for (q = l->lenght; q >= pos; q--)
			l->A[q] = l->A[q - 1];
		l->A[pos - 1] = x;
		l->lenght++;
	}
	else printf("Error, List is full!");
}

void delete_list(List *l, int pos) {
	if (empty_list(*l))
		printf("Error, List is empty!");
	else if (pos < 1 || pos > l->lenght)
		printf("This position is wrong!");
	else {
		int i;
		for (i = pos - 1; i < l->lenght; i++)
			l->A[i] = l->A[i + 1];
		l->lenght--;
	}
}

void sort_list(List *l) {
	int i, j;
	for (i = 0; i < l->lenght - 1; i++)
		for (j = i + 1; j < l->lenght; j++)
			if (l->A[i]->heuristic > l->A[j]->heuristic) {
				//swap
				Node* temp = l->A[i];
				l->A[i] = l->A[j];
				l->A[j] = temp;
			}
}

//---------------- Array list ----------------

int cmpState(State s1, State s2) {
	int r, c;
	for (r = 0; r < size; r++)
		for (c = 0; c < size; c++)
			if (s1.E[r][c] != s2.E[r][c])
				return 0;
	return 1;
}

Node* find_state(State s, List l, int *pos) {
	int i;
	for (i = 1; i <= l.lenght; i++)
		if (cmpState(element_at(i, l)->state, s)) {
			*pos = i;
			return element_at(i, l);
		}
	return NULL;
}

//4 operators ---------------------------------------------
int up(State state, State *result) {
	*result = state;
	if (state.holeRow > 0) {
		result->holeRow = state.holeRow - 1;
		result->holeCol = state.holeCol;
		result->E[state.holeRow][state.holeCol] = state.E[state.holeRow - 1][state.holeCol];
		result->E[state.holeRow - 1][state.holeCol] = Hole;
		return 1;
	}
	return 0;
}

int down(State state, State *result) {
	*result = state;
	if (state.holeRow < size - 1) {
		result->holeRow = state.holeRow + 1;
		result->holeCol = state.holeCol;
		result->E[state.holeRow][state.holeCol] = state.E[state.holeRow + 1][state.holeCol];
		result->E[state.holeRow + 1][state.holeCol] = Hole;
		return 1;
	}
	return 0;
}

int left(State state, State *result) {
	*result = state;
	if (state.holeCol > 0) {
		result->holeRow = state.holeRow;
		result->holeCol = state.holeCol - 1;
		result->E[state.holeRow][state.holeCol] = state.E[state.holeRow][state.holeCol - 1];
		result->E[state.holeRow][state.holeCol - 1] = Hole;
		return 1;
	}
	return 0;
}

int right(State state, State *result) {
	*result = state;
	if (state.holeCol < size - 1) {
		result->holeRow = state.holeRow;
		result->holeCol = state.holeCol + 1;
		result->E[state.holeRow][state.holeCol] = state.E[state.holeRow][state.holeCol + 1];
		result->E[state.holeRow][state.holeCol + 1] = Hole;
		return 1;
	}
	return 0;
}
//4 operators ---------------------------------------------

int call_operator(State s, int opt, State *result) {
	switch (opt) {
		case 1: return up(s, result);
		case 2: return down(s, result);
		case 3: return left(s, result);
		case 4: return right(s, result);
	}
}

//heuristic 1: dem so o sai khac
int h1(State state, State goal) {
	int r, c, cnt = 0;
	for (r = 0; r < size; r++)
		for (c = 0; c < size; c++)
			if (state.E[r][c] != goal.E[r][c])
				cnt += 1;
	return cnt;
}

//heuristic 2: dem do lech cua moi o hien tai voi goal
int h2(State state, State goal) {
	int cnt = 0;
	int r, c, rg, cg;
	for (r = 0; r < size; r++)
		for (c = 0; c < size; c++)
			if (state.E[r][c] != Hole)
				for (rg = 0; rg < size; rg++)
					for (cg = 0; cg < size; cg++)
						if (state.E[r][c] == goal.E[rg][cg]) {
							cnt += abs(r - rg) + abs(c - cg);
							rg = size;
							cg = size;
						}
	return cnt;
}

Node* bestFirstSearch(State state, State goal) {
	List open, closed;
	makenull_list(&open);
	makenull_list(&closed);
	
	Node* root = (Node*) malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_func = 0;
	root->heuristic = h1(root->state, goal);
	
	insert_list(&open, open.lenght + 1, root);
	
	while (!empty_list(open)) {
		Node* node = element_at(1, open);
		delete_list(&open, 1);
		insert_list(&closed, closed.lenght + 1, node);
		
		//goalcheck
		if (cmpState(node->state, goal))
			return node;
		
		int opt;
		for (opt = 1; opt <= 4; opt++) {
			State newstate = node->state;
			
			if (call_operator(node->state, opt, &newstate)) {
				Node* newnode = (Node*) malloc(sizeof(Node));
				newnode->state = newstate;
				newnode->parent = node;
				newnode->no_func = opt;
				newnode->heuristic = h1(newstate, goal);
				
				int pos_open, pos_closed;
				Node* nodeOpen = find_state(newstate, open, &pos_open);
				Node* nodeClosed = find_state(newstate, closed, &pos_closed);
				
				if (nodeOpen == NULL && nodeClosed == NULL)
					insert_list(&open, open.lenght + 1, newnode);
					
				else if (nodeOpen != NULL && nodeOpen->heuristic > newnode->heuristic) {
					delete_list(&open, pos_open);
					insert_list(&open, pos_open, newnode);
				}
				
				else if (nodeClosed != NULL && nodeClosed->heuristic > newnode->heuristic) {
					delete_list(&closed, pos_closed);
					insert_list(&open, open.lenght + 1, newnode);
				}
				sort_list(&open);
			}
		}
	}
	return NULL;
}

void print_state(State state) {
	int r, c;
	printf("\n----------\n");
	for (r = 0; r < size; r++) {
		for (c = 0; c < size; c++)
			printf("|%d ", state.E[r][c]);
		printf("|\n");
	}
	printf("\n----------\n");
}

void printWay(Node* node) {
	List pr;
	makenull_list(&pr);
	while (node->parent != NULL) {
		insert_list(&pr, pr.lenght + 1, node);
		node = node->parent;
	}
	insert_list(&pr, pr.lenght + 1, node);
	
	int no_action = 0, i;
	for (i = pr.lenght; i > 0; i--) {
		printf("\nAction %d: %s", no_action, act[element_at(i, pr)->no_func]);
		print_state(element_at(i, pr)->state);
		no_action++;
	}
}

int main() {
	State start;
	start.holeRow=1;
	start.holeCol =1; 
	start.E[0][0] = 3;
	start.E[0][1] = 4;
	start.E[0][2] = 5;
	start.E[1][0] = 1;
	start.E[1][1] = Hole;
	start.E[1][2] = 2;
	start.E[2][0] = 6;
	start.E[2][1] = 7;
	start.E[2][2] = 8;
	
	State goal;
	goal.holeRow =  0;
	goal.holeCol = 0; 
	goal.E[0][0] = Hole;
	goal.E[0][1] = 1;
	goal.E[0][2] = 2;
	goal.E[1][0] = 3;
	goal.E[1][1] = 4;
	goal.E[1][2] = 5;
	goal.E[2][0] = 6;
	goal.E[2][1] = 7;
	goal.E[2][2] = 8;
	
	Node* p = bestFirstSearch(start, goal);
	printWay(p);
	return 0;
}





//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h> 
//#define rows 3 //so hang 
//#define cols 3 //so cot 
//#define empty 0 //tt o trong 
//#define max_op 4 // so hanh dong max = 4
//#define Maxlength 500
//
//const char* action[]={"First State","Move cell EMPTY to UP","Move cell EMPTY to DOWN",
//"Move cell EMPTY to LEFT","Move cell EMPTY to RIGHT"
//} ;
//
////khai bao cau truc state 8 puzzle
//typedef struct{
//	int eightPuzzle[rows][cols]; //mang 2 chieu rows - cols
//	int emptyRow; //vi tri hang o trong
//	int emptyCol; //vi tri cot o trong 
//}State;
//
//// in trang thai cua 8 puzzle
//void printState(State state){
//	int row, col;
//	//tao khung + in tt 
//	printf("\n----------\n");  
//	for(row=0; row<rows ; row++){
//		for(col=0; col<cols ;col++)
//			printf("|%d ", state.eightPuzzle[row][col]);
//		printf("|\n"); 
//	}
//	printf("----------\n"); 
//} 
////ham so sanh 2 TT
//int compareStates(State state1, State state2){
//	//so sanh tt hang o trong & tt cot o trong 
//	if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol)
//		return 0;
//	//so sanh o cac vi tri con lai 
//	int row, col; 
//	for(row=0 ; row<rows ; row++){
//		for(col=0 ; col<cols ; col++)
//			if(state1.eightPuzzle[row][col] != state2.eightPuzzle[row][col])
//				return 0; 
//	} 
//	return 1; 
//} 
//
//// kt TT dich
//int goalcheck(State state, State goal){
//	return  compareStates(state, goal); 
//} 
//
////==============================operators=========================//
// 
////di chuyen o trong len tren mot o
//int upOperator(State state, State *result){
//	*result = state; //kq = tt htai
//	int emptyR_cur = state.emptyRow; // vi tri hang o trong hien tai 
//	int emptyC_cur = state.emptyCol; // vi tri cot o trong hien tai 
//	//TH vi tri hang khac bien tren _ nam o hang 1,2 
//	if(emptyR_cur > 0){
//		result->emptyRow = emptyR_cur - 1; //hang o trong di chuyen len 1 o
//		result->emptyCol = emptyC_cur; //giu nguyen vi tri cot
//		//vi tri 2 o hoan doi cho nhau:  
//		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur -1][emptyC_cur];
//		result->eightPuzzle[emptyR_cur-1][emptyC_cur] =  empty;
//		return 1; 
//	}
//	return 0; 
//}
////di chuyen o trong xuong duoi mot o
//int downOperator(State state, State *result){
//	*result = state; //tt hien tai
//	int emptyR_cur = state.emptyRow; //vi tri hang o trong htai 
//	int emptyC_cur = state.emptyCol; //vi tri cot o trong htai 
//	
//	//Th vi tri hang khac bien duoi_nam o hang 0,1
//	if(emptyR_cur < 2){
//		result->emptyRow = emptyR_cur+1; 
//		result->emptyCol = emptyC_cur;
//		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur+1][emptyC_cur]; 
//		result->eightPuzzle[emptyR_cur+1][emptyC_cur] = empty; 
//		return 1; 
//	} 
//	return 0; 
//} 
//
////di chuyen o trong sang trai mot o
//int leftOperator(State state, State *result){
//	*result = state;
//	int emptyR_cur = state.emptyRow; //tt hang htai o trong 
//	int emptyC_cur = state.emptyCol; //tt cot htai o trong
//	//TH vi tri cot khac bien trai _ o cot 1,2 
//	if(emptyC_cur > 0){
//		result->emptyRow = emptyR_cur;
//		result->emptyCol = emptyC_cur-1; 
//		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur][emptyC_cur - 1];
//		result->eightPuzzle[emptyR_cur][emptyC_cur - 1] = empty;
//		return 1; 
//	} 
//	return 0; 
//} 
//
//// di chuyen o trong sang phai mot o
//int rightOperator(State state, State *result){
//	*result = state;
//	int emptyR_cur = state.emptyRow;
//	int emptyC_cur = state.emptyCol;
//	
//	//TH o trong khac bien phai - o cot 0,1
//	if(emptyC_cur < 2){
//		result->emptyRow = emptyR_cur;
//		result->emptyCol = emptyC_cur + 1;
//		result->eightPuzzle[emptyR_cur][emptyC_cur] = state.eightPuzzle[emptyR_cur][emptyC_cur+1];
//		result->eightPuzzle[emptyR_cur][emptyC_cur+1] = empty;
//		return 1; 
//	} 
//	return 0; 
//} 
//
////goi cac hanh dong chuyen o trong cho state htai
//int callOperator(State state, State *result, int opt){
//	switch(opt){
//		case 1: return upOperator(state, result);
//		case 2: return downOperator(state, result);
//		case 3: return leftOperator(state, result);
//		case 4: return rightOperator(state, result);
//		default: printf("ERROR !");
//			return 0; 
//	} 
//} 
////==========================================================//
////ham heuristic 1
////dem so o sai khac so voi goal
//int heuristic1(State state, State goal){
//	int row,col,cnt=0;
//	for(row=0; row<rows; row++)
//		for(col=0; col<cols; col++)
//			if(state.eightPuzzle[row][col] != goal.eightPuzzle[row][col])
//				cnt++;
//	return cnt; 
//} 
//
////ham heuristic 2
////dem so buoc chuyen sai ve o dung cua tt goal 
//int heuristic2(State state, State goal){
//	int cnt=0;
//	int row, col, rowG, colG;
//	for(row=0; row<rows; row++){ //dong tt htai 
//		for(col=0; col<cols; col++){ //cot tt htai 
//			if(state.eightPuzzle[row][col] != empty){ 
//				for(rowG=0; rowG<rows; rowG++){
//					for(colG=0; colG<rows; colG++){ 
//						if(state.eightPuzzle[row][col] == goal.eightPuzzle[rowG][colG]){
//							cnt += abs(row - rowG) + abs(col - colG); //so buoc chuyen 
//							 colG = cols; 
//							 rowG = rows; 
//						}
//					} 
//				} 
//			} 
//		} 
//	} 
//	return cnt; 
//} 
////==========================================================//
//typedef struct Node{
//	State state;
//	struct Node* parent;
//	int no_funct;
//	int f,g,h;
//}Node;
////----------------------List--------------------------------// 
//typedef struct{
//	Node* elements[Maxlength]; //mang
//	int size; 
//}List;
////khoi tao ds
//void makenullList(List *L){
//	L->size = 0; 
//} 
//
////kt ds rong
//int emptyList(List L){
//	return L.size == 0; 
//} 
//
////kt ds day
//int fullList(List L){
//	return  L.size == Maxlength; 
//} 
//
////tra ve phan tu 
//Node* element_at(int p, List L){
//	return L.elements[p-1]; 
//} 
//
////them phan tu x vao 1 vi tri pos trong ds L 
//void push_List(Node *x, int pos, List *L){
//	if(fullList(*L))
//		printf("List is full !");
//	else{
//		int q;
//		for(q=L->size; q>=pos; q--) 
//			L->elements[q] = L->elements[q-1]; 
//		L->elements[pos-1] = x; //them phan tu 
//		L->size++; //tang kich thuoc danh sach 
//	} 
//} 
//
////xoa phan tu tai vi tri pos trong ds L
//void delete_List(int pos, List *L){
//	if(emptyList(*L)) 
//		printf("List is empty !");
//	else if(pos < 1 || pos >L->size)
//		printf("Position is not possible to delete !"); // khong the xoa 
//	else{
//		int i;
//		for(i = pos-1 ; i<L->size; i++)
//			L->elements[i] = L->elements[i+1];
//		L->size--;
//	}
//} 
//
//// tim tt co thuoc open or closed  
//// luu vi tri tim duoc vao bien pos
//Node* findState(State state, List L, int *pos){
//	int i;
//	for(i=1; i<=L.size; i++){
//		if(compareStates(element_at(i, L)->state, state)){
//			*pos = i;
//			return element_at(i,L); 
//		}
//	} 
//	return NULL; 
//}
//
////sx ds theo trong so heuristic
//void sort_List(List *L){
//	int i,j;
//	for(i=0; i<L->size - 1; i++){
//		for(j=i+1; j<L->size; j++){
//			if(L->elements[i]->f > L->elements[j]->f){
//				Node* node = L->elements[i];
//				L->elements[i] = L->elements[j];
//				L->elements[j] = node;
//			}
//		}
//	}
//}
////==========================================================//
////thuat toan tim kiem tot nhat dau tien
////f = h 
//Node* Astar(State state, State goal){
//	List open;
//	List closed;
//	makenullList(&open);
//	makenullList(&closed);
//	//khoi tao tt nut cha 
//	Node* root = (Node*)malloc(sizeof(Node));
//	root->state = state;
//	root->parent = NULL;
//	root->no_funct = 0;root->g = 0;
//	root->h = heuristic1(root->state, goal);
//	root->f = root->g + root->h;
//	push_List(root, open.size+1, &open);
//	
//	while(!emptyList(open)){
//		Node* node = element_at(1,open);
//		delete_List(1,&open); //xoa phan tu dau tien trong ds pen 
//		push_List(node,closed.size+1,&closed) ; //them vao closed 
//		//kt tt dich 
//		if(goalcheck(node->state, goal))
//			return node;
//		int opt;
//		for(opt=1; opt<=max_op; opt++){
//			State newstate;
//			newstate = node->state;
//			//goi cac hanh dong 
//			if(callOperator(node->state, &newstate, opt)){
//				Node *newnode = (Node*)malloc(sizeof(Node));
//				newnode->state = newstate;
//				newnode->parent = node;
//				newnode->no_funct = opt;
//				newnode->g = node->g + 1;
//				newnode->h = heuristic1(newstate, goal);
//				newnode->f = newnode->g + newnode->h;
//				
//				//kt tt moi co thuoc open / closed
//				int pos_open, pos_closed;
//				Node* nodeFoundopen = findState(newstate, open, &pos_open);
//				Node* nodeFoundclosed = findState(newstate, closed, &pos_closed);
//				if(nodeFoundopen == NULL && nodeFoundclosed == NULL){
//					push_List(newnode, open.size+1, &open); 
//				} 
//				else if(nodeFoundopen!=NULL && nodeFoundopen->g > newnode->g){
//					delete_List(pos_open, &open);
//					push_List(newnode, pos_open, &open); 
//				} 
//				else if(nodeFoundclosed!=NULL && nodeFoundclosed->g > newnode->g){
//					delete_List(pos_closed, &closed);
//					push_List(newnode, open.size+1, &open); 
//				} 
//				sort_List(&open); 
//			}
//		} 
//	} 
//	return NULL; 
//} 
// 
////==========================================================//
////ham in kq cua thuat toan bestFS
//void print_WaysToGetGoal(Node* node){
//	List listPrint;
//	makenullList(&listPrint);
//	//duyet nguoc ve parent
//	while(node->parent != NULL){
//		push_List(node, listPrint.size+1, &listPrint);//them vao sau ds 
//		node = node->parent; 
//	} 
//	push_List(node, listPrint.size+1, &listPrint);
//	int no_action = 0, i;
//	for(i=listPrint.size; i>0; i--){
//		printf("\nAction %d: %s", no_action, action[element_at(i,listPrint)->no_funct]);
//		printState(element_at(i,listPrint)->state);
//		no_action++; 
//	}
//} 
////==========================================================//
//int main(){
//	State state;
//	state.emptyRow = 1;
//	state.emptyCol = 1;
//	state.eightPuzzle[0][0] = 1;
//	state.eightPuzzle[0][1] = 2;
//	state.eightPuzzle[0][2] = 3;
//	state.eightPuzzle[1][0] = 8;
//	state.eightPuzzle[1][1] = 0;
//	state.eightPuzzle[1][2] = 4;
//	state.eightPuzzle[2][0] = 7;
//	state.eightPuzzle[2][1] = 6;
//	state.eightPuzzle[2][2] = 5;
//	
//	State goal;
//	goal.emptyRow = 1;
//	goal.emptyCol = 0;
//	goal.eightPuzzle[0][0] = 2; 
//	goal.eightPuzzle[0][1] = 8;
//	goal.eightPuzzle[0][2] = 1;
//	goal.eightPuzzle[1][0] = 0;
//	goal.eightPuzzle[1][1] = 4;
//	goal.eightPuzzle[1][2] = 5;
//	goal.eightPuzzle[2][0] = 6;
//	goal.eightPuzzle[2][1] = 7;
//	goal.eightPuzzle[2][2] = 8;
//	
//	Node* p = Astar(state, goal);
//	print_WaysToGetGoal(p);	
//	return 0; 
//} 


//#include<stdio.h>
//#include<stdlib.h>
//
//#define Up 0
//#define Ngua 1
//#define SLy 6
//#define empty -1
//#define maxlength 100
//
//const char* action[] = {"First State", "1-2-3", "2-3-4", "3-4-5", "4-5-6"};
//			
////khai bao trang thai
//typedef struct{
//	int Ly[SLy];//luu so ly
//}State;
//
////khoi tao TT
//void makeNullState(State *state){
//	int i;
//	for(i=0; i<SLy; i++)
//		state->Ly[i] = empty;
//}
//
////kt muc tieu
//int goalCheck(State state){
//	int i;
//	for(i=0; i<SLy; i++)
//		if(state.Ly[i] != Ngua)
//			return 0;
//	return 1;
//}
//
////in trang thai
//void print_State(State state){
//	int i;
//	for(i=0; i<SLy; i++)
//		printf(" %d ", state.Ly[i]);
//	printf("\n");
//}
//
////cac phep toan
//void call_operator(State state, State *result, int position){
//	int i;
//	for(i=0; i<SLy; i++)
//		if(position-1 <= i && position+1 >= i)
//			result->Ly[i] = 1 - state.Ly[i];
//		else result->Ly[i] = state.Ly[i];
//}
//
////-----------------------------Duyet Chieu Sau-----------------------------
//
////khai bao cau truc dinh => dung cay tim kiem
//typedef struct Node{
//	State state;
//	struct Node* Parent;
//	int no_function;
//}Node;
//
////khai bao stack
//typedef struct{
//	Node* Elements[maxlength];
//	int Top_idx;
//}Stack;
//
////them ptu vao stack
//void pushStack(Node* x, Stack *stack){
//	if(full_Stack(*stack))
//		printf("Error! Stack full");
//	else{
//		stack->Top_idx -= 1;
//		stack->Elements[stack->Top_idx] = x;
//	}
//}
//
////khoi tao rong
//void makeNullStack(Stack *stack){
//	stack->Top_idx = maxlength;
//}
//
////kt rong
//int emptyStack(Stack stack){
//	return stack.Top_idx == maxlength;
//}
//
////kt day
//int full_Stack(Stack stack){
//	return stack.Top_idx == 0;
//}
//
////tra ve ptu tren dinh
//Node* top(Stack stack){
//	if(!emptyStack(stack))
//		return stack.Elements[stack.Top_idx];
//	return NULL;
//}
//
////xoa ptu dinh
//void pop(Stack *stack){
//	if(!emptyStack(*stack))
//		stack->Top_idx += 1;
//	else printf("Error!");
//}
//
////so sanh 2 TT
//int compareStates(State S1, State S2){
//	int i;
//	for(i=0; i<SLy; i++)
//		if(S1.Ly[i] != S2.Ly[i])
//			return 0;
//	return 1;
//}
////tim trang thai trong stack Open&Close
//int find_State(State state, Stack openStack){
//	while(!emptyStack(openStack)){
//		if(compareStates(top(openStack)->state, state))
//			return 1;
//		pop(&openStack);
//	}
//	return 0;
//}
//
////thuat toan duyet chieu sau
//Node* DFS_Algorithm(State state){
//	//khai bao 2 stack open & close
//	Stack Open_DFS;
//	Stack Close_DFS;
//	makeNullStack(&Open_DFS);
//	makeNullStack(&Close_DFS);
//	
//	//tao nut trang thai cha
//	Node* root = (Node*)malloc(sizeof(Node));
//	root->state = state;
//	root->Parent = NULL;
//	root->no_function = 0;
//	pushStack(root, &Open_DFS);
//	
//	while(!emptyStack(Open_DFS)){
//		//lay 1 dinh trong ngan xep
//		Node* node = top(Open_DFS);
//		pop(&Open_DFS);
//		pushStack(node, &Close_DFS);
//		
//		//kt co phai TT muc tieu
//		if(goalCheck(node->state))
//			return node;
//		
//		//goi ham trang thai
//		int opt;
//		for(opt=1; opt<=4; opt++){
//			State newstate;
//			makeNullState(&newstate);
//			call_operator(node->state, &newstate, opt);
//			
//			//neu trang thai moi sinh ra da ton tai thi bo qua
//			if(find_State(newstate, Close_DFS) || find_State(newstate, Open_DFS))
//				continue;
//				
//			//neu chua ton tai thi them vao stack
//			Node* newNode = (Node*)malloc(sizeof(Node));
//			newNode->state = newstate;
//			newNode->Parent = node;
//			newNode->no_function = opt;
//			pushStack(newNode, &Open_DFS);
//		}
//	}
//	return NULL;
//}
//
////in kq Trang thai
//void print_WaysToGetGoal(Node* node){
//	Stack stackPrint;
//	makeNullStack(&stackPrint);
//	
//	//duyet nguoc ve nut cha
//	while(node->Parent != NULL){
//		pushStack(node, &stackPrint);
//		node = node->Parent; 
//	}
//	pushStack(node, &stackPrint);
//	
//	//in ra thu ttu hanh dong
//	int no_action = 0;
//	while(!emptyStack(stackPrint)){
//		printf("\nAction %d: %s", no_action, action[top(stackPrint)->no_function]);
//		print_State(top(stackPrint)->state);
//		pop(&stackPrint);
//		no_action++;
//	}
//}	
////-----------------------------*$%$*-----------------------------
//
////-----------------------------Duyet Chieu Rong-----------------------------
////khai bao queue
//typedef struct{
//	Node* Elements[maxlength];
//	int front, rear;
//}Queue;
//
////khoi tao rong
//void makeNullQueue(Queue *queue){
//	queue->front = -1;
//	queue->rear = -1;
//}
//
////kt rong
//int emptyQueue(Queue queue){
//	return queue.front == -1;
//}
//
////kt day
//int full_Queue(Queue queue){
//	return ((queue.rear - queue.front + 1) % maxlength) == 0;
//}
//
////tra ve ptu dau hang doi
//Node* get_Front(Queue queue){
//	if(emptyQueue(queue))
//		printf("Error get");
//	else return queue.Elements[queue.front];
//}
//
////xoa ptu khoi hang doi
//void del_Queue(Queue *queue){
//	if(!emptyQueue(*queue)){
//		if(queue->front == queue->rear)
//			makeNullQueue(queue);
//		else queue->front = (queue->front + 1) % maxlength;
//	}
//	else printf("Error! del");
//}
//
////them ptu vao queue
//void pushQueue(Node* x, Queue *queue){
//	if(!full_Queue(*queue)){
//		if(emptyQueue(*queue))
//			queue->front = 0;
//		queue->rear = (queue->rear + 1) % maxlength;
//		queue->Elements[queue->rear] = x;
//	}
//	else printf("Error push");
//}
//
////tim trang thai trong queue Open&Close
//int find_State1(State state, Queue openQueue){
//	while(!emptyQueue(openQueue)){
//		if(compareStates(get_Front(openQueue)->state, state))
//			return 1;
//		del_Queue(&openQueue);
//	}
//	return 0;
//}
//
////thuat toan duyet chieu rong
//Node* BFS_Algorithm(State state){
//	//khai bao 2 hang doi open&close
//	Queue Open_BFS;
//	Queue Close_BFS;
//	makeNullQueue(&Open_BFS);
//	makeNullQueue(&Close_BFS);
//	
//	//tao trang thai nut cha
//	Node* root = (Node*)malloc(sizeof(Node));
//	root->state = state;
//	root->Parent = NULL;
//	root->no_function = 0;
//	
//	//them nut goc vao open
//	pushQueue(root, &Open_BFS);
//	
//	while (!emptyQueue(Open_BFS)){
//		//lay 1 dinh trong hang doi
//		Node* node = get_Front(Open_BFS);
//		del_Queue(&Open_BFS);
//		pushQueue(node, &Close_BFS);
//		
//		//kt TT dinh
//		if(goalCheck(node->state))
//			return node;
//
//	
//		int opt;
//		for(opt=1; opt<=4; opt++){
//			State newState;
//			makeNullState(&newState);
//			call_operator(node->state, &newState, opt);
//			
//			//neu TT moi da toon tai thi bo qua
//			if(find_State1(newState, Close_BFS) || find_State1(newState, Open_BFS))
//				continue;
//				
//			//neu chua ton tai them vao hang doi
//			Node* newNode = (Node*)malloc(sizeof(Node));
//			newNode->state = newState;
//			newNode->Parent = node;
//			newNode->no_function = opt;
//			pushQueue(newNode, &Open_BFS);
//		}	
//	}
//	return NULL;
//}
//
////in kq duyet
//void print_WaysToGetGoal1(Node* node){
//	Queue queuePrint;
//	makeNullQueue(&queuePrint);
//	
//	//tao nut trang thai cha
//	while(node->Parent != NULL){
//		pushQueue(node, &queuePrint);
//		node = node->Parent;
//	}
//	pushQueue(node, &queuePrint);
//
//
////	=========================================//
//	
//	Stack S;
//	makeNullStack(&S);
//	//chuyen ptu Q -> S;
//	while(!emptyQueue(queuePrint)){
//		node = get_Front(queuePrint);
//		del_Queue(&queuePrint);
//		pushStack(node, &S);
//	}
//	
//	//chuyen ptu S -> Q
//	while(!emptyStack(S)){
//		node = top(S);
//		pop(&S);
//		pushQueue(node, &queuePrint);
//	}
//
////	========================================//
//
//	//in thu tu hanh dong
//	int no_action = 0;
//	while(!emptyQueue(queuePrint)){
//		printf("\nAction %d: %s", no_action, action[get_Front(queuePrint)->no_function]);
//		print_State(get_Front(queuePrint)->state);
//		del_Queue(&queuePrint);
//		no_action++;
//	}
//}
////-----------------------------*$%$*-----------------------------
//int main(){
//	State cur_state = {1, 0, 1, 0, 1, 0};
//	//bt1
//	printf("\t-----DUYET CHIEU SAU-----");
//	Node* p = DFS_Algorithm(cur_state);
//	print_WaysToGetGoal(p);
//	
////	printf("\n\n=============================================\n");
//	printf("\n\t-----DUYET CHIEU RONG-----");
//	Node* C = BFS_Algorithm(cur_state);
//	print_WaysToGetGoal1(C);
//	return 0;
//}
//
//

