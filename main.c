#include <stdio.h>
#include <string.h>
#include "funcs.h"
#define TXT 1024
#define WORD 30
int main(){
    char word[WORD];
    char txt[TXT];
    int wordLen=0, txtLen=0;
    scanf("%s",word);
    scanf("%1024[^~]s", txt);
    wordLen = strlen(word);
    txtLen = strlen(txt);
    printf("%s", txt);
    printf("Gematria Sequences: ");
    f1(word, wordLen, txt, txtLen);
    printf("\nAtbash Sequences: ");
    // f2(word, wordLen, txt, txtLen);
    // printf("\nAnagram Sequences: ");
    // f3(word, wordLen, txt, txtLen);
    return 1;
}