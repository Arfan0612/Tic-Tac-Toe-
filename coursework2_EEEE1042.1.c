#include <stdio.h>
#include <string.h>
#define N 3
#define M 9

void welcome();
void clearboard();
void printBoard();
int validateinput();
void markboard(char markingboard[],int decision,char player);
int checkwin();
int checkdraw();
void printmssg();

int main(){
  char board[M]={'1','2','3','4','5','6','7','8','9'};//max index is 8
  char markingboard[M];//needed just for aesthetic wise when printing out board as game goes on
  char player1='O';
  char player2='X';
  int turn=1; //1 = player1 turn and 2 = player2 turn
  int end=0;//to know if game is finish, game finish after turn 9
  int decision;//to temporarily store user's choice
  int control=-1;//to control the loop
  int chances=2;//each player has 2 chances to input legal value
  int validation;//to store result from validating input

  welcome();  
  printBoard(board);
  
  strcpy(markingboard,board);//to initialize the markingboard
  clearboard(markingboard);//to clear the markingboard
  
  while(control==-1 && end<M && chances>0){
    if(turn==1){//player1 has to input 
      printf("Enter move for Player%d(\'%c\'): ",turn,player1);
      scanf("%d",&decision);//store player1 input in decision
      printf("\n");

      //validating user input from player1
      validation=validateinput(decision,board);
      if(validation==0){//check if player has entered illegal move
	printf("Player%d('%c') entered illegal value\n",turn,player1);
	chances--;//reduce the chances for inputting correct input 
	continue;//restart while loop
      }
   
      markboard(board,decision,player1);//calling function to mark the board with 'X' or 'O'
      markboard(markingboard,decision,player1);
      control=checkwin(board);//to check which player1 won
      printmssg(control,turn);//print winning message if this player won
      turn++;//to change person who has to input
    }
    else if(turn==2){//player2 has to input
      printf("Enter move for Player%d(\'%c\'): ",turn,player2);
      scanf("%d",&decision);//store player2 input in decision
      printf("\n");

      //validating user input from player2
      validation=validateinput(decision,board);
      if(validation==0){
	printf("Player%d('%c') entered illegal value\n",turn,player2);
	chances--;
	continue;//restart loop for user to try again
      }
      
      markboard(board,decision,player2);//calling function to mark the board with 'X' or 'O'
      markboard(markingboard,decision,player2);
      control=checkwin(board);//to check which player2 won
      printmssg(control,turn);//print winning message if this player won
      turn--;//to change person who has to input
    }
    
    printBoard(markingboard);//to print ongoing game board
    end++;//to control how many times correct input can be entered 
  }

  //print error message if chances become 0
  if(chances==0){
    printf("Error wrong inputs have been entered!\n");
    printf("Program shut down!\n");
  }
  return 0;
}

void welcome(){
  printf("----------------------------\n");
  printf("\tTIC TAC TOE\n");
  printf("----------------------------\n\n");
  printf("----------------------------\n");
  printf("***Caution***\n");
  printf("Given 2 total chances to enter legal input\n");
  printf("If those chances are used up by either player, program stop\n");
  printf("----------------------------\n\n");
}

void clearboard(char markingboard[]){
  
  //clearing board by entering each postion
  for(int i=0; i<9; i++){
    markingboard[i]=' ';//replace each position from 0 to 8 with white spaces
  }
}

void printBoard(char markingboard[]){

  //printing board 1D array as a 2D array
  printf("\t    |    |   \n");
  for(int i=0; i<N; i++){//rows 
    printf("\t");
    
    for(int j=0; j<N; j++){//colomns for that row  
      if(j<2){
      printf(" %c  |", markingboard[i*N+j]);
      }
      else printf(" %c ", markingboard[i*N+j]);
      
    }
    printf("\n");
    
    if(i<2){
      printf("\t ___|____|___\n");
      printf("\t    |    |   \n");
 
    }
    else printf("\t    |    |   \n");
    
  } 
}

int validateinput(int decision, char board[]){
  int digit=0;//to check number of digits entered
  int temp=decision;//temporarily stores decision value
  int occ;//to see that user doesn't entered same value 

  //if 1 digit number, after decision divided by 10 the number will be 0
  //***as int type will cut off the values after decimal
  //if digit>1, after decision divide by 10 the result is digit>0
  while(temp!=0){
    temp=temp/10;
    digit++;//digit counter
  }
  
  //to check if user entered input that has already been occupied
  //[decision-1] is for it to be a valid position in the board due to index difference 
  if(board[decision-1]!='O' && board[decision-1]!='X'){
    occ=1;
  }
  else occ=0;
  
  //double check to see if decision is correct input
  if (digit==1 && decision>0 && decision<10 && occ){
    return 1;//return 1 if input is legal move
  }
  else return 0;
  
}

void markboard(char board[],int decision,char player){
  //mark the moves down 
  for(int i=0; i<M; i++){
    //if decision same as i position on board
    //it will mark the board at that position
    if (decision==i+1){
      board[i]=player;
    }
  }
  
}

int checkwin(char board[]){
  int checking;//to store return value from checking for a draw
  //returns 1 if either player has won the game
  //returns -1 to continue the game
  //returns 0 if game ends in a draw
  
  //*******checking 1st row if any player wins
  //1st row 
  if(board[0]==board[1] && board[1]==board[2]){
    return 1;
  }
  //2nd row
  else if(board[3]==board[4] && board[4]==board[5]){
    return 1;
  }
  //3rd row
  else if(board[6]==board[7] && board[7]==board[8]){
    return 1;
  }

  //*******checking colomn if any player wins
  //1st colomn
  else if(board[0]==board[3] && board[3]==board[6]){
    return 1;
  }
  
  //2nd colomn
  else if(board[1]==board[4] && board[4]==board[7]){
    return 1;
  }

  //3rd colomn
  else if(board[2]==board[5] && board[5]==board[8]){
    return 1;
  }

  //*******checking diagonal if any player wins
  //from top left diagonally to bottom right
  else if(board[0]==board[4] && board[4]==board[8]){
    return 1;
  }

  //from top right diagonally to bottom left
  else if(board[2]==board[4] && board[4]==board[6]){
    return 1;
  }

  checking=checkdraw(board);
  //*******checking for draw
  if(checking==1){
    return 0;
  }
  //continue playing
  else return -1;

}

int checkdraw(char board[]){
  int draw=0;//counter for how many spaces have been occupied

  //check to see how many spaces have been occupied
  for(int i; i<M; i++){
    if(board[i]=='X' || board[i]=='O'){
      draw++;
    }
  }

  /*program decides it's a draw if 8 spaces occupied 
    but no player has won the game yet*/
  if(draw==8){ 
    return 1;
  }
  else return 0;
}

void printmssg(int control,int turn){
  if(control==1){
    printf("Congrats to Player%d for winning the game!\n",turn);
  }
  else if(control==0){
    printf("Game ended in a Draw!\n");
  }
}
