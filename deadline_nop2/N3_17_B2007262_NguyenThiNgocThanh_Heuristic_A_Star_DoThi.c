//============Thanh===========//

#include <stdio.h>
#include <stdlib.h>
#define max_v 5 //so dinh toi da 
#define Maxlength 500 //ds 

//ten cac dinh 
const char name[]={'A','B','C','D','G'};

//cau truc dinh cua do thi 
typedef struct{
	int nei[max_v]; //luu gia tri heuristic & dinh ke 
	int h; //tu hien tai den goal 
}Vertices; 

//dothi 
typedef struct{
	int no_ver; //so luong dinh
	Vertices v[max_v]; //gia tri moi dinh 
}Graph; 
//khoi tao do thi 
void initGraph(int num_ver, Graph *G){
	G->no_ver = num_ver;
	
	int i,j;
	for(i=0 ; i < G->no_ver ; i++) 
		for(j=0 ; j < G->no_ver ; j++){ 
			G->v[i].nei[j] = 0;
			G->v[i].h = 0; 
		} 
} 

//cau truc tt luu dinh htai cua moi tt 
typedef struct{
	int vertex; 
}State; 

//in tt
void printState(State state){
	printf(" %c ", name[state.vertex]); //in ten tt dinh 
} 
//kt tt muc tieu 
int goalcheck(State state, State goal){
	return compareStates(state, goal);  
}
//====================================================//
//cau truc 1 nut 
typedef struct Node{
	State state;
	struct Node* parent;
	int f,g,h;
}Node;
//--------------------------List--------------------------//
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
//them phan tu  
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
//xoa phan tu 
void deleteL(int pos, List *L){
	if(emptyList(*L))
		printf("List is empty !");
	else if(pos < 1 || pos > L->size)
		printf("Position is not possible to Delete !");
	else{
		int i;
		for(i = pos-1; i<L->size; i++)
			L->ele[i] = L->ele[i+1];
		L->size--;
	}
}
//====================================================//

//so sanh 2 tt 
int compareStates(State state1, State state2){
	return state1.vertex == state2.vertex; 
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

//sap xep 
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
//A_star_Graph 
Node* Astar(Graph G, State state, State goal){
	List open;
	List closed;
	makenullList(&open);
	makenullList(&closed);
	//tt  nut cha 
	Node* root=(Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->g = 0; //dinh dau tien g = 0 
	root->h = G.v[state.vertex].h; //lay h cua dinh vertex 
	root->f = root->g + root->h; // f = g+h 
	
	push(root, open.size+1, &open);
	
	while(!emptyList(open)){
		
		Node* node = ele_at(1, open);
		deleteL(1, &open);
		push(node, closed.size+1, &closed);
		//kt tt muc tieu 
		if(goalcheck(node->state, goal))
			return node;
		
		int opt; 
		for(opt = 0; opt < G.no_ver ; opt++){ //duyet qua tung dinh 
			State newstate ;
			
			if(G.v[node->state.vertex].nei[opt] > 0){ // ">0" la co duong di 
				
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state.vertex = opt;
				newNode->parent = node;
				newNode->g = node->g + G.v[node->state.vertex].nei[opt]; // lay g tu dinh state.vertex -> opt 
				newNode->h = G.v[opt].h; // lay gia tri h cua dinh state.vertex 
				newNode->f = newNode->g + newNode->h;
				
				//kt tt moi co thuoc open/closed 
				int pos_open, pos_closed;
				Node* nodeFoundopen = findState(newNode->state, open, &pos_open);
				Node* nodeFoundclosed = findState(newNode->state, closed, &pos_closed);
				
				if(nodeFoundopen == NULL && nodeFoundclosed == NULL)
					push(newNode, open.size+1, &open);
				else if(nodeFoundopen != NULL && nodeFoundopen->g > newNode->g){
					deleteL(pos_open, &open);
					push(newNode, pos_open, &open);
				}
				else if(nodeFoundclosed != NULL && nodeFoundclosed->g > newNode->g){
					deleteL(pos_closed, &closed);
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
	
	//in thu tu hanh di chuyen
	int no_action = 0, i;
	for(i=listPrint.size ; i>0 ; i--){
		
		printState(ele_at(i, listPrint)->state);
		if(i != 1){
			printf("->"); 
		}
		no_action++; 
	}
} 

int main(){
	int i, j;
	Graph Graph;
	freopen("test.txt","r",stdin);
	initGraph(max_v, &Graph); 
	
	for(i = 0 ; i < max_v ; i++){
		int x;
		scanf("%d", &x);
		Graph.v[i].h = x; 
		for(j = 0; j < max_v ; j++){
			scanf("%d", &x);
			Graph.v[i].nei[j] = x; 
		} 
	} 
	
	State A, G;
	A.vertex = 0;
	G.vertex = 4;
	Node* result = Astar(Graph, A, G);
	print_WaysToGetGoal(result); 
	return 0;
}







