
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
 
#define TRUE 1
#define FALSE 0
 
int Cot[8],CheoTru[15],CheoCong[15];
int Queen[8];
int SoLoiGiai = 0;
 
/* Ham khoi tao tat ca cac cot, duong cheo xuoi, duong cheo nguoc deu co the dat hoang hau */
void KhoiTao()
{
    int i;
   for(i = 0; i <8; i++)
      Cot[i] = TRUE;
   for(i = 0; i <15; i++)
   {
      CheoTru[i] = TRUE;
      CheoCong[i] = TRUE;
   }
}
 
/* Ham kiem tra xem tai vi tri (i,j)  co the dat quan hau duoc khong*/
int KiemTra(int i,int j)
{
    if(Cot[j] && CheoTru[i-j+7] && CheoCong[i+j])return 1;
    else return 0;
}
 
/* Ham cai dat cot, duong cheo xuoi, duong cheo nguoc tai vi tri Dat quan hau */
void DatHau(int i,int j)
{
    Queen[i]=j;
    Cot[j]=FALSE;
    CheoTru[i-j+7]=FALSE;
    CheoCong[i+j]=FALSE;
}
 
/* Ham cai dat cot, duong cheo xuoi, duong cheo nguoc tai vi tri Rut quan hau */
void RutHau(int i,int j)
{
    Cot[j]=TRUE;
    CheoTru[i-j+7]=TRUE;
    CheoCong[i+j]=TRUE;
}
 
void DoHoa()
{
   
    cleardevice();
    setgraphmode(getgraphmode());
    int l=175,t=135,r=205,b=165,g,x=180,y=140,i,j;
    setbkcolor(0);
    setcolor(WHITE);
    settextstyle(0,0,1);
    outtextxy(185,120,"0   1   2   3  4   5   6   7");
    outtextxy(160,145,"0");
    outtextxy(160,175,"1");
    outtextxy(160,205,"2");
    outtextxy(160,235,"3");
    outtextxy(160,265,"4");
    outtextxy(160,295,"5");
    outtextxy(160,325,"6");
    outtextxy(160,355,"7");
    outtextxy(400,90,"Loi giai:");
    outtextxy(140,430,"Nhan <ESC> de thoat, phim bat ki de tiep tuc...");
    settextstyle(0,0,1);
    outtextxy(160,60,"CHUONG TRINH MINH HOA BAI TOAN 8 HAU");
    setfillstyle(1,0);
    rectangle(l,t,r,b);
    bar3d(l,t+30,r,b+30,0,0);
    bar3d(l,t+60,r,b+60,0,0);
    bar3d(l,t+90,r,b+90,0,0);
    bar3d(l,t+120,r,b+120,0,0);
    bar3d(l,t+150,r,b+150,0,0);
    bar3d(l,t+180,r,b+180,0,0);
    bar3d(l,t+210,r,b+210,0,0);
    bar3d(l+30,t,r+30,b,0,0);
    bar3d(l+30,t+30,r+30,b+30,0,0);
    bar3d(l+30,t+60,r+30,b+60,0,0);
    bar3d(l+30,t+90,r+30,b+90,0,0);
    bar3d(l+30,t+120,r+30,b+120,0,0);
    bar3d(l+30,t+150,r+30,b+150,0,0);
    bar3d(l+30,t+180,r+30,b+180,0,0);
    bar3d(l+30,t+210,r+30,b+210,0,0);
    bar3d(l+60,t,r+60,b,0,0);
    bar3d(l+60,t+30,r+60,b+30,0,0);
    bar3d(l+60,t+60,r+60,b+60,0,0);
    bar3d(l+60,t+90,r+60,b+90,0,0);
    bar3d(l+60,t+120,r+60,b+120,0,0);
    bar3d(l+60,t+150,r+60,b+150,0,0);
    bar3d(l+60,t+180,r+60,b+180,0,0);
    bar3d(l+60,t+210,r+60,b+210,0,0);
    bar3d(l+90,t,r+90,b,0,0);
    bar3d(l+90,t+30,r+90,b+30,0,0);
    bar3d(l+90,t+60,r+90,b+60,0,0);
    bar3d(l+90,t+90,r+90,b+90,0,0);
    bar3d(l+90,t+120,r+90,b+120,0,0);
    bar3d(l+90,t+150,r+90,b+150,0,0);
    bar3d(l+90,t+180,r+90,b+180,0,0);
    bar3d(l+90,t+210,r+90,b+210,0,0);
    bar3d(l+120,t,r+120,b,0,0);
    bar3d(l+120,t+30,r+120,b+30,0,0);
    bar3d(l+120,t+60,r+120,b+60,0,0);
    bar3d(l+120,t+90,r+120,b+90,0,0);
    bar3d(l+120,t+120,r+120,b+120,0,0);
    bar3d(l+120,t+150,r+120,b+150,0,0);
    bar3d(l+120,t+180,r+120,b+180,0,0);
    bar3d(l+120,t+210,r+120,b+210,0,0);
    bar3d(l+150,t,r+150,b,0,0);
    bar3d(l+150,t+30,r+150,b+30,0,0);
    bar3d(l+150,t+60,r+150,b+60,0,0);
    bar3d(l+150,t+90,r+150,b+90,0,0);
    bar3d(l+150,t+120,r+150,b+120,0,0);
    bar3d(l+150,t+150,r+150,b+150,0,0);
    bar3d(l+150,t+180,r+150,b+180,0,0);
    bar3d(l+150,t+210,r+150,b+210,0,0);
    bar3d(l+180,t,r+180,b,0,0);
    bar3d(l+180,t+30,r+180,b+30,0,0);
    bar3d(l+180,t+60,r+180,b+60,0,0);
    bar3d(l+180,t+90,r+180,b+90,0,0);
    bar3d(l+180,t+120,r+180,b+120,0,0);
    bar3d(l+180,t+150,r+180,b+150,0,0);
    bar3d(l+180,t+180,r+180,b+180,0,0);
    bar3d(l+180,t+210,r+180,b+210,0,0);
    bar3d(l+210,t,r+210,b,0,0);
    bar3d(l+210,t+30,r+210,b+30,0,0);
    bar3d(l+210,t+60,r+210,b+60,0,0);
    bar3d(l+210,t+90,r+210,b+90,0,0);
    bar3d(l+210,t+120,r+210,b+120,0,0);
    bar3d(l+210,t+150,r+210,b+150,0,0);
    bar3d(l+210,t+180,r+210,b+180,0,0);
    bar3d(l+210,t+210,r+210,b+210,0,0);
    setfillstyle(1,1);
    for(i=0;i<8;i++)
    {
        if(i%2==0)
        {
        j=0;
        while(j<7){
        setfillstyle(1,1);
        floodfill(x+30*j,y+30*i,15);j+=2;}
        }
        else{
        j=1;while(j<8){
        floodfill(x+30*j,y+30*i,15);j+=2;}
        }
    }
        setfillstyle(1,15);
        for(i=0;i<8;i++)
    {
        if(i%2==0)
        {j=1;
        while(j<8){
        floodfill(x+30*j,y+30*i,15);j+=2;}
        }
        else{
        j=0;while(j<8){
        floodfill(x+30*j,y+30*i,15);j+=2;}
        }
    }
}
/* Ham xuat ra man hinh */
void Xuat(int *Queen)
{
   int i, j;
   char c,s[10];
   setcolor(4);
 
   for(i = 0; i <8; i++)
   {
      outtextxy(187+30*Queen[i],147+30*i,"Q");
   }
   itoa(++SoLoiGiai,s,10);
   setcolor(15);
   outtextxy(475,90,s);
   c = getche();
   if(c == 27)exit(1);
}
/* Ham dat hau*/
void Queens()
{
int i,j,t,k[8];
for(j=0;j<8;j++)
{
    KhoiTao();
    DatHau(0,j);
    for(i=1;i<8;i++)k[i]=0;//Mang k[i] dung de luu giu gia tri cot ma quan hau da duyet toi o hang i
    i=1;
    while(i<8)
    {
        while(k[i]<8)
        {
            t=k[i];
            if(KiemTra(i,t)){DatHau(i,t);break;}
            else k[i]++;
        }
        if(k[i]==8)//Neu gia tri cot tai hang i bang 8,tuc la tai hang i ko  the dat quan hau.
        {
            k[i]=0;
            i--;
            if(i==0)break;
            else {t=k[i];RutHau(i,t);k[i]++;}
        }
        else i++;
        if(i==8)
        {
            DoHoa();
            Xuat(Queen);
            i--;
            t=k[i];
            RutHau(i,t);k[i]++;
        }
    }
 
}
}
void main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"C:\\Tc\\BGI");
    Queens();
}