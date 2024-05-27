#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#include <vector>
#include <algorithm> 
#define rows 3 //so hang 
#define cols 3 //so cot 
#define emptys 0 //tt o trong 
#define max_op 4 // so hanh dong max = 4
#define Maxlength 500


using namespace std; 
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
		result->eightPuzzle[emptyR_cur-1][emptyC_cur] =  emptys;
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
		result->eightPuzzle[emptyR_cur+1][emptyC_cur] = emptys; 
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
		result->eightPuzzle[emptyR_cur][emptyC_cur - 1] = emptys;
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
		result->eightPuzzle[emptyR_cur][emptyC_cur+1] = emptys;
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
			if(state.eightPuzzle[row][col] != emptys){ 
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

// tim tt co thuoc open or closed  
// luu vi tri tim duoc vao bien pos
Node* findState(State state, vector<Node*> v, vector<Node*>::iterator *pos){
	vector<Node*>::iterator it = v.begin();  //khoi tao
	if(v.size()==0)
		return NULL; 
	while(it != v.end()) {
		if(compareStates((*it)->state, state)){
			*pos = it;
			return *it; 
		} 
		it = v.erase(it); 
	}
	return NULL; 
}

//tieu chi sx 1 vector
bool compareHeuristic(Node* a, Node* b){
	return a->heuristic > b->heuristic; 
} 

//==========================================================//
//thuat toan tim kiem tot nhat dau tien
//f = h 
Node* best_FS(State state, State goal){
	vector<Node*> open(Maxlength);
	open.clear(); 
	vector<Node*> closed(Maxlength);
	closed.clear(); 
	//khoi tao tt nut cha 
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_funct = 0;
	root->heuristic = heuristic1(root->state, goal);
	open.push_back(root);
	
	while(!open.empty()){
		Node* node = open.back();
		open.pop_back(); //xoa phan tu dau tien trong ds pen 
		closed.push_back(node); //them vao closed 
		//kt tt dich 
		if(goalcheck(node->state, goal)){
			//cout<<"Goal\n"; 
			return node;
		}
			
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
				vector<Node*>::iterator pos_open, pos_closed;
				Node* nodeFoundopen = findState(newstate, open, &pos_open);
				Node* nodeFoundclosed = findState(newstate, closed, &pos_closed);
				if(nodeFoundopen == NULL && nodeFoundclosed == NULL){
					open.push_back(newnode);
				} 
				else if(nodeFoundopen!=NULL && nodeFoundopen->heuristic > newnode->heuristic){
					open.erase(pos_open);
					open.push_back(newnode); 
				} 
				else if(nodeFoundclosed!=NULL && nodeFoundclosed->heuristic > newnode->heuristic){
					open.erase(pos_closed);
					open.push_back(newnode); 
				} 
				sort(open.begin(),open.end(),compareHeuristic); 
			}
		} 
	} 
	return NULL; 
} 
 
//==========================================================//
//ham in kq cua thuat toan bestFS
void print_WaysToGetGoal(Node* node){
	vector<Node*> vectorPrint;
	
	//duyet nguoc ve parent
	while(node->parent != NULL){
		vectorPrint.push_back(node);//them vao sau ds 
		node = node->parent; 
	} 
	vectorPrint.push_back(node);
	int no_action = 0, i;
	for(i=vectorPrint.size()-1; i>=0; i--){
		printf("\nAction %d: %s", no_action, action[vectorPrint.at(i)->no_funct]);
		printState(vectorPrint.at(i)->state);
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

