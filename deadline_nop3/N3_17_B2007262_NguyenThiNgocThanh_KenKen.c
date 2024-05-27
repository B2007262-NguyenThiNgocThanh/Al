#include <stdio.h>
#include <stdlib.h>

#define R 4
#define C 4
#define area 4 
#define empty 0
#define oo 9999999
#define maxvalue 5
#define maxlength 500

//diem 
typedef struct{
	int x,y; 
}Point;
//
typedef struct{
	Point A[maxvalue];
	int n; 
}Listpoint;

typedef struct{
	int value; //gia tri o chuong 
	char oper; //phep toan
	Listpoint L[5]; 
}Box;

typedef struct{
	int data[R*C][R*C];
	int n; 
}Cons;
 
void initLp(Listpoint *list){
	list->n = 0; 
} 

void appendLp(Listpoint *l, Point p){
	l->A[l->n++] = p; 
} 

void initC(Cons* c){
	int i,j;
	for(i=0;i<R*C,i++)
		for(j=0;j<R*C;j++)
			c->data[i][j]=empty; 
		
	c->n = R*C; 
} 

int idxOf(Point p){
	return (R*p.x + p.y); 
} 

Point posOf(int v){
	Point p;
	p.x = v / R;
	p.y = v % C;
	return p; 
} 
//them RB 
int addC(Cons* c, Point src, Point target){
	int u = idxOf(src) ;
	int v = idxOf(target);
	
	if(c->data[u][v] == 0){
		c->data[u][v] = 1;
		c->data[v][u] = 1;
		return 1; 
	} 
	return 0; 
} 

//tap RB 1 vertex
Listcoord getC(Cons c, Point p){
 	int v = idxOf(p);
	Listpoint result;
	initLp(&result);
	
	for(i=0; i<c.n; i++)
		if(c.data[v][i] == 1) 
			appendLp(&result, posOf(i));
	return result; 
} 


 




 
