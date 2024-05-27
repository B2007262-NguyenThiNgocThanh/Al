//=======THANH_B2007262=====\\ 

#include <stdio.h> 

#define tankcapacity_X 9 //suc chua cua binh X la 9 lit
#define tankcapacity_Y 4 //suc chua cua binh Y la 4 lit
#define empty 0 //trang thai rong 
#define goal 6 //trang thai dich la 6 lit
#define Maxlength 100 //Stack 

const char* action[] = {"First State","pour Water Full X","pour Water Full Y","pour Water Empty X",
"pour Water Empty Y","pour Water X to Y","pour Water Y to X"}; 

//Cau truc trang thai
typedef struct{
	int x,y; // luong nuoc trong binh x,y 
}State; 

//khoi tao trang thai start cua 2 bình x = y = 0 
void makenullState(State *state){
	state->x = 0;
	state->y = 0; 
} 

//in cac trang thai
void printState(State state){
	printf("\n X:%d --- Y:%d",state.x,state.y); 
} 

//kiem tra trang thai dich
int goalcheck(State state){
	return (state.x == goal || state.y == goal); 
} 

// cur_state: TT h.tai, result: kq
//lam day binh X
int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X){ // trang thai h.tai < suc chua 
		result->x = tankcapacity_X;
		result->y = cur_state.y;
		return 1; 
	} 
	return 0; 
} 
//lam day binh Y
int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y < tankcapacity_Y){
		result->x = cur_state.x;
		result->y = tankcapacity_Y;
		return 1; 
	} 
	return 0; 
} 
//lam rong binh X
int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x > 0){
		result->x = empty;
		result->y = cur_state.y;
		return 1; 
	} 
	return 0; 
} 
//lam rong binh Y
int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y > 0){
		result->x = cur_state.x;
		result->y = empty;
		return 1; 
	} 
	return 0; 
} 
int max(int a, int b){
	return (a>b)? a:b; 
} 
int min(int a, int b){
	return a<b ? a:b; 
} 

//chuyen nuoc tu X-> Y 
int pourWaterXY(State cur_state, State *result){
	if(cur_state.x > 0 && cur_state.y < tankcapacity_Y){
		result->x = max(cur_state.x-(tankcapacity_Y - cur_state.y),empty);
		result->y = min(cur_state.y + cur_state.x, tankcapacity_Y); 
		return 1; 
	} 
	return 0; 
} 

//chuyen nuoc tu Y->X
int pourWaterYX(State cur_state, State *result){
	if(cur_state.y > 0 && cur_state.x < tankcapacity_X){
		result->x = min(cur_state.x + cur_state.y, tankcapacity_X);
		result->y = max(cur_state.y - (tankcapacity_X - cur_state.x),empty);
		return 1; 
	} 
	return 0; 
} 

//goi cac phep toan tren trang thai
int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourWaterFullX(cur_state, result);
		case 2: return pourWaterFullY(cur_state, result);
		case 3: return pourWaterEmptyX(cur_state, result);
		case 4: return pourWaterEmptyY(cur_state, result);
		case 5: return pourWaterXY(cur_state, result);
		case 6: return pourWaterYX(cur_state, result); 
		default: printf("Loi goi trang thai !");
			return 0; 
	} 
} 

int main(){
	State cur_state = {5,4}, result;
	printf("Trang thai bat dau");
	printState(cur_state);
	int opt;
	for(opt=1; opt<=6; opt++){
		int thuchien = call_operator(cur_state,&result,opt);
		if(thuchien == 1){ //thuc hien hanh dong thanh cong
			printf("\nHanh dong %s thanh cong", action[opt]);
			printState(result);			
		} 
		else printf("\nHanh dong %s KHONG thanh cong",action[opt]); 
	} 
	return 0; 
} 
