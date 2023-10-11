#include<stdio.h>
#include<stdlib.h> 
//main-function
int mazeTraverse( char mazePtr[ 12 ][ 12 ], int currentRow, int currentColumn );
void printMaze( char maze[ 12 ][ 12 ], const int currentRow, const int currentColumn );
int main( void ){
   int startRow = 2, startColumn = 0, state = 0;
                            // 0    1    2    3    4    5    6    7    8    9    10   11
   char maze[ 12 ][ 12 ] = {{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},  // 0
                             {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},  // 1
                             {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},  // 2
                             {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},  // 3
                             {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', '.'},  // 4
                             {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},  // 5
                             {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},  // 6
                             {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},  // 7
                             {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},  // 8
                             {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},  // 9
                             {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},  // 10
                             {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} };// 11
   
   printf("The maze\n********\n");
   printMaze( maze, 12, 12 );
   printf("  This program is brought to you\n  by aeriqusyairi...\n\n  Enjoy!!\n\n");
   system("pause");
   system("cls");
   //printf("\n");
   
   state = mazeTraverse( maze, startRow, startColumn );
   
   if(state == 0){
      printf("\nPlayer found the exit!\n\n");         
   }
   
   system("pause");
   return 0;
}
//global
int startingFlag = 1, direction = 0;
//enumeration
enum Stat { OVER, NOT_OVER };
/*core function*/
int mazeTraverse( char maze[ 12 ][ 12 ], int currentRow, int currentColumn ){
   //sub-function
   int gameOver( const int currentRow, const int currentColumn );
   int move( char maze[ 12 ][ 12 ], int *currentRow, int *currentColumn, int *currentDirection );
   
   enum Stat State;
   
   //check if game is over
   State = gameOver( currentRow, currentColumn );
   if(State == OVER && startingFlag == 0){
      printMaze( maze, currentRow, currentColumn );
      return OVER; //return OVER indicating succesfully find the exit
      //algorithm for if this function can't find the exit is not available       
   }
   
   //indicate player is ready to move
   if(startingFlag == 1){
      //print initial maze
      printf("Player's ready\n**************\n");
      printMaze( maze, currentRow, currentColumn );
      system("pause");
      system("cls");
      //set first direction based on starting position
      if(currentRow == 0){
         direction = 1;              
      }else if(currentRow == 11){
         direction = 0;      
      }else if(currentColumn == 0){
         direction = 2;      
      }else if(currentColumn == 11){
         direction == 3;      
      }
      startingFlag = 0;             
   }  
   
   //seek for next move
   move( maze, ¤tRow, ¤tColumn, &direction );
   
   //system("pause");//activate this to see each move
   system("cls");
   
   mazeTraverse( maze, currentRow, currentColumn );
   
   return OVER;
}
/*seek for next move*/
enum Direction { NORTH, SOUTH, EAST, WEST };
int move( char maze[ 12 ][ 12 ], int *currentRow, int *currentColumn, int *currentDirection ){
   int posibble[ 4 ] = { 0 };// 1 -> North; 2 -> South; 3 -> East; 4 -> West;
   int counter = 0;
   
   enum Direction Seek; 
   
   Seek = *currentDirection;
   
   /*move the player respect to current direction*/
   
   //cover the current position
   maze[ *currentRow ][ *currentColumn ] = '.';
   
   //move the player respect to current direction
   if(Seek == NORTH){
      //print direction
      printf("direction = NORTH\n");
      //move north
      *currentRow -= 1;
   }else if(Seek == SOUTH){
      //print direction
      printf("direction = SOUTH\n");
      //move south
      *currentRow +=1;      
   }else if(Seek == EAST){
      //print direction
      printf("direction = EAST\n");
      //move east
      *currentColumn += 1;   
   }else if(Seek == WEST){
      //print direction
      printf("direction = WEST\n");
      //move west
      *currentColumn -= 1;
   }
   
   //print each move
   printMaze( maze, *currentRow, *currentColumn );// print maze with player current position
   
   /*analyse for next direction*/
   
   //seek posibble direction
   printf("Seek next direction...\n\n");
   if(maze[ *currentRow - 1 ][ *currentColumn ] == '.' && Seek != SOUTH){
      printf("NORTH is possible\n");
      posibble[ 0 ] = 1;
      counter++;
   }
   if(maze[ *currentRow + 1 ][ *currentColumn ] == '.' && Seek != NORTH){
      printf("SOUTH is possible\n"); 
      posibble[ 1 ] = 1;
      counter++; 
   } 
   if(maze[ *currentRow ][ *currentColumn + 1 ] == '.' && Seek != WEST){
      printf("EAST is possible\n"); 
      posibble[ 2 ] = 1; 
      counter++; 
   } 
   if(maze[ *currentRow ][ *currentColumn - 1 ] == '.' && Seek != EAST){
      printf("WEST is possible\n");  
      posibble[ 3 ] = 1;
      counter++; 
   }  
   printf("\n");
   
   //follow right wall
   //Direction { NORTH, SOUTH, EAST, WEST };
   if(counter == 1){
      if(posibble[ 1 ] == 1){//south
         *currentDirection = 1;
      }else if(posibble[ 2 ] == 1){//east
         *currentDirection = 2;
      }else if(posibble[ 0 ] == 1){//north
         *currentDirection = 0;      
      }else if(posibble[ 3 ] == 1){//west
         *currentDirection = 3;
      }
   }else if(counter == 2){
      if(posibble[ 2 ] == 1 && posibble[ 3 ] == 1){// posibble: EAST, WEST
         if(Seek == SOUTH){
            *currentDirection = 3;
         }else if(Seek == NORTH){
            *currentDirection = 2;      
         }                
      }else if(posibble[ 0 ] == 1 && posibble[ 1 ] == 1){// posibble: NORTH,SOUTH
         if(Seek == EAST){
            *currentDirection = 1;        
         }else if(Seek == WEST){
            *currentDirection = 0;      
         }
      }else if(posibble[ 0 ] == 1 && posibble[ 3 ] == 1){// NORTHWEST
            *currentDirection = 0;        
      }else if(posibble[ 0 ] == 1 && posibble[ 2 ] == 1){// NORTHEAST
            *currentDirection = 2;        
      }else if(posibble[ 1 ] == 1 && posibble[ 2 ] == 1){// SOUTHEAST
            *currentDirection = 1;        
      }else if(posibble[ 1 ] == 1 && posibble[ 3 ] == 1){// SOUTHWEST
            *currentDirection = 3;        
      }
   }else if(counter == 3){
      if(Seek == NORTH){
         *currentDirection = 2;        
      }else if(Seek == SOUTH){
         *currentDirection = 3;      
      }else if(Seek == EAST){
         *currentDirection = 1;      
      }else if(Seek == WEST){
         *currentDirection = 0;      
      }
   }else if(counter == 0){
      //dead end
      if(Seek == NORTH){
         *currentDirection = 1;         
      }else if(Seek == SOUTH){
         *currentDirection = 0;      
      }else if(Seek == EAST){
         *currentDirection = 3;      
      }else if(Seek == WEST){
         *currentDirection = 2;      
      }
   }
   
}
/*check if game is over*/
int gameOver( const int currentRow, const int currentColumn ){
   if(currentRow == 0 || currentRow == 11 || currentColumn == 0 || currentColumn == 11 ){
      return OVER;
   }else{
      return NOT_OVER;      
   }
}
/*print current maze*/
 void printMaze( char maze[ 12 ][ 12 ], const int currentRow, const int currentColumn ){
    int mazeRow, mazeColumn;
    
    printf("\n    "); 
    for(mazeRow = 0; mazeRow < 12; mazeRow++){
      for(mazeColumn = 0; mazeColumn < 12; mazeColumn++){
         if(mazeRow == currentRow && mazeColumn == currentColumn){
            maze[ mazeRow ][ mazeColumn ] = 'X';
         }
         printf("%2c", maze[ mazeRow ][ mazeColumn ] );
         
      }
      printf("\n    ");
   }   
   printf("\n");   
 }
