#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define N 3
#define M 9
#define P 2000

void welcome();
void clearboard();
void printBoard();
int situation();
int validateinput();
int randomAI();
int smartAI(char board[],char letter);
void markboard(char markingboard[],int decision,char player);
int checkwin();
int checkdraw();
void printmssg();
void printcounter();

int main(){
  char board[M];//max index is 8
  char markingboard[M];//needed just for aesthetic wise when printing out board as game goes on
  char AI1='O';
  char AI2='X';
  int turn;//change this to make who goes first  
  int end;//to know if game is finish, game finish after 9 turns
  int decision;//to temporarily store user's choice
  int control;//to control the while loop
  int validation;//to store result from validating input 
  int scenario;//determine which scenario to run
  int running=0;//how many times the program has to run
  int win1=0;//store win counter for AI1
  int win2=0;//store win counter for AI2
  int draw=0;//store how many draws occured

  welcome();
  scenario=situation();//user decides to go against randomAI or SmartAI
  
  if(scenario!=4){//check to see if user put in correct input
    while(running<P){
      clearboard(markingboard,board);//to clear the markingboard
      turn=1;//so that AI1 always start first 1 ='O' and 2 ='X'
      end=0;//so it start from 0 turns and goes until 8
      control=-1;//to continue the game
      
      while(control==-1 && end<M){
	if(turn==1){//player1 has to input
	
	  if(scenario==1 || scenario==2){
	    //printf("for turn 1 smartAI was chosen\n");
	    decision=smartAI(board,AI1);
	  }
	  else{
	    //printf("for turn 1 randomAI was chosen\n");
	    decision=randomAI();
	  }
	
        
	  //validating user input from AI1
	  validation=validateinput(decision,board);
	  if(validation==0){//to see if AI has picked a illegal move
	    continue;//restarts while loop
	  }

	  //to print what move was made by AI 1
	  printf("\n");
	  printf("     --------------------\n");
	  printf("       AI 1(O) move is %d\n",decision);
	  printf("     --------------------\n");
	
   
	  markboard(board,decision,AI1);//calling function to mark the board with 'X' or 'O'
	  markboard(markingboard,decision,AI1);
	  control=checkwin(board);//to check if player1 won
	  printmssg(control,turn,&win1,&win2,&draw);//print winning message if this player won and update counters
	  turn++;//to change who has to input
	}
      
	else if(turn==2){//computer has to input
	
	  if(scenario==1){
	    //printf("for turn 2 smartAI was chosen\n");
	    decision=smartAI(board,AI2);
	  }
	  else if(scenario==2 || scenario==3){
	    //printf("for turn 2 randomAI was chosen\n");
	    decision=randomAI();
	  }
	
	  //validating user input from AI2
	  validation=validateinput(decision,board);
	  if(validation==0){
	    continue;//restart loop for computer to try again
	  }

	  //to print what move was made by AI 2
	  printf("\n");
	  printf("     --------------------\n");
	  printf("       AI 2(X) move is %d\n",decision);
	  printf("     --------------------\n");
	
	  markboard(board,decision,AI2);//calling function to mark the board with 'X' or 'O'
	  markboard(markingboard,decision,AI2);
	  control=checkwin(board);//to check for win
	  printmssg(control,turn,&win1,&win2,&draw);//print winning message if this player won and update counters
	  turn--;//to change who has to input
	}
    
	printBoard(markingboard);//to print ongoing game board
	end++;//to control how many times correct input can be entered 
      }
      running++;
    }
  }

  printcounter(win1,win2,draw);//print final results for that situation after running for P times
  

  //print error message if chances become 0
  //or user input wrong when picking which scenario to play
  if(scenario==4){
    printf("\nError has occurred!\n");
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
  printf("Given 2 chances to enter legal input\n");
  printf("If those chances are used up by the player, program stop\n");
  printf("----------------------------\n\n");
}

void clearboard(char markingboard[],char board[]){
  //clearing board by entering each postion
  for(int i=0; i<9; i++){
    markingboard[i]=' ';//replace each position from 0 to 8 with white spaces

    //replace each position with num from 1 to 9
    //48 is acsii code for '0'
    board[i]=(i+1)+48;
  }

}

void printBoard(char markingboard[]){

  //printing board 1D array as a 2D array
  printf("\t    |    |   \n");
  for(int i=0; i<N; i++){//rows 
    printf("\t");
    
    for(int j=0; j<N; j++){//colomn for that row 
      
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

int situation(){
  int userdecision;//to store user's choice 
  int attempt=0;//number of attempts if user enter wrong input
  
  do{
    printf("Which scenario to run?\n");
    printf("1:SmartAI vs SmartAI\n");
    printf("2:SmartAI vs RandomAI\n");
    printf("3:RandomAI vs RandomAI\n");
    scanf("%d",&userdecision);

    //user has chosen SmartAI vs SmartAI
    if(userdecision==1) return 1;
    
    //user has chosen SmartAI vs RandomAI
    else if(userdecision==2) return 2;
    
    //user has chosen RandomAI vs RandomAI
    else if(userdecision==3) return 3;

    //user has 2 chances to insert correct input
    else if(attempt<1){
      printf("\nInvalid input!\n");
      attempt++;
      continue;//restart the while loop to ask for user input 
    }

    //user has failed to enter correct input
    else return 4; 
    
  } while (attempt!=0);
}


int validateinput(int decision, char board[]){
  int digit=0;//to check number of digits entered
  int temp=decision;//temporarily stores decision value
  int occ;//to see that user doesn't entered same value 

  //if 1 digit number, after decision divide by 10 the number will be 0
  //***as int type will cut off the values after decimal
  //if digit>1, after decision divide by 10 the number>0
  while(temp!=0){
    
    temp=temp/10;
    digit++;
  }
  
  //to check if user entered input that has already been occupied
  //[decision-1] is for it to be a valid position in the board due to index difference 
  if(board[decision-1]!='O' && board[decision-1]!='X'){
    occ=1;
  }
  else occ=0;
  
  //double check to see if decision is correct input
  if (digit==1 && decision>0 && decision<10 && occ){
    return 1;
  }
  else return 0;
  
}

int randomAI(){
  int choiceR;//to store randomAI's choice 
  srand(clock());//to initialize random seed
  choiceR=1+(int)((float)M*rand()/(RAND_MAX+1.0));//for the AI to make random move 
  return choiceR;//return value stored in choiceR to caller
}

int smartAI(char board[],char letter){
  //to see which letter is used by current turn smartAI
  char sign1;
  char sign2;
  
  //*****variables for row
  int choiceR;//store best possible move by AI by row move or random move
  int rowX=0;//to store how many X in a row 
  int rowO=0;//to store how many O in a row

  //*****variables for colomn
  int choiceC;//store best possible move by AI by colomn
  int colomnX=0;//to store how many X in a colomn
  int colomnO=0;//to store how many O in a colomn

  //*****for checking white spaces
  int whiteR=0;
  int whiteC=0;
  int whiteD=0;

  //*****variables for diagonal
  int choiceD;
  int diagonalO=0;
  int diagonalX=0;

  //to see which letter is used by current turn smartAI
  if(letter=='O') {
    //printf("AI using 'O'\n");
    sign1='O';
    sign2='X';
  }
  else if(letter=='X'){
    //printf("AI using 'X'\n");
    sign1='X';
    sign2='O';
  }
  
  //computer's possible winning moves by row or colomn
  for(int i=0; i<N; i++){
    //check every space in board by row and by colomn 
    for(int j=0; j<N; j++){

      //************checking by row
      if(board[i*N+j]==sign1){//check for each colomn in that row 
	rowX++;//add to X counter for row 
      }
      else if(board[i*N+j]!=sign2) {
	choiceR=(i*N+j);//this position is a white space in the row
	whiteR++;//add to row white space counter
      }  
      
      //************checking by colomn
      if(board[j*N+i]==sign1){//check for each row in that colomn
	colomnX++;//add to X counter for colomn
      }
      else if(board[j*N+i]!=sign2) {
	choiceC=(j*N+i);//this position is a white space in the colomn
	whiteC++;//add to white space counter for colomn
      }

    }
    //stop loop as there is a winning for the computer
    if(rowX==2 || colomnX==2) {
      break;
    }
    //reset for values for each row and colomn
    rowX=0;
    whiteR=0;
    colomnX=0;
    whiteC=0;
  }

  if(rowX==2 && whiteR==1){
    //printf("computer moved row\n");
    choiceR++;
    return choiceR;
  }
  else if(colomnX==2 && whiteC==1){
    //printf("computer moved colomn\n");
    choiceC++;
    return choiceC;
  }

  //diagonally from 1 to 9
  int t=0;
  while(t<9){
    //check if space is occupied by X
    if(board[t]==sign1){
      diagonalX++;
    }
    //check if space is occupied by O
    else if(board[t]==sign2){
      diagonalO++;
    }
    else{//store that position that only has white space
      choiceD=t;
      whiteD++;//counter for white space 
    }
    //there is a winning or blocking move for the computer
    if((diagonalX==2 && whiteD==1) || (diagonalO==2 && whiteD==1)){
      break;
    }
    t+=4;//indentation for controlling while loop
  }

  if(diagonalX==2 && whiteD==1){
    //printf("computer moves diagonally to right\n");
    choiceD++;
    return choiceD;
  }
  else if(diagonalO==2 && whiteD==1){
    //printf("computer blocks diagonally to right\n");
    choiceD++;
    return choiceD;
  }

  //reset values to be able to reuse it
  diagonalX=0;
  diagonalO=0;
  whiteD=0;

  //diagonally from 2 to 7 
  t=2;//so that it start from top right of board
  while(t<9){
    //check if space is occupied by X
    if(board[t]==sign1){
      diagonalX++;
    }
    //check if space is occupied by O
    else if(board[t]==sign2){
      diagonalO++;
    }
    else{
      choiceD=t;//store position where it is just a white space
      whiteD++;//counter for white space
    }
    //printf("diagonalX is %d and diagonalO is %d\n",diagonalX,diagonalO);
    //stop loop if there is a winning or blocking move to be made by computer
    if((diagonalX==2 && whiteD==1) || (diagonalO==2 && whiteD==1)){
      break;
    }
    t+=2;//indentation for controlling while loop
  }
  
  if(diagonalX==2 && whiteD==1){
    //printf("computer moves diagonally to left\n");
    choiceD++;
    return choiceD;
  }
  else if(diagonalO==2 && whiteD==1){
    //printf("computer blocks diagonally to left\n");
    choiceD++;
    return choiceD;
  }

  //reset so it can be reused
  rowX=0;
  colomnX=0;

  //to intercept player's winning move by row or colomn
  for(int k=0; k<N; k++){
    for(int l=0; l<N; l++){
      
      if(board[k*N+l]==sign2){//check for each colomn in that row
	rowO++;//count O in that row 
      }
      else if(board[k*N+l]==sign1){
	rowX++;//count X in that row
      }
      
      else{
	choiceR=(k*N+l);//this position holds white space
      }
      
      if(board[l*N+k]==sign2){
	colomnO++;//to count O in that colomn
      }
      else if(board[l*N+k]==sign1){
	colomnX++;//to count X in that colomn
      }
      
      else{
	choiceC=(l*N+k);//this position is a white space in the colomn
      }
      
    }
    //stop loop if there is a move that can block player's winning move
    if((rowO==2 & rowX==0) || (colomnO==2 && colomnX==0)) {
      break;
    }
    //reset for each row or colomn
    rowO=0;
    colomnO=0;
    rowX=0;
    colomnX=0;
  }

  if(rowO==2 && rowX==0){
    //printf("computer blocked row\n");
    choiceR++;//make it a legal move
    return choiceR;
  }
  else if(colomnO==2 && colomnX==0){
    //printf("computer blocked colomn\n");
    choiceC++;//make it a legal move
    return choiceC;
  }

  //last option to do random move if no best move to be made by AI 
  //printf("computer random move\n");
  choiceR=randomAI();
  return choiceR;
  
}
  
  

void markboard(char board[],int decision,char AI){
  //mark the moves by player or computer down 
  for(int i=0; i<M; i++){
    //if decision same as i position on board
    //it will mark the board at that position
    if (decision==i+1){//to check which position player or computer has input
      board[i]=AI;//mark that position down with 'X' or 'O'
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
  for(int i=0; i<M; i++){
    if(board[i]=='X' || board[i]=='O'){
      draw++;
    }
  }

  /*program decides it's a draw if 8 spaces occupied 
    but no one has won the game yet*/
  if(draw==8){ 
    return 1;
  }
  else return 0;
}

void printmssg(int control,int turn,int *win1,int *win2,int *draw){
  //if game still continue it will not print anything from here nor update the counters
  if(control==1){
    printf("    Congrats to AI%d for winning the game!\n",turn);
    if(turn==1){//if AI1 won the game 
      *win1+=1;//increase win counter for AI1
    }
    else if(turn==2){//if AI2 won the game 
      *win2+=1;//increase win counter for AI2
    }
  }
  else if(control==0){
    printf("    Game ended in a Draw!\n");
    *draw+=1;//increase draw counter
  }
}

void printcounter(int win1, int win2, int draw){
  //to print result of counter
  printf("----------------------------\n");
  printf("Results\n");
  printf("----------------------------\n");
  
  printf("wins for AI 1: %d\n",win1);
  printf("wins for AI 2: %d\n",win2);
  printf("draws: %d\n",draw);
}

