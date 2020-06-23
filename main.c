#include <stdio.h>

//fills the board with '.' at the beginning of the game
void fillEmptyBoard(char board[6][7]){
  for(int i=0;i<6;i++){
    for(int j=0;j<7;j++){
       board[i][j]='.';
    }
  }
}

//prints the board 
void printBoard(char board[6][7]){
  printf("   %c  %c  %c  %c  %c  %c  %c\n",'A','B','C','D','E','F','G');
  for(int i = 0;i < 6;i++){
     for(int j = 0;j < 8;j++){
        if(j==0){
          printf("%i ",(6-i));
        }
        else{
          printf(" %c ",board[i][j-1]);
        }
     }
     printf("\n");
  }
}

//checks for 4 same symbols consecutively in vertical direction
int verticalCheck(char board[6][7]){
  for(int j=0;j<7;j++){
    for(int i = 5;i>=3;i--){
      if(board[i][j]=='.'){
        continue;
      }
      if(board[i][j]==board[i-1][j]&&board[i][j]==board[i-2][j]&&board[i][j]==board[i-3][j]){
        return 1;
      }
    }
  }
  return 0;
}

//checks for 4 same symbols consecutively in horizontal direction
int horizontalCheck(char board[6][7]){
  for(int i=0;i<6;i++){
    for(int j=0;j<3;j++){
      if(board[i][j]=='.'){
        continue;
      }
      if(board[i][j]==board[i][j+1]&&board[i][j]==board[i][j+2]&&board[i][j]==board[i][j+3]){
        return 1;
      }
    }
  }
  return 0;
}

//checks for a right diagonal with 4 same symbols
int rightDiagonalCheck(char board[6][7]){
  for(int i = 5;i >= 3;i--){
    for(int j = 0;j <= 3;j++){
      if(board[i][j]=='.'){
        continue;
      }
      if(board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2] && board[i][j] == board[i-3][j+3]){
        return 1;
      }
    }
  }
  return 0;
}

//checks for a left diagonal with 4 same symbols
int leftDiagonalCheck(char board[6][7]){
  for(int i = 5;i >= 3;i--){
    for(int j = 6;j>=3;j--){
      if(board[i][j]=='.'){
        continue;
      }
      if(board[i][j] == board[i-1][j-1] && board[i][j] == board[i-2][j-2] && board[i][j] == board[i-3][j-3]){
        return 1;
      }
    }
  }
  return 0;
}

/*If the value of l passed is 0, then the below function returns the
the frequency(score) of 'symbol' appearing consecutively in the vertical direction starting from location (x,y)*/
/*If the value of l passed is 1, then the below function returns the column in which the symbol should be dropped in the board*/
int verticalScore(char board[6][7],int x,int y,char symbol,int l){
  int a=0;
  int topScore = 0;
  int d = 1;
  int top = x;
  while(d<=4 && top>=0){
    if(board[top][y]==symbol){
      topScore++;
    }
    else{
      break;
    }
    d++;
    top--;
  }
  if(board[x-topScore][y]=='.'){
    if(l==0){
      a=topScore;
    }
    if(l==1){
      a=y;
    }
  }
  return a;  
}

/*If the value of l passed is 0, then the below function calculates the
the frequency(score) of 'symbol' appearing consecutively in the horizontal right and left direction starting from location (x,y)*/
/*It then returns the the maximum of both the left and right scores. If both the left and right scores are equal then it returns the right score*/
/*If the value of l passed is 1, then the below function returns the column in which the symbol should be dropped in the board*/
/*Before returning the column index, the function also checks for the validity of the column index */
int horizontalScore(char board[6][7],int x,int y,char symbol,int l){
  int a = 0;
  int leftScore = 0;
  int rightScore = 0;
  int left = y;
  int right = y;
  int d = 1;
  while(d<=4 && left>=0){
    if(board[x][left]==symbol){
      leftScore++;
    }
    if(board[x][left]!=symbol){
        break;
    }
    left--;
    d++;
  }
  d = 1;
  while(d<=4 && right<7){
    if(board[x][right]==symbol){
      rightScore++;
    }
    if(board[x][right]!=symbol&& board[x][right]!='.'){
      break;
    }
    right++;
    d++;
  }
  if(rightScore>=leftScore){
    if(board[x][y+rightScore]=='.' && (x+1)<=5 && board[x+1][y+rightScore]!='.'){
      if(l==0){
        a=rightScore;
      }
      if(l==1){
        a=y+rightScore;
      }     
    }
    else{
      if(l==0){
        a=0;
      }
      if(l==1){
        a=y;
      }
    }
  }
  else{
    if(y-leftScore>=0 && board[x][y-leftScore]=='.' && (x+1)<=5 && board[x+1][y-leftScore]!='.'){
      if(l==0){
        a=leftScore;
      }
      if(l==1){
        a=y-leftScore;}
    }
    else{
      if(l==0){
        a=0;
      }
      if(l==1){
        a=y;
      }
    }
  }
  return a;
}

/*If the value of l passed is 0, then the below function calculates the
the frequency(score) of 'symbol' appearing consecutively in the right diagonal direction starting from location (x,y)*/
/*If the value of l passed is 1, then the below function returns the column in which the symbol should be dropped in the board*/
/*Before returning the column index, the function also checks for the validity of the column index*/
int rightDiagonalScore(char board[6][7],int x,int y,char symbol,int l){
  int a = 0;
  int diagScore = 0;
  int diagX = x;
  int diagY = y;
  int d = 1;
  while(d<=4 && diagX>=0 && diagY<7){
    if(board[diagX][diagY]==symbol){
      diagScore++;
    }
    else{
      break;
    }
    diagX--;
    diagY++;
    d++;        
  }
  if(board[x-diagScore][y+diagScore]=='.' && board[x-diagScore-1][y+diagScore]!='.'){
    if(l==0){
      a=diagScore;
    }
    if(l==1){
      a=y+diagScore;
    }
  }
  else{
    if(l==0){
      a=0;
    }
    if(l==1){
      a=y;
    }
  }
  return a;
}

/*If the value of l passed is 0, then the below function calculates the
the frequency(score) of 'symbol' appearing consecutively in the left diagonal direction starting from location (x,y)*/
/*If the value of l passed is 1, then the below function returns the column in which the symbol should be dropped in the board*/
/*Before returning the column index, the function also checks for the validity of the column index*/
int leftDiagonalScore(char board[6][7],int x,int y,char symbol,int l){
  int a=0;
  int diagScore = 0;
  int diagX = x;
  int diagY = y;
  int d = 1;
  while(d<=4 && diagX>=0 && diagY>=0){
    if(board[diagX][diagY]==symbol){
      diagScore++;
    }
    else{
      break;
    }
    diagX--;
    diagY--;
    d++;        
  }
  if(y-diagScore>=0 && board[x-diagScore][y-diagScore]=='.' && board[x-diagScore+1][y-diagScore]!='.'){
    if(l==0){
      a = diagScore;
    }
    if(l==1){
      a = y-diagScore;
    }
  }
  else{
    if(l==0){
      a = 0;
    }
    if(l==1){
      a = y;
    }
  }
  return a;
}

//Checks if Column of index y is completely filled with symbols(either X or O) or not
int checkColumnFull(char board[6][7],int y){
  int count = 0;
  for(int i = 5;i >= 0;i--){
    if(board[i][y]!='.'){
      count++;
    }
  }
  if(count == 6){
    return 1;
  }
  else{
    return 0;
  }
}

//Function to drop the character 'symbol' in column y
void drop(char board[6][7], int y,char symbol ){
  for(int i=5; i>=0; i--){
    if(board[i][y]=='.'){
      board[i][y] = symbol;
      break;
    }
  }
}

/*If the value of l passed is 0, then the below function returns the maximum score(horizontally/vertically/diagonally) for the character 'symbol'
*/
/*If the value of l passed is 1, then the below function returns the best possible column to drop the character 'symbol', corresponding to the above score
*/
int maxScrCol(char board[6][7], char symbol,int l){
  int maxScore=0;
  int maxCol=0;
  for(int i=5; i>=0;i--) {
    for(int j=0;j<7;j++){
      int col=0;
      int horScr = horizontalScore(board,i,j,symbol,0);
      int verScr = verticalScore(board,i,j,symbol,0);
      int leftDiagScr = leftDiagonalScore(board,i,j,symbol,0);
      int rightDiagScr = rightDiagonalScore(board,i,j,symbol,0);
      int score=0;
      if(horScr>verScr){
        score = horScr;
        col = horizontalScore(board,i,j,symbol,1);
      }
      else{
        score = verScr;
        col = verticalScore(board,i,j,symbol,1);
      }
      if(leftDiagScr>score){
        score=leftDiagScr;
        col = leftDiagonalScore(board,i,j,symbol,1);
      }
      if(rightDiagScr>score){
        score=rightDiagScr;
        col = rightDiagonalScore(board,i,j,symbol,1);
      }
      if(score>=maxScore){
        maxScore = score;
        maxCol = col;
      }
    }
  }
  
  if(l==0){
    return  maxScore;
  }
  else{
    return maxCol;
  }
       
}

/*
The below function makes use of int maxColScr(...) function to first calculate the maximum score of AI symbol and the best possible column for AI to win. 
If the AI score is not good enough(score < 3) then the AI makes an offensive move. 
It calcuates the player's maximum score and best column for the player to win. Then it drops the AI symbol in that column index and hence blocks the player's best move.

*/
int aiInput(char board[6][7], char AIsymbol, char humanSymbol){
  int count = 0;
  for(int i=0; i<7; i++){
    if(board[5][i]=='.'){
      count++;
    }
  }
  if(count == 7 || (count==6 && board[5][3]=='.')){
    board[5][3]=AIsymbol;
    return 3;
  }
  else if(count==6){
    board[5][4]=AIsymbol;
    return 4;
  }
  else{
    int aiScr = maxScrCol(board, AIsymbol,0);
    int aiCol = maxScrCol(board, AIsymbol,1);
    if(aiScr==3){
      if(checkColumnFull(board,aiCol)==0){
        drop(board,aiCol,AIsymbol);
      }
      else{
        int i = 0;
        while(checkColumnFull(board,i)!=0){
          i++;
        }
        aiCol = i;
        drop(board,aiCol,AIsymbol);
      }
      return aiCol;
    }
    
    int playerCol = maxScrCol(board, humanSymbol,1);
    
    if(checkColumnFull(board,playerCol)==0){
       drop(board,playerCol,AIsymbol);
       return playerCol;
      }
    else{
       int i = 0;
        while(checkColumnFull(board,i)!=0){
          i++;
        }
        playerCol = i;
        drop(board,playerCol,AIsymbol);
      return playerCol;
    }
   
  }

}

//The function returns 1 if it finds 4 in a line(horizontally/vertically/diagonally) on the board, else returns 0
int win(char board[6][7]){
  if(horizontalCheck(board)==1 || verticalCheck(board)==1 ||  rightDiagonalCheck(board)==1 || leftDiagonalCheck(board)==1){
    printf("Win!!");
    return 1;
  }
  return 0;
}


int main(void) {
  int size = 0;
  char board[6][7]; 
  char moves[42];
  fillEmptyBoard(board);
  char a;
  printBoard(board);
  char humanSymbol;
  char aiSymbol;
  while(1){
    printf("Please enter 1 for and human 2 for computer to go first : \n");
    scanf(" %c",&a);
    if(a=='1' || a=='2'){
      if(a=='1'){
        humanSymbol = 'X';
        aiSymbol = 'O';
        a=1;
      }
      else{
        humanSymbol = 'O';
        aiSymbol = 'X';
        a=2;
      }
      break;
    }
    else{
      continue;  
    }
  }
  
  do{ 
    char move;
    if(a%2==1){
      printf("Please enter the column letter (A-G)\n");
      scanf(" %c",&move);
      if(move>'G'||move<'A'){
        printf(" Please try again!\n");
        continue;
      }
      if(checkColumnFull(board,move-65)==0){
        for(int i=5; i>=0; i--){
          if(board[i][move-65]=='.'){
            drop(board,move-65,humanSymbol);
            moves[size++] = move;
            printf(" Letter %c \n",moves[size-1]);
            a=2;
            break;
          }
        }
      }
      else{
        printf(" Try another column!\n");
        continue;
      }
    }
    else{
      int column = aiInput(board,aiSymbol,humanSymbol);
      moves[size++] = column+65;
      printf(" Letter %c \n",moves[size-1]);
      a=1;
    }
    printBoard(board);
    printf("\n");
  }while(win(board)!=1 && size!=42);
  if(size == 42 && win(board)==0){
    printf(" It's a DRAW!");
  }
  else if(a==2){
    printf(" You won! \n");
  }
  else{
    printf(" Computer won! \n");
  }
  
  printf("\n Moves:\n");
  for(int i=0;i<size;i++){
    printf("%2c",moves[i]);
  }
  printf("\n");
  return 0;
}

