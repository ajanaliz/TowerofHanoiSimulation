#include<iostream>
#include<conio.h>
#include<windows.h>
#include<MMSystem.h>

using namespace std;
int z=0;
int  disk [4][20];
int  disk_n [4];
//the elements of the arrays above are automatically assigned the value 0 because they're global varibales


HANDLE get ()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

int gotoxy ( int x , int y )
{
	COORD position = {x,y};
	SetConsoleCursorPosition( get() , position );
	return 0;
}

int set_color ( int color_code )
{
	return (int) SetConsoleTextAttribute ( get() , color_code );
	
}
 
void  move (int x,int y , int n)
{
}

void load(){
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);//to display the character slowly
    printf("%c",177);}
    getch();
}


void clean(int x,int y,int n,int color)
{

	set_color(color);
	for (int i=-n-1;i<n+1;i++)
	{
		gotoxy(x+i,y);
		cout<<"  ";
	}
		gotoxy(x-1,y);
	
		cout<<"  "<<n;
}

//dark red = 75,violet = 91,light blue = 59, light red = 203, yellow = 23
void draw(int x,int y,int n,int color)
{
	if( ( n % 5 ) == 0)
		set_color(75);
	else if( ( n % 5 ) == 1)
		set_color(91);
	else if( ( n % 5 ) == 2)
		set_color(59);
	else if( ( n % 5 ) == 3)
		set_color(235);
	else if( ( n % 5 ) == 4)
		set_color(203);
	else
		set_color(187);
	
//	set_color(color);
	for (int i=-n-1;i<n+1;i++)
	{
		gotoxy(x+i,y);
		cout<<"  ";
	}
		gotoxy(x-1,y);
	
		cout<<"  "<<n;
}

void draws(int x,int y,int n,int color)/*i used this function for drawing the disks*/
{
	set_color(color);
for (int i=-1;i<1;i++)
	{
		gotoxy(x+i,y);
		cout<<"  ";
	}
		gotoxy(x-1,y);
		cout<<"  ";
		
}

void draws1(int x,int y,int n,int color)/*i used this function for drawing the pires and the base of the toy*/
{
	set_color(color);
	
	for (int i=-19;i<19;i++)
	{
		gotoxy(x+i,y);
		cout<<"  ";
	}
		gotoxy(x-1,y);
		cout<<"  ";
} 

void drawdisks()
{
	
	for(int i=0;i<3;i++)
		for(int j=0;j<disk_n[i];j++ )
			draw( 20*(i+1) , 24-j , disk[i][j], 75);
	
}



void move ( int start, int dst)//start is the starting pire and dst is the ending pire wich can be anyone of 0,1 and 2
{
	int xp1 = 20 , xp2 = 40 , xp3 = 60, yp = 24;
	int x1 = 20 * (	start + 1);
	int x2 = 20 * (	dst + 1);
	int y1 = 24 - disk_n[start] + 1 ;
	int y2 = 24 - disk_n[dst] ;
	int x = x1 , y = y1;


	 /*the function calls below draws the base*/
	 draws1 ( xp1 ,25, disk[start][disk_n[start]], 282);
	 draws1 ( xp2 ,25, disk[start][disk_n[start]], 282);
	 draws1 ( xp3 ,25, disk[start][disk_n[start]], 282);
		


	 while( yp > 5 )
	 {
		 if( z == 19 )
			 break;
		/*the functions calls below draws the poles*/ 		
		draws ( xp1 ,yp, disk[start][disk_n[start]], 282);
		draws ( xp2 ,yp, disk[start][disk_n[start]], 282);
		draws ( xp3 ,yp, disk[start][disk_n[start]], 282);
		yp--;
		z++;
	 }
	 
	 drawdisks();
	// PlaySound(TEXT("beep.wav"), NULL, SND_SYNC);
	 while (y >= 3)
	 {
		 
		 clean( x , y , disk[start][disk_n[start]-1] , 0 );
		 y--;
		 draw( x , y , disk[start][disk_n[start]-1] , 75 );
		 yp = 24 - disk_n[start] + 1;
		 while( yp > 5 )
		 {
			if( yp ==  y + 1)
			/*the functions calls below draws the poles*/ 		
			draws ( x1 ,yp, disk[start][disk_n[start]], 282);
			else{}
			yp--;

		 }
		 Sleep(50);
	 }
	
	 while (x != x2)
	 {
		clean( x , y , disk[start][disk_n[start]-1] , 0 );
		if (x > x2)
				x -= 2;
		else
				x += 2;
		draw( x , y , disk[start][disk_n[start]-1] , 75 );
		
		Sleep(60);
	 }
	
	 while (y != y2)
	 {
		 
		 clean( x , y , disk[start][disk_n[start]-1] , 0 );
		 if (y > y2) 
				y-- ;
		 else 
				y++;
		 draw( x , y , disk[start][disk_n[start]-1] , 75 );
		 yp = 24 - disk_n[dst];
		 while( yp > 5 )
		 {
			if(yp  == y - 1)
			/*the functions calls below draws the poles*/ 		
			draws ( x2 ,yp, disk[start][disk_n[start]], 282);
			else{}
			yp--;
		 }
		
		 Sleep(30);
	 }
	/*every disk getting to its destination means we have to add 1 to the disks in the 
	dst array and take 1 from the starting point disks*/
	disk[dst][ disk_n[dst] ] = disk[start] [ disk_n[start]-1];
	disk_n[start]--;
	disk_n[dst]++;
//	 PlaySound(TEXT("cashtill.wav"), NULL, SND_SYNC);
	
	/*this is the delay between each cycle*/
}
int recursive(int n , int from , int to , int tmp)
{
	if(n==1)
		move(from,to);
	else 
	{
		recursive(n-1,from,tmp,to);
		recursive(1,from,to,tmp);
		recursive(n-1,tmp,to,from);
	}
	return 0;
}
int main ()
{
	
	int n,soundtracknum,answer;
		set_color(11);
	printf( "Enter the number of disks you want me to work with:\n" );
	printf( "please keep in mind that the console cant sopport a large number of disks\n" );
	printf( "just to be sure u obey this rule i'll keep u in a loop until u enter a valid and reasonable number :P\n" );
	scanf( "%d", &n );
	if ( n < 0 )
		n *= -1;
	while( n >= 19 )
	{
		printf( "duuuudeeee......i told u...not that big....\n" );
		printf( "this program wont support over 19 disks(even 19 disks wont be displayed \nperfectly)\n" );
		printf( "but,u didnt know that so i'll give u another shot:\n" );
		scanf( "%d", &n );
		set_color(0);
		system( "cls" );
		
		if ( n < 0 )
			n *= -1;
	}
	set_color(268);
	printf("which of the following songs would u rather listen to? :D\n");
	set_color(269);
	printf( "1.Talagh_Tooloogh_KOlahGhermezi\n" );
	set_color(270);
	printf( "2.Something 1 of my friends made(NOT RECOMMENDED)\n" );
	set_color(271);
	printf( "3.SELSELEH ----> moosighi sonnati\n" );
	set_color(267);
	printf( "4.30 Seconds To Mars Feat. Kanye West - Hurricane\n" );
	set_color(266);
	printf( "5.Survivur. Eye Of The Tiger\n" );
	set_color(265);
	printf( "6.Imagine_Dragons-Demons\n" );
	set_color(264);
	printf( "7.Taylor Swift - Blank Space\n" );
	set_color(15);
	scanf( "%d", &soundtracknum );
	switch(soundtracknum)
	{
	case 1:
		PlaySound(TEXT("Talagh_Tooloogh_KOlahGhermezi.wav"), NULL, SND_ASYNC);
		break;
	case 2:
		PlaySound(TEXT("REZA LOL.wav"), NULL, SND_ASYNC);
		break;
	case 3:
		PlaySound(TEXT("SELSELEH.wav"), NULL, SND_ASYNC);
		break;
	case 4:
		PlaySound(TEXT("30 Seconds To Mars Feat. Kanye West - Hurricane.wav"), NULL, SND_ASYNC);
		break;
	case 5:
		PlaySound(TEXT("Survivur. Eye Of The Tiger.wav"), NULL, SND_ASYNC);
		break;
	case 6:
		PlaySound(TEXT("Imagine_Dragons-Demons.orig(http-__mobileline.wav"), NULL, SND_ASYNC);
		break;
	case 7:
		PlaySound(TEXT("09 Taylor Swift - Blank Space.wav"), NULL, SND_ASYNC);
		break;
	default:
		break;
	}
	
	set_color(0);
	system( "cls" );
	
	disk_n[1]=disk_n[2]=0;
	disk_n[0]=n;


	for (int i=0 ; i<n ; i++)
		disk[0][i] = n-i;

	drawdisks();
	recursive(n,0,2,1);
 	drawdisks();
	gotoxy(30,2);
	set_color(178);
	printf( "press any key to continue" );
	getchar();
	getchar();
	set_color(0);
	system( "cls" );
	set_color(268);
	printf("which of the following songs would u rather listen to? :D\n");
	set_color(269);
	printf( "1.Talagh_Tooloogh_KOlahGhermezi\n" );
	set_color(270);
	printf( "2.Something 1 of my friends made(NOT RECOMMENDED)\n" );
	set_color(271);
	printf( "3.SELSELEH ----> moosighi sonnati\n" );
	set_color(267);
	printf( "4.30 Seconds To Mars Feat. Kanye West - Hurricane\n" );
	set_color(266);
	printf( "5.Survivur. Eye Of The Tiger\n" );
	set_color(265);
	printf( "6.Imagine_Dragons-Demons\n" );
	set_color(264);
	printf( "7.Taylor Swift - Blank Space\n" );
	set_color(15);
	while( true )
	{
		scanf( "%d", &soundtracknum );
		switch(soundtracknum)
		{
		case 1:
			PlaySound(TEXT("Talagh_Tooloogh_KOlahGhermezi.wav"), NULL, SND_ASYNC);
			break;
		case 2:
			PlaySound(TEXT("REZA LOL.wav"), NULL, SND_ASYNC);
			break;
		case 3:
			PlaySound(TEXT("SELSELEH.wav"), NULL, SND_ASYNC);
			break;
		case 4:
			PlaySound(TEXT("30 Seconds To Mars Feat. Kanye West - Hurricane.wav"), NULL, SND_ASYNC);
			break;
		case 5:
			PlaySound(TEXT("Survivur. Eye Of The Tiger.wav"), NULL, SND_ASYNC);
			break;
		case 6:
			PlaySound(TEXT("Imagine_Dragons-Demons.orig(http-__mobileline.wav"), NULL, SND_ASYNC);
			break;
		case 7:
			PlaySound(TEXT("09 Taylor Swift - Blank Space.wav"), NULL, SND_ASYNC);
			break;
		default:
			break;
		}
		printf( "\ncare for another?\n" );
		printf( "1.sure\n" );
		printf( "2.i think ill pass,but thanks! :D\n" );
		scanf( "%d" , &answer );
		if( answer == 2 )
			break;
		else{}
	}
	set_color(0);
	system( "cls" );
	set_color(15);
	gotoxy(30,15);
	printf( "hope to see u again soon!!" );
	getchar();
	getchar();
	return 0;
}