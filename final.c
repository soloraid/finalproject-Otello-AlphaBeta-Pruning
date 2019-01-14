#include <stdio.h>
void detect( char boardGame[][8] , int argc , int selection[][2] );
void alphaBetaPruning( char boardGame[][8] , int selection[][2] , int depth , int nextMove[][2] ,
 int score[][8] , char player , int max );
void newBoardGame( char boardGame[][8] );

int main(int argc, char const *argv[])
{   
    char boardGame[argc][argc];
    int selection[30][2];
    int nextMove[1][2];
    int depth = 5;
    int score[8][8]={
        {9,0,8,5,5,8,0,9},
        {0,1,5,6,6,5,1,0},
        {8,5,3,4,4,3,5,8},
        {5,6,4,0,0,4,6,5},
        {5,6,4,0,0,4,6,5},
        {8,5,3,4,4,3,5,8},
        {0,1,5,6,6,5,1,0},
        {9,0,8,5,5,8,0,9},
    };

    for(int i = 0 ; i<argc-2 ; i++)
    {
        for(int j = 0 ; j<argc-2 ; j++)
        {
            boardGame[i][j]=argv[i+1][j];
        }
    }
    detect( boardGame , argc-2 , selection );
    return 0;
}


/*void detect(char boardgameptr[][8],int argc)
{
    char *rowptr;
    rowptr = (char *)calloc(argc,sizeof(char));

}*/

void alphaBetaPruning( char boardGame[][8] , int selection[][2] , int depth , int nextMove[][2] , int score[][8] , char player , int max );
{   
    int counterA=0;
    int counterB=0;
    
    if ( depth!=0 )
    {
        for(int  i = 0 ; i<30 ; i++ )
        {
            if( selection[i][0]==-1 )
            break;
            boardGame[selection[i][0]][selection[i][1]] = player ;
            newBoardGame(boardGame);

        }
    }
}

