//=======================THANH============================// 

#include <stdio.h>
#include <stdlib.h> 
#define R 9 //so hang
#define C 9  //so cot
#define maxvalue 10 //gia tri lon nhat co the cua cell
#define empty 0 //tt rong
#define oo 999999 
#define area 3 //kich thuoc khoi
#define maxlength 1000

//===========================STRUCT======================// 

//toa do - (x,y) 
typedef struct{
	int x,y; // co gia tri tu 0-8 
}Coord; 

//danh sach toa do
typedef struct{
	Coord data[maxlength]; //mang 1 c luu giu cac phan tu toa do 
	int length; //chieu dai danh sach 
}Listcoord; 

//rang buoc
typedef struct{
	int data[R*C][R*C]; //matrix 
	int  n; 
}Constrains;  

//sudoku
typedef struct{
	int cell[R][C];
	Constrains cons;
}Sudoku;

typedef struct{
	int data1[maxlength];
	int size;
}List;
//--------------------------------

void initList(List *L){
	L->size = 0;
}

void appendList(List *L, int i){
	L->data1[L->size++]  = i;
}
//khoi tao danh sach toa do
void initLc(Listcoord *L){
	L->length = 0; 
} 

//them toa do vao ds toa do
void appendLc(Listcoord *L, Coord c){
	L->data[L->length++] = c; 
} 

//khoi tao RB - dinh chua co RB 
void initC(Constrains *cons){
	int i, j;

	for(i=0; i<R*C; i++)
		for(j=0; j<R*C ; j++)
			 cons->data[i][j] = 0;
			 
	cons->n = R*C; 
} 

//chuyen toa do (x,y) ve toa do dinh
int idxOf(Coord co){
	return (R*co.x + co.y); 
} 

//chuyen toa do dinh ve toa do (x,y)
Coord posOf(int v) {
	Coord coo;
	coo.x = v/R; 
	coo.y = v%C;
	
	return coo; 
}

//them RB
int addC(Constrains* cons, Coord src, Coord target){

	int u = idxOf(src);
	int v = idxOf(target);
	
	if(cons->data[u][v] == 0){ //chua co rb thi tao rb  
		cons->data[u][v] = 1;
		cons->data[v][u] = 1;
		return 1;
	}
	return 0;
}

//tap rang buoc cua 1 dinh - danh sach cac dinh rang buoc
Listcoord getC(Constrains cons, Coord coo){
	
	int v = idxOf(coo);
	Listcoord result; //ds ket qua
	initLc(&result); //khoi tao ds ket qua
	int i;
	for(i = 0 ; i < cons.n ; i++) 
	
		if(cons.data[v][i] == 1) //neu i co rang buoc voi v thi them vao ds result
			
			appendLc(&result, posOf(i)); //them toa do (x,y) vao ds 
			
	return result;
}

//-----------------------------------------------------//
//khoi tao bang 
void initSu(Sudoku* s){
	int i,j;
	for(i=0; i<R; i++)
		for(j=0; j<C; j++)
			s->cell[i][j] = empty; //cac o trong
	//them RB rong cho o
	initC(&s->cons);		
}

//khoi tao bang sudoku co value
void initSV(Sudoku* s, int input[R][C]){
	int i,j;
	for(i=0; i<R; i++)
		for(j=0; j<C; j++)
			s->cell[i][j] = input[i][j]; //them gia tri vao o 
			
	initC(&s->cons);
}

//in bang sudoku
void Print(Sudoku s){
	int i ,j;
	printf("----------SUDOKU---------\n");
	
	for(i=0; i<R ; i++){
		if(i % area == 0)
			printf("-------------------------\n");
		for(j=0; j<C ; j++){
			if(j % area == 0)
				printf("| ");
			printf("%d ", s.cell[i][j]); //in value cell
		}
		printf("|\n");		
	}
	
	printf("-------------------------\n");
}

//kt tt goal - cac o da dien het hay chua
int goalcheck(Sudoku s){
	int i,j;
	for(i=0; i<R; i++)
		for(j=0; j<C; j++)
			if(s.cell[i][j] == empty)
				return 0;
				
	return 1;
}

//tao RB tu pos cho truoc
void spread(Coord pos, Constrains* cons, Listcoord *changed){
	int r = pos.x, c = pos.y;
	
	int i,j;
	//tao constrains theo cols - chay theo rows de quet het 1 cot
	for(i=0 ; i<R ; i++){
		if( i != r ){ //toa do hien tai cua x
			Coord pos_r = {i, c}; //toa do (dong i, cot c)
			if(addC(cons, pos, pos_r))
				appendLc(changed, pos_r);
		}
	}
	
	//tao rang buoc theo hang - chay theo cot de quet het cac hang
	for(i=0; i<C; i++){
		if(i != c){
			Coord pos_c = {r, i};
			if(addC(cons, pos, pos_c))
				appendLc(changed, pos_c);
		}
	}
		
	//truyen RB theo khoi
	for(i=0; i<area; i++){
		for(j=0; j<area; j++){
			int areaX = (r/area) * area; //0-1-2
			int areaY = (c/area) * area; //0-1-2
			if(areaX + i != r || areaY + j != c){
				Coord pos_f = {areaX + i, areaY + j};
				if(addC(cons, pos, pos_f))
					appendLc(changed, pos_f);
			}
		}
	}
} 

//tim domain cua empty cell  (***)
List getAV(Coord pos, Sudoku s){
	Listcoord posL = getC(s.cons, pos);
	int avai[maxvalue]; // array: 0-9, just use 1-9
	int i;
	for(i=1; i<maxvalue ; i++)
		avai[i] = 1; //nam trong domain value tu 1-9

	for(i=0; i<posL.length; i++){
		Coord position = posL.data[i];
		if(s.cell[position.x][position.y] != empty) //dang mang gia tri
			avai[s.cell[position.x][position.y]] = 0;
	}
	
	//ds ket qua ***
	List result; 
	initList(&result);
	for(i=1; i<maxvalue; i++)
		if(avai[i])
			appendList(&result, i);
	return result;	
}
//xac dinh o nao uu tien duoc dien truoc 
//==uu tien o nao co mien gia tri it nhat===//
Coord getDocell(Sudoku s){
	int min = oo;
	int i,j;
	
	Coord result; //toa do ket qua
	for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			if(s.cell[i][j] == empty){ //neu o chua duoc dien gia tri
				Coord pos = {i, j};
				int avai_length = getAV(pos, s).size;
				if(avai_length < min){
					min = avai_length;
					result = pos;
				}
			}
		}
	}
	return result;
}


int excnt = 0; //dem 
int suBTracking(Sudoku* s){
	if(goalcheck(*s)) //kt tt muc tieu
		return 1;
		
	Coord pos = getDocell(*s);
	List avai = getAV(pos,*s);
	if(avai.size == 0)//neu mien gia tri rong nhung chua duoc dien
		return 0;
		
	int j;
	for(j = 0; j < avai.size ; j++){
		
		int val = avai.data1[j]; //gia tri tai o j
		s->cell[pos.x][pos.y] = val; //them gi tri vao o
		excnt++;
		
		if(suBTracking(s)) //kt lang truyen rb
			return 1;
		else s->cell[pos.x][pos.y] = empty; //nguoc lai 
	}	
	return 0;
}

//lan truyen RB
Sudoku solve(Sudoku s){
	int i,j;

	for(i=0; i<R; i++){
		for(j=0; j<C; j++){	
			if(s.cell[i][j]==empty)	{
				Listcoord history;
				initLc(&history);
				Coord pos = {i, j};
				spread(pos, &s.cons, &history); 
			}
			
		}
	}
	
	excnt = 0;
	if(suBTracking(&s))
		printf("Solve\n");
	else 
		printf("Can not solve ! \n");
		
	printf("Explore %d state\n", excnt);
	return s; 
}


//du lieu dau vao
int inputs[9][9] = {
	{5, 3, 0, 0, 7, 0, 0, 0, 0},
	{6, 0, 0, 1, 9, 5, 0, 0, 0},
	{0, 9, 8, 0, 0, 0, 0, 6, 0},
	{8, 0, 0, 0, 6, 0, 0, 0, 3},
	{4, 0, 0, 8, 0, 3, 0, 0, 1},
	{7, 0, 0, 0, 2, 0, 0, 0, 6},
	{0, 6, 0, 0, 0, 0, 2, 8, 0},
	{0, 0, 0, 4, 1, 9, 0, 0, 5},
	{0, 0, 0, 0, 8, 0, 0, 7, 9},
};

int main(){
	Sudoku s;
	initSV(&s, inputs);
	Print(s);
	Sudoku result = solve(s);
	Print(result);
	return 0;
}
