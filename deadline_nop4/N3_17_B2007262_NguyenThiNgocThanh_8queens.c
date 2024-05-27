//===============THANH-B2007262===============// 
#include <stdio.h>
#include <math.h> 

int n, R[50],cnt=0; 

//kiem tra 
int check(int pos){ 
	int i;
	for(i=1; i<pos;i++) 
	//neu cung cot or duong cheo 
		if((R[i] == R[pos])||(abs(R[i]-R[pos])==abs(i-pos)))
			return 0; //false 
	return 1; //true 
} 

//in ma tran ban co 
void print(){
	int i,f; 
	cnt++; //dem so giai phap 
	printf("\nGiai phap thu %d\n\n", cnt);
	//in bang ma tran 
	printf("---------------------------------\n");
	for(i=1;i<=n;i++){
		for(f=1;f<=n;f++)
			if(f==R[i]) //neu quan hau thu i duoc dat o cot f roi thi in ra 
				printf("| Q ");
			else 
				printf("|   "); 
		
		printf("|\n---------------------------------\n");
	} 
	//(x1, x2, x3, x4, x5, x6, x7, x8) 
	printf("\n(");
	for(i=1;i<n;i++)
		printf("%d, ",R[i]); //in vi tri queen tren tung hang , tu tren xuong 
	printf("%d)\n",R[n]); //in vi tri hang cuoi cung 
	//================================
	//cai nay lam choi cho dui thoi a :> 
	Sleep(10); //lap lai sau 1000s 
	system("CLS"); //xoa man hinh  
	printf("\n");
	//=================================
} 

//giai phap 
void QueenBackTracking(){
	int k=1;
	R[k] = 0; 
	while(k!=0){
		do{
			R[k]++;  
		} while((R[k] <= n) && !check(k)); 
		
		if(R[k] <= n){ //tao khung ban co n=8 
			if(k==n) 
				print(n); //in ma tran ban co 
			else{ //k<n 
				k++; //tang len 
				R[k] = 0; //tra ve luc dau r lam lai 
			} 
		} 
		else //R[k] > n=8 
			k--; //giam xuong 
	} 
} 

int main(){
	printf("============[ EIGHT - QUEEN ]============\n\n");
	printf("Nhap kich thuoc ban co: ");  
	scanf("%d", &n); 
	QueenBackTracking();
	return 0; 
} 
