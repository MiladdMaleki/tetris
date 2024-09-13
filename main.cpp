#include <iostream>
#include <conio.h>
using namespace std;
//block with  x and y property
struct block
{
  int x;
  int y;	
}mainBlock[4],badBlock[4];

#define w 18
#define h 30

int board[h][w];
int score=0;
//define prototypes
void show();
void genBlock();
void changeBoard(int);
int  checkIsValidChange(int);
int  downBlock();
void rightBlock();
void atob(struct block a[],struct block b[],int n=4);
void leftBlock();
void checkRow();
void rotateBlock();

int main() {
	//init 0
	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)board[i][j]=0;
	}
	//board[10][w/2+1]=-1;
	system("color 02");
	while(1)
	{
		checkRow();
	    genBlock();
		if(checkIsValidChange(0))//can running game
		 {	 	
			 changeBoard(0);//make change with new block
			 show();
			 while(1){
				  //if pressed any key
                  if(kbhit())
                  {
                  	char ch1=getch();
                  	if(ch1==-32)
                  	{			
					    char ch2=getch();		  
	                    
						if(ch2==80)
	                  	{
	                  		downBlock();
	                  		downBlock();
					    }
						else if(ch2== 77)
						{
							rightBlock();
							
						}
	                  	else if(ch2==75)
	                  	{
	                  		leftBlock();
						  }
					    else if(ch2==72)
						{
						 rotateBlock();	
					     }
			     	}
			     	else if(ch1=='s') //stope game
			     	{
			     		printf("\n press r to continue");
			     		while(1)
			     		{
			     			if(kbhit())
			     			{
							 
			     			 char ch=getch();
			     			 if(ch=='r')break;
						    } 
						 }
			     		
					 }
				 }
                  if(!downBlock())break;				
				  usleep(500);
				  show();	 
		       }
		  //after end of each new block check rows for delate them     
		 }
		 else //end game
		 {
		 	cout<<endl<<"end";
		 	break;
		 }
    }
    cout<<"press q to quit...";
    while(getch()!='q');
    
	return 0;
}

//show board and blocks
void show()
{
    system("cls");
	printf("pres s to stope . . . . \n\n");
	for(int i=0;i<h;i++)
	{
		cout<<'#';
		for(int j=0;j<w;j++)
		{
			if(board[i][j]==0)cout<<"  ";
		    else cout<<"[]";
		}
		cout<<"#";
		if(i==3) cout<<"          score="<<score;
		cout<<endl;
	}
    for(int i=0;i<2*(w)+2;i++)cout<<'#';
	
}
//generate blocks with pattern
void genBlock()
{
  struct block typeBlock[5][4];		
  int number;//number of type block
 // block  @ @ @ @
  number=0; 
  typeBlock[number][0].x=0;
  typeBlock[number][0].y=w/2;
  typeBlock[number][1].x=0;
  typeBlock[number][1].y=w/2+1;
  typeBlock[number][2].x=0;
  typeBlock[number][2].y=w/2+2;
  typeBlock[number][3].x=0;
  typeBlock[number][3].y=w/2+3;
  //block   @ @
  //        @ @
  number=1;
  typeBlock[number][0].x=0;
  typeBlock[number][0].y=w/2;
  typeBlock[number][1].x=0;
  typeBlock[number][1].y=w/2+1;
  typeBlock[number][2].x=1;
  typeBlock[number][2].y=w/2;
  typeBlock[number][3].x=1;
  typeBlock[number][3].y=w/2+1;
  //block   @ @ @
  //        @ 
  number=2;
  typeBlock[number][0].x=0;
  typeBlock[number][0].y=w/2;
  typeBlock[number][1].x=0;
  typeBlock[number][1].y=w/2+1;
  typeBlock[number][2].x=0;
  typeBlock[number][2].y=w/2+2;
  typeBlock[number][3].x=1;
  typeBlock[number][3].y=w/2;
  //block    @
  //       @ @
  //       @
  number=3;
  typeBlock[number][0].x=0;
  typeBlock[number][0].y=w/2;
  typeBlock[number][1].x=1;
  typeBlock[number][1].y=w/2;
  typeBlock[number][2].x=1;
  typeBlock[number][2].y=w/2-1;
  typeBlock[number][3].x=2;
  typeBlock[number][3].y=w/2-1;    
  //block    
  //       @ @
  //         @ @ 
  number=4;
  typeBlock[number][0].x=0;
  typeBlock[number][0].y=w/2;
  typeBlock[number][1].x=0;
  typeBlock[number][1].y=w/2+1;
  typeBlock[number][2].x=1;
  typeBlock[number][2].y=w/2+1;
  typeBlock[number][3].x=1;
  typeBlock[number][3].y=w/2+2;    
  
  int cho=rand()%5;//choice block type random

  for(int i=0;i<4;i++)
  {
  	badBlock[i].x=typeBlock[cho][i].x;
	badBlock[i].y=typeBlock[cho][i].y;
   }
     
}
//change board with mainBlock values flag=0 runing block    flag=1 fixing
void changeBoard(int flag)
{ 
       if(flag==0)//for running block and is changable 
       {
	     //change board with new block is possible
		 for(int i=0;i<4;i++)
	     {
			board[mainBlock[i].x][mainBlock[i].y]=1;
	     }
        }
      else if(flag==1)//for fixing block and not changable
      {
		 for(int i=0;i<4;i++)
	     {
			board[mainBlock[i].x][mainBlock[i].y]=-1;
	     }      	
	  }
}
//for check can change board with new block if can replace badBlock mainBlock
int checkIsValidChange(int action)
{
  if(action==0)//for check new block
  {
        //check for can generate new block
	  	for(int i=0;i<4;i++)
	  	{
	    	  if(badBlock[i].x>=h || badBlock[i].y>=w || board[badBlock[i].x][badBlock[i].y]== -1)return 0;
		}
		atob(badBlock,mainBlock,4);
		return 1;  	
  }
  else if(action==1)//for check and change running block   last main block=new valid bad block
  {
  	    //check for is valid badBlock
	  	for(int i=0;i<4;i++)
	  	{
	    	  if(badBlock[i].y<0 || badBlock[i].x<0 || badBlock[i].x>=h || badBlock[i].y>=w || board[badBlock[i].x][badBlock[i].y]== -1)return 0;
		}
		//mainBlock(last true Block) value to 0(init)
		for(int i=0;i<4;i++)
	  	{
			board[mainBlock[i].x][mainBlock[i].y]=0;
		}
		atob(badBlock,mainBlock,4);
  }

}
//////////////////////////////////

// for downing main block (x++ for main block)
int downBlock()
{
 atob(mainBlock,badBlock,4);
 for(int i=0;i<4;i++)
 {
 	badBlock[i].x++;
 }
 
 if(checkIsValidChange(1)){
    changeBoard(0);
    return 1; 
    }
 else
  {
    changeBoard(1);//fix main block
    return 0;    	
   }
}
//for assign array a to b     b=a
void atob(struct block a[],struct block b[],int n)
{
	for(int i=0;i<n;i++)b[i]=a[i];
}
//for just check if can got to right main block running go to right and else nothing(dont fixed like downBlock)
void rightBlock()
{
	 atob(mainBlock,badBlock,4);
	 for(int i=0;i<4;i++)
	 {
	 	badBlock[i].y++;
	 }
	 if(checkIsValidChange(1)){
	    changeBoard(0);
	    }
} 
//just like rightBlock with diffrence y--
void leftBlock()
{
	 atob(mainBlock,badBlock,4);
	 for(int i=0;i<4;i++)
	 {
	 	badBlock[i].y--;
	 }
	 if(checkIsValidChange(1)){
	    changeBoard(0);
	    }
}

//rotate block
void rotateBlock()
{
  struct block p=mainBlock[1];
  for(int i=0;i<4;i++)
  {
	int x=mainBlock[i].y-p.y;
	int y=mainBlock[i].x-p.x;
	badBlock[i].x=p.x-x;
	badBlock[i].y=p.y+y;
  }
  if(checkIsValidChange(1)){
	    changeBoard(0);
	 }  
 	
}


///////////check row and change upper rows/////////////
void checkRow()
{
	int isNotCompleteRow[h];// isNotCompleteRow is array store index if (from big to low)row is not compete (max size array is h)
	int len=0;//length of isNotCompleteRow 
    int flag=0;
	for(int i=h-1;i>=0;i--)
	{
		int isCompleteRow=1;
		for(int j=0;j<w;j++)
		{
			if(board[i][j]==0)isCompleteRow=0;
		}
		if(!isCompleteRow)
		{
			isNotCompleteRow[len++]=i;			
		}
		else
		{
		  score++;
		  flag=1;
		}
	}
	if(flag)
	{
		int isNotCompleteRow_counter=0;
		for(int i=h-1;i>=0;i--)
		{
		   	if(isNotCompleteRow_counter<len)
		   	{
		   		// board row [i]=board row [count_IsNotCompleteRow]   replace row i with fitst row is not complete from upper index
		   		for(int j=0;j<w;j++)
		   		{
		   		   board[i][j]=board[isNotCompleteRow[isNotCompleteRow_counter]][j];		
				}
				isNotCompleteRow_counter++;
			}
			else
			{
			  // board row [i]=empity row
		   		for(int j=0;j<w;j++)
		   		{
		   		   board[i][j]=0;		
				}	
			}
		}
    }
}

