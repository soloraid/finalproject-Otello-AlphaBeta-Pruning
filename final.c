#include <stdio.h>
#define INF 10000000
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

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

/*int validPoint(int x,int y)
{
    code
}*/

/*int change(char boardGame[][8], char tmpBoard[][8], int x, int y, char player)
{
    code
}*/

/*int heuristic_value ( char boardGame[][8], int score[][8] )
{
    code
}*/


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

