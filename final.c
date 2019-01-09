#include <stdio.h>
void detect(char boardgameptr[][8],int argc);



int main(int argc, char const *argv[])
{   
    char boardgame[argc][argc],*boardgameptr[argc-2];
    //printf("%d\n",argc);
    for(int i = 0 ; i<argc-2 ; i++){
        for(int j = 0 ; j<argc-2 ; j++){
            boardgame[i][j]=argv[i+1][j];
            //printf("%3c",boardgame[i][j]);
        }
        //printf("\n");
    }
    detect(boardgame,argc-2);
    return 0;
}


void detect(char boardgameptr[][8],int argc)
{
    
}

