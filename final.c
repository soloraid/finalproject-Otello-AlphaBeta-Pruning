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