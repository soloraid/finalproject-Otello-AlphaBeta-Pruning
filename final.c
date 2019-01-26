#include <stdio.h>
void detect( char boardGame[][8] , int selection[][2] , char player );
int maxValue( char boardGame[][8] , int selection[][2] , int nextMove[][2] , int score[][8] , int depth , char player , int *alphaPtr , int *betaPtr , int *ratingIndex );
int minValue( char boardGame[][8] , int selection[][2] , int nextMove[][2] , int score[][8] , int depth , char player , int *alphaPtr , int *betaPtr , int *ratingIndex );
void newBoardGame( char boardGame[][8] , char player , int x , int y);
int scoree( char player , char boardGame[][8] , int score[][8] );

int main(int argc, char const *argv[])
{   
    char boardGame[argc][argc];
    int selection[30][2];
    int nextMove[1][2];
    int *alphaPtr , *betaPtr , *ratingIndex ;
    int depth = 5;
    char player = argv[9][0] ;
    int score[8][8]={
        {9,1,8,5,5,8,1,9},
        {1,1,5,6,6,5,1,1},
        {8,5,3,4,4,3,5,8},
        {5,6,4,1,1,4,6,5},
        {5,6,4,1,1,4,6,5},
        {8,5,3,4,4,3,5,8},
        {1,1,5,6,6,5,1,1},
        {9,1,8,5,5,8,1,9},
    };
    *alphaPtr = -1;
    *betaPtr = 400;

    for(int i = 0 ; i<argc-2 ; i++)
    {
        for(int j = 0 ; j<argc-2 ; j++)
        {
            boardGame[i][j]=argv[i+1][j];
        }
    }
    detect( boardGame , selection , player );
    maxValue( boardGame , selection , nextMove , score , depth , player , alphaPtr , betaPtr , ratingIndex );
    return 0;
}

int maxValue( char boardGame[][8] , int selection[][2] , int nextMove[][2] , int score[][8] , int depth , char player , int *alphaPtr , int *betaPtr , int *ratingIndex )
{   
    int a = *alphaPtr , b = *betaPtr ;
	int tmpBoard[8][8];
	int tmpselect[30][2];
    int hold;
    int max=-1;
	*ratingIndex = -100000;
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
            if( tmpselect[i][0]==-1 )
                return scoree ( '1' , tmpBoard , score );
            newBoardGame( tmpBoard , player , tmpBoard[i][0] , tmpBoard[i][1] );
            detect( tmpBoard , tmpselect , player );
            //change player
            player = '2';
            hold = minValue( tmpBoard , tmpselect , nextMove , score , depth-- , player , &a , &b , ratingIndex );
            if( hold >= *betaPtr )
                return hold;
            if( hold > *ratingIndex )
                *ratingIndex = hold ;
            if( hold > *alphaPtr )
                *alphaPtr = hold ;
            //choosing best coordination after calculationg each branches
            if( max < *ratingIndex && depth==5 )
            {
                max = *ratingIndex ;
                nextMove[0][0]=selection[i][0];
                nextMove[0][1]=selection[i][1];
            }
        }
        return hold ;
    }
    return scoree( '1' , boardGame , score );
    
}

int minValue( char boardGame[][8] , int selection[][2] , int nextMove[][2] , int score[][8] , int depth , char player , int *alphaPtr , int *betaPtr , int *ratingIndex )
{   
    int a = *alphaPtr , b = *betaPtr ;
	int tmpBoard[8][8];
	int tmpselect[30][2];
    int hold;
	*ratingIndex = +100000;
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
            if( tmpselect[i][0]==-1 )
                return scoree ( '1' , tmpBoard , score );
            newBoardGame( tmpBoard , player , tmpBoard[i][0] , tmpBoard[i][1] );
            detect( tmpBoard , tmpselect , player );
            //change player
            player = '1';
            hold = maxValue( tmpBoard , tmpselect , nextMove , score , depth-- , player , &a , &b , ratingIndex );
            if( hold <= *alphaPtr )
                return hold;
            if( hold < *ratingIndex )
                *ratingIndex = hold ;
            if( hold < *betaPtr )
                *betaPtr = hold ;
        }
        return hold ;
    }
    return scoree( '1' , boardGame , score );
}


int scoree( char player , char boardGame[][8] , int score[][8] )
{   
    int counterA=0;
    int counterB=0;
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
    if( player=='1')
        return counterA;
    else
        return counterB;
              
}

/*void detect( char boardGame[][8] , int selection[][2] , char player );
{

}*/

/*void newBoardGame( char boardGame[][8] , char player , int x , int y);
{

}*/