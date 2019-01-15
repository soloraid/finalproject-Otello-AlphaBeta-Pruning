#include <stdio.h>
void detect( char boardGame[][8] , int argc , int selection[][2] , char player );
void alphaBetaPruning( char boardGame[][8] , int selection[][2] , int depth , int nextMove[][2] ,
int score[][8] , char player , int *alphaPtr , int *betaPtr );
void newBoardGame( char boardGame[][8] , char player);

int main(int argc, char const *argv[])
{   
    char boardGame[argc][argc];
    int selection[30][2];
    int nextMove[1][2];
    int *alphaPtr , *betaPtr ;
    int depth = 5;
    char player = '1' ;
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
    *alphaPtr = 0;
    *betaPtr = 576;

    for(int i = 0 ; i<argc-2 ; i++)
    {
        for(int j = 0 ; j<argc-2 ; j++)
        {
            boardGame[i][j]=argv[i+1][j];
        }
    }
    detect( boardGame , argc-2 , selection , player );
    return 0;
}


/*void detect(char boardgameptr[][8],int argc)
{
    char *rowptr;
    rowptr = (char *)calloc(argc,sizeof(char));

}*/

void alphaBetaPruning( char boardGame[][8] , int selection[][2] , int depth , int nextMove[][2] , int score[][8] , char player , int *alphaPtr , int *betaPtr )
{   
    int counterA=0;
    int counterB=0;
	int tmpBoard[8][8];
	int tmpselect[30][2];
	
	for (int i = 0 ; i<8 ; i++)
	{
		for ( int j = 0 ; j<8 ; j++)
		{
			tmpBoard[i][j] = boardGame[i][j];
		}
	}

	for(int i = 0 ; i<30 ; i++)
	{
		tmpselect[i][0] = selection[i][0];
		tmpselect[i][1] = selection[i][1];
	}

    if ( depth!=0 )
    {
        for(int  i = 0 ; i<30 ; i++ )
        {
            if( selection[i][0]==-1 )
            break;
            tmpBoard[selection[i][0]][selection[i][1]] = player ;
            newBoardGame( tmpBoard , player);
            //change player
            if ( player == '1')
            	player = '2';
            else
            	player = '1';
			checkAlphaBeta(alphaPtr,betaPtr)

        }
    }
}

{
    for(int k = 0 ; k<8 ; k++)
    {
        for(int q = 0 ; q<8 ; q++)
        {
            if( boardGame[k][q]=='1' )
                counterA+=score[k][q] ;
            else if ( boardGame[k][q]=='2')
                counterB+=score[k][q] ;
            else
        	    continue ;
        }
    }
    if( counterA >= *alphaPtr)
        *alphaPtr = counterA ;
    if( counterB <= *betaPtr)
        *betaPtr = counterB ;
              
}