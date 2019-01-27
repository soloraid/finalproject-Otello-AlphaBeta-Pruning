#include <stdio.h>
#include <stdlib.h>
#define INF 10000000
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
//void print_table(char boardGame[][8]); just fot checking 
int validPoint(int x,int y);
int change(char boardGame[][8], char tmpBoard[][8], int x, int y, char player);
int heuristic_value ( char boardGame[][8], int score[][8] );
int alphaBetaPruning( char boardGame[][8] , int depth , int nextMove[] , int score[][8] , char player , int alpha , int beta, int is_max_node);

/*int int main(int argc, char const *argv[])
{
    code 
    return 0;
}*/

/*void print_table(char boardGame[][8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            printf("%c",boardGame[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("\n");
}*/

int validPoint(int x,int y)
{   
    // function for checking the coordinates correct or out of boundary
    if( x<0 || y<0 || x>=8 || y>=8)
        return 0;//out of boundary
    return 1;//correct place
}

int change( char boardGame[][8] , char tmpBoard[][8] , int x , int y , char player )
{   
    int takeNumber=0;
    /*tmp x ,y*/
    int X=x;
    int Y=y;
    
    // holding boardGame to tmpBoard
    for(int i = 0 ; i < 8 ; i++)
        for(int j = 0 ; j < 8 ; j++)
            tmpBoard[i][j] = boardGame[i][j];

    //place coordinates in tmpBoard
    tmpBoard[x][y] = player;

    // validris mean 9 plance aroud the x,y we have
    int validDirs[8][2] = {
        {1, 1},
        {1, 0},
        {1, -1},
        {0, 1},
        {0, -1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
    };

    //Releasing our tmpBoard from place we set coordinate in 9 direction
    for( int k = 0; k < 8 ; k++)
    {   
        /* X , Y tmp for driving on boardGame !!!!*/
        int tmpx=X;
        int tmpy=Y;
        x=X;
        y=Y;
        /**/
        /*through which direction we move*/
        int dx=validDirs[k][0];
        int dy=validDirs[k][1];
        /**/
        int seenOtherPlayer=0;
        int ok=0;
        //through tmpBoard detects to change any bead 2 to 1 
        while( validPoint(x+dx,y+dy))
        {
            x=x+dx;
            y=y+dy;
            if(tmpBoard[x][y]=='0')//not change bead
                break;
            if(tmpBoard[x][y]==player)//continue through board
            {
                if(seenOtherPlayer)
                    ok=1;// see onter player after loop we place bead
                break;
            }
            else
                seenOtherPlayer=1;
        }
        if(ok)// ok ==1 for moving through board to change beads
        {
            while( (tmpx+dx)!=x || (tmpy+dy)!=y)
            {   
                /*contiune to tmpBoard*/
                tmpx+=dx;
                tmpy+=dy;
                /**/
                takeNumber++;//increase of our beads 
                tmpBoard[tmpx][tmpy]=player;//change of bead with player
            }
        }
    }//end loop of changing tmpBoard after placing  coordinate and Releasing
    //print_table(tmpBoard);
    return takeNumber;// for check the coordinate is candidate (tankNumber>0) or not
}

int heuristic_value ( char boardGame[][8], int score[][8] )
{

    char player='1';
    char opp='2';
    int heuristic_value = 0;//the difference score of max & min players
    int k,q;
    for(k = 0 ; k<8 ; k++)
    {
        for(q = 0 ; q<8 ; q++)
        {
            if( boardGame[k][q]==player )//score of max player increase heuristic_value
                heuristic_value+=score[k][q];
            else if ( boardGame[k][q]==opp)//score of min player decrease heuristic_value
                heuristic_value-=score[k][q];
            else
        	    continue ;
        }
    }

    return heuristic_value;//return the score_value of the difference max and min players
}

/*int alphaBetaPruning( char boardGame[][8] , int depth , int nextMove[] , int score[][8] , char player , int alpha , int beta, int is_max_node)
{
    code
}*/