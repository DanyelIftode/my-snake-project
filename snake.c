#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#define MAX 30
#define MIN 15

typedef struct{ //USED TO SAVE COORDINATES OF THE SNAKE PARTS
	int x;
	int y;
} coord;

void delay(double number_of_seconds) //DELAYS EXECUTION OF CODE
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds); 
} 

void gotoxy( short x, short y ) //MOVES CURSOR AT BEGINNING
{ 
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ; 
    COORD position = { x, y } ; 
     
    SetConsoleCursorPosition( hStdout, position ) ; 
} 

void printgame(char gameMap[MIN][MAX],int count){ // UPDATES THE GAME AREA
	int i,j;
	gotoxy(0, 0);
	for(i=0;i<MIN;i++){
		for(j=0;j<MAX;j++){
			if(i==0 || j==0 || i==MIN-1 || j==MAX-1) gameMap[i][j]='*';
			printf("%c",gameMap[i][j]);
			if(i==5 &&j==MAX-1) printf("\t Score:%d",count);
			if(i==1 &&j==MAX-1) printf("\t W:Move up   ; S:Move down ");
			if(i==2  &&j==MAX-1) printf("\t A:Move left ; D:Move right"); 
		}
		printf("\n");
	}
}

void win(){
	int i,j;
	system("cls");
	system("color E");
	printf("\tVICTORY\t\n");
	for(i=0;i<MIN;i++){
		for(j=0;j<MAX;j++){
			if(i%2==0 &&j%2==0) printf("$");
			else if(i%2==1 &&j%2==1) printf("$");
			else printf(" ");
		}
		printf("\n");
	}
	system("pause");
}

void gameOver(){
	int i,j;
	gotoxy(0, 0);
	for(i=0;i<MIN;i++){
		for(j=0;j<MAX;j++){
			if(i==MIN/2 && j==MAX/2){
				printf("GAME OVER!");
			}
			else printf(" ");
		}
		printf("\n");
	}
	system("pause");
}



main(){
	srand(time(NULL));
	int n;
	printf("Choose difficulty:\n1)Easy:10\n2)Medium:20\n3)Hard:30\n...\n10)Impossible:100\n");
	scanf("%d",&n);
	n=n*10;
	double d=1/sqrt(n);
	int i,j,count=0,s=0;
	coord food;
	char ch,ch1;
	coord snake[n];//The snake can be long only n*10
	snake[0].x=2;
	snake[0].y=1;
	char gameMap [MIN][MAX];
	for(i=0;i<MIN;i++){
		for(j=0;j<MAX;j++){
			gameMap[i][j]=' ';
		}
	}
	food.x=rand()%(MIN-3)+1;//randomly position food
	food.y=rand()%(MAX-3)+1;
	gameMap[food.x][food.y]='#';
	gameMap[snake[0].x][snake[0].y]='@';
	printgame(gameMap,count);
	if(!kbhit()) ch=getch();
	while(count!=n){
		if((snake[0].x==food.x && snake[0].y==food.y) || (snake[count].x==food.x && snake[count].y==food.y)){//when the snake eats, randomly move the fruit
			food.x=rand()%(MIN-3)+1;//randomly position food
			food.y=rand()%(MAX-3)+1;
			gameMap[food.x][food.y]='#';// # is the food
			count++;
			s=1;//used to know the first movement of the snake after eating
			snake[count]=snake[count-1];//the new position of the snake part is at it's end 
			printgame(gameMap,count);//refresh the map to see where's the food at
		}
		if(snake[0].x==MIN-1 || snake[0].x==0 || snake[0].y==MAX-1 || snake[0].y==0){//used to control when you reach the border of the map , so it teleports in the opposite part
			if(snake[0].x==MIN-1){
				snake[0].x=1;
			}
			if(snake[0].x==0){
				snake[0].x=MIN-1;
			}
			if(snake[0].y==MAX-1){
				snake[0].y=1;
			}
			if(snake[0].y==0){
				snake[0].y=MAX-1;
			}
		}
		if(count==0){//at the beginning when it's only long 1 it moves thanks to this
			gameMap[snake[0].x][snake[0].y]=' ';
			if(ch=='w'){
				if(ch1=='s'){
					snake[0].x++;
					
				}
				else{
					ch1=ch;
					snake[0].x--;
				}
			}
			if(ch=='s'){
				if(ch1=='w'){
					snake[0].x--;
				}
				else{
					ch1=ch;
					snake[0].x++;}
				}
			if(ch=='d'){
				if(ch1=='a'){
					snake[0].y--;
				}
				else{
					ch1=ch;
					snake[0].y++;
				}
			}
			if(ch=='a'){
				if(ch1=='d'){
					snake[0].y++;
				}
				else{
					ch1=ch;
					snake[0].y--;
				}
			}
			gameMap[snake[0].x][snake[0].y]='@';
		}
		else{//after eating we start using this movement
			if(s>0){//thanks to the s we can make the snake bigger 
				for(i=count-1;i>0;i--) snake[i]=snake[i-1];
				if(ch=='w') snake[0].x--;
				if(ch=='s') snake[0].x++;
				if(ch=='d') snake[0].y++;
				if(ch=='a') snake[0].y--;		
				for(i=0;i<count;i++) gameMap[snake[i].x][snake[i].y]='@';
				s--;//after, we make the snake bigger we block the program entering this condition by decrementing s
			}
			else{//at the next cycle we start moving the bigger snake normally
				gameMap[snake[count].x][snake[count].y]=' ';//delete the tail
				for(i=count;i>0;i--){
						snake[i]=snake[i-1];//all body parts without the head get the position of the one that come before
				}
				if(ch=='w') {//move up
					if(ch1=='s'){//can't go backwards
						snake[0].x++;
					}
					else{
						ch1=ch;
						snake[0].x--;
					}
					if(gameMap[snake[0].x][snake[0].y]=='@'){
						count=-1;//we use the -1 to flag when we hit our tail
						break;
					}
				}
				if(ch=='s') {//move down
					if(ch1=='w') {//can't go backwards
						snake[0].x--;
					}
					else{
						ch1=ch;
						snake[0].x++;
					}
					if(gameMap[snake[0].x][snake[0].y]=='@'){
							count=-1;//we use the -1 to flag when we hit our tail
							break;
						}
				}
				if(ch=='d' ) {//move right
					if(ch1=='a'){//can't go backwards
						snake[0].y--;
					}
					else{
						ch1=ch;
						snake[0].y++;
					}
					if(gameMap[snake[0].x][snake[0].y]=='@'){
							count=-1;//we use the -1 to flag when we hit our tail
							break;
					}
				}
				if(ch=='a') {//move left
					if(ch1=='d'){//can't go backwards
						snake[0].y++;
					}
					else{
						ch1=ch;
						snake[0].y--;
					}
					if(gameMap[snake[0].x][snake[0].y]=='@'){
							count=-1;//we use the -1 to flag when we hit our tail
							break;
						}
				}
				for(i=0;i<=count;i++)	gameMap[snake[i].x][snake[i].y]='@';
			}
		}
		printgame(gameMap,count);
		if(kbhit())	ch=getch();//if a key is pressed , and is a direction key we change direction
		delay(d);
	}
	if(count==-1){//we use the -1 to flag when we hit our tail
		gameOver();
	}
	if(count==n){//if you achieve the score you input at beginning you win :)
		win();
	}
}
