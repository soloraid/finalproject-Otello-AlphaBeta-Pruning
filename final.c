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


int main(int argc, char const *argv[])
{
    char boardGame[8][8];//*argve save on this boardGame
    int nextMove[2];// best choice of max player move
    int depth = 4;// depth of alphaBetaPruning in alghorithm of minimax
    char player = argv[9][0] ;
    int score[8][8]={
        {20, -3, 11, 8, 8, 11, -3, 20},
    	{-3, -7, -4, 1, 1, -4, -7, -3},
    	{11, -4, 2, 2, 2, 2, -4, 11},
    	{8, 1, 2, -3, -3, 2, 1, 8},
    	{8, 1, 2, -3, -3, 2, 1, 8},
    	{11, -4, 2, 2, 2, 2, -4, 11},
    	{-3, -7, -4, 1, 1, -4, -7, -3},
        {20, -3, 11, 8, 8, 11, -3, 20}
    };//potential score of each places on boardGame
    
    int i;
    for(i = 0 ; i<8 ; i++)
    {
        int j;
        for(j = 0 ; j<8 ; j++)
            boardGame[i][j]=argv[i+1][j];
    }//end of loop for save strings on boardGame

    // call function for best choice
    alphaBetaPruning(boardGame, depth, nextMove, score, player , -INF , INF, 1);
    printf("%d %d", nextMove[1], nextMove[0]);
    return 0;
}

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

int alphaBetaPruning( char boardGame[][8] , int depth , int nextMove[] , int score[][8] , char player , int alpha , int beta, int is_max_node)
{
    if(depth==0)// in depth==0 we must return value for node max or min in difference depths
        return heuristic_value(boardGame, score);
	char tmpBoard[8][8];
	int nextMoveTmp[2];
	int value;
    int ok=0;//when ok==1 return to up level of game branch (minimax)
    int i,j;
	if(is_max_node)//for every node at first value -inf or +inf although the alpha or beta has value
        value=alpha;
    else
        value=beta;

    for(i=0;i<8;i++)// loop for candidate of choices
        for(j=0;j<8;j++)
            if(boardGame[i][j]=='0')
                if( change(boardGame, tmpBoard, i, j, player) > 0)//candidate i , j
                {
                    ok=1;
                    //recursive function for depth in minimax (game tree)
                    int childValue=alphaBetaPruning(tmpBoard, depth-1, nextMoveTmp, score, player, alpha, beta, 1-is_max_node);
                    if(is_max_node)//max plyer
                    {
                        if(childValue>value)
                        {
                            nextMove[0]=i;
                            nextMove[1]=j;
                        }
                        value=max(value,childValue);//check to change value after return childValue
                        alpha=max(alpha, value);//new alpha on max branch
                        if(value>beta)//prunned of min branch
                            return beta;
                    }
                    else//min plyer
                    {
                        if(childValue<value)
                        {
                            nextMove[0]=i;
                            nextMove[1]=j;
                        }
                        value=min(value,childValue);//check to change value after return childValue
                        beta=min(beta, value);//new beta on min branch
                        if(value<alpha)//prunned of max branch
                            return alpha;
                    }
                }//end if of candidate coordinates
    if(ok)
        return value;//return value to upper branch after candidate we have in this branch
    return heuristic_value(boardGame, score);//no candidate for this branch because no nextmove 
}

