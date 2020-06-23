## README ##

Link to video - https://drive.google.com/file/d/1W3Pto34IPD5gM6Qf1LrzleR2TsDUlIcY/view?usp=sharing


The game is played on 6*7 board being represented by a double dimensional char array – char board[6][7]. This array is filled with ‘.’ at the beginning of the game to represent an empty board. The user is then prompted to go first or second and the every time it’s the user’s chance, the user is required to input a column Name (A-G) and is prompted to input column name again if there is an invalid input. The game terminates with a Win if 4 symbols(either ‘X’ or ‘O’) are found in a line horizontally, vertically, or diagonally. Also, the game ends with a Draw if the entire board gets filled with symbols(‘X’ or ‘O’) and there are no 4 symbols in a line. 

Below are the descriptions of major functions used in the program :

// int maxScrCol(char board[6][7], char symbol,int l)

This function returns the maximum score (frequency of same symbols horizontally/vertically/diagonally) on the board for the character ‘symbol’ when the value of ‘l’ passed is 0.
When the value of ‘l’ passed is 1, this function returns the best column to drop the character ‘symbol’ with respect to the above calculated score.

This function makes use of the following helper functions to calculate the maximum score:
# int verticalScore(char board[6][7],int x,int y,char symbol,int l)
# int horizontalScore(char board[6][7],int x,int y,char symbol,int l)
# int rightDiagonalScore(char board[6][7],int x,int y,char symbol,int l)
# int leftDiagonalScore(char board[6][7],int x,int y,char symbol,int l)

The above function has the flexibility of providing both the scores and best possible column index for both the Human and AI by passing their corresponding symbols. 


// int aiInput(char board[6][7], char AIsymbol, char humanSymbol)

The above function utilizes maxScrCol(…) function to get the maximum score for AI first and place the AI move. If the AI’s maximum score is not good enough then it utilizes the same maxScrCol(…) to calculate the maximum score of player and the best possible move(column index) of player to win and instantly blocks it by placing the AI symbol there.


