#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

char list[][6] = {"gamer", "coder", "maker", "first", "horse", "water", "stick", "brick", "paths", "drugs", "death"}; 
int size = sizeof(list)/sizeof(list[0]);
char oboard[6][100]= {"_,_,_,_,_,",
                      "_,_,_,_,_,",
                      "_,_,_,_,_,",
                      "_,_,_,_,_,",
                      "_,_,_,_,_,",
                      "_,_,_,_,_,",};

char* takeguess(){
    printf("entr 5 letter word:\n");
    char* guess = malloc(10);
    scanf("%s" , guess);
    return strupr(guess);
}
char* generateword(char list[][6]){
    srand(time(NULL));
    int r = rand() % size;
    char word[6];
    strcpy(word, list[r]);
    return strupr(word);
}

bool isin(char letter, char* word ){
    int i = 0;
    do{
        if (word[i] == letter){return true;}
        i++;
    } while (i<strlen(word));
    return false;
}

void updategrid(int row, char board[6][100], char* guess, char* word){
    char c[100] = "";
    int pos = 0;  // Current write position in `c`

    for (int i = 0; i < 5; i++) {
        if (guess[i] == word[i]) {
            pos += sprintf(c + pos, "\033[32m%c\033[0m,", guess[i]);
        } else if (isin(guess[i], word)) {
            pos += sprintf(c + pos, "\033[33m%c\033[0m,", guess[i]);
        } else {
            pos += sprintf(c + pos, "\033[37m%c\033[0m,", guess[i]);
        }
    }

    strcpy(board[row], c);
}

void printboard(char curboard[6][100]){
//    char temp[] = "";
//    sprintf(temp,"\r%s" , curboard[0] );
//    strcpy(curboard[0] , temp);
    for (int i = 0; i < 6; i++) {
        printf("%s\n",curboard[i]);
    }
}
bool checkguess(char* guess , char* realword){
    for (int i = 0 ; i<5; i++){
        if (guess[i]!=realword[i]){return false;}
    }
    return true ;
}

void game(){
    int cur = 0;
    char realword[6];
    strcpy(realword, generateword(list));
    char board[6][100];
    memcpy(board, oboard, sizeof(board));
    printf("%s\n", realword);
    bool iswinner = false;
    while (cur < 6 && iswinner == false){
        printboard(board);
        char* guess = takeguess();
        printf("%s\n" , guess);
        iswinner = checkguess(guess, realword);
        updategrid( cur , board, guess ,realword);
        cur++;
    }
    if (iswinner == true){
        printf("CONGRATS!!, you win!!");
    }
    else{
        printf("yoo lose the right word is : %s", realword);
    }
}

int main(){
    game();

    return 0;
}

